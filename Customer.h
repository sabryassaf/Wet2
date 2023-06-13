//
// Created by soso_ on 6/13/2023.
//

#ifndef WET_2_CUSTOMER_H
#define WET_2_CUSTOMER_H

class Customer
{
private:
    int m_id;
    int m_phoneNumber;
    bool m_VIP;


public:
    Customer(int id, int phoneNumber, bool isVIP) : m_id(id), m_phoneNumber(phoneNumber), m_VIP(isVIP)
    {}

};

#endif //WET_2_CUSTOMER_H
