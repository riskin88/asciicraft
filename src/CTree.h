//
// Created by honza on 08.05.21.
//

#pragma once

#include "CDynamicBlock.h"

class CTree : public CDynamicBlock {
public:
    CTree(CCoord coord, int elapsed, int growTime = GROW_TIME)
            : CDynamicBlock(EID::TREE, CExtendedChar((char) EID::TREE, EColor::DEFAULT, EColor::BG_GREEN), coord, true,
                            std::vector<EID>{EID::TREE}, 0, EID::NONE),
              m_Elapsed(elapsed), m_ToStageOne(growTime / 2) {}

    /**
    * grow in 2 directions upon reaching stage one,
     * then proceedes to grow in all 4 directions and builds Wood in its place
    * @param grid
    * @return false if is to be removed, i.e. is fully grown
    */
    bool Update(CGrid &grid) override;

    /**
     * sends data about self into the steam ss
     * @param ss
     */
    void getData(std::stringstream &ss) const override;


private:
    int m_Elapsed;
    static constexpr int GROW_TIME = 5;
    int m_ToStageOne;
};


