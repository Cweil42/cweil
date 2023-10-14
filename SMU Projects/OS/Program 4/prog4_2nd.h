//
// Created by Colin Weil on 12/6/21.
//

#ifndef WEIL_PROG4_PROG4_2ND_H
#define WEIL_PROG4_PROG4_2ND_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <tuple>
#include <map>
#include <queue>
using namespace std;

class PRDS_2nd {
public:
    PRDS_2nd(int n){ numPages = n; }
    int numPages;
    // vector of tuples
    // pair = pageNum, index in pages vector, reference number
    vector<tuple<int,int, int>> priority;
}; // Data Structure for the 2nd chance algorithm


int Page_Replacement_2nd(vector<int>& pages, int nextpage, PRDS_2nd* p){
    // Look for page in current priority vector
    auto pageIndex = find_if(p->priority.begin(), p->priority.end(),
                             [&nextpage](const tuple<int,int,int>& obj) { return get<0>(obj) == nextpage; });
    // If it is found then put to the back of the priority vector and return -1
    if(pageIndex != p->priority.end()){
        int refNumber = get<2>(*pageIndex);
        if(refNumber < 3)
            refNumber++;
        p->priority.push_back(tuple<int,int,int>(nextpage,get<1>(*pageIndex),refNumber));
        p->priority.erase(pageIndex);
        return -1;
    }

    // If pages vector is full - put new page at end of list and deleted old then return index
    if(p->priority.size() == p->numPages) {
        while(get<2>(p->priority.front()) != 0){
            p->priority.push_back(tuple<int,int,int>(get<0>(p->priority.front()), get<1>(p->priority.front()),
                                                        get<2>(p->priority.front())-1));
            p->priority.erase(p->priority.begin());
        }
        p->priority.push_back(tuple<int,int,int>(nextpage, get<1>(p->priority[0]),0));
        p->priority.erase(p->priority.begin());
        return get<1>(p->priority[0]);
    }
    else{ // if not full size - emplace pair into vector and return index of next -1
        p->priority.push_back(tuple<int,int,int>(nextpage, p->priority.size(), 0));
        return p->priority.size()-1;
    }
}


#endif //WEIL_PROG4_PROG4_2ND_H
