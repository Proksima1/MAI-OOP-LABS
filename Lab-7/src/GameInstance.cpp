#include "GameInstance.h"
#include "Visitor.h"
#include <iostream>
#include <chrono>
#include <random>


using namespace std::chrono_literals;

GameInstance &GameInstance::getInstance() {
    static GameInstance instance;
    return instance;
}

void GameInstance::addNPC(NPC *npc) {
    std::lock_guard<std::mutex> lock(npcsMutex);
    npcs.push_back(npc);
}

void GameInstance::removeNPC(NPC *npc) {
    std::lock_guard<std::mutex> lock(npcsMutex);
    npcs.erase(std::remove(npcs.begin(), npcs.end(), npc), npcs.end());
    delete npc;
}

void GameInstance::printNPC(NPC *npc) const {
    std::cout << *npc << std::endl;
}

void GameInstance::printNPCs() const {
    for (const auto &npc: npcs) {
        printNPC(npc);
    }
}

std::vector<NPC *> GameInstance::getNPCs() const {
    std::lock_guard<std::mutex> lock(npcsMutex);
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


void GameInstance::setupGame(int MAP_HEIGHT, int MAP_WIDTH) {
    spawnRandomNPCs(50, MAP_WIDTH, MAP_HEIGHT);
}

void GameInstance::spawnRandomNPCs(int count, int mapWidth, int mapHeight) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> xDist(0, mapWidth - 1);
    std::uniform_int_distribution<> yDist(0, mapHeight - 1);
    std::uniform_int_distribution<> typeDist(0, 2);

    for (int i = 0; i < count; ++i) {
        int x = xDist(gen);
        int y = yDist(gen);
        std::string name = "NPC" + std::to_string(i + 1);
        std::string type;
        switch (typeDist(gen)) {
            case 0:
                type = "Slaver";
                break;
            case 1:
                type = "Druid";
                break;
            case 2:
                type = "Ork";
                break;
        }
        addNPC(NPCFactory::createNPC(type, name, x, y, mapWidth, mapHeight));
    }
}