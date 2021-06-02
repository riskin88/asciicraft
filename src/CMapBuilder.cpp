//
// Created by honza on 11.05.21.
//

#include "CMapBuilder.h"

CGrid CMapBuilder::BuildAll() {
    CGrid grid = BuildGrid();
    int objectCount;
    if (!(m_File >> objectCount) || m_File.get() != '\n')
        throw std::runtime_error("Failed to read number of objects.");
    for (int i = 0; i < objectCount; ++i) {
        int id;
        size_t y, x;
        int time;
        if (!(m_File >> id >> y >> x))
            throw std::runtime_error("Failed to read object info.");
        if ((EID) id != EID::LAVA) {
            if (!(m_File >> time))
                throw std::runtime_error("Failed to read object info.");
            if (!grid.Plant((EID) id, {y, x}, time))
                throw std::runtime_error("Invalid object info.");
        } else {
            if (!grid.TryBuild({y, x}, EID::LAVA))
                throw std::runtime_error("Invalid object info.");
        }
        if (m_File.get() != '\n')
            throw std::runtime_error("Unexpected newline issue.");
    }
    return grid;
}

CGrid CMapBuilder::BuildGrid() {
    size_t width, height;
    if (!(m_File >> width >> height) || m_File.get() != '\n')
        throw std::runtime_error("Failed to read dimensions.");

    CGrid grid(width, height);
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            int ch = m_File.get();
            if (!grid.TryBuild({i, j}, (EID) ch))
                throw std::runtime_error("Unknown character in map.");
        }
        if (m_File.get() != '\n')
            throw std::runtime_error("Unexpected newline issue.");
    }
    return grid;
}
