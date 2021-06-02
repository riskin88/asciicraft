//
// Created by honza on 11.05.21.
//

#pragma once

#include <iostream>
#include <fstream>
#include "CGrid.h"


class CMapBuilder {
public:
    explicit CMapBuilder(std::ifstream &file)
            : m_File(file) {}

    CMapBuilder(const CMapBuilder &src) = delete;

    CMapBuilder &operator=(const CMapBuilder &src) = delete;

    /**
     * creates grid based from the user created character map in m_File
     * @return grid
     */
    CGrid BuildGrid();

    /**
     * creates grid from the character map and initializes the dynamic blocks in it
     * @return grid
     */
    CGrid BuildAll();


private:
    /** file stream to build the map from */
    std::ifstream &m_File;
};


