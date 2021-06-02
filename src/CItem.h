//
// Created by honza on 05.05.21.
//

#pragma once


#include "EID.h"
#include <string>

class CItem {
public:
    EID m_Id;
    std::string m_Name;
    /** how much strength does this add to the player when owned */
    int m_PlusStrength;
    /** how much armor does this add to the player when owned */
    int m_PlusArmor;

    /** required as a comparator for the maps */
    bool operator<(const CItem &rhs) const {
        return m_Id < rhs.m_Id;
    }
};


