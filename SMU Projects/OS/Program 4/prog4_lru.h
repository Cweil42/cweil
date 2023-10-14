//
// Created by Colin Weil on 12/6/21.
//

#ifndef WEIL_PROG4_PROG4_LRU_H
#define WEIL_PROG4_PROG4_LRU_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <utility>
#include <map>
#include <queue>
using namespace std;

class PRDS_LRU {
public:
    PRDS_LRU(int n){ numPages = n; }
    int numPages;
    // vector of pairs
    // pair = pageNum, index in pages vector
    vector<pair<int,int>> priority;

}; // Data Structure for the LRU


int Page_Replacement_LRU(vector<int>& pages, int nextpage, PRDS_LRU* p){
    // Look for page in current priority vector
    auto pageIndex = find_if(p->priority.begin(), p->priority.end(),
                             [&nextpage](const pair<int,int>& obj) { return obj.first == nextpage; });
    // If it is found then put to the back of the priority vector and return -1
    if(pageIndex != p->priority.end()){
        p->priority.push_back(pair<int,int>(nextpage,pageIndex->second));
        p->priority.erase(pageIndex);
        return -1;
    }

    // If pages vector is full - put new page at end of list and deleted old then return index
    if(p->priority.size() == p->numPages) {
        p->priority.push_back(pair<int,int>(nextpage, p->priority[0].second));
        p->priority.erase(p->priority.begin());
        return p->priority[0].second;
    }
    else{ // if not full size - emplace pair into vector and return index of next -1
        p->priority.push_back(pair<int,int>(nextpage, p->priority.size()));
        return p->priority.size()-1;
    }
}
// // THIS IS USING MAP BUT IS SLOWER FOR SOME REASON
//class PRDS_LRU {
//public:
//    PRDS_LRU(int n){
//        numPages = n;
//    }
//    int numPages;
//    map<int, int> curPages;     // pageNum, index in pages vector
//    deque<int> priority;
//}; // Data Structure for the LRU
//
//int Page_Replacement_LRU(vector<int>& pages, int nextpage, PRDS_LRU* p){
//    // If nextpage is found in curPages then put to the back of the priority vector and return -1
//    auto found = p->curPages.find(nextpage);
//    if(found != p->curPages.end() && found->second != -1){
//        p->priority.emplace_back(nextpage);
//        return -1;
//    }
//
//    // If pages vector is full - put new page at end of list and deleted old then return index
//    if(p->curPages.size() >= p->numPages) {
//        while(p->curPages[p->priority.front()] == -1)
//            p->priority.pop_front();
//        // Insert new page into map and deque
//        int index = p->curPages[p->priority.front()];
//        p->curPages[nextpage] = index; //.insert(pair<int,int>(nextpage, index));
//        p->priority.emplace_back(nextpage);
//        // Remove old pagese from data strucutres
//        p->curPages[p->priority.front()] = -1;
//        p->priority.pop_front();
//        return index;
//    }
//    else{ // if not full size - emplace num into queue and return index of next -1
//        p->priority.emplace_back(nextpage);
//        p->curPages.insert(pair<int,int>(nextpage,p->priority.size()-1));
//        return p->curPages.size()-1;
//    }
//}

#endif //WEIL_PROG4_PROG4_LRU_H
