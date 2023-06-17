//
// Created by halam on 14/06/2023.
//

#ifndef WET2DS_RECORD_H
#define WET2DS_RECORD_H


class Record
{
    int m_stocks;
    int m_sales;
    int m_height;

public:

    Record() : m_stocks(0), m_sales(0), m_height(0)
    {}

    int getHeight() const
    {
        return m_height;
    }

    void setHeight(int newHeight)
    {
        m_height = newHeight;
    }

    void addHeight(int add)
    {
        m_height += add;
    }

    int getStocks() const
    {
        return m_stocks;
    }

    void setStocks(int stocks)
    {
        m_stocks = stocks;
    }

    int getSales() const
    {
        return m_sales;
    }

    void addPurchase()
    {
        m_sales++;
    }
};


#endif //WET2DS_RECORD_H
