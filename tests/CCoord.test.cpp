//
// Created by honza on 02.06.21.
//

#include <cassert>
#include "CCoord.h"

int main() {
    CCoord zero{0, 0};

    CCoord down = zero + EDirection::DOWN;
    assert(down.m_Y == 1 && down.m_X == 0);

    CCoord up = down + EDirection::UP;
    assert(up.m_Y == 0 && up.m_X == 0);

    CCoord right = zero + EDirection::RIGHT;
    assert(right.m_Y == 0 && right.m_X == 1);

    CCoord left = right + EDirection::LEFT;
    assert(left.m_Y == 0 && left.m_X == 0);

    CCoord none = zero + EDirection::NONE;
    assert(none.m_Y == 0 && none.m_X == 0);

    assert(zero.Distance(zero) == 0);
    assert(zero.Distance(down) == 1);
    assert(right.Distance(down) == 1);

    assert(zero.Distance({0,2}) == 2);
    assert(zero.Distance({2,2}) == 2);
    assert(zero.Distance({2,1}) == 2);
    assert(zero.Distance({1,2}) == 2);

    return 0;

}