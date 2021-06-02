//
// Created by honza on 03.05.21.
//

#include "CCommand.h"

void CCommand::Execute(std::unique_ptr<CGame> &game, std::shared_ptr<CInterface> &interface) {
    m_Execute(game, interface);
}

const std::string &CCommand::Name() const {
    return m_Name;
}
