//
// Created by honza on 08.05.21.
//

#include "CLava.h"
#include "CGrid.h"

bool CLava::Update(CGrid &grid) {
    if (shouldExpand) {
        if (grid.isWalkable(m_Coord + EDirection::UP)) {
            grid.TryBuild(m_Coord + EDirection::UP, EID::LAVA);
        }
        if (grid.isWalkable(m_Coord + EDirection::RIGHT)) {
            grid.TryBuild(m_Coord + EDirection::RIGHT, EID::LAVA);
        }
        if (grid.isWalkable(m_Coord + EDirection::DOWN)) {
            grid.TryBuild(m_Coord + EDirection::DOWN, EID::LAVA);
        }
        if (grid.isWalkable(m_Coord + EDirection::LEFT)) {
            grid.TryBuild(m_Coord + EDirection::LEFT, EID::LAVA);
        }
        shouldExpand = false;
    } else
        shouldExpand = true;
    return true;
}

void CLava::getData(std::stringstream &ss) const {
    CDynamicBlock::getData(ss);
    ss << std::endl;

}
