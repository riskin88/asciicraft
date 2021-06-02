//
// Created by honza on 04.05.21.
//

#include "CDynamicBlock.h"

void CDynamicBlock::getData(std::stringstream &ss) const {
    ss << (int) m_ID << ' ' << m_Coord.m_Y << ' ' << m_Coord.m_X;
}
