#pragma once
#include "NPC.h"
#include <string>

class Editor {
public:
    void addNPC(const std::string& type, const std::string& name, int x, int y);
    void saveNPCs(const std::string& filename) const;
    void loadNPCs(const std::string& filename);
    void printNPCs() const;
    void startBattle(int range);
};
