//
// Created by halam on 14/06/2023.
//

#ifndef WET2DS_RECORD_H
#define WET2DS_RECORD_H


class Record
{
private:
    int m_rId;
    int m_copys;
    int m_purchases;

public:

    Record();

    Record(int RecordId, int copys);

    int getRId() const;

    void addAPurchase();

    int getPurchases() const;
};


#endif //WET2DS_RECORD_H
