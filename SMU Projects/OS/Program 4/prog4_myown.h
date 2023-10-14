//
// Created by Colin Weil on 12/6/21.
//
#ifndef WEIL_PROG4_PROG4_MYOWN_H
#define WEIL_PROG4_PROG4_MYOWN_H

#include <vector>
using namespace std;

class PRDS_MyOwn {
public:
    PRDS_MyOwn(int n){ numPages = n; }
    int numPages;
    // vector of pairs
    // pair = pageNum, index in pages vector
    vector<pair<int,int>> priority;

}; // Data Structure for the your own algorithm

// This is just going to be MRU
int Page_Replacement_MyOwn(vector<int>& pages, int nextpage, PRDS_MyOwn* p){
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
        p->priority.push_back(pair<int,int>(nextpage, (p->priority.end()-1)->second));
        p->priority.erase(p->priority.end()-2);
        return p->priority.end()->second;
    }
    else{ // if not full size - emplace pair into vector and return index of next -1
        p->priority.push_back(pair<int,int>(nextpage, p->priority.size()));
        return p->priority.size()-1;
    }
}


#endif //WEIL_PROG4_PROG4_MYOWN_H
