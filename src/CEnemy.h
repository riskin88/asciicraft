//
// Created by honza on 01.05.21.
//

#pragma once

#include "CAgent.h"

class CEnemy : public CAgent {
public:
    explicit CEnemy(CCoord coord, int hp = ENEMY_HP, int strength = ENEMY_STRENGTH)
            : CAgent(coord, CExtendedChar('&', EColor::RED), hp, strength) {}

    CEnemy(const CEnemy &src) = default;

    CEnemy &operator=(const CEnemy &src) = default;

    ~CEnemy() override = default;

    /**
     * deals damage to all agents around self - within the radius of 1
     * @param agents
     */
    void TryAttack(std::vector<std::shared_ptr<CAgent>> &agents) const override;

    /**
     * adjusts this HP by the damage
     * @param damage
     * @return HP after damage taken
     */
    int TakeDamageByPlayer(int damage) override;

    /** empty, enemy cannot be harmed by another enemy */
    void TakeDamageByEnemy(int damage) override {}

    /**
     * changes this direction to a random value
     * @return true if the enemy actually moves in this turn
     */
    bool Move() override;

    /**
     * @param state
     * @return true if HP below 0
     */
    bool isDead(EState &state) const override;

private:
    static constexpr int ENEMY_HP = 10;
    static constexpr int ENEMY_STRENGTH = 3;

};


