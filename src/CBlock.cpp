//
// Created by honza on 01.05.21.
//

#include "CBlock.h"

EID CBlock::Drop() const {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, m_Drops.size() - 1);
    return m_Drops[distrib(gen)];
}

EID CBlock::getID() const {
    return m_ID;
}

CExtendedChar CBlock::Display() const {
    return m_Display;
}

bool CBlock::isSolid() const {
    return m_IsSolid;
}

int CBlock::getDamage() const {
    return m_Damage;
}

EID CBlock::minedWith() const {
    return m_ToolToMine;
}
