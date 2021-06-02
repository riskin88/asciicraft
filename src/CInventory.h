//
// Created by honza on 01.05.21.
//

#pragma once

#include <map>
#include <vector>
#include "CItem.h"

class CInventory {
public:
    /**
     * initializes items in m_Items
     */
    CInventory();

    /**
     * adds item into the inventory
     * @param item
     * @return true if item is a valid item
     */
    bool Add(EID item);

    /**
     * inserts record item->count into m_Invent
     * @param item
     * @param count
     * @return true if item had not existed
     */
    bool Insert(int item, int count);

    /**
     * tries to remove item from m_Invent
     * @param item
     * @return true if contained and removal was successful
     */
    bool Remove(EID item);

    /**
     * @param item
     * @return true if inventory contains this item
     */
    bool Has(EID item) const;

    /**
     * @return map with pairs items: currently owned->counts of these
     */
    std::map<CItem, int> GetItems() const;

private:
    /** all items with currently owned->count of these */
    std::map<EID, int> m_Invent;
    /** dictionary from item ID to the corresponding CItem with all info about the item */
    std::map<EID, CItem> m_Items;

};


