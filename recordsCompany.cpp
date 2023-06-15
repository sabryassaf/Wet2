//
// Created by soso_ on 6/13/2023.
//


#include "recordsCompany.h"

StatusType
RecordsCompany::addPrizeAUX(int c_id, double amount, AVLNode<int, Customer *> *node, int condition)
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

}


StatusType RecordsCompany::addPrize(int c_id1, int c_id2, double amount)
{
    RecordsCompany::addPrizeAUX(c_id2, amount, this->m_CustomersTable.getRoot(), 0);
    RecordsCompany::addPrizeAUX(c_id1-1, -amount, this->m_CustomersTable.getRoot(), 0);
}
