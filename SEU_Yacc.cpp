#include <iostream>
#include "helper.h"
#include "LR1ToLALR.h"
#include "First.h"
#include "CFGToLRDFA.h"
#include "Parse_Yacc.h"
#include "Parsing.h"
#include "CodeGeneration.h"
extern map<int, set<int> > firstMap;

using namespace std;
int main(/*int argc, char const *argv[]*/) {
/*
    if(argc != 2){
        cout<<"Usage: ./SEU_Yacc yacc.y\n";
        exit(0);
    }
*/

    string filepath = "/Users/mac/Desktop/编译原理课程设计/SeuYacc/yacc.y";

//    vector<int> aa= {};
//    GlobalProducerVec.push_back(pair<int,vector<int> >(0,aa));
//    vector<string> bb ={};
//    GlobalProductionVec.push_back(pair<string,vector<string> >("",bb));
    Parse_Yacc(filepath,GlobalSymbolVec,GlobalProductionVec,GlobalProducerVec,FuncVec);
//    GlobalProductionVec.push_back(pair<string,vector<string> >("S",{"L","=","R"}));
//    GlobalProductionVec.push_back(pair<string,vector<string> >("S",{"R"}));
//    GlobalProductionVec.push_back(pair<string,vector<string> >("L",{"*","R"}));
//    GlobalProductionVec.push_back(pair<string,vector<string> >("L",{"i"}));
//    GlobalProductionVec.push_back(pair<string,vector<string> >("R",{"L"}));
//    GlobalProductionVec.push_back(pair<string,vector<string> >("S'",{"S"}));
//
//    Symbol a;
//    a={.isTerminal=true,.symbol="="};
//    GlobalSymbolVec.push_back(a);
//    a={.isTerminal=true,.symbol="i"};
//    GlobalSymbolVec.push_back(a);
//    a={.isTerminal=true,.symbol="*"};
//    GlobalSymbolVec.push_back(a);
//    a={.isTerminal=false,.symbol="S"};
//    GlobalSymbolVec.push_back(a);
//    a={.isTerminal=false,.symbol="L"};
//    GlobalSymbolVec.push_back(a);
//    a={.isTerminal=false,.symbol="R"};
//    GlobalSymbolVec.push_back(a);
//    a={.isTerminal=false,.symbol="S'"};
//    GlobalSymbolVec.push_back(a);
//    a={.isTerminal=true,.symbol="$r"};
//    GlobalSymbolVec.push_back(a);
//
//
//    for(int i = 0 ; i < GlobalProductionVec.size(); i++){
//        cout<<GlobalProductionVec[i].first<<" -> ";
//        int aa;
//        for(int k =0;k<GlobalSymbolVec.size();k++){
//            if(GlobalSymbolVec[k].symbol==GlobalProductionVec[i].first){
//                aa= k;
//                break;
//            }
//        }
//        vector<int> t;
//        for(int j = 0 ; j < GlobalProductionVec[i].second.size(); j++){
//            cout<<GlobalProductionVec[i].second[j]<<" ";
//            for(int k =0;k<GlobalSymbolVec.size();k++){
//                if(GlobalSymbolVec[k].symbol==GlobalProductionVec[i].second[j]){
//                    t.push_back(k);
//                    break;
//                }
//            }
//        }
//        GlobalProducerVec.push_back(pair<int,vector<int> >(aa,t));
//        cout<<endl;
//    }
//
//
//    for(int i = 0 ; i < GlobalProducerVec.size(); i++){
//        cout<<GlobalProducerVec[i].first<<" -> ";
//
//        for(int j = 0 ; j < GlobalProducerVec[i].second.size(); j++){
//            cout<<GlobalProducerVec[i].second[j]<<" ";
//        }
//        cout<<endl;
//    }
//
//    startProduction = 5;
//
//    pair<int,int> t;
//    t.first=0;t.second=2;
//    indexMap.insert(pair<int,pair<int,int> >(3,t));
//    t.first=2;t.second=2;
//    indexMap.insert(pair<int,pair<int,int> >(4,t));
//    t.first=4;t.second=1;
//    indexMap.insert(pair<int,pair<int,int> >(5,t));
//    t.first=5;t.second=1;
//    indexMap.insert(pair<int,pair<int,int> >(6,t));


    cout<<"\n------------Parse yacc.y.........done\n";

    //PrintTopologyProduction();

    Collection LR1;
    calc_first();
    cout<<"\n------------calculate First set.........done\n";

//    for(auto&u:firstMap){
//        if(!GlobalSymbolVec[u.first].isTerminal)
//        {cout<<GlobalSymbolVec[u.first].symbol<<" : ";
//        for(auto&v:u.second){
//            cout<<GlobalSymbolVec[v].symbol<<" ";
//        }
//        cout<<endl;}
//    }


    CFGToLRDFA(LR1);
    cout<<"\n------------Construct LR(1) DFA.........done\n";

    Collection LALRCollectionTestcase;
    LR1ToLALR(LR1,LALRCollectionTestcase);
    cout<<"\n------------Construct LALR DFA.........done\n";

    Parse_Table p2;
    LR1ToTable(LALRCollectionTestcase,p2);
    cout<<"\n------------Construct LALR Parsing Table........done\n";

    Print_ParsingTable2(p2);

    GenerateCode(p2);
    cout<<"\n------------Generate Code for SEU_Yacc........done\n";

//    Parsing_Tokens("/Users/mac/Desktop/编译原理课程设计/SeuYacc/Lex_Tokens.txt",p2);


//    for(int i = 0;i<GlobalProductionVec.size();i++){
//        cout<<i<<" "<<GlobalProductionVec[i].first<<" -> ";
//        for(auto&u:GlobalProductionVec[i].second){
//            cout<<u<<" ";
//        }
//        cout<<endl;
//    }
//
//    for(int i = 0 ;i<GlobalSymbolVec.size();i++){
//        cout<<i<<" : "<<GlobalSymbolVec[i].symbol<<" "<<GlobalSymbolVec[i].isTerminal<<endl;
//    }
//
//
//

   /*
   for(int i =0;i<LR1.size();i++){
       PrintItemSet(LR1[i]);
   }

   for(int i = 0 ;i<GlobalSymbolVec.size();i++){
       cout<<GlobalSymbolVec[i].symbol<<" "<<GlobalSymbolVec[i].isTerminal<<endl;
   }
*/


    /*
     for(int i = 0 ; i < GlobalSymbolVec.size() ; i ++){
         if(GlobalSymbolVec[i].symbol == "S"){vector<Symbol>::iterator it1 = GlobalSymbolVec.begin();  GlobalSymbolVec.erase(it1+i);}
     }


     for(int i = 0 ; i < GlobalSymbolVec.size() ; i ++){
         if(GlobalSymbolVec[i].isTerminal)
             cout<<"Terminal Symbol:"<<GlobalSymbolVec[i].symbol<<"\n";
         else{
             cout<<"Non-Terminal Symbol: "<<GlobalSymbolVec[i].symbol<<'\n';
         }
     }

     vector<pair<string, vector<string> > >::iterator it2 = GlobalProductionVec.begin();
     while (it2 != GlobalProductionVec.end()){
         if((*it2).first == "S"){
             GlobalProductionVec.erase(it2);
         }
         else{
             if((*it2).first == "S'"){
                 (*it2).second = vector<string>{"translation_unit"};
             }
             it2++;
         }
     }
 */

//    for(int i = 0 ; i < GlobalSymbolVec.size() ; i ++){
//        if(GlobalSymbolVec[i].isTerminal)
//            cout<<"Terminal Symbol:"<<GlobalSymbolVec[i].symbol<<"\n";
//        else{
//            cout<<"Non-Terminal Symbol: "<<GlobalSymbolVec[i].symbol<<'\n';
//        }
//    }
//
//    for(int i = 0 ; i < GlobalProductionVec.size(); i++){
//        cout<<GlobalProductionVec[i].first<<" -> ";
//        for(int j = 0 ; j < GlobalProductionVec[i].second.size(); j++){
//            cout<<GlobalProductionVec[i].second[j]<<" ";
//        }
//        cout<<endl;
//    }

//    //cout<<GlobalProductionVec.size();
//
//    Parsing_Tokens("/Users/mac/Desktop/编译原理课程设计/YaccTest/Lex_Tokens.txt");
//

    //std::cout << "Hello, World!" << std::endl;

    //symbol
    /*
     * = 0
     * i 1
     * * 2
     * $r 3
     * S' 4
     * S 5
     * L 6
     * R 7
     *
     * */
/*
    Symbol t1;t1.symbol="=";t1.isTerminal= true;
    Symbol t2;t2.symbol="i";t2.isTerminal= true;
    Symbol t3;t3.symbol="*";t3.isTerminal= true;
    Symbol t4;t4.symbol="$r";t4.isTerminal= true;

    Symbol t5;t5.symbol="S'";t5.isTerminal= false;
    Symbol t6;t6.symbol="S";t6.isTerminal= false;
    Symbol t7;t7.symbol="L";t7.isTerminal= false;
    Symbol t8;t8.symbol="R";t8.isTerminal= false;

    extern SymbolVec GlobalSymbolVec;
    extern ProductionVec GlobalProductionVec;
    GlobalSymbolVec.push_back(t1);
    GlobalSymbolVec.push_back(t2);
    GlobalSymbolVec.push_back(t3);
    GlobalSymbolVec.push_back(t4);
    GlobalSymbolVec.push_back(t5);
    GlobalSymbolVec.push_back(t6);
    GlobalSymbolVec.push_back(t7);
    GlobalSymbolVec.push_back(t8);

    GlobalProductionVec.push_back(pair<string,vector<string> >("S'",vector<string>{"S"}));//0
    GlobalProductionVec.push_back(pair<string,vector<string> >("S",vector<string>{"L","=","R"}));//1
    GlobalProductionVec.push_back(pair<string,vector<string> >("S",vector<string>{"R"}));//2
    GlobalProductionVec.push_back(pair<string,vector<string> >("L",vector<string>{"*","R"}));//3
    GlobalProductionVec.push_back(pair<string,vector<string> >("L",vector<string>{"i"}));//4
    GlobalProductionVec.push_back(pair<string,vector<string> >("R",vector<string>{"L"}));//5

    Item i00;i00.productionrInt=0;i00.dot_positionInt=0;i00.prediction= set<int>{3};
    Item i01;i01.productionrInt=1;i01.dot_positionInt=0;i01.prediction= set<int>{3};
    Item i02;i02.productionrInt=2;i02.dot_positionInt=0;i02.prediction= set<int>{3};
    Item i03;i03.productionrInt=3;i03.dot_positionInt=0;i03.prediction= set<int>{3,0};
    Item i04;i04.productionrInt=4;i04.dot_positionInt=0;i04.prediction= set<int>{0,3};
    Item i05;i05.productionrInt=5;i05.dot_positionInt=0;i05.prediction= set<int>{3};
    ItemSet IS0;IS0.stateInt = 0;
    IS0.itemSet.push_back(i00);IS0.itemSet.push_back(i01);IS0.itemSet.push_back(i02);IS0.itemSet.push_back(i03);IS0.itemSet.push_back(i04);IS0.itemSet.push_back(i05);
    IS0.edgeMap.insert(pair<int,int>(1,5));IS0.edgeMap.insert(pair<int,int>(2,4));IS0.edgeMap.insert(pair<int,int>(7,3));IS0.edgeMap.insert(pair<int,int>(6,2));IS0.edgeMap.insert(pair<int,int>(5,1));

    Item i10;i10.productionrInt=0;i10.dot_positionInt=1;i10.prediction=set<int>{3};
    ItemSet IS1;IS1.stateInt = 1;IS1.itemSet.push_back(i10);

    Item i20;i20.productionrInt=1;i20.dot_positionInt=1;i20.prediction=set<int>{3};
    Item i21;i21.productionrInt=5;i21.dot_positionInt=1;i21.prediction=set<int>{3};
    ItemSet IS2;IS2.stateInt = 2;IS2.itemSet.push_back(i20);IS2.itemSet.push_back(i21);
    IS2.edgeMap.insert(pair<int,int>(0,6));

    Item i30;i30.productionrInt=2;i30.dot_positionInt=1;i30.prediction=set<int>{3};
    ItemSet IS3;IS3.stateInt=3;IS3.itemSet.push_back(i30);

    Item i40;i40.productionrInt=3;i40.dot_positionInt=1;i40.prediction=set<int>{3,0};
    Item i41;i41.productionrInt=5;i41.dot_positionInt=0;i41.prediction=set<int>{0,3};
    Item i42;i42.productionrInt=3;i42.dot_positionInt=0;i42.prediction=set<int>{0,3};
    Item i43;i43.productionrInt=4;i43.dot_positionInt=0;i43.prediction=set<int>{3,0};
    ItemSet IS4;IS4.stateInt=4;IS4.itemSet.push_back(i40);IS4.itemSet.push_back(i41);IS4.itemSet.push_back(i42);IS4.itemSet.push_back(i43);
    IS4.edgeMap.insert(pair<int,int>(1,5));IS4.edgeMap.insert(pair<int,int>(2,4));IS4.edgeMap.insert(pair<int,int>(6,8));IS4.edgeMap.insert(pair<int,int>(7,7));

    Item i50;i50.productionrInt=4;i50.dot_positionInt=1;i50.prediction=set<int>{0,3};
    ItemSet IS5;IS5.stateInt=5;IS5.itemSet.push_back(i50);

    Item i60;i60.productionrInt=1;i60.dot_positionInt=2;i60.prediction=set<int>{3};
    Item i61;i61.productionrInt=5;i61.dot_positionInt=0;i61.prediction=set<int>{3};
    Item i62;i62.productionrInt=3;i62.dot_positionInt=0;i62.prediction=set<int>{3};
    Item i63;i63.productionrInt=4;i63.dot_positionInt=0;i63.prediction=set<int>{3};
    ItemSet IS6;IS6.stateInt=6;IS6.itemSet.push_back(i60);IS6.itemSet.push_back(i61);IS6.itemSet.push_back(i62);IS6.itemSet.push_back(i63);
    IS6.edgeMap.insert(pair<int,int>(1,10));IS6.edgeMap.insert(pair<int,int>(2,12));IS6.edgeMap.insert(pair<int,int>(6,11));IS6.edgeMap.insert(pair<int,int>(7,9));

    Item i70;i70.productionrInt=3;i70.dot_positionInt=2;i70.prediction=set<int>{0,3};
    ItemSet IS7;IS7.stateInt=7;IS7.itemSet.push_back(i70);

    Item i80;i80.productionrInt=5;i80.dot_positionInt=1;i80.prediction=set<int>{0,3};
    ItemSet IS8;IS8.stateInt=8;IS8.itemSet.push_back(i80);

    Item i90;i90.productionrInt=1;i90.dot_positionInt=3;i90.prediction=set<int>{3};
    ItemSet IS9;IS9.stateInt=9;IS9.itemSet.push_back(i90);

    Item i100;i100.productionrInt=4;i100.dot_positionInt=1;i100.prediction=set<int>{3};
    ItemSet IS10;IS10.stateInt=10;IS10.itemSet.push_back(i100);

    Item i110;i110.productionrInt=5;i110.dot_positionInt=1;i110.prediction=set<int>{3};
    ItemSet IS11;IS11.stateInt=11;IS11.itemSet.push_back(i110);

    Item i120;i120.productionrInt=3;i120.dot_positionInt=1;i120.prediction=set<int>{3};
    Item i121;i121.productionrInt=5;i121.dot_positionInt=0;i121.prediction=set<int>{3};
    Item i122;i122.productionrInt=3;i122.dot_positionInt=0;i122.prediction=set<int>{3};
    Item i123;i123.productionrInt=4;i123.dot_positionInt=0;i123.prediction=set<int>{3};
    ItemSet IS12;IS12.stateInt=12;IS12.itemSet.push_back(i120);IS12.itemSet.push_back(i121);IS12.itemSet.push_back(i122);IS12.itemSet.push_back(i123);
    IS12.edgeMap.insert(pair<int,int>(6,11));IS12.edgeMap.insert(pair<int,int>(2,12));IS12.edgeMap.insert(pair<int,int>(7,13));IS12.edgeMap.insert(pair<int,int>(1,10));

    Item i130;i130.productionrInt=3;i130.dot_positionInt=2;i130.prediction=set<int>{3};
    ItemSet IS13;IS13.stateInt=13;IS13.itemSet.push_back(i130);

    Collection LRCollectionTestcase;
    LRCollectionTestcase.push_back(IS0);
    LRCollectionTestcase.push_back(IS1);
    LRCollectionTestcase.push_back(IS2);
    LRCollectionTestcase.push_back(IS3);
    LRCollectionTestcase.push_back(IS4);
    LRCollectionTestcase.push_back(IS5);
    LRCollectionTestcase.push_back(IS6);
    LRCollectionTestcase.push_back(IS7);
    LRCollectionTestcase.push_back(IS8);
    LRCollectionTestcase.push_back(IS9);
    LRCollectionTestcase.push_back(IS10);
    LRCollectionTestcase.push_back(IS11);
    LRCollectionTestcase.push_back(IS12);
    LRCollectionTestcase.push_back(IS13);



    Parse_Table p1;
    LR1ToTable(LRCollectionTestcase,p1);
    Print_ParsingTable2(p1);

    Collection LALRCollectionTestcase;
    LR1ToLALR(LRCollectionTestcase,LALRCollectionTestcase);

    Parse_Table p2;
    LR1ToTable(LALRCollectionTestcase,p2);
    Print_ParsingTable2(p2);
*/


/*
    for(int i = 0 ; i < GlobalSymbolVec.size() ; i ++){
        if(GlobalSymbolVec[i].isTerminal)
            cout<<"Terminal Symbol:"<<GlobalSymbolVec[i].symbol<<"\n";
        else{
            cout<<"Non-Terminal Symbol: "<<GlobalSymbolVec[i].symbol<<'\n';
        }
    }

    for(int i = 0 ; i < GlobalProductionVec.size(); i++){
        cout<<GlobalProductionVec[i].first<<" -> ";
        for(int j = 0 ; j < GlobalProductionVec[i].second.size(); j++){
            cout<<GlobalProductionVec[i].second[j]<<" ";
        }
        cout<<endl;
    }

    //Parsing_Tokens("/Users/mac/Desktop/编译原理课程设计/YaccTest/Lex_Tokens.txt");


    for(int i = 0 ; i < GlobalProductionVec.size(); i++){
        //cout<<GlobalProductionVec[i].first<<" -> ";
        int j;
        cout<<"GlobalProductionVec.push_back(pair<string, vector<string> >(\""<<GlobalProductionVec[i].first<<"\",{";
        for(j = 0 ; j < GlobalProductionVec[i].second.size()-1; j++){
            //cout<<GlobalProductionVec[i].second[j]<<" ";
            cout<<"\""<<GlobalProductionVec[i].second[j]<<"\",";
        }
        cout<<"\""<<GlobalProductionVec[i].second[j]<<"\"";
        cout<<"}));"<<endl;
    }



    cout<<"Symbol a;\n";
    for(int i = 0 ; i < GlobalSymbolVec.size() ; i ++){
        if(GlobalSymbolVec[i].isTerminal) {
            cout << "a={.isTerminal=true,.symbol=\"" << GlobalSymbolVec[i].symbol << "\"};\n";
            cout << "GlobalSymbolVec.push_back(a);\n";
        }
        else{
            cout<<"a={.isTerminal=false,.symbol=\""<<GlobalSymbolVec[i].symbol<<"\"};\n";
            cout<<"GlobalSymbolVec.push_back(a);\n";
        }
    }
*/

    /*
    Parse_Table testParse_Table{
            {9,{{0,0},{1,0},{2,0},{3,-1},{4,0},{5,0},{6,0},{7,0}}},
            {8,{{0,-5},{1,0},{2,0},{3,-5},{4,0},{5,0},{6,0},{7,0}}},
            {7,{{0,-3},{1,0},{2,0},{3,-3},{4,0},{5,0},{6,0},{7,0}}},
            {6,{{0,0},{1,5},{2,4},{3,0},{4,0},{5,0},{6,8},{7,9}}},
            {5,{{0,-4},{1,0},{2,0},{3,-4},{4,0},{5,0},{6,0},{7,0}}},
            {4,{{0,0},{1,5},{2,4},{3,0},{4,0},{5,0},{6,8},{7,7}}},
            {3,{{0,0},{1,0},{2,0},{3,-2},{4,0},{5,0},{6,0},{7,0}}},
            {2,{{0,6},{1,0},{2,0},{3,-5},{4,0},{5,0},{6,0},{7,0}}},
            {1,{{0,0},{1,0},{2,0},{3,-2147483647},{4,0},{5,0},{6,0},{7,0}}},
            {0,{{0,0},{1,5},{2,4},{3,0},{4,0},{5,1},{6,2},{7,3}}}
    };
*/
/*
    unordered_map<int,unordered_map<int,int > > ::iterator i = p2.begin(); int l = 0;
    cout<<"Parse_Table testParse_Table{\n";
    for(i = p2.begin();l<p2.size()-1 && i!= p2.end();l++,i++){
        cout<<"{"<<(*i).first<<",{";
        int k = 0 ; unordered_map<int,int>::iterator j=(*i).second.begin();
        for(j=(*i).second.begin() ; k<(*i).second.size()-1 && j != (*i).second.end(); j++ ,k++){
            cout<<"{"<<(*j).first<<","<<(*j).second<<"},";
        }
        cout<<"{"<<(*j).first<<","<<(*j).second<<"}";
        cout<<"}},"<<endl;
    }
    cout<<"{"<<(*i).first<<",{";
    int k = 0 ; unordered_map<int,int>::iterator j=(*i).second.begin();
    for(j=(*i).second.begin() ; k<(*i).second.size()-1 && j != (*i).second.end(); j++ ,k++){
        cout<<"{"<<(*j).first<<","<<(*j).second<<"},";
    }
    cout<<"{"<<(*j).first<<","<<(*j).second<<"}";
    cout<<"}}"<<endl;
    cout<<"};"<<endl;
*/
    //GenerateCode();
    /*
    Symbol symbol;
    symbol.isTerminal = false;
    symbol.symbol = "S'";
    GlobalSymbolVec.push_back(symbol);
    symbol.symbol = "S";
    GlobalSymbolVec.push_back(symbol);
    symbol.symbol = "C";
    GlobalSymbolVec.push_back(symbol);
    symbol.isTerminal = true;
    symbol.symbol = "c";
    GlobalSymbolVec.push_back(symbol);
    symbol.symbol = "d";
    GlobalSymbolVec.push_back(symbol);

    pair<int,vector<int> >Producer;
    vector<int> p;
    p = { 1 };
    Producer.first = 0; Producer.second = p;
    GlobalProducerVec.push_back(Producer);
    p = { 2,2 };
    Producer.first = 1; Producer.second = p;
    GlobalProducerVec.push_back(Producer);
    p = { 3,2 };
    Producer.first = 2; Producer.second = p;
    GlobalProducerVec.push_back(Producer);
    p = { 4 };
    Producer.first = 2; Producer.second = p;
    GlobalProducerVec.push_back(Producer);

    calc_first();
    Collection LRStates;
    CFGToLRDFA(LRStates);

    //return 0;
    */
    return 0;
}