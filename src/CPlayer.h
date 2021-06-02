//
// Created by honza on 01.05.21.
//

#pragma once


#include <utility>
#include <memory>

#include "CAgent.h"
#include "CInventory.h"

class CInterface;

class CPlayer : public CAgent {
public:
    CPlayer(CCoord coord, std::shared_ptr<CInterface> interface, int hp = INIT_HP, int strength = INIT_STRENGTH,
            int armor = 0)
            : CAgent(coord, CExtendedChar('@', EColor::GREEN), hp, strength), m_Interface(std::move(interface)),
              m_Armor(armor) {}


    /**
     * if the interface tells to hit, deals damage to all agents around self - within the radius of 1
     * @param agents
     */
    void TryAttack(std::vector<std::shared_ptr<CAgent>> &agents) const override;

    /**
     * adjusts this HP by the damage, reduced by some factor based on the armor value
     * @param damage
     */
    void TakeDamageByEnemy(int damage) override;

    /** empty, player cannot be harmed by themselves */
    void TakeDamageByPlayer(int damage) override {}

    /**
     * if the interface tells to move, alters direction to the new one
     * @return true if the player actually moves in this turn
     */
    bool Move() override;

    int GetArmor() const;

    int GetStrength() const;

    /**
     * changes state, if the player is dead
     * @param state
     * @return true if HP below 0
     */
    bool isDead(EState &state) const override;

    /**
     * raise HP by heal, but to INIT_HP at most
     * @param heal
     * @return true if any healing was possible
     */
    bool Heal(int heal);

    /**
     * sets new strength and armor values based on the items in inventory
     * @param inventory
     */
    void UpdateStats(const CInventory &inventory);

protected:
    std::shared_ptr<CInterface> m_Interface;
    static constexpr int INIT_STRENGTH = 5;
    static constexpr int INIT_HP = 20;
    /** reduces damage from enemies */
    int m_Armor;
};


