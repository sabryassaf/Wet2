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
    Record *m_recordStocks;

public:
    UnionFindRecords(int *new_records_stocks, int size)
    {
        m_parent = new int[size];
        m_size = new int[size];
        m_recordStocks = new Record[size];
        for (int i = 0; i < size; i++)
        {
            m_parent[i] = i;
            m_size[i] = 1;
            m_recordStocks[i].setStocks(new_records_stocks[i]);

        }
    }

    ~UnionFindRecords()
    {
        delete[] m_parent;
        delete[] m_size;
        delete[] m_recordStocks;
    }

    int find(int r_id)
    {
        int totalHeight = 0;
        int temp = r_id;
        int root = m_parent[temp];
        /// first we find the root of the r_id and while going over the nodes we sum all the height not including the parent of the union
        while (temp != root)
        {
            totalHeight += m_recordStocks[temp].getHeight();
            temp = root;
            root = m_parent[temp];
        }
        /// in the second time we hold the sum of parameters in the search path till the current node without it and we delete it from the total height;
        int reverseSub = 0;
        while (root != m_parent[r_id])
        {
            reverseSub += m_recordStocks[r_id].;
            int tempNext = m_parent[r_id];
            m_parent[r_id] = root;
            m_recordStocks[r_id].setHeight(totalHeight - reverseSub);
            r_id = tempNext;
        }
        return root;
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
            m_size[group2] += m_size[group1];
            m_size[group1] = 0;
            m_parent[group1] = group2;
            m_recordStocks[group1].setHeight(m_recordStocks[group2].getStocks());

        }
    };

#endif //CUSTOMER_H_RECORDSUNIONSABRY_H



