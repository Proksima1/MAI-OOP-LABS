#include "GameInstance.h"
#include "Visitor.h"
#include <iostream>

GameInstance &GameInstance::getInstance() {
    static GameInstance instance;
    return instance;
}

void GameInstance::addNPC(NPC *npc) {
    if (npc != nullptr) {
        npcs.push_back(npc);
    }
}

void GameInstance::removeNPC(NPC *npc) {
    npcs.erase(std::remove(npcs.begin(), npcs.end(), npc), npcs.end());
    delete npc;
}

void GameInstance::printNPCs() const {
    for (const auto &npc: npcs) {
        if (dynamic_cast<Slaver *>(npc)) {
            std::cout << "Slaver(";
        } else if (dynamic_cast<Druid *>(npc)) {
            std::cout << "Druid(";
        } else if (dynamic_cast<Ork *>(npc)) {
            std::cout << "Ork(";
        } else {
            std::cout << "Unknown(";
        }
        std::cout << "name=\"" << npc->getName() << "\", " << "x=" << npc->getX() << ", " << "y=" << npc->getY() << ")"
                  << std::endl;
    }
}

void GameInstance::saveNPCs(const std::string &filename) const {
    NPCFactory::saveNPCsToFile(filename, npcs);
}

void GameInstance::loadNPCs(const std::string &filename) {
    for (auto &npc: npcs) delete npc;
    npcs = NPCFactory::loadNPCsFromFile(filename);
    std::cout << "Загружено ";
    if (npcs.size() == 1) {
        std::cout << npcs.size() << " враг" << std::endl;
    } else if (npcs.size() < 5) {
        std::cout << npcs.size() << " врага" << std::endl;
    } else if (npcs.size() >= 5 || npcs.size() == 0) {
        std::cout << npcs.size() << " врагов" << std::endl;
    }
}

void GameInstance::startBattle(int range) {
    BattleVisitor visitor(range);
    for (auto &npc: npcs) {
        if (npc->isAlive()) {
            npc->accept(&visitor);
        }
    }
    for (auto & i : npcs) {
        auto npc = i;
        i = nullptr;
        delete npc;
    }
}

std::vector<NPC *> GameInstance::getNPCs() const {
    return npcs;
}

void GameInstance::attach(Observer *observer) {
    observers.push_back(observer);
}

void GameInstance::detach(Observer *observer) {
    observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void GameInstance::notify(const std::string &event) {
    for (auto &observer: observers) {
        observer->update(event);
    }
}

GameInstance::~GameInstance() {
    for (auto npc: npcs) {
        delete npc;

    }
    for (auto observer: observers) {
        detach(observer);
    }
}
