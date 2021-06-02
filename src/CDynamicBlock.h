//
// Created by honza on 04.05.21.
//

#pragma once


#include <utility>
#include <iomanip>

#include "CBlock.h"
#include "CCoord.h"

class CGrid;

class CDynamicBlock : public CBlock {
public:
    CDynamicBlock(EID id, CExtendedChar display, CCoord coord, bool solid, std::vector<EID> drops, int damage = 0,
                  EID tool = EID::NONE)
            : CBlock(id, display, solid, std::move(drops), damage, tool), m_Coord(coord) {}

    /**
     * is called during each move
     * @param grid
     * @return false if this block is to be removed
     */
    virtual bool Update(CGrid &grid) = 0;

    /**
     * sends data about self into the steam ss
     * @param ss
     */
    virtual void getData(std::stringstream &ss) const;

protected:
    CCoord m_Coord;
};


