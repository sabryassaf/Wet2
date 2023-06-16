//
// Created by halam on 14/06/2023.
//

#ifndef WET2DS_HASHTABLE_H
#define WET2DS_HASHTABLE_H
#include "RankTree.h"
//#include "DynamicArray.h"
#define InitialSize 64

template <class Key, class Data>
class HashTable {

    RankTree<Key,Data>** m_TreeArr;
    int m_sizeArr;
    int m_sizeElem;
    double m_stressFactor;

public:
    HashTable();
    ~HashTable();
    bool insertToTable(Key key,Data data);
    bool Delete(int key);
    int HashFunction(int key);
    void ExpandHash ();
    void ShrinkHash ();
    Data findHash (const Key& key);

};

template<class Key,class Data>
HashTable<Key,Data>::HashTable() : m_TreeArr(new RankTree<Key,Data>*[InitialSize]),m_sizeArr(InitialSize),m_sizeElem(0),m_stressFactor(0){
    for(int i = 0 ; i < m_sizeArr ; i++){
        m_TreeArr[i] = new RankTree<Key,Data>;
    }
}

template<class Key,class Data>
HashTable<Key,Data>::~HashTable(){
    for(int i = 0 ; i < m_sizeArr ; i++){
        delete m_TreeArr[i];
    }
    delete[] m_TreeArr;
}

template<class Key,class Data>
int HashTable<Key,Data>::HashFunction(int ID) {
    return (ID)%(m_sizeArr);
}

template<class Key,class Data>
void HashTable<Key,Data>::ExpandHash(){

    int expandedSize = 2*(m_sizeArr);
    auto* newArray = new RankTree<Key,Data>*[expandedSize];
    int oldSize =m_sizeArr;
    m_sizeArr = expandedSize;
    for(int i = 0 ; i < 2 * oldSize ; i++){
        newArray[i] = new RankTree<Key,Data>;
    }
    for (int i = 0; i < oldSize; ++i) {

        try {
            auto *arr = new Key [newArray[i]->getSize()];
            newArray[i]->ReverseInOrderArrayKeys(arr);
            for (int j = 0; j < newArray[i]->getSize(); j++) {
                int newIndex = HashFunction(arr[j]);
                Data temp=m_TreeArr[i]->Find(arr[j]);
                newArray[newIndex]->Insert(arr[j], temp);
                m_TreeArr[i]->Remove(arr[j]);
            }
            delete[] arr;
        }
        catch (const std::bad_alloc &) {
            delete[] newArray;
            throw;
        }
    }
        for(int i = 0 ; i < oldSize ; i++){
            delete m_TreeArr[i];
        }

        delete[] m_TreeArr; // check if this is the correct way
        m_TreeArr = newArray;
        m_stressFactor = (double) m_sizeElem / m_sizeArr;
    }

template<class Key,class Data>
bool HashTable<Key,Data>::insertToTable(Key key,Data data){

    int index = HashFunction(key);
    if(m_TreeArr[index]->Find(key))
        return false;
    m_TreeArr[index] ->Insert(key,data);
    m_sizeElem++;
    m_stressFactor=(double) m_sizeElem/m_sizeArr;
    if (m_stressFactor > 0.5) {
        ExpandHash();
    }
    return true;
}
template<class Key,class Data>
Data HashTable<Key,Data>::findHash (const Key& key){
    int index = (key)%(m_sizeArr);
    return m_TreeArr[index]->Find(key);
}



#endif //WET2DS_HASHTABLE_H
