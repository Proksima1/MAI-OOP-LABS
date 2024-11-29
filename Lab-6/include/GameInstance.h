#pragma once

#include "NPC.h"
#include "Observer.h"
#include <vector>
#include <memory>

class GameInstance {
public:
    static GameInstance &getInstance();

    ~GameInstance();

    void addNPC(NPC *npc);

    void removeNPC(NPC *npc);

    void printNPCs() const;

    void saveNPCs(const std::string &filename) const;

    void loadNPCs(const std::string &filename);

    void startBattle(int range);

    std::vector<NPC *> getNPCs() const;

    void attach(Observer *observer);

    void detach(Observer *observer);

    void notify(const std::string &event);

private:
    GameInstance() = default;

    GameInstance(const GameInstance &) = delete;

    GameInstance &operator=(const GameInstance &) = delete;

    std::vector<NPC *> npcs;
    std::vector<Observer *> observers;
};
