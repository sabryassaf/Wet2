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
    int m_monthlyDebt;
    int m_prize;

public:
    Customer(int id, int phoneNumber, bool isVIP) : m_id(id), m_phoneNumber(phoneNumber), m_VIP(isVIP),
                                                    m_monthlyDebt(0), m_prize(0)
    {}

    ~Customer() = default;

    int getId() const
    {
        return m_id;
    }

    int getPhone() const
    {
        return m_phoneNumber;
    }

    bool VIPStatus() const
    {
        return m_VIP;
    }

    void makeVIP()
    {
        m_VIP = true;
    }

    void addMonthlyDebt(int payment)
    {
        m_monthlyDebt += payment;
    }

    int getMonthlyPayment() const
    {
        return m_monthlyDebt;
    }

    void updatePrize(int money)
    {
        m_prize += money;
    }

    int getPrize() const
    {
        return m_prize;
    }
};

#endif //WET_2_CUSTOMER_H
