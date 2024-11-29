#include "Visitor.h"
#include "NPC.h"
#include "GameInstance.h"
#include <cmath>

BattleVisitor::BattleVisitor(int range) : range(range) {}

void BattleVisitor::visit(Slaver *slaver) {
    for (auto &npc: GameInstance::getInstance().getNPCs()) {
        if (dynamic_cast<Druid *>(npc)) {
            if (npc != slaver && npc->isAlive()) {
                int distance = static_cast<int>(std::sqrt(
                        std::pow(slaver->getX() - npc->getX(), 2) + std::pow(slaver->getY() - npc->getY(), 2)));
                if (distance <= range) {
                    npc->setAlive(false);
                    GameInstance::getInstance().notify(
                            npc->getName() + " has been defeated by " + slaver->getName());
                }
            }
        }
    }
}

void BattleVisitor::visit(Druid *ork) {}

void BattleVisitor::visit(Ork *ork) {
    for (auto &npc: GameInstance::getInstance().getNPCs()) {
        if (npc != ork && npc->isAlive()) {
            int distance = static_cast<int>(std::sqrt(
                    std::pow(ork->getX() - npc->getX(), 2) + std::pow(ork->getY() - npc->getY(), 2)));
            if (distance <= range) {
                npc->setAlive(false);
                GameInstance::getInstance().notify(
                        npc->getName() + " has been defeated by " + ork->getName());
            }
        }
    }
}