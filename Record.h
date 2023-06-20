//
// Created by halam on 14/06/2023.
//

#ifndef WET2DS_RECORD_H
#define WET2DS_RECORD_H


class Record
{

    int m_sales;

public:
    int m_stocks;
    int m_r;
    int m_column;
//    int m_height;

    Record(int id) : m_sales(0), m_stocks(0), m_r(0), m_column(id)
    {}


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
