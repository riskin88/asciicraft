//
// Created by honza on 28.05.21.
//

#include "CSeed.h"
#include "CGrid.h"

bool CSeed::Update(CGrid &grid) {
    if (++m_Elapsed >= GROW_TIME) {
        grid.Build(m_Coord, EID::CROP);
        return false;
    }
    return true;
}


void CSeed::getData(std::stringstream &ss) const {
    CDynamicBlock::getData(ss);
    ss << ' ' << m_Elapsed << std::endl;
}
