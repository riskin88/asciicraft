//
// Created by honza on 01.05.21.
//

#pragma once

#include <random>


enum class EDirection : int {
    NONE = 0,
    UP = 1,
    RIGHT = 2,
    DOWN = 3,
    LEFT = 4,

};

/**
 * @return random direction
 * @inspiredBy https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
 * */
EDirection randomDir();




