//
// Created by halam on 15/06/2023.
//

#ifndef WET2DS_UNIONNODE_H
#define WET2DS_UNIONNODE_H
#include "Record.h"
class UnionNode {
public:
    int m_GroupID;
    int m_size;
    UnionNode *m_father;
    Record* m_record;
    int m_height;
    int m_col;
    explicit UnionNode(int groupid) : m_GroupID(groupid), m_size(1), m_father(nullptr),m_record(new Record()),m_height(0),m_col(0){}

    ~UnionNode() {
        delete m_record;
    };

};


#endif //WET2DS_UNIONNODE_H
