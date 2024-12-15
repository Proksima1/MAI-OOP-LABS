#include "NPC.h"
#include "Visitor.h"
#include <utility>
#include "iostream"
#include <cmath>

NPC::NPC(std::string name, int x, int y) : name(std::move(name)), x(x), y(y), alive(true) {}

std::string NPC::getName() const { return name; }

int NPC::getX() {
    std::lock_guard<std::mutex> lock(this->mutex);
    return x;
}

int NPC::getY() {
    std::lock_guard<std::mutex> lock(this->mutex);
    return y;
}

Slaver::Slaver(const std::string &name, int x, int y) : NPC(name, x, y) {}

bool Slaver::accept(const NPC *attacker) {
    Visitor *attacker_visitor = VisitorFactory::CreateVisitor(attacker);
    bool result = attacker_visitor->visit(*this);
    return result;
}

void Slaver::printType(std::ostream &os) const {
    os << "Slaver(";
}

Druid::Druid(const std::string &name, int x, int y) : NPC(name, x, y) {}

bool Druid::accept(const NPC *attacker) {
    Visitor *attacker_visitor = VisitorFactory::CreateVisitor(attacker);
    bool result = attacker_visitor->visit(*this);
    return result;
}

void Druid::printType(std::ostream &os) const {
    os << "Druid(";
}

Ork::Ork(const std::string &name, int x, int y) : NPC(name, x, y) {}

bool Ork::accept(const NPC *attacker) {
    Visitor *attacker_visitor = VisitorFactory::CreateVisitor(attacker);
    bool result = attacker_visitor->visit(*this);
    return result;
}

void Ork::printType(std::ostream &os) const {
    os << "Ork(";
}

void NPC::move(int mapWidth, int mapHeight) {
    std::lock_guard<std::mutex> lock(this->mutex);
    x += std::rand() % (2 * getMoveRange() + 1) - getMoveRange();
    y += std::rand() % (2 * getMoveRange() + 1) - getMoveRange();

    if (x < 0) x = 0;
    if (x >= mapWidth) x = mapWidth - 1;
    if (y < 0) y = 0;
    if (y >= mapHeight) y = mapHeight - 1;
}

bool NPC::canKill(const NPC &other) {
    std::lock_guard<std::mutex> lock(this->mutex);
    double distance = std::sqrt(std::pow(x - other.x, 2) + std::pow(y - other.y, 2));
    return distance <= getKillRange();
}

NPC *NPCFactory::createNPC(const std::string &type, const std::string &name, int x, int y, int MAP_WIDTH,
                           int MAP_HEIGHT) {
    if (!((0 <= x && x <= MAP_WIDTH) || (0 <= y && y <= MAP_HEIGHT))) {
        std::cout << "Position cannot be less 0 and bigger than 500" << std::endl;
        return nullptr;
    }
    if (type == "Slaver") return new Slaver(name, x, y);
    if (type == "Druid") return new Druid(name, x, y);
    if (type == "Ork") return new Ork(name, x, y);
    return nullptr;
}

int NPC::throw_dice() noexcept {
    return std::rand() % 6 + 1;
}

std::ostream &operator<<(std::ostream &os, const NPC &npc) {
    npc.printType(os);
    os << "name=\"" << npc.name << "\", "
       << "x=" << npc.x << ", "
       << "y=" << npc.y << ")";
    return os;
}