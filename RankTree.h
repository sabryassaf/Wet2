//
// Created by halam on 15/05/2023.
//

#ifndef STREAMINGDBA1_CPP_RankTree_H
#define STREAMINGDBA1_CPP_RankTree_H

#include <iostream>
#include "AVLNode.h"
#include "utilesWet2.h"


template<class Key, class Data>
class RankTree
{
private:

    int m_size;
    AVLNode<Key, Data> *m_root;
    AVLNode<Key, Data> *m_max;

    AVLNode<Key, Data> *RollingRR(AVLNode<Key, Data> *node);

    AVLNode<Key, Data> *RollingLL(AVLNode<Key, Data> *node);

    AVLNode<Key, Data> *RollingLR(AVLNode<Key, Data> *node);

    AVLNode<Key, Data> *RollingRL(AVLNode<Key, Data> *node);

    AVLNode<Key, Data> *FindNodeAux(const Key &key, AVLNode<Key, Data> *node);

    AVLNode<Key, Data> *DeleteNodeAux(const Key &key, AVLNode<Key, Data> *node);

    AVLNode<Key, Data> *InsertNodeAux(Key &key, Data &data, AVLNode<Key, Data> *node);

    AVLNode<Key, Data> *UpdateAndBalance(AVLNode<Key, Data> *node);

    void ReverseInOrderArrayAux(AVLNode<Key, Data> *node, Data *InOrderArray, int *index);

    AVLNode<Key,Data>* SelectAux(AVLNode<Key,Data>* node , int rank);

    void AddExtraRangeAux(AVLNode<Key, Data> *node,Key maxKey,double extra,  int rightcounter);

    double SumExtraAux(const Key &key, AVLNode<Key, Data> *node,double sum) const;

    void ReverseInOrderArrayKeysAux(AVLNode<Key, Data> *node, Key *InOrderArray, int *index);


public:

    void FreeData(AVLNode<Key, Data> *node);

    void DeleteTree(AVLNode<Key, Data> *node);

    RankTree() : m_size(0), m_root(nullptr), m_max(nullptr)
    {}

    RankTree(const RankTree &other) = delete;

    RankTree &operator=(const RankTree &other) = delete;

    virtual ~RankTree()
    {
        DeleteTree(m_root);

    }

    int getSize() const;

    StatusType Insert(Key &key, Data &data);

    StatusType Remove(const Key &key);

    Data Find(const Key &key);

    AVLNode<Key, Data> *getRoot() const;

    AVLNode<Key, Data> *getMax() const;

    void ReverseInOrderArray(Data *InOrderArray);

    bool EmptyTree() const;

    void setNewMax();

    AVLNode<Key,Data>* Select( int rank) ;

    void AddExtraRange(Key maxKey,double extra);

    double SumExtra(const Key &key) const; // before inset new element we want to initial the m_extra as minus the ones in its path

    void ReverseInOrderArrayKeys(Key *InOrderArray);
  };
////////////////////// Implementations for private//////////////



template<class Key, class Data>

AVLNode<Key, Data> *RankTree<Key, Data>::getRoot() const
{
    return this->m_root;
}

template<class Key, class Data>

AVLNode<Key, Data> *RankTree<Key, Data>::getMax() const
{
    return this->m_max;
}

template<class Key, class Data>
AVLNode<Key, Data> *RankTree<Key, Data>::RollingLL(AVLNode<Key, Data> *node)
{
    AVLNode<Key, Data> *RotateNode = node->getLeftChild();
    double tempOld = node->getExtra(); // for the old root
    double tempNew = RotateNode->getExtra(); // for the new root
    node->setLeftChild(RotateNode->getRightChild());
    if( node->getLeftChild())
       node->getLeftChild() ->UpdateExtra(tempNew);
    if (node->getParent())
    {
        if (node->getParent()->getLeftChild() == node)
        {
            node->getParent()->setLeftChild(RotateNode);
        } else
        {
            node->getParent()->setRightChild(RotateNode);
        }
    }
    RotateNode->setParent(node->getParent());
    RotateNode->setRightChild(node);
    RotateNode->UpdateExtra(tempOld);
    node->UpdateExtra(- (RotateNode->getExtra()));
    if (this->m_root == node)
    {
        this->m_root = RotateNode;
    }
    node->updateParameters();
    RotateNode->updateParameters();
    return RotateNode;

}

