#ifndef SEUYACC_HELPER_H
#define SEUYACC_HELPER_H

#include <string>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <vector>
#include <queue>
using namespace std;

//定义LR1中的项目
typedef struct Item {
    int dot_positionInt = 0;      //表示·的位置
    int productionrInt = -1;      //表示表达式文法标号
    set<int> prediction;         //表示预测符标号的set
    inline bool operator==(const Item& item)const {
        if (dot_positionInt != item.dot_positionInt ||
            productionrInt != item.productionrInt ||
            prediction != item.prediction
                )
            return false;
        else
            return true;
    }

    Item& operator=(const Item&item) {
        dot_positionInt = item.dot_positionInt;
        productionrInt = item.productionrInt;
        prediction.clear();
        prediction.insert(item.prediction.cbegin(), item.prediction.cend());
        return *this;
    }

    bool operator<(const Item& rhs) const
    {
        if (productionrInt < rhs.productionrInt) {
            return true;
        }  //assume that you compare the record based on a
        else {
            if (productionrInt == rhs.productionrInt) {
                if (dot_positionInt < rhs.dot_positionInt) {
                    return true;
                }
            }
        }
        return false;
    }
    Item() {
    }
    Item(int a, int b, set<int>c) {
        dot_positionInt = a;
        productionrInt = b;
        prediction = c;
    }

}Item;


//定义LR1中的项目集
typedef struct ItemSet {
    int stateInt = -1;                    //状态号
    unordered_map<int, int> edgeMap;     //<字符标号，状态号>
    vector<Item> itemSet;        //项目集内各项目

    inline bool operator==(const ItemSet& BSet)const {
        int la = itemSet.size(), lb = BSet.itemSet.size();
        if (la != lb)
            return false;
        for (int i = 0; i < la; i++) {
            int j = 0;
            for (; j < lb; j++)
                if (itemSet[i] == BSet.itemSet[j])break;
            if (j == lb)return false;
        }
        return true;
    }
}ItemSet;



//定义LR1中的项目集族
typedef vector<ItemSet> Collection;

//存放字符
typedef struct Symbol {
    string symbol;          //字符内容
    bool isTerminal;        //是否是终结符号
}Symbol;

//存放Symbol的全局变量
typedef vector<Symbol> SymbolVec;
SymbolVec GlobalSymbolVec;

//存放产生式，<左，右>=<string,vector<string> >
typedef vector<pair<string, vector<string> > > ProductionVec;
ProductionVec GlobalProductionVec;

//存放产生式，<左，右>=<int,vector<int> > 数字版本
typedef vector<pair<int, vector<int> > > ProducerVec;
ProducerVec GlobalProducerVec;

//分析表
typedef unordered_map<int, unordered_map < int, int > >  Parse_Table;
//vector 下表表示状态号，<int,int> <Token在Tokenvec标号，规约/转移结果>
//正数表示 shift  负数表示reduce   accept INT_MAX


//对yacc.y文件进行解析,得到产生式vec/辅助函数/Symbol
vector<string> FuncVec;
//存放辅助函数
map<int, pair<int, int> >indexMap;
//记录一个非终结符所对应的产生式的序号区间
//pair 中first是开始下标 second是该非终结符有多少个产生式
map<int, set<int> > firstMap;
//存放first集合
int startProduction;


#endif //SEUYACC_HELPER_H
