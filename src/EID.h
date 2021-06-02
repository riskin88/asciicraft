//
// Created by honza on 06.05.21.
//

#pragma once

/**
 * All blocks and items used for further crafting have their IDs corresponding
 * to the ASCII value of the character it is represented by in the grid.
 * This allows user to easily interact with the crafting interface, as well as create own maps
 */
enum class EID : int {
    AIR = 32, // ' '
    STONE = 88, // 'X'
    LAVA = 76,  // 'L'
    IRON = 73,  // 'I'
    TREE = 84,  // 'T'
    WOOD = 87, // 'W'
    SEED = 46, // '.'
    CROP = 58, // ':'
    NONE = 0,
    SWORD = 1,
    SPEAR = 2,
    PICKAXE = 3,
    STEEL = 83, // 'S'
    DONUT = 68, // 'D'
    IRON_ARMOR = 4,
    STEEL_ARMOR = 5,
    UNCRAFTABLE = -1


};


