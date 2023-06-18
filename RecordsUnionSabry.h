//
// Created by soso_ on 6/17/2023.
//

#ifndef CUSTOMER_H_RECORDSUNIONSABRY_H
#define CUSTOMER_H_RECORDSUNIONSABRY_H

#include "Record.h"


class UnionFindRecords
{
private:
    int *m_parent;
    int *m_size;
    Record **m_recordStocks;

public:
    UnionFindRecords() = default;

    UnionFindRecords(int *new_records_stocks, int size)
    {
        m_parent = new int[size];
        m_size = new int[size];
        m_recordStocks = new Record *[size];
        for (int i = 0; i < size; i++)
        {
            m_parent[i] = i;
            m_size[i] = 1;
            m_recordStocks[i] = new Record(i);
            m_recordStocks[i]->m_stocks = new_records_stocks[i];

        }
    }

    ~UnionFindRecords()
    {
        delete[] m_parent;
        delete[] m_size;
        delete[] m_recordStocks;
    }

    Record *getRecordPointer(int r_id)
    {
        return m_recordStocks[r_id];
    }

    int getHeightOfRecords(int r_id) const
    {
        int root = r_id;
        int height = 0;
        while (root != m_parent[root])
        {
            height += m_recordStocks[root]->m_r;
            root = m_parent[root];
        }
        height += m_recordStocks[root]->m_r;
        return height;
    }

    int find(int r_id)
    {
        int totalHeight = 0;
        int temp = r_id;
        int root = m_parent[temp];
        /// first we find the root of the r_id and while going over the nodes we sum all the height not including the parent of the union
        while (temp != root)
        {
            totalHeight += m_recordStocks[temp]->m_r;
            temp = root;
            root = m_parent[temp];
        }
        /// in the second time we hold the sum of parameters in the search path till the current node without it and we delete it from the total height;
        int reverseSub = 0;
        while (root != m_parent[r_id])
        {
            int tempNext = m_parent[r_id];
            m_parent[r_id] = root;
            m_recordStocks[r_id]->m_r = totalHeight - reverseSub;
            reverseSub += m_recordStocks[r_id]->m_r;
            r_id = tempNext;
        }
        return root;
    }

    int getColumn(int r_id) const
    {
        return m_recordStocks[r_id]->m_column;
    }


    void unite(int first_records, int second_records)
    {
        int group1 = find(first_records);
        int group2 = find(second_records);
        if (group1 == group2)
        {
            return;

        } else
        {
            if (m_size[group2] >= m_size[group1])
            {
                m_size[group2] += m_size[group1];
                m_size[group1] = 0;
                m_parent[group1] = group2;
                m_recordStocks[group1]->m_column = m_recordStocks[group2]->m_column;
                m_recordStocks[group1]->m_r =
                        m_recordStocks[group1]->m_r + m_recordStocks[group2]->m_stocks - m_recordStocks[group2]->m_r;
                m_recordStocks[group2]->m_stocks+=m_recordStocks[group1]->m_stocks;
            } else
            {
                m_size[group1] += m_size[group2];
                m_size[group2] = 0;
                m_parent[group2] = group1;
                m_recordStocks[group1]->m_column = m_recordStocks[group2]->m_column;
                m_recordStocks[group1]->m_r = m_recordStocks[group1]->m_r + m_recordStocks[group2]->m_stocks;
                m_recordStocks[group2]->m_r = m_recordStocks[group2]->m_r - m_recordStocks[group1]->m_r;
                m_recordStocks[group1]->m_stocks += m_recordStocks[group2]->m_stocks;
            }
        }
    }

    bool alreadyOnTop(int r_id1, int r_id2)
    {
        if (find(r_id1) == find(r_id2))
        {
            return true;
        }
        return false;
    }
};

#endif //CUSTOMER_H_RECORDSUNIONSABRY_H