template<class Key, class Data>
AVLNode<Key, Data> *RankTree<Key, Data>::RollingRR(AVLNode<Key, Data> *node)
{
    AVLNode<Key, Data> *RotateNode = node->getRightChild();
    double tempOld = node->getExtra(); // for the old root
    double tempNew = RotateNode->getExtra(); // for the new root
    node->setRightChild(RotateNode->getLeftChild());
    if (node->getRightChild())
        node->getRightChild() ->UpdateExtra(tempNew);


    if (node->getParent())
    {
        if (node->getParent()->getLeftChild() == node)
        {
            node->getParent()->setLeftChild(RotateNode);
        } else
        {
            node->getParent()->setRightChild(RotateNode);
        }
    }
    RotateNode->setParent(node->getParent());
    RotateNode->setLeftChild(node);
    RotateNode->UpdateExtra(tempOld);
    node->UpdateExtra(- (RotateNode->getExtra()));
    if (this->m_root == node)
    {
        this->m_root = RotateNode;
    }
    node->updateParameters();
    RotateNode->updateParameters();
    return RotateNode;
}

template<class Key, class Data>
AVLNode<Key, Data> *RankTree<Key, Data>::RollingRL(AVLNode<Key, Data> *node)
{
    AVLNode<Key, Data> *RotateNode = node->getRightChild();
    node->setRightChild(RollingLL(RotateNode));
    return RollingRR(node);
}

template<class Key, class Data>
AVLNode<Key, Data> *RankTree<Key, Data>::RollingLR(AVLNode<Key, Data> *node)
{
    AVLNode<Key, Data> *RotateNode = node->getLeftChild();
    node->setLeftChild(RollingRR(RotateNode));
    return RollingLL(node);
}


template<class Key, class Data>
AVLNode<Key, Data> *RankTree<Key, Data>::FindNodeAux(const Key &key, AVLNode<Key, Data> *node)
{
    if (!node)
        return nullptr;


    if (key == node->getKey())
        return node;


    if (key > node->getKey())
        return FindNodeAux(key, node->getRightChild());


    if (key < node->getKey())
        return FindNodeAux(key, node->getLeftChild());


    return nullptr;
}

template<class Key, class Data>
AVLNode<Key, Data> *RankTree<Key, Data>::UpdateAndBalance(AVLNode<Key, Data> *node)
{
    node->updateParameters();

    if(node->getBalanceFactor()==-2 && node->getRightChild()->getBalanceFactor()>0 )
        return RollingRL(node);

    if(node->getBalanceFactor()==-2 && node->getRightChild()->getBalanceFactor()<=0 )
        return RollingRR(node);

    if(node->getBalanceFactor()==2 && node->getLeftChild()->getBalanceFactor()<0 )
        return RollingLR(node);

    if(node->getBalanceFactor()==2 && node->getLeftChild()->getBalanceFactor()>=0 )
        return RollingLL(node);
    // if we didn't commit any rolling we need to update the initial val of extra to gave us sum of 0

    return node;
}


template<class Key, class Data>
AVLNode<Key, Data> *RankTree<Key, Data>::DeleteNodeAux(const Key &key, AVLNode<Key, Data> *node)

