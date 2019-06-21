//
// Created by mac on 2019/6/2.
//

#ifndef SEUYACC_CODEGENERATION_H
#define SEUYACC_CODEGENERATION_H

#include <fstream>
using namespace std;

void GenerateCode(Parse_Table& p2 ){
    ofstream out("yyparse.cpp");
    out<<"#ifndef SEUYACC_PARSING_H"<<endl;
    out<<"#define SEUYACC_PARSING_H"<<endl;
    out<<""<<endl;
    out<<"#include <string>"<<endl;
    out<<"#include <fstream>"<<endl;
    out<<"#include <iostream>"<<endl;
    out<<"#include <stack>"<<endl;
    out<<"#include <vector>"<<endl;
    out<<"#include <map>"<<endl;
    out<<"#include <unordered_map>"<<endl;
    out<<""<<endl;
    out<<"using namespace std;"<<endl;
    out<<""<<endl;
    out<<"struct Token_Unit {"<<endl;
    out<<"    string type;"<<endl;
    out<<"    string content;"<<endl;
    out<<"    int id;"<<endl;
    out<<"};"<<endl;
    out<<""<<endl;
    out<<"//存放字符"<<endl;
    out<<"typedef struct Symbol {"<<endl;
    out<<"    string symbol;          //字符内容"<<endl;
    out<<"    bool isTerminal;        //是否是终结符号"<<endl;
    out<<"}Symbol;"<<endl;
    out<<""<<endl;
    out<<"//存放Symbol的全局变量"<<endl;
    out<<"typedef vector<Symbol> SymbolVec;"<<endl;
    out<<"SymbolVec GlobalSymbolVec;"<<endl;
    out<<""<<endl;
    out<<"//存放产生式，<左，右>=<string,vector<string> >"<<endl;
    out<<"typedef vector<pair<string, vector<string> > > ProductionVec;"<<endl;
    out<<"ProductionVec GlobalProductionVec;"<<endl;
    out<<""<<endl;
    out<<""<<endl;
    out<<"//分析表"<<endl;
    out<<"typedef unordered_map<int, unordered_map < int, int > >  Parse_Table;"<<endl;
    out<<""<<endl;
    out<<""<<endl;


//    out<<"Parse_Table testParse_Table{"<<endl;
//    out<<"{9,{{0,0},{1,0},{2,0},{3,-1},{4,0},{5,0},{6,0},{7,0}}},"<<endl;
//    out<<"{8,{{0,-5},{1,0},{2,0},{3,-5},{4,0},{5,0},{6,0},{7,0}}},"<<endl;
//    out<<"{7,{{0,-3},{1,0},{2,0},{3,-3},{4,0},{5,0},{6,0},{7,0}}},"<<endl;
//    out<<"{6,{{0,0},{1,5},{2,4},{3,0},{4,0},{5,0},{6,8},{7,9}}},"<<endl;
//    out<<"{5,{{0,-4},{1,0},{2,0},{3,-4},{4,0},{5,0},{6,0},{7,0}}},"<<endl;
//    out<<"{4,{{0,0},{1,5},{2,4},{3,0},{4,0},{5,0},{6,8},{7,7}}},"<<endl;
//    out<<"{3,{{0,0},{1,0},{2,0},{3,-2},{4,0},{5,0},{6,0},{7,0}}},"<<endl;
//    out<<"{2,{{0,6},{1,0},{2,0},{3,-5},{4,0},{5,0},{6,0},{7,0}}},"<<endl;
//    out<<"{1,{{0,0},{1,0},{2,0},{3,-2147483647},{4,0},{5,0},{6,0},{7,0}}},"<<endl;
//    out<<"{0,{{0,0},{1,5},{2,4},{3,0},{4,0},{5,1},{6,2},{7,3}}}"<<endl;
//    out<<"};"<<endl;
//    out<<""<<endl;


    int error_number = p2.size() + 1;
    for(int i =0 ; i< p2.size() ; i++){
        for(int j =0 ;j<p2[i].size();j++){
            if(p2[i][j]==INT_MAX){
                p2[i][j] = error_number;
            }
        }
    }


    unordered_map<int,unordered_map<int,int > > ::iterator i = p2.begin(); int l = 0;
    out<<"Parse_Table testParse_Table{\n";
    for(i = p2.begin();l<p2.size()-1 && i!= p2.end();l++,i++){
        out<<"{"<<(*i).first<<",{";
        int k = 0 ; unordered_map<int,int>::iterator j=(*i).second.begin();
        for(j=(*i).second.begin() ; k<(*i).second.size()-1 && j != (*i).second.end(); j++ ,k++){
            out<<"{"<<(*j).first<<","<<(*j).second<<"},";
        }
        out<<"{"<<(*j).first<<","<<(*j).second<<"}";
        out<<"}},"<<endl;
    }
    out<<"{"<<(*i).first<<",{";
    int k = 0 ; unordered_map<int,int>::iterator j=(*i).second.begin();
    for(j=(*i).second.begin() ; k<(*i).second.size()-1 && j != (*i).second.end(); j++ ,k++){
        out<<"{"<<(*j).first<<","<<(*j).second<<"},";
    }
    out<<"{"<<(*j).first<<","<<(*j).second<<"}";
    out<<"}}"<<endl;
    out<<"};"<<endl;

    out<<"void init(){"<<endl;
//    out<<"    GlobalProductionVec.push_back(pair<string, vector<string> >(\"S'\",{\"S\"}));"<<endl;
//    out<<"GlobalProductionVec.push_back(pair<string, vector<string> >(\"S\",{\"L\",\"=\",\"R\"}));"<<endl;
//    out<<"GlobalProductionVec.push_back(pair<string, vector<string> >(\"S\",{\"R\"}));"<<endl;
//    out<<"GlobalProductionVec.push_back(pair<string, vector<string> >(\"L\",{\"*\",\"R\"}));"<<endl;
//    out<<"GlobalProductionVec.push_back(pair<string, vector<string> >(\"L\",{\"i\"}));"<<endl;
//    out<<"GlobalProductionVec.push_back(pair<string, vector<string> >(\"R\",{\"L\"}));"<<endl;

    for(int i = 0 ; i < GlobalProductionVec.size(); i++){
        //cout<<GlobalProductionVec[i].first<<" -> ";
        int j;
        out<<"GlobalProductionVec.push_back(pair<string, vector<string> >(\""<<GlobalProductionVec[i].first<<"\",{";
        for(j = 0 ; j < GlobalProductionVec[i].second.size()-1; j++){
            //cout<<GlobalProductionVec[i].second[j]<<" ";
            out<<"\""<<GlobalProductionVec[i].second[j]<<"\",";
        }
        out<<"\""<<GlobalProductionVec[i].second[j]<<"\"";
        out<<"}));"<<endl;
    }


    out<<"Symbol a;\n";
    for(int i = 0 ; i < GlobalSymbolVec.size() ; i ++){
        if(GlobalSymbolVec[i].isTerminal) {
            out << "a={.isTerminal=true,.symbol=\"" << GlobalSymbolVec[i].symbol << "\"};\n";
            out << "GlobalSymbolVec.push_back(a);\n";
        }
        else{
            out<<"a={.isTerminal=false,.symbol=\""<<GlobalSymbolVec[i].symbol<<"\"};\n";
            out<<"GlobalSymbolVec.push_back(a);\n";
        }
    }

    out<<"}"<<endl;
    out<<""<<endl;
    out<<""<<endl;
    out<<"void Parsing_Tokens(string filepath){"<<endl;
    out<<"    ifstream input(filepath);"<<endl;
    out<<"    if(!input.is_open()){cout<<\"fail to open the input tokens file!\\n\";}"<<endl;
    out<<""<<endl;
    out<<"    init();"<<endl;
    
    out<<"    //parse Tokens result from Lex"<<endl;
    out<<"    string line;"<<endl;
    out<<"    vector<Token_Unit> Token_List;"<<endl;
    out<<"    while(getline(input, line))"<<endl;
    out<<"    {"<<endl;
    out<<"        line = line.c_str();"<<endl;
    out<<"        Token_Unit new_Token;"<<endl;
    out<<""<<endl;
    out<<"        int cur = 0 ,next =0 ;"<<endl;
    out<<"        while (line[next] != ' '&& line[next] != '\\t'){next++;}"<<endl;
    out<<"        new_Token.content = line.substr(cur,next-cur);"<<endl;
    out<<""<<endl;
    out<<"        while(line[next] == ' ' || line[next] == '\\t'){next++;}"<<endl;
    out<<"        cur = next;"<<endl;
    out<<"        while (line[next] != ' '&& line[next] != '\\t'){next++;}"<<endl;
    out<<"        new_Token.type = line.substr(cur,next-cur);"<<endl;
    out<<""<<endl;
    out<<"        while(line[next] == ' ' || line[next] == '\\t'){next++;}"<<endl;
    out<<"        cur = next;"<<endl;
    out<<"        while (next != line.size()&& line[next] != ' '&& line[next] != '\\t'){next++;}"<<endl;
    out<<"        new_Token.id = atoi(line.substr(cur,next-cur).c_str());"<<endl;
    out<<""<<endl;
    out<<"        Token_List.push_back(new_Token);"<<endl;
    out<<""<<endl;
    out<<"    }"<<endl;
    out<<""<<endl;
    out<<"    //Construct hashMap from Token name to Token Number"<<endl;
    out<<"    map<string,int> SymbolMap;"<<endl;
    out<<"    for(int i = 0 ; i < GlobalSymbolVec.size();i++)"<<endl;
    out<<"    {"<<endl;
    out<<"        SymbolMap.insert(pair<string,int>(GlobalSymbolVec[i].symbol,i));"<<endl;
    out<<"    }"<<endl;
    out<<""<<endl;
    out<<"    //create symbol stack"<<endl;
    out<<"    stack<Symbol> Symbol_Stack;"<<endl;
    out<<"    //create state stack"<<endl;
    out<<"    stack<int> State_Stack;"<<endl;
    out<<""<<endl;
    out<<"    //create and push end symbol into Symbol Stack"<<endl;
    out<<"    Symbol End_Symbol;End_Symbol.symbol=\"$r\";End_Symbol.isTerminal=true;"<<endl;
    out<<"    Symbol_Stack.push(End_Symbol);"<<endl;
    out<<""<<endl;
    out<<"    //push state 0 into State Stack"<<endl;
    out<<"    State_Stack.push(0);"<<endl;
    out<<""<<endl;
    out<<"    map<int,vector<int> >AST;// parsing tree"<<endl;
    out<<"    struct node{"<<endl;
    out<<"        int node_index_number;"<<endl;
    out<<"        int level_number;"<<endl;
    out<<"    };"<<endl;
    out<<"    map<int,string> node_num2node_content;//hash map from node number to node content to be printed"<<endl;
    out<<""<<endl;
    out<<"    int Parse_Token_index = 0 ;"<<endl;
    out<<""<<endl;
    out<<"    ofstream out1(\"dotfile.gv\");"<<endl;
    out<<"    out1<<\"digraph{\"<<endl;"<<endl;
    out<<"    stack<int> helper_Stack;"<<endl;
    out<<"    helper_Stack.push(-1);"<<endl;
    out<<"    int node_num = 0;"<<endl;
    out<<"    int elment;"<<endl;
    out<<"    while(Parse_Token_index <= Token_List.size()){"<<endl;
    out<<"        // check the parsing table"<<endl;
    out<<"        if(Parse_Token_index < Token_List.size())"<<endl;
    out<<"            elment = testParse_Table[State_Stack.top()][SymbolMap[Token_List[Parse_Token_index].type]];"<<endl;
    out<<"        else{"<<endl;
    out<<"            elment = testParse_Table[State_Stack.top()][SymbolMap[End_Symbol.symbol]];"<<endl;
    out<<"        }"<<endl;
    out<<"        //if shift"<<endl;
    out<<"        if(elment > 0){"<<endl;
    out<<"            if(elment != testParse_Table.size() + 1) {"<<endl;
    out<<"                //cout << elment << endl;"<<endl;
    out<<"                State_Stack.push(elment);"<<endl;
    out<<"                Symbol_Stack.push(GlobalSymbolVec[SymbolMap[Token_List[Parse_Token_index].type]]);"<<endl;
    out<<"                //if(GlobalSymbolVec[SymbolMap[Token_List[Parse_Token_index].type]].isTerminal)"<<endl;
    out<<"                string token_name = GlobalSymbolVec[SymbolMap[Token_List[Parse_Token_index].type]].symbol;"<<endl;
    out<<"                if(token_name == \"STRING_LITERAL\"){"<<endl;
    out<<"                    out1<<\"Node\"<<node_num<<\"[label=\\\"STRING_LITERAL\"<<\"   \\\\\"<<Token_List[Parse_Token_index].content.substr(0,Token_List[Parse_Token_index].content.size()-1)<<\"\\\\\\\" \\\",shape=doublecircle];\"<<endl;"<<endl;
    out<<"                }"<<endl;
    out<<"                else out1<<\"Node\"<<node_num<<\"[label=\\\"\"<<GlobalSymbolVec[SymbolMap[Token_List[Parse_Token_index].type]].symbol<<\"   \"<<Token_List[Parse_Token_index].content<<\"\\\",shape=doublecircle];\"<<endl;"<<endl;
    out<<"                //create node"<<endl;
    out<<"                node newNode;newNode.node_index_number=node_num; node_num2node_content.insert(pair<int,string>(node_num,GlobalSymbolVec[SymbolMap[Token_List[Parse_Token_index].type]].symbol+\"   \"+Token_List[Parse_Token_index].content));"<<endl;
    out<<"                AST.insert(pair<int,vector<int> >(node_num,{}));"<<endl;
    out<<"                helper_Stack.push(node_num);node_num++;"<<endl;
    out<<"                Parse_Token_index++;"<<endl;
    out<<"            }"<<endl;
    out<<"            else{"<<endl;
    out<<"                cout<<\"error!\\n\";"<<endl;
    out<<"                break;"<<endl;
    out<<"            }"<<endl;
    out<<"        }"<<endl;
    out<<"        // if reduce"<<endl;
    out<<"        if(elment <= 0 ){"<<endl;
    out<<"            if(elment == -INT_MAX){"<<endl;
    out<<"                cout<<\"yyparse done!\\n\";"<<endl;
    out<<"                break;"<<endl;
    out<<"            }"<<endl;
    out<<"            //get the length of the reduce production"<<endl;
    out<<"            int gama = GlobalProductionVec[-elment].second.size();"<<endl;
    out<<"            //cout<<elment<<\" : \";"<<endl;
    out<<"            cout<<GlobalProductionVec[-elment].first<<\" -> \";"<<endl;
    out<<"            for(auto&u:GlobalProductionVec[-elment].second){"<<endl;
    out<<"                cout<<u<<\" \";"<<endl;
    out<<"            }"<<endl;
    out<<"            cout<<endl;"<<endl;
    out<<""<<endl;
    out<<"            int k =0 ;"<<endl;
    out<<"            vector<int> h;"<<endl;
    out<<"            while(k<gama){"<<endl;
    out<<"                State_Stack.pop();"<<endl;
    out<<"                Symbol_Stack.pop();"<<endl;
    out<<"                k++;"<<endl;
    out<<"                h.push_back(helper_Stack.top());"<<endl;
    out<<"                helper_Stack.pop();"<<endl;
    out<<"            }"<<endl;
    out<<"            int l_p_n = SymbolMap[GlobalProductionVec[-elment].first];"<<endl;
    out<<"            Symbol_Stack.push(GlobalSymbolVec[l_p_n]);"<<endl;
    out<<"            State_Stack.push(testParse_Table[State_Stack.top()][l_p_n]);"<<endl;
    out<<"            out1<<\"Node\"<<node_num<<\"[label=\\\"\"<<GlobalSymbolVec[SymbolMap[GlobalProductionVec[-elment].first]].symbol<<\"\\\",shape=circle];\"<<endl;"<<endl;
    out<<"            node newNode2;newNode2.node_index_number=node_num; node_num2node_content.insert(pair<int,string>(node_num,GlobalSymbolVec[SymbolMap[GlobalProductionVec[-elment].first]].symbol));"<<endl;
    out<<"            AST.insert(pair<int,vector<int> >(node_num,h));"<<endl;
    out<<"            for(auto&u:h){"<<endl;
    out<<"                out1<<\"Node\"<<node_num<<\" -> \"<<\"Node\"<<u<<\";\"<<endl;"<<endl;
    out<<"            }"<<endl;
    out<<"            helper_Stack.push(node_num);node_num++;"<<endl;
    out<<"        }"<<endl;
    out<<""<<endl;
    out<<"    }"<<endl;
    out<<""<<endl;
    out<<"    out1<<\"}\"<<endl;"<<endl;
    out<<""<<endl;
    out<<""<<endl;
    out<<"    cout<<\"\\n\\nAST:\\n\";"<<endl;
    out<<"    int root=0;"<<endl;
    out<<"    for(auto&u:AST){"<<endl;
    out<<"        if(u.first>root) root=u.first;"<<endl;
    out<<"    }"<<endl;
    out<<""<<endl;
    out<<"    vector<int> firstStack;firstStack.push_back(root);"<<endl;
    out<<"    vector< vector<int> > childListStack;childListStack.push_back(firstStack);"<<endl;
    out<<""<<endl;
    out<<"    while(childListStack.size()>0){"<<endl;
    out<<"        vector<int> childStack = childListStack[childListStack.size()-1];"<<endl;
    out<<"        if(childStack.size()==0){"<<endl;
    out<<"            vector< vector<int> >::iterator i1 =childListStack.begin() ;"<<endl;
    out<<"            childListStack.erase(i1+childListStack.size()-1);"<<endl;
    out<<"            //childListStack.pop_back();"<<endl;
    out<<"        }"<<endl;
    out<<"        else{"<<endl;
    out<<"            int cur = childStack[0];"<<endl;
    out<<"            vector<int>::iterator i2 = childStack.begin();"<<endl;
    out<<"            childStack.erase(i2);"<<endl;
    out<<"            childListStack.pop_back();"<<endl;
    out<<"            childListStack.push_back(childStack);"<<endl;
    out<<""<<endl;
    out<<"            string indent = \"\";"<<endl;
    out<<"            for(int i =0;i<childListStack.size()-1;i++){"<<endl;
    out<<"                indent += (childListStack[i].size()>0) ? \"|  \":\"   \";"<<endl;
    out<<"            }"<<endl;
    out<<"            cout<<indent<<\"+- \"<<node_num2node_content[cur]<<\"   \"<<endl;"<<endl;
    out<<""<<endl;
    out<<"            if(AST[cur].size()>0){"<<endl;
    out<<"                vector<int> temp;vector<int>::reverse_iterator riter;"<<endl;
    out<<"                for(riter=AST[cur].rbegin();riter !=AST[cur].rend();riter++){"<<endl;
    out<<"                    temp.push_back(*riter);"<<endl;
    out<<"                }"<<endl;
    out<<"                childListStack.push_back(temp);"<<endl;
    out<<"            }"<<endl;
    out<<"        }"<<endl;
    out<<"    }"<<endl;
    out<<""<<endl;
    out<<"    cout<<\"\\n\\nRendering the PDF for the AST......\\n\";"<<endl;
    out<<"    FILE * fp = NULL;"<<endl;
    out<<""<<endl;
    out<<"    char chBuffer[1024]={0};"<<endl;
    out<<"    char chCmd[100] = \"dot -Tpdf dotfile.gv -o AST.pdf\";"<<endl;
    out<<"    fp = popen(chCmd,\"r\");"<<endl;
    out<<"    if (fp) {"<<endl;
    out<<"        memset(chBuffer, 0, sizeof(chBuffer));"<<endl;
    out<<"        while (NULL != fgets(chBuffer, sizeof(chBuffer), fp)) {"<<endl;
    out<<"            printf(\"%s\", chBuffer);"<<endl;
    out<<"        }"<<endl;
    out<<"        pclose(fp);"<<endl;
    out<<"    }"<<endl;
    out<<""<<endl;
    out<<"    cout<<\"PDF for the AST has been generated!\\n\";"<<endl;
    out<<""<<endl;
    out<<"}"<<endl;
    out<<"int main(int argc, char const *argv[])"<<endl;
    out<<"{"<<endl;
    out<<"    /* code */"<<endl;
    out<<"    if(argc != 2){"<<endl;
    out<<"        cout<<\"Usage: ./yyarse <Lex_Token_List_Result.txt>\\n\";"<<endl;
    out<<"        exit(0);"<<endl;
    out<<"    }"<<endl;
    out<<""<<endl;
    out<<"    string filepath = argv[1];"<<endl;
    out<<""<<endl;
    out<<"    Parsing_Tokens(filepath);"<<endl;
    out<<""<<endl;
    out<<"    return 0;"<<endl;
    out<<"}"<<endl;
    out<<"#endif //SEUYACC_PARSING_H"<<endl;

}

#endif //SEUYACC_CODEGENERATION_H
