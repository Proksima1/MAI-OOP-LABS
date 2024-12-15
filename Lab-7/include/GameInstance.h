#pragma once

#include "NPC.h"
#include "Observer.h"
#include <vector>
#include <memory>
#include "mutex"
#include <condition_variable>

class GameInstance {
public:
    static GameInstance &getInstance();

    ~GameInstance();

    void addNPC(NPC *npc);

    void removeNPC(NPC *npc);

    void printNPCs() const;

    std::vector<NPC *> getNPCs() const;

    void attach(Observer *observer);

    void detach(Observer *observer);

    void notify(const std::string &event);

    void spawnRandomNPCs(int count, int mapWidth, int mapHeight);

    void setupGame(int MAP_HEIGHT, int MAP_WIDTH);

    void printNPC(NPC *npc) const;


private:
    GameInstance() = default;

    GameInstance(const GameInstance &) = delete;

    GameInstance &operator=(const GameInstance &) = delete;

    std::vector<NPC *> npcs;
    std::vector<Observer *> observers;
    mutable std::mutex npcsMutex;
    std::vector<std::thread> threads;

};
