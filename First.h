#ifndef SEUYACC_FIRST_H
#define SEUYACC_FIRST_H

#include"helper.h"
extern map<int, set<int> > firstMap;
extern ProducerVec GlobalProducerVec;
extern SymbolVec GlobalSymbolVec;
extern map<int, pair<int, int> >indexMap;

void intersection(set<int>&, const set<int>&);
void first_symbol(set<int>&, int&, set<int>&);
void first_string(set<int>&, const vector<int>&);

//若有epsilon 表示为-1

void first_symbol(set<int>&firstSet, int&symbol, set<int>&stateSet) {

    if (firstMap.count(symbol) != 0) {
        intersection(firstSet, firstMap[symbol]);
        return;
    }//已经完成求解
    if (symbol == -1)return;
    if (GlobalSymbolVec[symbol].isTerminal) {//终结符
        firstSet.insert(symbol);
        return;
    }
    else {//非终结符
        stateSet.insert(symbol);
        auto indexPair = indexMap[symbol];
        for (int i = indexPair.first; i < indexPair.first + indexPair.second; i++) {//所有symbol在左边的产生式
            auto &producer = GlobalProducerVec[i];
            int le = producer.second.size();
            if (le == 1 && producer.second[0] == -1) {//symbol->epsilon
                firstSet.insert(-1);
                continue;
            }
            //向右遍历所有的项
            set<int> tempSet;//临时存放当前符号的first
            for (int j = 0; j < le; j++) {
                tempSet.clear();
                if (stateSet.find(producer.second[j]) != stateSet.end()) {//防止左递归
                    break;
                }
                first_symbol(tempSet, producer.second[j], stateSet);
                if (tempSet.count(-1) == 0) {
                    intersection(firstSet, tempSet);
                    break;
                }
                if (j == le - 1) {//最后一项还有epsilon
                    firstSet.insert(-1);
                    break;
                }
                tempSet.erase(-1);//-1最后判断是否加入stateSet  即会不会最后产生epsilon
                intersection(firstSet, tempSet);//当前first集合并入总集合
            }
        }
    }
}

void intersection(set<int>& leftSet, const set<int>& rightSet) {
    leftSet.insert(rightSet.cbegin(), rightSet.cend());
}

void calc_first() {
    set<int> firstSet, stateSet;
    int le = GlobalSymbolVec.size();
    for (int symbol = 0; symbol < le; symbol++) {
        firstSet.clear();
        stateSet.clear();
        first_symbol(firstSet,symbol, stateSet);
        firstMap.emplace(symbol, firstSet);
    }
}

//用于LR1中项目集 产生非内核项的时候得出向前看符号
void first_string(set<int>& inputSet, const vector<int>& symbols) {
    if (symbols.size() == 0) {//点在最后
        inputSet.insert(-1);
        return;
    }
    int le = symbols.size();
    for (int i = 0; i < le; i++) {
        auto & firstSet = firstMap[symbols[i]];
        if (firstSet.count(-1) == 0) {  //epsilon不在first中
            intersection(inputSet, firstSet);
            break;
        }
        if (i == le-1) {//最后一项还有epsilon
            inputSet.insert(-1);
            break;
        }
        firstSet.erase(-1); //-1最后判断是否加入inputSet  即会不会最后产生epsilon
        intersection(inputSet, firstSet); //当前first集合并入总集合
    }
}

#endif //SEUYACC_FIRST_H
