//
// Created by honza on 08.05.21.
//

#pragma once


#include "CDynamicBlock.h"

class CLava : public CDynamicBlock {
public:
    explicit CLava(CCoord coord)
            : CDynamicBlock(EID::LAVA, CExtendedChar((char) EID::LAVA, EColor::RED, EColor::BG_RED), coord, false,
                            std::vector<std::pair<EID, int>>{std::make_pair(EID::NONE, 1)}, DAMAGE, EID::UNCRAFTABLE) {}

    CLava(const CLava &src) = default;

    CLava &operator=(const CLava &src) = default;

    ~CLava() override = default;
    /**
     * every other move expands into all 4 directions
     * @param grid
     * @return true - i.e. is never to be removed after update
     */
    bool Update(CGrid &grid) override;

    /**
     * sends data about self into the steam ss
     * @param ss
     */
    void getData(std::stringstream &ss) const override;

private:
    /** ensures that this expands only every other move */
    bool shouldExpand = false;
    static constexpr int DAMAGE = 1;

};


