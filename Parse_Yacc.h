//
// Created by mac on 2019/6/1.
//

#ifndef SEUYACC_PARSE_YACC_H
#define SEUYACC_PARSE_YACC_H
#include "helper.h"
#include "fstream"
#include "iostream"
#include"map"
#include <stdio.h>

using namespace std;

//对yacc.y文件进行解析,得到产生式vec/辅助函数/Symbol
extern vector<string> FuncVec;     //存放辅助函数
extern vector<Symbol> GlobalSymbolVec;        //存放终结符
extern ProductionVec GlobalProductionVec;//存放产生式
extern ProducerVec GlobalProducerVec;     //数字版本
extern map<int,pair<int,int> >indexMap;
extern int startProduction;
//记录一个非终结符所对应的产生式的序号区间
//pair 中first是开始下标 second是该非终结符有多少个产生式


//输入yacc地址,修改产生式vec
//正确结束 return 1
//错误结束 return 0
int Parse_Yacc(const string& filename,vector<Symbol>& symbolvec,
               ProductionVec& production,
               ProducerVec& production_int,
               vector<string>&FuncVec){
    ifstream in;
    in.open(filename,ios::in);
    if(!in){
        cout<<"ERROR:Can't open yacc.y!"<<endl;
        return 0;
    }


    //0.首先加入标点等 终结符号
    //    vector<string> Terminal_Str={"(",")","[","]","{","}",".",",",";","&",
    //        "*","+","-","~","!","%",">","<","^","|",
    //        "?",":","="};
    //
    //    for(int i=0;i<Terminal_Str.size();i++){
    //        string s=Terminal_Str[i];
    //        Symbol item;
    //        item.symbol=s;
    //        item.isTerminal=true;
    //        symbolvec.push_back(item);
    //    }

    //开始根据yacc.y形式 解析
    string str;     //当前读入字符串


    //1.读入Token,并存入symbolvec,都为终结符

    in>>str;
    while(str!="%start"){
        //新行,跳过%token
        if("%token"==str){
            in>>str;
        }
        Symbol item;
        item.symbol=str;
        item.isTerminal=true;
        symbolvec.push_back(item);
        in>>str;
    }


    //2.读入产生式,并存入production
    while(str!="%%")
        in>>str;
    in>>str;

    vector<int> vec_left_int;       //记录在左式出现的int

    //vector<pair<string,vector<string> > > ProductionVec;
    //下次%%是辅助子例程
    int COUNT=0;
    int symbol_index=0;

    while(str!="%%"){
        //开始记录左
        if(str==";")
            in>>str;
        if(str=="%%")
            break;
        string lefr=str;
        int left_int;
        //left 是否在SymbolVec中,并记录其symbol_index
        bool isExist=false;
        bool isQuotation=false;
        bool isT=false;
        if(str[0]=='\''){
            isQuotation=true;
            str=str[1];
            isT=true;
        }


        for(int i=0;i<symbolvec.size();i++){
            if(str==symbolvec[i].symbol){
                symbol_index=i;
                left_int=i;
                isExist=true;
                break;
            }
        }
        if(!isExist){
            symbol_index=symbolvec.size();
            Symbol item;
            item.symbol=str;
            item.isTerminal=false;
            if(isT)
                item.isTerminal=true;
            symbolvec.push_back(item);
            left_int=symbolvec.size()-1;
        }

        vec_left_int.push_back(left_int);

        int left_index=COUNT;
        int right_index=0;

//        cout<<lefr<<endl;
        in>>str;
        if(str==":"){
            in>>str;
        }
        while(str!=";"){
            //本次left 结束
            vector<string> right;
            vector<int> right_int;      //记录右式中的编号
            int count=0;        //记录'
            do{
                if(str=="\'")
                    count++;
                if(count)
                    count--;

                bool isExist=false;
                //加入新的Symbol
                bool isQuotation=false;
                bool isT=false;
                if(str[0]=='\''){
                    isQuotation=true;
                    str=str[1];
                    isT=true;
                }
                right.push_back(str);


                for(int i=0;i<symbolvec.size();i++){
                    //                    cout<<str<<endl;
                    //                    cout<<symbolvec[i].symbol<<endl;
                    string temp_symbol="\'"+symbolvec[i].symbol+"\'";
                    if(str==symbolvec[i].symbol||
                       str==temp_symbol){
                        right_int.push_back(i); //右边
                        isExist=true;
                        break;
                    }
                }
                if(!isExist){
                    Symbol item;
                    item.symbol=str;
                    item.isTerminal=false;
                    if(isT)
                        item.isTerminal=true;
                    symbolvec.push_back(item);
                    right_int.push_back(symbolvec.size()-1);
                    //如果当前刚刚加入后为3个,则编号为2
                }

                in>>str;

            }while(str!="|"&&str!=";"&&str!="%%"&&count==0);
            //存入左式相同
            pair<string,vector<string> > production_item(lefr,right);
            production.push_back(production_item);

            pair<int,vector<int> > production_item_int(left_int,right_int);
            production_int.push_back(production_item_int);

            COUNT++;
            right_index++;

            if(str==";")
                continue;
            in>>str;
        }
        pair<int,int> temp(left_index,right_index);
        indexMap[symbol_index]=temp;
    }

    //构造加入S,S'
    //更新symbol
    //构造S'->translation_unit
    //更新GlobalProductionVec GlobalProducerVec
    //更新indexMap

    //S'
    int l1=symbolvec.size();
    Symbol item;
    item.symbol="S'";
    item.isTerminal=false;
    symbolvec.push_back(item);

    int prodcution_size=production.size();
    //添加S'->translation_unit
    string l="S'";
    vector<string> r{"translation_unit"};
    pair<string,vector<string> > production_item(l,r);
    production.push_back(production_item);
    startProduction = production.size() - 1;
    int trans_item=0;
    for(int i=0;i<symbolvec.size();i++){
        if(symbolvec[i].symbol=="translation_unit")
        {
            trans_item=i;
            break;
        }
    }

    vector<int> vec_l1{trans_item};
    pair<int,vector<int> > production_item_int(l1,vec_l1);
    production_int.push_back(production_item_int);


    //加入S'的indexMap
    pair<int,int> temp(prodcution_size,1);
    indexMap[l1]=temp;

    //$r
    l1 = symbolvec.size();
    Symbol item1;
    item1.symbol = "$r";
    item1.isTerminal = true;
    symbolvec.push_back(item1);


    //3.读入辅助子例程序
    if(str=="%%")
    {
        while (!in.eof())
        {
            getline(in, str);
            while (str.empty()&&!in.eof())
            {
                getline(in, str);

            }
        }
        FuncVec.push_back(str);
    }

    //正确结束
    return 1;
}


#endif //SEUYACC_PARSE_YACC_H
