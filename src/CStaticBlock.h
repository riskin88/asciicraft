//
// Created by honza on 04.05.21.
//

#pragma once


#include <utility>

#include "CBlock.h"

class CStaticBlock : public CBlock {
public:
    CStaticBlock(EID id, CExtendedChar display, bool solid, std::vector<EID> drops, int damage = 0, EID tool = EID::NONE)
            : CBlock(id, display, solid, std::move(drops), damage, tool) {}
};


