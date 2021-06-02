//
// Created by honza on 15.05.21.
//

#pragma once

#include "CCommand.h"
#include "CApplication.h"
#include <fstream>

class SCommands {
public:
    SCommands() = delete;

    /** generates the command for creating a new game from a .map file */
    static CCommand New();

    /** generates the command for loading a game from a .save file */

    static CCommand Load();

    /** generates the command for saving the game into a file
     * (file name with path is provided by the user, including the extension) */
    static CCommand Save();

    /** generates the command for terminating the application */
    static CCommand Quit(CApplication &application);

    /** generates the command for transitioning into the pause */
    static CCommand Pause();

    /** generates the command for transitioning into the game playing mode */
    static CCommand Unpause();

    /** generates the command for the crafting dialogue */
    static CCommand Craft();

    /** generates the command for mining a block in front of the player */
    static CCommand Mine();

    /** generates the command for bulding stone block in front of the player */
    static CCommand Build();

    /** generates the command for planting a tree or seed in front of the player */
    static CCommand Plant();

    /** generates the command for eating a donut */
    static CCommand Eat();
};


