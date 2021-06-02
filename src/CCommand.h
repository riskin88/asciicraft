//
// Created by honza on 03.05.21.
//

#pragma once

#include <functional>
#include <utility>
#include "CInterface.h"
#include "CGame.h"

class CCommand {
public:
    CCommand(std::string name, std::function<void(std::unique_ptr<CGame> &, std::shared_ptr<CInterface> &)> execute)
            : m_Name(std::move(name)), m_Execute(std::move(execute)) {}

    /**
     * calls the m_Execute function
     * @param game
     * @param interface
     */
    void Execute(std::unique_ptr<CGame> &game, std::shared_ptr<CInterface> &interface);

    const std::string &Name() const;

private:
    /** name of the command, expected to be typed by the user on the input */
    std::string m_Name;
    /** the function this command calls upon execution */
    std::function<void(std::unique_ptr<CGame> &, std::shared_ptr<CInterface> &)> m_Execute;
};



