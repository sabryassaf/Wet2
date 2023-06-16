//
// Created by halam on 15/06/2023.
//

#include "GroupUnion.h"

GroupUnion::GroupUnion(int k) : m_groupsArr(nullptr), m_Arrsize(k)
{
    for(int i=0;i<m_Arrsize;i++)
        m_groupsArr[i] = new UnionNode(i);
}

GroupUnion::~GroupUnion() {
    for(int i=0 ; i<m_Arrsize ; i++) {
        delete m_groupsArr[i];
    }
    delete[] m_groupsArr;
}

UnionNode* GroupUnion::FindHead(int group_id) {  // the number of col that id in
    UnionNode* temp = m_groupsArr[group_id];
    while(temp->m_father != nullptr)
    {
        temp = temp->m_father;
    }
    UnionNode* head = temp;
    temp = m_groupsArr[group_id];
    UnionNode* iterator = temp;
    //compress the path
    while(temp != head)
    {
        temp = temp->m_father;
        iterator->m_father = head;
        iterator = temp;
    }
    return head;
}
int GroupUnion::Find(int group_id) {
    return FindHead(group_id)->m_GroupID;
}

void GroupUnion::UnionRecords(int groupRecord1, int groupRecord2) {
    UnionNode *first = FindHead(groupRecord1);
    UnionNode *second = FindHead(groupRecord2);

    if (first->m_GroupID == second->m_GroupID) { // means that the two groups had been merged before
        return;
    }
    UnionNode* bigger = (first->m_size >= second->m_size) ? first : second;
    UnionNode* smaller = (first->m_size < second->m_size) ? first : second;
    for(int i =0 ; i<first->m_size ;i++){


    }
    smaller->m_father = bigger;
    bigger->m_size += smaller->m_size;
}


    void GroupUnion::Union(int group1, int group2) {
        UnionRecords(Find(group1), Find(group2));
}

