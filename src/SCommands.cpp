//
// Created by honza on 15.05.21.
//

#include "SCommands.h"
#include "CMapBuilder.h"
#include "CEnemy.h"

CCommand SCommands::New() {
    return CCommand("new", [](std::unique_ptr<CGame> &game, std::shared_ptr<CInterface> &interface) {
        std::string fileName = interface->getByPrompt("Enter map to load:");
        std::ifstream fin(fileName);
        if (!fin.is_open() || !fin)
            throw std::runtime_error("Unable to open file with map.");
        CMapBuilder builder(fin);
        CGrid grid = builder.BuildGrid();
        char ch; if (fin >> ch) throw std::runtime_error("Wrong file format.");
        game = std::make_unique<CGame>(grid);
        game->State() = EState::PLAYING;
        int enemyCount;
        do {
            enemyCount = atoi(interface->getByPrompt("How many opponents? (min 1)").c_str());
        } while (enemyCount < 1);

        CCoord coord{0, 0};
        for (int i = 0; i < enemyCount; ++i) {

            do {
                coord = CCoord::getRandom(grid.getHeight(), grid.getWidth());
            } while (!grid.isEmpty(coord));

            game->AddAgent(std::make_shared<CEnemy>(coord));
        }

        do {
            coord = CCoord::getRandom(grid.getHeight(), grid.getWidth());
        } while (!grid.isEmpty(coord));
        game->AddPlayer(std::make_shared<CPlayer>(coord, interface));
    });
}

CCommand SCommands::Load() {
    return CCommand("load", [](std::unique_ptr<CGame> &game, std::shared_ptr<CInterface> &interface) {
        std::string fileName = interface->getByPrompt("Enter file to load:");
        std::ifstream fin(fileName);
        if (!fin.is_open() || !fin)
            throw std::runtime_error("Unable to open file with map.");
        CMapBuilder builder(fin);
        CGrid grid = builder.BuildAll();
        game = std::make_unique<CGame>(grid);
        game->State() = EState::PLAYING;

        size_t y, x;
        int hp;
        if (!(fin >> y >> x >> hp) || fin.get() != '\n')
            throw std::runtime_error("Failed to read player info.");
        CCoord coord{y, x};
        if (!grid.isWalkable(coord))
            throw std::invalid_argument("Invalid player coordinates.");
        game->AddPlayer(std::make_shared<CPlayer>(coord, interface, hp))
                .LoadInventory(fin)
                .UpdatePlayerStats();
        int enemyCount;
        if (!(fin >> enemyCount) || fin.get() != '\n')
            throw std::runtime_error("Failed to read enemy count.");
        for (int i = 0; i < enemyCount; ++i) {
            if (!(fin >> y >> x >> hp) || fin.get() != '\n')
                throw std::runtime_error("Failed to read enemy info.");
            coord = {y, x};
            if (!grid.isWalkable(coord))
                throw std::invalid_argument("Invalid enemy coordinates.");
            game->AddAgent(std::make_shared<CEnemy>(coord, hp));
        }
    });
}

CCommand SCommands::Quit(CApplication &application) {
    return CCommand("quit", [&application](std::unique_ptr<CGame> &game, std::shared_ptr<CInterface> &interface) {
        application.Running(false);
    });
}

CCommand SCommands::Pause() {
    return CCommand("pause", [](std::unique_ptr<CGame> &game, std::shared_ptr<CInterface> &interface) {
        game->State() = EState::PAUSED;
    });
}

CCommand SCommands::Unpause() {
    return CCommand("resume", [](std::unique_ptr<CGame> &game, std::shared_ptr<CInterface> &interface) {
        game->State() = EState::PLAYING;
    });
}

CCommand SCommands::Craft() {
    return CCommand("craft", [](std::unique_ptr<CGame> &game, std::shared_ptr<CInterface> &interface) {
        game->Craft(*interface);
    });
}

CCommand SCommands::Mine() {
    return CCommand("mine", [](std::unique_ptr<CGame> &game, std::shared_ptr<CInterface> &interface) {
        game->PlayerMine();
    });
}

CCommand SCommands::Build() {
    return CCommand("build", [](std::unique_ptr<CGame> &game, std::shared_ptr<CInterface> &interface) {
        game->PlayerBuild();
    });
}

CCommand SCommands::Plant() {
    return CCommand("plant", [](std::unique_ptr<CGame> &game, std::shared_ptr<CInterface> &interface) {
        int item = interface->getByPrompt("Item to plant [T/.]:").front();
        if (item == (int) EID::TREE || item == (int) EID::SEED)
            game->PlayerPlant((EID) item);
        else
            interface->printStr("Unknown item!");
    });
}

CCommand SCommands::Save() {
    return CCommand("save", [](std::unique_ptr<CGame> &game, std::shared_ptr<CInterface> &interface) {
        std::string fileName = interface->getByPrompt("Enter file name:");
        std::ofstream fout(fileName);
        if (!fout.is_open() || !fout)
            throw std::runtime_error("Unable to open this file.");
        size_t width = game->GetGrid().getWidth();
        size_t height = game->GetGrid().getHeight();
        fout << width << ' ' << height << std::endl;
        for (size_t i = 0; i < height; ++i) {
            for (size_t j = 0; j < width; ++j) {
                fout << (char) game->GetGrid().getStaticBlock({i, j}).getID();
            }
            fout << std::endl;
        }
        auto objects = game->GetGrid().getObjectData();
        fout << objects.first << std::endl << objects.second;
        auto playerPtr = game->GetPlayerPtr();
        fout << playerPtr->Coord().m_Y << ' ' << playerPtr->Coord().m_X << ' ' << playerPtr->GetHP() << std::endl;
        auto items = game->GetItems();
        fout << items.size() << std::endl;
        for (const auto &ref : items) {
            fout << (int) ref.first.m_Id << ' ' << ref.second << std::endl;
        }
        auto agents = game->GetAgents();
        fout << agents.size() - 1 << std::endl;
        for (const auto &ref : agents) {
            if (ref != playerPtr)
                fout << ref->Coord().m_Y << ' ' << ref->Coord().m_X << ' ' << ref->GetHP() << std::endl;
        }
    });
}

CCommand SCommands::Eat() {
    return CCommand("eat", [](std::unique_ptr<CGame> &game, std::shared_ptr<CInterface> &interface) {
        game->PlayerEat();
    });
}
