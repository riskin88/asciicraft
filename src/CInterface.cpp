//
// Created by honza on 01.05.21.
//

#include "CInterface.h"


CInterface &CInterface::readInput() {
    if (!(m_In >> m_Input))
        throw std::runtime_error("Error while reading ur input...aborting.");
    return *this;
}

std::string CInterface::getByPrompt(const std::string &prompt) const {
    printStr(prompt);
    std::string str;
    if (!(m_In >> str))
        throw std::runtime_error("Error while reading ur input...aborting.");
    return str;
}

void CInterface::printStr(const std::string &text) const {
    m_Out << text << std::endl;
}

bool CInterface::resolveGameInput() {
    if (m_Input == "w") {
        m_NextMove = EDirection::UP;
        return false;
    }
    if (m_Input == "a") {
        m_NextMove = EDirection::LEFT;
        return false;
    }
    if (m_Input == "s") {
        m_NextMove = EDirection::DOWN;
        return false;
    }
    if (m_Input == "d") {
        m_NextMove = EDirection::RIGHT;
        return false;
    }
    if (m_Input == "hit") {
        m_NextAttack = true;
        return false;
    }

    return true;
}

EDirection CInterface::getMove() {
    EDirection res = m_NextMove;
    m_NextMove = EDirection::NONE;
    return res;
}

bool CInterface::shouldHit() {
    bool res = m_NextAttack;
    m_NextAttack = false;
    return res;
}


void CInterface::printGame(const CGame &game) const {
    m_Out << std::endl;
    printStr("--PLAYING--");
    m_Out << "HP: " << game.GetPlayer().GetHP() <<
          " Strength: " << game.GetPlayer().GetStrength() << " Armor: " << game.GetPlayer().GetArmor() << std::endl;

    size_t width = game.GetGrid().getWidth();
    size_t height = game.GetGrid().getHeight();
    std::vector<std::vector<CExtendedChar>> buffer(height + 2, std::vector<CExtendedChar>(width + 2, CExtendedChar('#',
                                                                                                                   EColor::DEFAULT,
                                                                                                                   EColor::DEFAULT,
                                                                                                                   true)));

    printItems(game.GetItems());
    // print grid
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            buffer[i + 1][j + 1] = game.GetGrid().getBlock({i, j}).Display();
        }
    }
    // print agents
    for (const auto &agent : game.GetAgents()) {
        buffer[1 + agent->Coord().m_Y][1 + agent->Coord().m_X] = agent->Display();
    }
    // player always on top
    buffer[1 + game.GetPlayer().Coord().m_Y][1 + game.GetPlayer().Coord().m_X] = game.GetPlayer().Display();
    // flush
    for (auto &row : buffer) {
        for (auto ch : row)
            m_Out << ch;
        m_Out << std::endl;
    }
    printStr("Enter command [w|a|s|d, hit, mine, build, plant, eat or pause]:");
}

void CInterface::printPause(const CGame &game) const {
    m_Out << std::endl;
    printStr("--PAUSED--");
    printItems(game.GetItems());
    printStr("Enter command [resume, craft, save, or quit]:");
}

void CInterface::printMenu() const {
    printLogo();
    printStr("Welcome! Enter command [new, load, or quit]:");
}


void CInterface::printItems(const std::map<CItem, int> &items) const {
    printStr("Your items:");
    for (const auto &ref : items) {
        m_Out << ref.first.m_Name << " " << ref.second << "x" << std::endl;
    }
}

size_t CInterface::getCommand(const std::function<size_t(const std::string &)> &valid, size_t commandsSize) const {
    size_t idx = valid(m_Input);
    if (idx == commandsSize) {
        m_Out << "No such command!" << std::endl;
    }
    return idx;
}

void CInterface::printLogo() const {
    printStr("    _    ____   ____ ___ ___ ____            __ _  ");
    printStr("   / \\  / ___| / ___|_ _|_ _/ ___|_ __ __ _ / _| |_ ");
    printStr(R"(  / _ \ \___ \| |    | | | | |   | '__/ _` | |_| __|)");
    printStr(" / ___ \\ ___) | |___ | | | | |___| | | (_| |  _| |_ ");
    printStr(R"(/_/   \_\____/ \____|___|___\____|_|  \__,_|_|  \__|)");
    m_Out << std::endl;
}



