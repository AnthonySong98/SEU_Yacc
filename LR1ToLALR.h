//
// Created by mac on 2019/5/30.
//

#ifndef SEUYACC_LR1TOLALR_H
#define SEUYACC_LR1TOLALR_H

#include "helper.h"
#include <map>
#include <iostream>
#include <fstream>



void PrintItem(const Item it1){
    cout<<GlobalProductionVec[it1.productionrInt].first<<" -> ";
    int dotpos = it1.dot_positionInt;
    int i =0 ;
    for(i = 0;i<dotpos;i++){
        cout<<GlobalProductionVec[it1.productionrInt].second[i]<<" ";
    }
    cout<<"dot ";
    for(i = dotpos;i<GlobalProductionVec[it1.productionrInt].second.size();i++){
        cout<<GlobalProductionVec[it1.productionrInt].second[i]<<" ";
    }

    cout<<"---- {";
    for(auto& u:it1.prediction){
        cout<<GlobalSymbolVec[u].symbol<<" ";
    }
    cout<<"}";

    cout<<endl;
}


void PrintItemSet(const ItemSet IS){
    cout<<"I "<<IS.stateInt<<" : \n";
    for(auto& u:IS.itemSet){
        PrintItem(u);
    }

}

//detect whether two itemsets have the same core
bool hasSameCore(ItemSet& is1,ItemSet& is2){
    //if the size for two itemset is not the same, then return false
   if(is1.itemSet.size() != is2.itemSet.size()){
        return false;
   }
   else{
       set<pair<int,int> > core1; set<pair<int,int> > core2;
       //extract core from two itemsets
       for(auto &u:is1.itemSet){
            core1.insert(pair<int,int>(u.productionrInt,u.dot_positionInt));
       }
       for(auto &u:is2.itemSet){
           core2.insert(pair<int,int>(u.productionrInt,u.dot_positionInt));
       }
       if(core1 == core2){return true;}
       else{
           return false;
       }
   }
}


//concatenate two itemsets with the same cores and the result itemset is the first one
// only change the itemset not the edgeMap
ItemSet ConcatenateTwoItemsets(ItemSet& is1,ItemSet& is2){
    //sort two Itemsets based on their production number
    //sort(is1.itemSet.begin(),is1.itemSet.end(),[](const Item& i1, const Item& i2){return i1.productionrInt<i2.productionrInt;});
    //sort(is1.itemSet.begin(),is1.itemSet.end(),[](const Item& i1, const Item& i2){return i1.productionrInt<i2.productionrInt;});
    /*
    set<Item>::iterator it1,it2;
    for(it1=is1.itemSet.begin(),it2=is2.itemSet.begin();it1 !=is1.itemSet.end();it1++,it2++){
        sort((*it1).predicitonVec.begin(),(*it1).predicitonVec.end(),[](const int&);
        sort((*it2).predicitonVec.begin(),(*it2).predicitonVec.end());
        vector<int> v;
        //set_union((*it1).predicitonVec.begin(),(*it1).predicitonVec.end(),(*it2).predicitonVec.begin(),(*it2).predicitonVec.end(),back_inserter(v));
        //((*it1).predicitonVec).size();
    }
     */
    ItemSet is12;
    is12.stateInt=is1.stateInt;
    for(auto&u:is1.itemSet){
        int a=u.dot_positionInt;
        int b=u.productionrInt;
        //u.dot_positionInt = 1;
        for(auto&v:is2.itemSet){
            if(v.dot_positionInt==a && v.productionrInt==b){
                Item tempI;
                tempI.dot_positionInt = a;
                tempI.productionrInt = b;
                tempI.prediction.insert(v.prediction.begin(),v.prediction.end());
                tempI.prediction.insert(u.prediction.begin(),u.prediction.end());
                is12.itemSet.push_back(tempI);
            }
        }
    }

    is12.edgeMap.insert(is1.edgeMap.begin(),is1.edgeMap.end());
    is12.edgeMap.insert(is2.edgeMap.begin(),is2.edgeMap.end());

    return is12;
}



