//
// Created by soso_ on 6/13/2023.
//


#include "recordsCompany.h"

StatusType RecordsCompany::addPrizeAUX(int c_id, double amount, AVLNode<int, Customer *> *node, int condition)
{
    if (condition == 0)
    {
        if (c_id > node->getKey())
        {
            node->updatePrize(amount);
            return addPrizeAUX(c_id, amount, node->getRightChild(), 1);
        }
        if (c_id == node->getKey())
        {
            node->updatePrize(amount);
            if (node->getRightChild())
            {
                node->getRightChild()->updatePrize(-amount);
                return StatusType::SUCCESS;
            }
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
            node->updatePrize(amount);
            if (node->getRightChild())
            {
                node->getRightChild()->updatePrize(-amount);
                return StatusType::SUCCESS;
            }
        }
        if (c_id < node->getKey())
        {
            node->updatePrize(-amount);
            return addPrizeAUX(c_id, amount, node->getLeftChild(), 3);

        }
    }
    if (condition == 3)
    {
        if (c_id > node->getKey())
        {
            node->updatePrize(amount);
            return addPrizeAUX(c_id, amount, node->getRightChild(), 1);
        }
        if (c_id == node->getKey())
        {
            node->updatePrize(amount);
            if (node->getRightChild())
            {
                node->getRightChild()->updatePrize(-amount);
                return StatusType::SUCCESS;
            }
        }
        if (c_id < node->getKey())
        {
            return addPrizeAUX(c_id, amount, node->getLeftChild(), 0);
        }
    }
    return StatusType::FAILURE;

}


StatusType RecordsCompany::addPrize(int c_id1, int c_id2, double amount)
{
    if (RecordsCompany::addPrizeAUX(c_id2, amount, this->m_VipCustomersTree.getRoot(), 0) == StatusType::SUCCESS &&
        RecordsCompany::addPrizeAUX(c_id1 - 1, -amount, this->m_VipCustomersTree.getRoot(), 0) == StatusType::SUCCESS)
        return StatusType::SUCCESS;
    return StatusType::FAILURE;

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
        m_VipCustomersTree.Insert(c_id, requestedCustomer);
    }
    return StatusType::FAILURE;
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

/*Need to add a way to find the record and then t = the number of purchases*/
StatusType RecordsCompany::buyRecord(int c_id, int r_id)
{
    if (c_id < 0 || r_id < 0)
    {
        return StatusType::INVALID_INPUT;
    }
    Customer *requestedCustomer;
    requestedCustomer = m_CustomersTable->findHash(c_id);
    Record *requestedRecord;
    requestedRecord = m_RecordsGroup->Find(r_id);
    if (requestedCustomer && m_numberOfRecords >= r_id)
    {
        if (requestedCustomer->VIPStatus())
        {
            requestedCustomer->addMonthlyDebt(100 + requestedRecord->getPurchases());
        }
        requestedRecord->addAPurchase();
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
    requestedCustomer = m_VipCustomersTree.Find(c_id);
    if (requestedCustomer)
    {
        return requestedCustomer->getMonthlyPayment();
    }
    return StatusType::DOESNT_EXISTS;
}




