#include "NPC.h"
#include "Visitor.h"
#include <fstream>
#include <sstream>
#include "iostream"

NPC::NPC(const std::string &name, int x, int y) : name(name), x(x), y(y), alive(true) {}

std::string NPC::getName() const { return name; }

int NPC::getX() const { return x; }

int NPC::getY() const { return y; }

Slaver::Slaver(const std::string &name, int x, int y) : NPC(name, x, y) {}

void Slaver::accept(Visitor *visitor) { visitor->visit(this); }

Druid::Druid(const std::string &name, int x, int y) : NPC(name, x, y) {}

void Druid::accept(Visitor *visitor) { visitor->visit(this); }

Ork::Ork(const std::string &name, int x, int y) : NPC(name, x, y) {}

void Ork::accept(Visitor *visitor) { visitor->visit(this); }

NPC *NPCFactory::createNPC(const std::string &type, const std::string &name, int x, int y) {
    if (!((0 <= x && x <= 500) || (0 <= y && y <= 500))) {
        std::cout << "Position cannot be less 0 and bigger than 500" << std::endl;
        return nullptr;
    }
    if (type == "Slaver") return new Slaver(name, x, y);
    if (type == "Druid") return new Druid(name, x, y);
    if (type == "Ork") return new Ork(name, x, y);
    return nullptr;
}

std::vector<NPC *> NPCFactory::loadNPCsFromFile(const std::string &filename) {
    std::vector<NPC *> npcs;
    std::ifstream file(filename);
    if (!file.is_open()) {
        return npcs;
    }
    std::string type, name;
    int x, y;
    while (file >> type >> name >> x >> y) {
        npcs.push_back(createNPC(type, name, x, y));
    }
    return npcs;
}

void NPCFactory::saveNPCsToFile(const std::string &filename, const std::vector<NPC *> &npcs) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return;
    }
    for (const auto &npc: npcs) {
        if (dynamic_cast<Slaver *>(npc)) {
            file << "Slaver " << npc->getName() << " " << npc->getX() << " " << npc->getY() << std::endl;
        } else if (dynamic_cast<Druid *>(npc)) {
            file << "Druid " << npc->getName() << " " << npc->getX() << " " << npc->getY() << std::endl;
        } else if (dynamic_cast<Ork *>(npc)) {
            file << "Ork " << npc->getName() << " " << npc->getX() << " " << npc->getY() << std::endl;
        }
    }
    file.close();
}