{
    if (!node)
        return nullptr;

    if (node->getKey() == key)
    {
        if ((node->getLeftChild() == nullptr) && (node->getRightChild() == nullptr)) {
            if (m_root == node) {
                m_root = nullptr;
            }
            delete node;
            return nullptr;
        }
        else if ((node->getRightChild() == nullptr) && (node->getLeftChild())) //ONE CHILD ONLY
        {
            AVLNode<Key, Data> *tempNode;
            tempNode = node->getLeftChild();

            if (m_root == node) {
                m_root = tempNode;
                m_root->setParent(nullptr);
            } else{
                tempNode->setParent(node->getParent());
            }

            delete node;
            node = tempNode;
        }
        else if((node->getLeftChild() == nullptr) && node->getRightChild()){
            AVLNode<Key, Data> *tempNode;
            tempNode = node->getRightChild();
            if (m_root == node) {
                m_root = tempNode;
                m_root->setParent(nullptr);
            } else{
                tempNode->setParent(node->getParent());
            }

            delete node;
            node = tempNode;

        }
        else
        {
            AVLNode<Key, Data> *tempNode;
            tempNode = node->getRightChild();
            while (tempNode->getLeftChild()) {
                tempNode = tempNode->getLeftChild();
            }
            Key tempKey = tempNode->getKey();
            tempNode->setKey(node->getKey());
            node->setKey(tempKey);
            Data tempVal = tempNode->getData();
            tempNode->setData(node->getData());
            node->setData(tempVal);

            node->setRightChild(DeleteNodeAux(key, node->getRightChild()));
        }
    }
    else if (node->getKey() < key)
    {
        node->setRightChild(DeleteNodeAux(key, node->getRightChild()));
    }

    else if (node->getKey() > key)
    {
        node->setLeftChild(DeleteNodeAux(key, node->getLeftChild()));
    }

    node = UpdateAndBalance(node);
    return node;
}

template<class Key, class Data>
AVLNode<Key, Data> *RankTree<Key, Data>::InsertNodeAux(Key &key, Data &data, AVLNode<Key, Data> *node)
{
    if (node)

    {
        if (key > node->getKey())
        {
            node->setRightChild(InsertNodeAux(key, data, node->getRightChild()));
        }
        else if (key < node->getKey())
        {
            node->setLeftChild(InsertNodeAux(key, data, node->getLeftChild()));
        }
    }

    else
    {
        auto *newNode = new AVLNode<Key, Data>(key, data);
        if (!newNode )
            return nullptr;

        newNode->setHeight(0);
        if (!m_root)
        {
            m_root = newNode;
            m_max = newNode;
        }

        return newNode;
    }

    AVLNode<Key, Data> *balance = UpdateAndBalance(node);
    if (node == this->m_root)
    {
        this->m_root = balance;

    }

    return balance;
}

template<class Key, class Data>
void RankTree<Key, Data>::ReverseInOrderArrayAux(AVLNode<Key, Data> *node, Data *InOrderArray, int *index)
{
    if (!node)
        return;

    ReverseInOrderArrayAux(node->getRightChild(), InOrderArray, index);
    InOrderArray[(*index)++] = node->getData();
    ReverseInOrderArrayAux(node->getLeftChild(), InOrderArray, index);

}
template<class Key, class Data>
void RankTree<Key, Data>::ReverseInOrderArrayKeysAux(AVLNode<Key, Data> *node, Key *InOrderArray, int *index)
{
    if (!node)
        return;

    ReverseInOrderArrayKeysAux(node->getRightChild(), InOrderArray, index);
    InOrderArray[(*index)++] = node->getKey();
    ReverseInOrderArrayKeysAux(node->getLeftChild(), InOrderArray, index);

}
template<class Key, class Data>
void RankTree<Key, Data>::AddExtraRangeAux(AVLNode<Key, Data> *node,Key maxKey,double extra, int rightcounter){

    if (!node)
        return;


    if (maxKey == node->getKey()){

    }

    if (maxKey > node->getKey()) {
        if(rightcounter == 0) {
            node->UpdateExtra(extra);
            rightcounter=1;
        }
        FindNodeAux(maxKey, node->getRightChild(),rightcounter);

    }

    if (maxKey < node->getKey()) {
         if(rightcounter > 0) {
             node->UpdateExtra(-extra);
             FindNodeAux(maxKey, node->getLeftChild());
         }
    }
    return;
















}
////////////////////// Implementations for public//////////////

