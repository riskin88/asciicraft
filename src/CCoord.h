//
// Created by honza on 01.05.21.
//

#pragma once


#include "EDirection.h"
#include <cmath>

class CCoord {
public:
    CCoord(size_t y, size_t x)
            : m_X(x), m_Y(y) {}

    size_t m_X;
    size_t m_Y;

    /**
     * @param self
     * @param dir
     * @return coord next to self in the direction dir
     */
    friend CCoord operator+(const CCoord &coord, EDirection dir);

    /** required as a comparator in maps */
    bool operator<(const CCoord &rhs) const;

    /**
     * Euclidian distance
     * @param other
     * @return distance between self and other
     */
    int Distance(const CCoord &other) const;

    /**
     * @param height
     * @param width
     * @return random coord within height and width
     * @inspiredBy https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
     */
    static CCoord getRandom(size_t height, size_t width);
};




