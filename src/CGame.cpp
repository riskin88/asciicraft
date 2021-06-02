//
// Created by honza on 01.05.21.
//

#include "CGame.h"
#include "CInterface.h"

using namespace std;


CGame &CGame::LoadInventory(ifstream &fin) {
    int itemsCount;
    if (!(fin >> itemsCount) || fin.get() != '\n')
        throw std::runtime_error("Failed to read items count.");
    for (int i = 0; i < itemsCount; ++i) {
        int id, count;
        if (!(fin >> id >> count) || fin.get() != '\n')
            throw std::runtime_error("Failed to read item data.");
        m_Inventory.Insert(id, count);
    }
    return *this;

}

void CGame::Update() {

    for (const auto &agent : m_Agents) {
        if (agent->Move()) {
            CCoord target = agent->Coord() + agent->Direction();
            if (m_Grid.isWalkable(target)) {
                agent->Coord(target);
            }
        }
        agent->HP() -= m_Grid.getBlock(agent->Coord()).getDamage();
        agent->TryAttack(m_Agents);
    }

    for (auto it = m_Agents.begin(); it < m_Agents.end(); ++it) {
        if ((*it)->isDead(m_State))
            m_Agents.erase(it);
    }

    m_Grid.Update();

}

void CGame::Craft(CInterface &interface) {
    std::string ingredients = interface.getByPrompt("Insert items:");
    try {
        EID id = m_Recipes.at(ingredients);
        for (size_t idx = 0; idx < ingredients.size(); idx++) {
            char ch = toupper(ingredients.at(idx));
            if (!m_Inventory.Has((EID) ch)) {
                interface.printStr("Don't have enough items!");
                for (size_t i = 0; i < idx; ++i) {
                    m_Inventory.Add(EID(toupper(ingredients.at(i))));
                }
                return;
            }
            m_Inventory.Remove((EID) ch);
        }
        m_Inventory.Add(id);
        UpdatePlayerStats();
        interface.printStr("Crafting successful!");
    }
    catch (const std::out_of_range &e) {
        interface.printStr("Unknown recipe!");
    }
}

CGame &CGame::AddAgent(const std::shared_ptr<CAgent> &agent) {
    m_Agents.push_back(agent);
    return *this;
}

CGame &CGame::AddPlayer(const std::shared_ptr<CPlayer> &player) {
    m_Agents.push_back(player);
    m_Player = player;
    return *this;
}

bool CGame::PlayerMine() {
    return m_Grid.Mine(m_Player->Coord() + m_Player->Direction(), m_Inventory);
}

bool CGame::PlayerBuild() {
    if (m_Inventory.Has(EID::STONE) && m_Grid.TryBuild(m_Player->Coord() + m_Player->Direction(), EID::STONE)) {
        m_Inventory.Remove(EID::STONE);
        return true;
    }
    return false;
}

bool CGame::PlayerPlant(EID item) {
    if (m_Inventory.Has(item) && m_Grid.Plant(item, m_Player->Coord() + m_Player->Direction(), 0)) {
        m_Inventory.Remove(item);
        return true;
    }
    return false;
}


bool CGame::PlayerEat() {
    if (m_Inventory.Has(EID::DONUT)) {
        if (m_Player->Heal(HEAL_BY_FOOD)) {
            m_Inventory.Remove(EID::DONUT);
            return true;
        }
    }
    return false;
}

EState &CGame::State() {
    return m_State;
}

const CGrid &CGame::GetGrid() const {
    return m_Grid;
}

const std::vector<std::shared_ptr<CAgent>> &CGame::GetAgents() const {
    return m_Agents;
}

std::map<CItem, int> CGame::GetItems() const {
    return m_Inventory.GetItems();
}

const CPlayer &CGame::GetPlayer() const {
    return *m_Player;
}

CGame &CGame::UpdatePlayerStats() {
    m_Player->UpdateStats(m_Inventory);
    return *this;
}

void CGame::loadRecipes() {
    m_Recipes.emplace("wwxxx", EID::PICKAXE);
    m_Recipes.emplace("wwiii", EID::SWORD);
    m_Recipes.emplace("ii", EID::STEEL);
    m_Recipes.emplace("wwss", EID::SPEAR);
    m_Recipes.emplace("iiiii", EID::IRON_ARMOR);
    m_Recipes.emplace("sssss", EID::STEEL_ARMOR);
    m_Recipes.emplace("::::", EID::DONUT);
}

std::shared_ptr<CAgent> CGame::GetPlayerPtr() const {
    return m_Player;
}

CGame::CGame(CGrid grid)
        : m_Grid(std::move(grid)), m_State(EState::NOT_RUNNING) {
    loadRecipes();
}


