//
// Created by honza on 01.05.21.
//

#include "CBlock.h"

std::pair<EID, int> CBlock::Drop() const {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribIdx(0, m_Drops.size() - 1);
    size_t idx = distribIdx(gen);
    std::uniform_int_distribution<> distribCount(1, m_Drops[idx].second);
    int count = distribCount(gen);
    return std::make_pair(m_Drops[idx].first, count);
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
