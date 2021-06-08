//
// Created by honza on 01.05.21.
//
#pragma once

#include <utility>

#include "CInterface.h"
#include "CGame.h"
#include "CMapBuilder.h"
#include "CCommand.h"


class CApplication {
public:
    explicit CApplication(std::shared_ptr<CInterface> interface)
            : m_Interface(std::move(interface)) {}

    CApplication(const CApplication &src) = delete;

    CApplication &operator=(const CApplication &src) = delete;

    ~CApplication() = default;

    /**
     * Goes through the main game loop
     * prints the board, gets next command from the interface and executes it based on the current game state
     */
    void Run();

    /**
     * setter for m_Running
     * @param running
     * @return self
     */
    CApplication &Running(bool running);

    /**
     * adds command to the list of commands available in the playing mode
     * @param command
     * @return
     */
    CApplication &RegisterPlayCommand(const CCommand &command);


    /**
     * adds command to the list of commands available in the pause menu
     * @param command
     * @return
     */
    CApplication &RegisterPauseCommand(const CCommand &command);


    /**
     * adds command to the list of commands available in the main menu
     * @param command
     * @return
     */
    CApplication &RegisterMenuCommand(const CCommand &command);

private:
    /** list of commands that are available while the game is actually running */
    std::vector<CCommand> m_PlayCommands;
    /** list of commands that are available while the game is paused */
    std::vector<CCommand> m_PauseCommands;
    /** list of commands that are available in the main meny */
    std::vector<CCommand> m_MenuCommands;
    std::shared_ptr<CInterface> m_Interface;
    std::unique_ptr<CGame> m_Game = nullptr;
    bool m_Running = false;

    /**
     *
     * @param commands
     * @return validating function, which tells whether its argument is a valid command
     * in the context of the list provided at its definition
     * the validating function returns the index of such command in the list, end if does not exist
     */
    static std::function<size_t(const std::string &)> generateValid(const std::vector<CCommand> &commands);
};
