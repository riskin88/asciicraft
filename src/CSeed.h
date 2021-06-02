//
// Created by honza on 28.05.21.
//

#pragma once

#include "CDynamicBlock.h"

class CSeed : public CDynamicBlock {
public:
    CSeed(CCoord coord, int elapsed)
            : CDynamicBlock(EID::SEED, CExtendedChar((char) EID::SEED, EColor::GREEN, EColor::DEFAULT, true), coord,
                            false,
                            std::vector<EID>{EID::SEED}, 0, EID::NONE),
              m_Elapsed(elapsed) {}

    /**
    * advances elapsed time by 1, builds Crop if fully grown
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
    static constexpr int GROW_TIME = 3;
};


