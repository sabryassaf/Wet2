//
// Created by halam on 15/06/2023.
//

#ifndef WET2DS_GROUPUNION_H
#define WET2DS_GROUPUNION_H
#include "UnionNode.h"

class GroupUnion {

    UnionNode** m_groupsArr;
    int m_Arrsize;

    explicit GroupUnion(int k);
    ~GroupUnion();
    int Find(int group_id);
    void Union(int group1, int group2);


};


#endif //WET2DS_GROUPUNION_H
