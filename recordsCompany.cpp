//
// Created by soso_ on 6/13/2023.
//


#include "recordsCompany.h"

RecordsCompany::RecordsCompany()
        : m_CustomersTable(new( HashTable<int, Customer *>)), m_RecordsGroup(new UnionFindRecords()),
          m_VipCustomersTree(new RankTree<int, Customer *>), m_totalNumberOfRecords(64)
{}

StatusType RecordsCompany::newMonth(int *records_stocks, int number_of_records)
{
    if (number_of_records < 0)
    {
        return StatusType::INVALID_INPUT;
    }
    try
    {
        delete m_RecordsGroup;
        m_RecordsGroup = new UnionFindRecords(records_stocks, number_of_records);
        m_totalNumberOfRecords = number_of_records;
        m_VipCustomersTree->resetNodeForNewMonth(m_VipCustomersTree->getRoot());
        return StatusType::SUCCESS;
    }
    catch (const std::exception &e)
    {
        return StatusType::ALLOCATION_ERROR;
    }
}

StatusType RecordsCompany::addCostumer(int c_id, int phone)
{
    if (c_id < 0 || phone < 0)
    {
        return INVALID_INPUT;
    }
    if (m_CustomersTable->findHash(c_id))
    {
        return ALREADY_EXISTS;
    }
    try
    {
        auto *newCustomer = new Customer(c_id, phone, false);
        if (m_CustomersTable->insertToTable(c_id, newCustomer))
        {
            return StatusType::SUCCESS;
        }
        delete newCustomer;
        return StatusType::ALLOCATION_ERROR;
    }
    catch (const std::bad_alloc &)
    {
        return StatusType::ALLOCATION_ERROR;
    }
}

Output_t<int> RecordsCompany::getPhone(int c_id)
{
    if (c_id < 0)
    {
        return StatusType::INVALID_INPUT;
    }
    Customer *requestedCustomer = m_CustomersTable->findHash(c_id);
    if (requestedCustomer)
    {
        return requestedCustomer->getPhone();
    }
    return StatusType::DOESNT_EXISTS;
}

StatusType RecordsCompany::makeMember(int c_id)
{
    if (c_id < 0)
    {
        return StatusType::INVALID_INPUT;
    }
    Customer *requestedCustomer = m_CustomersTable->findHash(c_id);
    if (requestedCustomer)
    {
        if (requestedCustomer->VIPStatus())
        {
            return StatusType::ALREADY_EXISTS;
        }
        requestedCustomer->makeVIP();
        m_VipCustomersTree->Insert(c_id, requestedCustomer);
        return StatusType::SUCCESS;
    }
    return StatusType::DOESNT_EXISTS;
}

Output_t<bool> RecordsCompany::isMember(int c_id)
{
    if (c_id < 0)
    {
        return StatusType::INVALID_INPUT;
    }
    Customer *requestedCustomer;
    requestedCustomer = m_CustomersTable->findHash(c_id);
    if (requestedCustomer)
    {
        return requestedCustomer->VIPStatus();
    }
    return StatusType::DOESNT_EXISTS;
}

/*Need to add a way to find the record and then t = the number of purchases
 *
 * should we remove a copy when we do a purchase? need to ask*/
StatusType RecordsCompany::buyRecord(int c_id, int r_id)
{
    if (c_id < 0 || r_id < 0)
    {
        return StatusType::INVALID_INPUT;
    }
    if (r_id >= m_totalNumberOfRecords)
    {
        return StatusType::DOESNT_EXISTS;
    }
    Customer *requestedCustomer;
    requestedCustomer = m_CustomersTable->findHash(c_id);
    Record *requestedRecord;
    requestedRecord = m_RecordsGroup->getRecordPointer(r_id);
    if (requestedCustomer && requestedRecord)
    {
        if (requestedCustomer->VIPStatus())
        {
            requestedCustomer->addMonthlyDebt(100 + requestedRecord->getSales());
        }
        requestedRecord->addPurchase();
        return StatusType::SUCCESS;
    }
    return StatusType::DOESNT_EXISTS;
}

Output_t<double> RecordsCompany::getExpenses(int c_id)
{
    if (c_id < 0)
    {
        return StatusType::INVALID_INPUT;
    }
    Customer *requestedCustomer;
    requestedCustomer = m_VipCustomersTree->Find(c_id);
    if (requestedCustomer)
    {
        return requestedCustomer->getMonthlyPayment() - m_VipCustomersTree->SumExtra(c_id);
    }
    return StatusType::DOESNT_EXISTS;
}

