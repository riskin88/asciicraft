//
// Created by honza on 01.05.21.
//

#include "CAgent.h"

CAgent &CAgent::Coord(const CCoord &coord) {
    m_Coord = coord;
    return *this;
}

int CAgent::GetHP() const {
    return m_HP;
}

int &CAgent::HP() {
    return m_HP;
}

const CCoord &CAgent::Coord() const {
    return m_Coord;
}

CExtendedChar CAgent::Display() const {
    return m_Display;
}

EDirection CAgent::Direction() const {
    return m_Dir;
}

void CAgent::updateChar() {
    switch (m_Dir) {
        case EDirection::UP:
            m_Display.Char('^');
            break;
        case EDirection::RIGHT:
            m_Display.Char('>');

            break;
        case EDirection::DOWN:
            m_Display.Char('v');

            break;
        case EDirection::LEFT:
            m_Display.Char('<');

            break;
        default:
            break;
    }
}
