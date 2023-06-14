//
// Created by halam on 14/06/2023.
//

#ifndef WET2DS_HASHTABLE_H
#define WET2DS_HASHTABLE_H
#include "RankTree.h"
#include "DynamicArray.h"
#define InitialSize 64

template <class Key, class Data>
class HashTable {

    DynamicArray<Key,Data> m_TreeArr;

public:
    HashTable();
    ~HashTable();
    bool insertToTable(Key key,Data data);
    bool Delete(int key);
    int HashFunction(int key);
    void ExpandHash ();
    void ShrinkHash ();
    Data find (Key key);

};


#endif //WET2DS_HASHTABLE_H
