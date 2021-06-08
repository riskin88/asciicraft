//
// Created by honza on 01.05.21.
//

#include "CPlayer.h"
#include "CInterface.h"

void CPlayer::UpdateStats(const CInventory &inventory) {
    m_Strength = INIT_STRENGTH;
    m_Armor = 0;
    for (const auto &item : inventory.GetItems()) {
        m_Strength += item.first.m_PlusStrength;
        m_Armor += item.first.m_PlusArmor;
    }
}

bool CPlayer::isDead(EState &state) const {
    if (m_HP <= 0) {
        m_Interface->printStr("You died!");
        state = EState::NOT_RUNNING;
        return true;
    }
    return false;
}

bool CPlayer::Move() {
    EDirection dir = m_Interface->getMove();
    if (dir == m_Dir)
        return true;
    if (dir != EDirection::NONE) {
        m_Dir = dir;
        updateChar();
    }
    return false;

}

void CPlayer::TryAttack(std::vector<std::shared_ptr<CAgent>> &agents) const {
    if (m_Interface->shouldHit()) {
        for (auto &agent : agents) {
            if (m_Coord.Distance(agent->Coord()) <= 1) {
                int enemyHP = agent->TakeDamageByPlayer(m_Strength);
                if (enemyHP >= 0)m_Interface->printStr("Enemy hit! Their HP: " + std::to_string(enemyHP));
            }
        }
    }
}

void CPlayer::TakeDamageByEnemy(int damage) {
    m_HP -= (double) damage - (double) damage * 0.1 * m_Armor;
}

bool CPlayer::Heal(int heal) {
    if (m_HP == INIT_HP)
        return false;
    m_HP += heal;
    if (m_HP > INIT_HP)
        m_HP = INIT_HP;
    return true;
}

int CPlayer::GetArmor() const {
    return m_Armor;
}

int CPlayer::GetStrength() const {
    return m_Strength;
}
