//
// Created by honza on 01.05.21.
//

#include "CApplication.h"

CApplication &CApplication::RegisterPlayCommand(const CCommand &command) {
    m_PlayCommands.push_back(command);
    return *this;
}

CApplication &CApplication::RegisterPauseCommand(const CCommand &command) {
    m_PauseCommands.push_back(command);
    return *this;
}

CApplication &CApplication::RegisterMenuCommand(const CCommand &command) {
    m_MenuCommands.push_back(command);
    return *this;

}

void CApplication::Run() {
    m_Running = true;
    while (m_Running) {
        if (m_Game && m_Game->State() == EState::PAUSED) {
            m_Interface->printPause(*m_Game);
            m_Interface->readInput();
            size_t idx = m_Interface->getCommand(generateValid(m_PauseCommands), m_PauseCommands.size());

            if (idx < m_PauseCommands.size()) m_PauseCommands[idx].Execute(m_Game, m_Interface);
        } else if (m_Game && m_Game->State() == EState::PLAYING) {
            m_Interface->printGame(*m_Game);
            m_Interface->readInput();
            if (m_Interface->resolveGameInput()) {
                size_t idx = m_Interface->getCommand(generateValid(m_PlayCommands), m_PlayCommands.size());

                if (idx < m_PlayCommands.size()) m_PlayCommands[idx].Execute(m_Game, m_Interface);
                if (m_Game->State() == EState::PAUSED)
                    continue;
            }
            m_Game->Update();
        } else {
            m_Interface->printMenu();
            m_Interface->readInput();
            size_t idx = m_Interface->getCommand(generateValid(m_MenuCommands), m_MenuCommands.size());
            if (idx < m_MenuCommands.size()) m_MenuCommands[idx].Execute(m_Game, m_Interface);
        }
    }
}

CApplication &CApplication::Running(bool running) {
    m_Running = running;
    return *this;
}

std::function<size_t(const std::string &)> CApplication::generateValid(const std::vector<CCommand> &commands) {
    return [commands](const std::string &name) {
        for (size_t i = 0; i < commands.size(); ++i)
            if (name == commands[i].Name())
                return i;
        return commands.size();
    };
}