StatusType RecordsCompany::addPrizeAUX(int c_id, double amount, AVLNode<int, Customer *> *node, int condition)
{
    if (node == nullptr)
    {
        return StatusType::SUCCESS;
    }
    if (condition == 0)
    {
        if (c_id > node->getKey())
        {
            node->UpdateExtra(amount);
            return addPrizeAUX(c_id, amount, node->getRightChild(), 1);
        }
        if (c_id == node->getKey())
        {
            node->UpdateExtra(amount);
            if (node->getRightChild())
            {
                node->getRightChild()->UpdateExtra(-amount);
                return StatusType::SUCCESS;
            }
            return StatusType::SUCCESS;
        }
        return addPrizeAUX(c_id, amount, node->getLeftChild(), 0);

    }

    if (condition == 1)
    {
        if (c_id > node->getKey())
        {
            return addPrizeAUX(c_id, amount, node->getRightChild(), 1);
        }
        if (c_id == node->getKey())
        {
//            node->UpdateExtra(amount);
            if (node->getRightChild())
            {
                node->getRightChild()->UpdateExtra(-amount);
                return StatusType::SUCCESS;
            }
            return StatusType::SUCCESS;
        }
        if (c_id < node->getKey())
        {
            node->UpdateExtra(-amount);
            return addPrizeAUX(c_id, amount, node->getLeftChild(), 0);

        }
    }
//    if (condition == 3)
//    {
//        if (c_id > node->getKey())
//        {
//            node->UpdateExtra(amount);
//            return addPrizeAUX(c_id, amount, node->getRightChild(), 1);
//        }
//        if (c_id == node->getKey())
//        {
//            node->UpdateExtra(amount);
//            if (node->getLeftChild())
//            {
//                node->getLeftChild()->UpdateExtra(-amount);
//                return StatusType::SUCCESS;
//            }
//            return StatusType::SUCCESS;
//        }
//        if (c_id < node->getKey())
//        {
//            return addPrizeAUX(c_id, amount, node->getLeftChild(), 0);
//        }
//    }
    return StatusType::FAILURE;

}


StatusType RecordsCompany::addPrize(int c_id1, int c_id2, double amount)
{
    if (c_id1 < 0 || c_id2 < c_id1 || amount <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    if (m_VipCustomersTree->Find(c_id1))
    {
        c_id1--;
    }
    if (m_VipCustomersTree->Find(c_id2))
    {
        c_id2--;
    }

    if (RecordsCompany::addPrizeAUX(c_id2, amount, this->m_VipCustomersTree->getRoot(), 0) == StatusType::SUCCESS &&
        RecordsCompany::addPrizeAUX(c_id1 , -amount, this->m_VipCustomersTree->getRoot(), 0) == StatusType::SUCCESS)
        return StatusType::SUCCESS;
    return StatusType::FAILURE;

}

StatusType RecordsCompany::putOnTop(int r_id1, int r_id2)
{
    if (r_id1 < 0 || r_id2 < 0)
    {
        return StatusType::INVALID_INPUT;
    }
    if (r_id1 >= m_totalNumberOfRecords || r_id2 >= m_totalNumberOfRecords)
    {
        return StatusType::DOESNT_EXISTS;
    }
    if (m_RecordsGroup->alreadyOnTop(r_id1, r_id2))
    {
        return StatusType::FAILURE;
    }
    m_RecordsGroup->unite(r_id1, r_id2);
    return StatusType::SUCCESS;

}

StatusType RecordsCompany::getPlace(int r_id, int *column, int *hight)
{
    if (column == NULL || hight == NULL || r_id < 0)
    {
        return StatusType::INVALID_INPUT;
    }
    if (r_id >= m_totalNumberOfRecords)
    {
        return StatusType::DOESNT_EXISTS;
    }
    int temp = m_RecordsGroup->find(r_id);
    int realColumn = (m_RecordsGroup->getColumn(temp));
    *column = realColumn;
    int tempHeight = m_RecordsGroup->getHeightOfRecords(r_id);
    *hight = tempHeight;
    return StatusType::SUCCESS;

}

RecordsCompany::~RecordsCompany()
{
    delete m_RecordsGroup;
    delete m_CustomersTable;
}

