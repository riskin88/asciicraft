//
// Created by honza on 01.05.21.
//

#include "CGrid.h"

using namespace std;

void CGrid::Update() {
    std::map<CCoord, std::shared_ptr<CDynamicBlock>> tmp = m_Dynamics;
    for (auto &ref : tmp) {
        if (!ref.second->Update(*this))
            m_Dynamics.erase(ref.first);
    }
}

bool CGrid::TryBuild(CCoord coord, EID id) {
    if (!isWalkable(coord))
        return false;

    return Build(coord, id);
}

bool CGrid::Build(CCoord coord, EID id) {
    switch (id) {
        case EID::AIR:
            m_Blocks[coord.m_Y][coord.m_X] = m_AirPrototype;
            m_Dynamics.erase(coord);
            break;
        case EID::STONE:
            m_Blocks[coord.m_Y][coord.m_X] = m_StonePrototype;
            m_Dynamics.erase(coord);
            break;
        case EID::IRON:
            m_Blocks[coord.m_Y][coord.m_X] = m_IronPrototype;
            m_Dynamics.erase(coord);
            break;
        case EID::WOOD:
            m_Blocks[coord.m_Y][coord.m_X] = m_WoodPrototype;
            m_Dynamics.erase(coord);
            break;
        case EID::CROP:
            m_Blocks[coord.m_Y][coord.m_X] = m_CropPrototype;
            m_Dynamics.erase(coord);
            break;
        case EID::LAVA:
            m_Dynamics.insert(make_pair(coord, make_shared<CLava>(coord)));
            m_Blocks[coord.m_Y][coord.m_X] = m_AirPrototype;
            break;
        default:
            return false;
    }
    return true;
}

bool CGrid::Plant(EID id, CCoord coord, int elapsedTime) {
    if (!isEmpty(coord))
        return false;

    m_Blocks[coord.m_Y][coord.m_X] = m_AirPrototype;
    switch (id) {
        case EID::TREE:
            m_Dynamics.insert(make_pair(coord, make_shared<CTree>(coord, elapsedTime)));
            break;
        case EID::SEED:
            m_Dynamics.insert(make_pair(coord, make_shared<CSeed>(coord, elapsedTime)));
            break;
        default:
            return false;
    }

    return true;
}

bool CGrid::Mine(CCoord coord, CInventory &inventory) {
    if (isInside(coord) &&
        (getBlock(coord).minedWith() == EID::NONE || inventory.Has(getBlock(coord).minedWith()))) {
        auto drop = getBlock(coord).Drop();
        for (int i = 0; i < drop.second; ++i) {
            inventory.Add(drop.first);
        }
        m_Blocks[coord.m_Y][coord.m_X] = m_AirPrototype;
        m_Dynamics.erase(coord);
        return true;
    }
    return false;
}

CBlock &CGrid::getBlock(CCoord coord) {
    if (m_Dynamics.count(coord) == 1)
        return *(m_Dynamics.at(coord));

    return *(m_Blocks[coord.m_Y][coord.m_X]);
}

const CBlock &CGrid::getBlock(CCoord coord) const {
    if (m_Dynamics.count(coord) == 1)
        return *(m_Dynamics.at(coord));

    return *(m_Blocks[coord.m_Y][coord.m_X]);
}

const CBlock &CGrid::getStaticBlock(CCoord coord) const {
    return *(m_Blocks[coord.m_Y][coord.m_X]);
}

bool CGrid::isEmpty(CCoord coord) const {
    return isInside(coord) &&
           (m_Blocks[coord.m_Y][coord.m_X] == nullptr || m_Blocks[coord.m_Y][coord.m_X]->getID() == EID::AIR) &&
           m_Dynamics.count(coord) == 0;
}

bool CGrid::isWalkable(CCoord coord) const {
    try {
        return isInside(coord) &&
               (m_Blocks[coord.m_Y][coord.m_X] == nullptr || !m_Blocks[coord.m_Y][coord.m_X]->isSolid()) &&
               !m_Dynamics.at(coord)->isSolid();
    }
    catch (...) {
        return true;
    }

}

bool CGrid::isInside(CCoord coord) const {
    return coord.m_X >= 0 && coord.m_X < m_Width && coord.m_Y >= 0 && coord.m_Y < m_Height;
}

std::pair<size_t, std::string> CGrid::getObjectData() const {
    std::stringstream ss;
    for (const auto &item : m_Dynamics) {
        item.second->getData(ss);
    }
    return std::make_pair(m_Dynamics.size(), move(ss.str()));

}

CGrid::CGrid(size_t width, size_t height)
        : m_Width(width), m_Height(height), m_Blocks(height, std::vector<std::shared_ptr<CStaticBlock>>(width)) {
    m_StonePrototype = std::make_shared<CStaticBlock>(EID::STONE, CExtendedChar((char) EID::STONE), true,
                                                      std::vector<std::pair<EID, int>>{std::make_pair(EID::STONE, 1)});
    m_AirPrototype = std::make_shared<CStaticBlock>(EID::AIR, CExtendedChar((char) EID::AIR), false,
                                                    std::vector<std::pair<EID, int>>{std::make_pair(EID::NONE, 1)}, 0,
                                                    EID::UNCRAFTABLE);
    m_IronPrototype = std::make_shared<CStaticBlock>(EID::IRON, CExtendedChar((char) EID::IRON, EColor::YELLOW), true,
                                                     std::vector<std::pair<EID, int>>{std::make_pair(EID::IRON, 3)}, 0,
                                                     EID::PICKAXE);
    m_WoodPrototype = std::make_shared<CStaticBlock>(EID::WOOD, CExtendedChar((char) EID::WOOD, EColor::DEFAULT,
                                                                              EColor::BG_YELLOW), true,
                                                     std::vector<std::pair<EID, int>>{std::make_pair(EID::WOOD, 1),
                                                                                      std::make_pair(EID::TREE, 2)});
    m_CropPrototype = std::make_shared<CStaticBlock>(EID::CROP,
                                                     CExtendedChar((char) EID::CROP, EColor::YELLOW, EColor::BG_GREEN,
                                                                   true), false,
                                                     std::vector<std::pair<EID, int>>{std::make_pair(EID::CROP, 2),
                                                                                      std::make_pair(EID::SEED, 3)});
}

size_t CGrid::getWidth() const {
    return m_Width;
}

size_t CGrid::getHeight() const {
    return m_Height;
}


