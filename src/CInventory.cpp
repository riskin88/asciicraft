//
// Created by honza on 01.05.21.
//

#include "CInventory.h"

bool CInventory::Add(EID item) {
    if (item == EID::NONE)
        return false;
    const auto &res = m_Invent.insert(std::pair<EID, int>(item, 1));
    // already has some if this item
    if (!res.second) {
        (res.first)->second++;
    }
    return true;
}

bool CInventory::Insert(int item, int count) {
    if (!m_Items.count((EID) item))
        throw std::invalid_argument("Unknown item!");
    return m_Invent.emplace((EID) item, count).second;
}

bool CInventory::Remove(EID item) {
    const auto &it = m_Invent.lower_bound(item);
    // item not found
    if (it == m_Invent.end() || it->first != item)
        return false;
    // no items of this kind left
    if (--(it->second) <= 0)
        m_Invent.erase(it);
    return true;
}

bool CInventory::Has(EID item) const {
    return m_Invent.count(item) == 1;
}

std::map<CItem, int> CInventory::GetItems() const {
    std::map<CItem, int> res;
    for (const auto &ref : m_Invent) {
        res.emplace(m_Items.at(ref.first), ref.second);
    }
    return res;
}

CInventory::CInventory() {
    m_Items.emplace(EID::PICKAXE, CItem{EID::PICKAXE, "Pickaxe", 0, 0});
    m_Items.emplace(EID::IRON, CItem{EID::IRON, "Iron", 0, 0});
    m_Items.emplace(EID::STEEL, CItem{EID::STEEL, "Steel", 0, 0});
    m_Items.emplace(EID::SPEAR, CItem{EID::SPEAR, "Spear", 5, 0});
    m_Items.emplace(EID::SWORD, CItem{EID::SWORD, "Sword", 3, 0});
    m_Items.emplace(EID::STONE, CItem{EID::STONE, "Stone", 0, 0});
    m_Items.emplace(EID::WOOD, CItem{EID::WOOD, "Wood", 0, 0});
    m_Items.emplace(EID::TREE, CItem{EID::TREE, "Tree", 0, 0});
    m_Items.emplace(EID::IRON_ARMOR, CItem{EID::IRON_ARMOR, "Iron Armor", 0, 2});
    m_Items.emplace(EID::STEEL_ARMOR, CItem{EID::STEEL_ARMOR, "Steel Armor", 0, 5});
    m_Items.emplace(EID::SEED, CItem{EID::SEED, "Seed", 0, 0});
    m_Items.emplace(EID::CROP, CItem{EID::CROP, "Wheat", 0, 0});
    m_Items.emplace(EID::DONUT, CItem{EID::DONUT, "Donut", 0, 0});
}

