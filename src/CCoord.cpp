//
// Created by honza on 05.05.21.
//

#include "CCoord.h"

CCoord operator+(const CCoord &coord, EDirection dir) {
    switch (dir) {
        case EDirection::UP:
            return {coord.m_Y - 1, coord.m_X};
        case EDirection::RIGHT:
            return {coord.m_Y, coord.m_X + 1};
        case EDirection::DOWN:
            return {coord.m_Y + 1, coord.m_X};
        case EDirection::LEFT:
            return {coord.m_Y, coord.m_X - 1};
        default:
            return coord;
    }
}

CCoord CCoord::getRandom(size_t height, size_t width) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distribY(0, height - 1);
    std::uniform_int_distribution<> distribX(0, width - 1);
    return CCoord(distribY(gen), distribX(gen));
}


int CCoord::Distance(const CCoord &other) const {
    return sqrt((m_X - other.m_X) * (m_X - other.m_X) + (m_Y - other.m_Y) * (m_Y - other.m_Y));
}

bool CCoord::operator<(const CCoord &rhs) const {
    if (m_Y == rhs.m_Y)
        return m_X < rhs.m_X;
    return m_Y < rhs.m_Y;
}
