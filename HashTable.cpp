#include "HashTable.h"

template<class Key,class Data>
HashTable<Key,Data>::HashTable() : m_TreeArr(new DynamicArray<Key,Data>){}

template<class Key,class Data>
HashTable<Key,Data>::~HashTable() {
    delete m_TreeArr;
}

template<class Key,class Data>
int HashTable<Key,Data>::HashFunction(int ID) {
    return (ID)%(m_TreeArr->m_arraySize);
}

template<class Key,class Data>
void HashTable<Key,Data>::ExpandHash(){
    int expandedSize = 2*(m_TreeArr.m_size);
        auto* newArray = new DynamicArray<Key,Data>(expandedSize);
        int oldSize = m_TreeArr->m_size;
        m_TreeArr->m_size = expandedSize;
        for (int i = 0; i < oldSize; ++i){
            AVLNode<Key,Data>* currentNode = m_TreeArr->m_array[i].getHead();
            while(currentNode != nullptr){
                int newIndex = hashFunction(m_TreeArr.m_array[i]);
                try {
                    newArray->insertData(currentNode->m_key, currentNode->m_data, newIndex);
                }catch (std::bad_alloc&){
                    delete newArray;
                    throw;
                }
                (newArray->m_size)++;
                currentNode = currentNode->m_next;
            }
        }

    delete m_TreeArr;
    m_TreeArr = newArray;
}
template<class Key,class Data>
void HashTable<Key,Data>::ShrinkHash(){
    int shrinkedSize = (m_TreeArr.m_size)/2;
    auto* newArray = new DynamicArray<Key,Data>(shrinkedSize);
    int oldSize = m_TreeArr->m_size;
    m_TreeArr->m_size = shrinkedSize;
    for (int i = 0; i < oldSize; ++i){
        AVLNode<Key,Data>* currentNode = m_TreeArr->m_array[i].getHead();
        while(currentNode != nullptr){
            int newIndex = hashFunction(m_TreeArr.m_array[i]);
            try {
                newArray->insertData(currentNode->m_key, currentNode->m_data, newIndex);
            }catch (std::bad_alloc&){
                delete newArray;
                throw;
            }
            (newArray->m_size)++;
            currentNode = currentNode->m_next;
        }
    }
    delete m_TreeArr;
    m_TreeArr = newArray;
}
template<class Key,class Data>
bool HashTable<Key,Data>::insertToTable(Key key,Data data){
    if (m_TreeArr->m_size >= 3*m_TreeArr->m_size) {
        ExpandHash();
    }
    if ((m_TreeArr->m_size <= (0.25 * m_TreeArr->m_size)) && (m_TreeArr->m_size > INITIAL_SIZE)) {
        ShrinkHash();
    }
    int index = hashFunction(key);
    AVLNode<Key,Data>* insertion = m_TreeArr->insertData(key, data, index);
    if (insertion == nullptr){
        return false;
    }else {
        return true;
    }
}
template<class Key,class Data>
Data HashTable<Key,Data>::find (Key key){
    int index = (key)%(m_TreeArr.m_size);
    Data temp = m_TreeArr->getData(key, index);
    return temp;
}
