//
// Created by halam on 14/06/2023.
//
#ifndef WET2DS_UNIONFIND_H
#define WET2DS_UNIONFIND_H

#include "HashTable.h"
#include "RankTree.h"
#include "Record.h"
template<class Key,class Data>
class UnionNode{
public:

    Record* m_record;
    RankTree<Key,Data> m_tree;
    UnionNode* m_parent;



};


class UnionFind{
    HashTable<int,UnionNode<int,Record>> records;

public:

    UnionFind();
    UnionNode<int,Record>* Find(int recordId);
    UnionNode<int,Record>* findRecordNode(int recordID);
    UnionNode<int,Record>* Union(Record* rec1,Record* rec2);
    void DestroyNodes();


};

#endif //WET2DS_UNIONFIND_H
