//
// Created by honza on 01.05.21.
//

#pragma once

#include <queue>
#include <string>
#include <iostream>
#include <iomanip>
#include <exception>
#include <functional>
#include "CGame.h"

class CGame;

class CInterface {
public:
    CInterface(std::istream &in, std::ostream &out)
            : m_In(in), m_Out(out) {}

    CInterface(const CInterface &src) = delete;

    CInterface &operator=(const CInterface &src) = delete;

    ~CInterface() = default;

    /**
     * tries to read the input to m_Input
     * @return self
     */
    CInterface &readInput();

    /**
     * prompts user to insert input
     * @param prompt
     * @return said input as string
     */
    std::string getByPrompt(const std::string &prompt) const;

    /**
     * prints text to m_Out and adds a newline
     * @param text
     */
    void printStr(const std::string &text) const;

    /**  */

    /**
     * checks if m_Input is a valid command using the valid function
     * @param valid
     * @param commandsSize
     * @return index of the found command in the list of commands, commandsSize if not found
     * @inspiredBy Ing. David Bernhauer - specifically the idea of passing std::function for this purpose
     */
    size_t getCommand(const std::function<size_t(const std::string &)> &valid, size_t commandsSize) const;

    /**
     * checks if m_Input is a move, attack command or a regular command
     * @return true if input is a regular command
     */
    bool resolveGameInput();

    /**
     * clears m_NextMove
     * @return next move
     */
    EDirection getMove();

    /**
     * clears m_NextAttack
     * @return next attack
     */
    bool shouldHit();

    /**
     * prints the pause menu
     * @param game
     */
    void printPause(const CGame &game) const;

    /**
     * prints the main menu
     */
    void printMenu() const;

    /**
     * prints the grid and other game info
     * @param game
     */
    void printGame(const CGame &game) const;

private:
    /**
     * prints the item names and counts
     * @param items
     */
    void printItems(const std::map<CItem, int> &items) const;

    /** prints the awesome game title */
    void printLogo() const;

    std::istream &m_In;
    std::ostream &m_Out;
    /** last correctly read input */
    std::string m_Input;
    /** next move for the player */
    EDirection m_NextMove = EDirection::NONE;
    /** true if the player wants to attack */
    bool m_NextAttack = false;
};


