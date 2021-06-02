//
// Created by honza on 01.05.21.
//

#pragma once


#include <vector>
#include <random>

#include "CItem.h"
#include "EID.h"
#include "CExtendedChar.h"

class CBlock {
public:
    CBlock(EID id, CExtendedChar display, bool solid, std::vector<EID> drops, int damage = 0, EID tool = EID::NONE)
            : m_ID(id), m_Display(display), m_IsSolid(solid), m_Drops(std::move(drops)), m_Damage(damage),
              m_ToolToMine(tool) {}

    EID getID() const;

    /**
    * @return the chaacter to display in the form of extended char
    */
    CExtendedChar Display() const;

    bool isSolid() const;

    /**
    * @return damage to deal to whomever steps on this
    */
    int getDamage() const;

    EID minedWith() const;

    /**
     * randomly picks an item from the list of possible drops
     * @return ID of the item to drop when mined
     * @inspiredBy https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
     */
    EID Drop() const;

protected:
    EID m_ID;
    CExtendedChar m_Display;
    bool m_IsSolid;
    /** list of all possible items this can drop upon being mined */
    std::vector<EID> m_Drops;
    /** damage to deal to whomever steps on this */
    int m_Damage;
    /** item required to be owned in order to mine this */
    EID m_ToolToMine;
};


