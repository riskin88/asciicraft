//
// Created by honza on 08.05.21.
//

#include "CTree.h"
#include "CGrid.h"

bool CTree::Update(CGrid &grid) {
    if (++m_Elapsed >= m_ToStageOne) {
        if (grid.isWalkable(m_Coord + EDirection::UP)) {
            grid.TryBuild(m_Coord + EDirection::UP, EID::WOOD);
        }
        if (grid.isWalkable(m_Coord + EDirection::DOWN)) {
            grid.TryBuild(m_Coord + EDirection::DOWN, EID::WOOD);
        }
        m_ToStageOne += GROW_TIME;
    }

    if (m_Elapsed >= GROW_TIME) {

        if (grid.isWalkable(m_Coord + EDirection::RIGHT)) {
            grid.TryBuild(m_Coord + EDirection::RIGHT, EID::WOOD);
        }
        if (grid.isWalkable(m_Coord + EDirection::LEFT)) {
            grid.TryBuild(m_Coord + EDirection::LEFT, EID::WOOD);
        }
        grid.Build(m_Coord, EID::WOOD);
        return false;
    }
    return true;
}

void CTree::getData(std::stringstream &ss) const {
    CDynamicBlock::getData(ss);
    ss << ' ' << m_Elapsed << std::endl;
}
