//
// Created by honza on 01.05.21.
//

#include "CEnemy.h"

void CEnemy::TryAttack(std::vector<std::shared_ptr<CAgent>> &agents) const {
    for (auto &agent : agents) {
        if (m_Coord.Distance(agent->Coord()) <= 1)
            agent->TakeDamageByEnemy(m_Strength);
    }
}

int CEnemy::TakeDamageByPlayer(int damage) {
    return m_HP -= damage;
}

bool CEnemy::Move() {
    EDirection dir = randomDir();
    if (dir != EDirection::NONE) {
        m_Dir = dir;
        updateChar();
        return true;
    }
    return false;
}


bool CEnemy::isDead(EState &state) const {
    return m_HP <= 0;
}
