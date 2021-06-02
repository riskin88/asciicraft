//
// Created by honza on 01.05.21.
//

#pragma once

#include <vector>
#include <memory>
#include <sstream>
#include "CCoord.h"
#include "CInventory.h"
#include "CBlock.h"
#include "CStaticBlock.h"
#include "CLava.h"
#include "CTree.h"
#include "CSeed.h"

class CGrid {
public:
    /** initializes the static block prototypes */
    CGrid(size_t width, size_t height);

    /**
     * tries to mine the given Block with tools in inventory,
     * adds possible drop to inventory
     * @param coord
     * @param inventory
     * @return true if mining successful
     */
    bool Mine(CCoord coord, CInventory &inventory);

    /**
     * tries to place block with id on given coord
     * succedes only if there is not a solid block at coord
     * @param coord
     * @param id
     * @return true if building successful
     */
    bool TryBuild(CCoord coord, EID id);

    /**
     * places block with id on given coord
     * @param coord
     * @param id
     * @return true if id is valid
     */
    bool Build(CCoord coord, EID id);

    /**
     * tries to plant object with id and elapsedTime on given coord
     * @param id
     * @param coord
     * @param elapsedTime
     * @return true if the block on coord is empty and id is a valid plant
     */
    bool Plant(EID id, CCoord coord, int elapsedTime = 0);

    CBlock &getBlock(CCoord coord);

    const CBlock &getBlock(CCoord coord) const;

    const CBlock &getStaticBlock(CCoord coord) const;

    /**
     * @param coord
     * @return true if there is air and no dynamic block on coord
     */
    bool isEmpty(CCoord coord) const;

    /**
     * @param coord
     * @return true if there is no solid block on coord
     */
    bool isWalkable(CCoord coord) const;

    /**
     * @param coord
     * @return true if coord is within the bounds given by m_Height and m_Width
     */
    bool isInside(CCoord coord) const;

    size_t getWidth() const;

    size_t getHeight() const;

    /**
     * calls Update on all Dynamics, removes them if needed
     */
    void Update();

    /**
     * collects object data from all Dynamics
     * @return pair: count of Dynamics, string of all the data
     */
    std::pair<size_t, std::string> getObjectData() const;

private:
    size_t m_Width;
    size_t m_Height;
    std::shared_ptr<CStaticBlock> m_StonePrototype;
    std::shared_ptr<CStaticBlock> m_AirPrototype;
    std::shared_ptr<CStaticBlock> m_IronPrototype;
    std::shared_ptr<CStaticBlock> m_WoodPrototype;
    std::shared_ptr<CStaticBlock> m_CropPrototype;
    /** we do not need to have a unique object for each static block, so the matrix contains
     * just pointers to the fixed block prototypes stored in here
     */
    std::vector<std::vector<std::shared_ptr<CStaticBlock>>> m_Blocks;
    std::map<CCoord, std::shared_ptr<CDynamicBlock>> m_Dynamics;
};