//convert LA1 DFA to LALR DFA
void  LR1ToLALR(Collection& LRcollection, Collection& LALRcollection){

    /*
    //find all equivalent itemset
    int currentNewindex = 0;

    //record the map between the old itemset number to new itemset number
    unordered_map<int,int>old2new;

    for(int i = 0;i<LRcollection.size();i++){

        bool flag1=true;
        for(int j =0 ;j<LALRcollection.size()&&flag1;j++){
            if(hasSameCore(LALRcollection[j],LRcollection[i])){
                ItemSet temp = ConcatenateTwoItemsets(LALRcollection[j],LRcollection[i]);
                //remove the original LALRcollection[j]
                vector<ItemSet>::iterator it = LALRcollection.begin()+j;

                old2new.insert(pair<int,int>(LRcollection[i].stateInt,LALRcollection[j].stateInt));
                flag1 = false;
            }
        }
        //if no itemset in LALR DFA is the same as the current itemset in LR1
        if(flag1){
            LRcollection[i].stateInt = currentNewindex;
            old2new.insert(pair<int,int>(LRcollection[i].stateInt,currentNewindex));
            currentNewindex++;
            LALRcollection.push_back(LRcollection[i]);

        }
    }
    //update the map in LALRcollection
    for(auto& u:LALRcollection){
        for(auto& v:u.edgeMap){
            v.second = old2new[v.second];
        }
    }
     */

    //record all the hash function of the same core
    vector<vector<int> > hash_index;

    for(auto&u:LRcollection){

        bool flag = true;
        for(auto&v:hash_index){
            if(v.size()>0){
                if(hasSameCore(LRcollection[v[0]],u)){v.push_back(u.stateInt);flag = false;
                    break;}
            }
        }
        if(flag){
            hash_index.push_back(vector<int>{u.stateInt});
        }
    }

    //print hash_index
//    for(auto&u:hash_index){
//        for(auto&v:u){
//            cout<<v<<" ";
//        }
//        cout<<endl;
//    }

    //ensure the index in the Collection is the same as the StateInt
    for(int i = 0;i<LRcollection.size();i++){
        if(LRcollection[i].stateInt!=i) cout<<"not the same index as the stateInt!\n";
    }

    //create hash map for the map function from old stateInt to new stateInt
    map<int,int> hmap;

    int k =0;
    for(int j = 0 ;j < hash_index.size() ;j++){
        ItemSet tempIS;
        if(hash_index[j].size()>1){
            tempIS = ConcatenateTwoItemsets(LRcollection[hash_index[j][0]],LRcollection[hash_index[j][1]]);
            hmap.insert(pair<int,int>(LRcollection[hash_index[j][0]].stateInt,k));
            hmap.insert(pair<int,int>(LRcollection[hash_index[j][1]].stateInt,k));
            //cout<<hash_index[j][0]<<"--"<<hash_index[j][1];
            for(int i = 2 ; i<hash_index[j].size();i++){
                tempIS = ConcatenateTwoItemsets(LRcollection[hash_index[j][i]],tempIS);
                hmap.insert(pair<int,int>(LRcollection[hash_index[j][i]].stateInt,k));
                //cout<<"--"<<hash_index[j][i];
            }
            //cout<<endl;
            tempIS.stateInt = k;
        }
        else{
            if(hash_index[j].size()==1)
            {tempIS = LRcollection[hash_index[j][0]];
            hmap.insert(pair<int,int>(LRcollection[hash_index[j][0]].stateInt,k));
            tempIS.stateInt = k;}
        }
        if(hash_index[j].size()>0)
        {LALRcollection.push_back(tempIS);
        k++;}
    }

 //   cout<<hash_index.size()<<" in total!\n";

//    for(auto&u:LRcollection){
//        PrintItemSet(u);
//    }

//    for(auto&u:LALRcollection){
//        PrintItemSet(u);
//    }

    //for(auto&u:hmap)cout<<u.first<<"--"<<u.second<<endl;

    //update edgeMap for each ItemSet
    for(auto&u:LALRcollection){
        for(auto&v:u.edgeMap){
            u.edgeMap[v.first] = hmap[v.second];
        }
    }


}



void LR1ToTable(Collection& LRcollection,Parse_Table& Parsing_table){
    //initialize parsing tabel
    unordered_map < int,int >temp;
    for(int j =0;j< GlobalSymbolVec.size();j++){
        temp.insert(pair<int,int>(j,INT_MAX));//error
    }
    for(int i =0 ;i<LRcollection.size();i++){
        Parsing_table.insert(pair<int,unordered_map < int,int >>(i,temp));
    }

    for(auto& u:LRcollection){
        //cout<<u.stateInt<<" : "<<endl;
        for(auto& v:u.itemSet){
            //reduce
            //PrintItem(v);
            if(GlobalProductionVec[v.productionrInt].second.size()==v.dot_positionInt){
                for(auto& k:v.prediction){
                    Parsing_table[u.stateInt][k] = - v.productionrInt;
                    //cout<<u.stateInt<<" reduce! "<<v.productionrInt<<endl;
                }
                if(GlobalProductionVec[v.productionrInt].first == "S'"&& v.productionrInt==GlobalProductionVec.size()-1 ){
                    int j;
                    for(j = 0;j<GlobalSymbolVec.size();j++){if(GlobalSymbolVec[j].symbol == "$r") break;}
                    Parsing_table[u.stateInt][j] = - INT_MAX;
                }
            }
            else{
                //string a =(ProductionVec[v.productionrInt].second)[v.dot_positionInt];
            }
        }
        for(auto&v: u.edgeMap){
            Parsing_table[u.stateInt][v.first]=v.second;
        }
    }
}