template<class Key, class Data>
void RankTree<Key, Data>::DeleteTree(AVLNode<Key, Data> *node)
{
    if (!node)
        return;


    DeleteTree(node->getRightChild());
    DeleteTree(node->getLeftChild());
    delete node;

}


template<class Key, class Data>
void RankTree<Key, Data>::FreeData(AVLNode<Key, Data> *node)
{
    if (!node )
        return;

    FreeData(node->getRightChild());
    FreeData(node->getLeftChild());
    delete node->getData();
}

template<class Key, class Data>
StatusType RankTree<Key, Data>::Insert(Key &key, Data &data)
{
    if (this->FindNodeAux(key, m_root))
        return StatusType::FAILURE;


    m_root = InsertNodeAux(key, data, m_root);
    if (!m_root)
        return StatusType::ALLOCATION_ERROR;
    if(SumExtra(key) != 0){
        FindNodeAux(key,m_root)->UpdateExtra(-SumExtra(key));
    }
    this->setNewMax();
    m_size++;
    return StatusType::SUCCESS;
}

template<class Key, class Data>
StatusType RankTree<Key, Data>::Remove(const Key &key)
{

    if (!FindNodeAux(key, m_root))
        return StatusType::FAILURE;

    m_max = nullptr;
    m_root = DeleteNodeAux(key, m_root);
    this->setNewMax();
    m_size--;
    return StatusType::SUCCESS;
}

template<class Key, class Data>
void RankTree<Key, Data>::setNewMax()
{
    if (!m_root)
    {
        m_max = nullptr;
        return;
    }
    AVLNode<Key, Data> *tmp = m_root;
    while (tmp->getRightChild() != nullptr)
    {
        tmp = tmp->getRightChild();
    }
    m_max = tmp;
}

template<class Key, class Data>
Data RankTree<Key, Data>::Find(const Key &key)
{
    AVLNode<Key, Data> *tmp = FindNodeAux(key, m_root);
    if (!tmp)
        return nullptr;

    return tmp->getData();
}


template<class Key, class Data>
int RankTree<Key, Data>::getSize() const
{
    return m_size;
}


template<class Key, class Data>
void RankTree<Key, Data>::ReverseInOrderArray(Data *InOrderArray)
{
    int index = 0;
    ReverseInOrderArrayAux(m_root, InOrderArray, &index);
}

template<class Key, class Data>
void RankTree<Key, Data>::ReverseInOrderArrayKeys(Key *InOrderArray)
{
    int index = 0;
    ReverseInOrderArrayKeysAux(m_root, InOrderArray, &index);
}



template<class Key, class Data>
bool RankTree<Key, Data>::EmptyTree() const
{
    return m_size <= 0;
}
/////////////// addedd///////////////
template<class Key, class Data>
double RankTree<Key, Data>:: SumExtraAux(const Key &key, AVLNode<Key, Data> *node, double sum) const
{

    if (!node)
        return 0;


    if (key == node->getKey())
        return sum+=node->getExtra();


    if (key > node->getKey())
        return SumExtraAux(key, node->getRightChild(),sum+=node->getExtra() );


    if (key < node->getKey())
        return SumExtraAux(key, node->getLeftChild(),sum+=node->getExtra());


    return 0;

}
// before inset new element we want to initial the m_extra as minus the ones in its path


template<class Key, class Data>
double RankTree<Key, Data>::SumExtra(const Key &key) const
{
    return SumExtraAux(key, m_root,0);
}


#endif //STREAMINGDBA1_CPP_RankTree_H
