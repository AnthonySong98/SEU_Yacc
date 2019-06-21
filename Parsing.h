//
// Created by mac on 2019/6/2.
//

#ifndef SEUYACC_PARSING_H
#define SEUYACC_PARSING_H

#include <string>
#include <fstream>
#include <iostream>
#include <stack>

using namespace std;

struct Token_Unit {
    string type;
    string content;
    int id;
};



void Parsing_Tokens(string filepath,Parse_Table& testParse_Table){


    ifstream input(filepath);
    if(!input.is_open()){cout<<"fail to open the input tokens file!\n";}

    //parse Tokens result from Lex
    string line;
    vector<Token_Unit> Token_List;
    while(getline(input, line))
    {
        line = line.c_str();
        Token_Unit new_Token;

        int cur = 0 ,next =0 ;
        while (line[next] != ' '&& line[next] != '\t'){next++;}
        new_Token.content = line.substr(cur,next-cur);

        while(line[next] == ' ' || line[next] == '\t'){next++;}
        cur = next;
        while (line[next] != ' '&& line[next] != '\t'){next++;}
        new_Token.type = line.substr(cur,next-cur);

        while(line[next] == ' ' || line[next] == '\t'){next++;}
        cur = next;
        while (next != line.size()&& line[next] != ' '&& line[next] != '\t'){next++;}
        new_Token.id = atoi(line.substr(cur,next-cur).c_str());

        Token_List.push_back(new_Token);

    }

    //Construct hashMap from Token name to Token Number
    map<string,int> SymbolMap;
    for(int i = 0 ; i < GlobalSymbolVec.size();i++)
    {
        SymbolMap.insert(pair<string,int>(GlobalSymbolVec[i].symbol,i));
    }

    //create symbol stack
    stack<Symbol> Symbol_Stack;
    //create state stack
    stack<int> State_Stack;

    //create and push end symbol into Symbol Stack
    Symbol End_Symbol;End_Symbol.symbol="$r";End_Symbol.isTerminal=true;
    Symbol_Stack.push(End_Symbol);

    //push state 0 into State Stack
    State_Stack.push(0);

    int Parse_Token_index = 0 ;

    int elment;
    while(Parse_Token_index <= Token_List.size()){
        // check the parsing table
        if(Parse_Token_index < Token_List.size())
            elment = testParse_Table[State_Stack.top()][SymbolMap[Token_List[Parse_Token_index].type]];
        else{
            elment = testParse_Table[State_Stack.top()][SymbolMap[End_Symbol.symbol]];
        }
        //if shift
        if(elment > 0){
            if(elment != testParse_Table.size() + 1) {
                //cout << elment << endl;
                State_Stack.push(elment);
                Symbol_Stack.push(GlobalSymbolVec[SymbolMap[Token_List[Parse_Token_index].type]]);
                Parse_Token_index++;
            }
            else{
                cout<<"error!\n";
                break;
            }
        }
        // if reduce
        if(elment <= 0 ){
            if(elment == -INT_MAX){
                cout<<"done!\n";
                break;
            }
            //get the length of the reduce production
            int gama = GlobalProductionVec[-elment].second.size();
            //cout<<elment<<" : ";
            cout<<GlobalProductionVec[-elment].first<<" -> ";
            for(auto&u:GlobalProductionVec[-elment].second){
                cout<<u<<" ";
            }
            cout<<endl;

            int k =0 ;
            while(k<gama){
                State_Stack.pop();
                Symbol_Stack.pop();
                k++;
            }
            int l_p_n = SymbolMap[GlobalProductionVec[-elment].first];
            Symbol_Stack.push(GlobalSymbolVec[l_p_n]);
            State_Stack.push(testParse_Table[State_Stack.top()][l_p_n]);
        }
//        if(elment == 0){
//            cout<<"error!\n";
//            break;
//        }
    }
}

#endif //SEUYACC_PARSING_H
