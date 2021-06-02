//
// Created by honza on 14.05.21.
//

#include "EDirection.h"

EDirection randomDir() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, 4);
    return EDirection(distrib(gen));
}
