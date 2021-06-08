//
// Created by honza on 01.05.21.
//

#pragma once

#include <vector>
#include <memory>
#include <map>
#include <fstream>
#include "CInventory.h"
#include "CAgent.h"
#include "CGrid.h"
#include "CPlayer.h"
#include "EState.h"


class CGame {
public:
    explicit CGame(CGrid grid);

    CGame(const CGame &src) = default;

    CGame &operator=(const CGame &src) = default;

    ~CGame() = default;

    /**
     * updates all Agent directions, tries to move them, calls attacks among them,
     * removes dead agents and updates grid
     */
    void Update();

    /** m_State setter */
    EState &State();

    /**
     * loads items to inventory from a file in fin
     * @param fin
     * @return self
     */
    CGame &LoadInventory(std::ifstream &fin);

    /**
     * asks for the crafting recipe, tries to find corresponding one in m_Recipes, updates the inventory
     * @param interface
     */
    void Craft(CInterface &interface);

    /**
     * tries to mine the block in front of the player
     * @return true if the block was successfully mined
     */
    bool PlayerMine();

    /**
     * tries to build a stone in front of the player
     * @return true if the block was successfully built
     */
    bool PlayerBuild();

    /**
     * tries to plant item in front of the player
     * @param item
     * @return true if the item was successfully planted
     */
    bool PlayerPlant(EID item);

    /**
     * tries to eat a donut and add HP to the player
     * @return true if donut was consumed
     */
    bool PlayerEat();

    const CGrid &GetGrid() const;

    const std::vector<std::shared_ptr<CAgent>> &GetAgents() const;

    /**
     * adds agent to the list
     * @param agent
     * @return self
     */
    CGame &AddAgent(const std::shared_ptr<CAgent> &agent);

    /**
     * adds player to the list of agents, sets m_Player to player
     * @param player
     * @return self
     */
    CGame &AddPlayer(const std::shared_ptr<CPlayer> &player);

    /**
     * @return items the player currently owns
     */
    std::map<CItem, int> GetItems() const;

    const CPlayer &GetPlayer() const;

    std::shared_ptr<CAgent> GetPlayerPtr() const;

    /**
     * updates player statistics by the items currently owned
     * @return self
     */
    CGame &UpdatePlayerStats();

private:
    /** loads predefined crafting recipes into m_Recipes */
    void loadRecipes();

    std::vector<std::shared_ptr<CAgent>> m_Agents;
    std::shared_ptr<CPlayer> m_Player;
    CGrid m_Grid;
    EState m_State;
    CInventory m_Inventory;
    /** predefined recipes: recipe->result item */
    std::map<std::string, EID> m_Recipes;
    static constexpr int HEAL_BY_FOOD = 3;
};
