//
// Created by halam on 14/06/2023.
//


#ifndef WET2DS_DYNAMICARRAY_H
#define WET2DS_DYNAMICARRAY_H
#include "RankTree.h"
const int INITIAL_SIZE = 10;

template <class Key, class Data>
class DynamicArray{
public:
    RankTree<Key,Data>* m_array;
    int m_size;
    int m_arraySize;

    AVLNode<Key, Data>* getElement(const Key& key, int index){
        AVLNode<Key, Data>* findElement = m_array[index].getHead();
        if (findElement == nullptr){
            return nullptr;
        }
        do {
            if (findElement->m_key == key){
                return findElement;
            }
            findElement = findElement->m_next;
        } while (findElement != nullptr);
        return nullptr;
    }

    DynamicArray(int startingSize = INITIAL_SIZE) : m_array(new RankTree<Key,Data>[startingSize]), m_size(0), m_arraySize(startingSize) {}
    ~DynamicArray() {
        delete[] m_array;
    }

    AVLNode<Key, Data>* insertData(const Key& key, const Data& data, int index) {
        m_size++;
        if (m_array[index].getHead() == nullptr) {
            return m_array[index].InsertInfo(key, data, nullptr);
        }else {
            AVLNode<Key, Data> *prevNode = m_array[index].getHead();
            while (prevNode->m_next != nullptr) {
                if (prevNode->m_key == key){
                    m_size--;
                    return nullptr;
                }
                prevNode = prevNode->m_next;
            }
            return m_array[index].InsertInfo(key, data, prevNode);
        }
    }

    bool removeData(const Key& key, int index){
        AVLNode<Key, Data>* toDelete = m_array[index]->getHead();
        do {
            if (toDelete->m_key == key){
                m_array[index].RemoveInfo(key);
                return true;
            }
            toDelete = toDelete->m_next;
        } while (toDelete->m_next != nullptr);
        return false;
    }


    Data getData(const Key& key, int index){
        AVLNode<Key,Data>* node = getElement(key, index);
        if (node == nullptr){
            return nullptr;
        }
        return node->m_info;
    }

};


#endif //WET2DS_DYNAMICARRAY_H