void LALR2Table(Collection& LRcollection,Parse_Table& Parsing_table){

    //initialize parsing tabel
    unordered_map < int,int >temp;
    for(int j =0;j< GlobalSymbolVec.size();j++){
        temp.insert(pair<int,int>(j,0));//error
    }
    for(int i =0 ;i<LRcollection.size();i++){
        Parsing_table.insert(pair<int,unordered_map < int,int >>(i,temp));
    }

}


//for debugging
void Print_ParsingTable(Parse_Table& Parsing_table){

    fstream output("parsing_table.csv",ios::out);
    output<<"State:"<<',';
    //print all the terminal symbol and non-terminal symbol
    int i;
    for(i = 0; i < GlobalSymbolVec.size()-1;i++){
        output<<i<<',';
    }
    output<<i<<'\n';

    //print each state
    for(i=0;i<Parsing_table.size();i++){
        output<<i<<',';
        int j =0;
        for(j=0;j<Parsing_table[i].size()-1;j++){
            output<<Parsing_table[i][j]<<',';
        }
        output<<Parsing_table[i][j]<<'\n';
    }
}

//for debigging
void Print_ParsingTable2(Parse_Table& Parsing_table){
    fstream output("parsing_table2.csv",ios::out);
    output<<"State:"<<',';
    //print all the terminal symbol and non-terminal symbol
    int i;
    for(i = 0; i < GlobalSymbolVec.size()-1;i++){
        if(GlobalSymbolVec[i].symbol!=",")
            output<<GlobalSymbolVec[i].symbol<<',';
        else{
            output<<"\",\""<<',';
        }
    }
    output<<GlobalSymbolVec[i].symbol<<'\n';

    //print each state
    for(i=0;i<Parsing_table.size();i++){
        output<<i<<',';
        int j =0;
        for(j=0;j<Parsing_table[i].size()-1;j++){
            if(Parsing_table[i][j]>0)
            {
                if(Parsing_table[i][j]!=INT_MAX)
                {
                    if(GlobalSymbolVec[j].isTerminal)
                    output<<"S"<<Parsing_table[i][j]<<',';
                else{
                    output<<Parsing_table[i][j]<<',';
                    }
                }
                else{
                    output<<" "<<',';
                }
            }

//            if(Parsing_table[i][j]==0)
//                output<<" "<<',';

            if(Parsing_table[i][j]<=0)
            {
                if(Parsing_table[i][j]!=-INT_MAX)
                output<<"r"<<-Parsing_table[i][j]<<',';
                else{
                    output<<"acc"<<',';
                }
            }
        }
        //output<<Parsing_table[i][j]<<'\n';
        if(Parsing_table[i][j]>0)
        {
            if(Parsing_table[i][j]!=INT_MAX){
                if(GlobalSymbolVec[j].isTerminal)
                    output<<"S"<<Parsing_table[i][j]<<'\n';
                else{
                    output<<Parsing_table[i][j]<<'\n';
                }
            }
            else{
                output<<" "<<'\n';
            }

        }
//        if(Parsing_table[i][j]==0)
//            output<<" "<<'\n';
        if(Parsing_table[i][j]<=0)
        {
            if(Parsing_table[i][j]!=-INT_MAX)
                output<<"r"<<-Parsing_table[i][j]<<'\n';
            else{
                output<<"acc"<<'\n';
            }
        }
    }

}


void PrintTopologyProduction(){

    ofstream dotfile("TopologyProduction.txt");
    int i = 0;
    for(auto&u:GlobalSymbolVec){
        dotfile<<"Node"<<i<<"[label = \""<<i<<"  "<<u.symbol<<"\", shape = doublecircle];"<<endl;
        i++;
    }


    for(auto&u:GlobalProducerVec){
        for(auto&v:u.second){
            dotfile<<"Node"<<u.first<<" -> Node"<<v<<";"<<endl;
        }
        //cout<<endl;
    }

    for(auto&u:GlobalProductionVec){
        cout<<u.first<<" -> ";
        for(auto&v:u.second){
            cout<<v<<" ";
        }
        cout<<endl;
    }
}

void yyparse(){

}


#endif //SEUYACC_LR1TOLALR_H
