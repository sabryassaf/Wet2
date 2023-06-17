//
// Created by halam on 14/06/2023.
//

#include "Record.h"

Record::Record()=default;

Record::Record(int RecordId,int copys) : m_rId(RecordId), m_copys(copys), m_purchases(0)
{}


int Record::getRId() const
{
    return m_rId;
}

void Record::addAPurchase()
{
    m_purchases ++;
}

int Record::getPurchases() const
{
    return m_purchases;
}
