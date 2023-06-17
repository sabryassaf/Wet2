//
// Created by halam on 14/06/2023.
//

#ifndef WET2DS_RECORD_H
#define WET2DS_RECORD_H


class Record
{
    int m_stock;
    int m_sales;
    int m_height;

public:

    Record() : m_stock(0), m_sales(0), m_height(0)

    int getHeight() const
    {
        return m_height;
    }

    void addHeight(int add)
    {
        m_height += add;
    }

    int getStocks() const
    {
        return m_stock;
    }

    void setStocks(int stocks)
    {
        m_stocs = stocks;
    }
};


#endif //WET2DS_RECORD_H
