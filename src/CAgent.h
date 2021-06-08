//
// Created by honza on 01.05.21.
//

#pragma once

#include "CCoord.h"
#include "EDirection.h"
#include "EState.h"
#include "CExtendedChar.h"
#include <memory>

class CAgent {
public:
    CAgent(CCoord coord, CExtendedChar display, int hp, int strength)
            : m_Coord(coord), m_Display(display), m_HP(hp), m_Strength(strength) {};

    CAgent(const CAgent &src) = default;

    CAgent &operator=(const CAgent &src) = default;

    virtual ~CAgent() = default;

    /**
     * Goes through the list of agents, harms every one of them
     * @param agents
     */
    virtual void TryAttack(std::vector<std::shared_ptr<CAgent>> &agents) const = 0;

    virtual void TakeDamageByEnemy(int damage) = 0;

    virtual int TakeDamageByPlayer(int damage) = 0;

    /**
     * Changes agent's direction
     * @return true if the agent actually moves in this turn
     */
    virtual bool Move() = 0;

    /**
     * changes the state of the game if needed
     * @param state
     * @return true if the agent is dead
     */
    virtual bool isDead(EState &state) const = 0;

    /**
     * HP getter
     * @return agent's HP
     */
    int GetHP() const;

    /**
     * HP setter
     * @return agent's HP
     */
    int &HP();

    const CCoord &Coord() const;

    CAgent &Coord(const CCoord &coord);

    /**
     * @return the chaacter to display in the form of extended char
     */
    CExtendedChar Display() const;

    EDirection Direction() const;

protected:
    /**
     * updates m_Display according to current direction
     */
    void updateChar();

    CCoord m_Coord;
    CExtendedChar m_Display;
    EDirection m_Dir = EDirection::NONE;
    int m_HP;
    int m_Strength;
};


