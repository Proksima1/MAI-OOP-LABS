#include "GameInstance.h"
#include "Visitor.h"
#include "Observer.h"
#include <iostream>
#include <thread>
#include <chrono>
#include "FightManager.h"

using namespace std::chrono_literals;

const int MAP_WIDTH = 100;
const int MAP_HEIGHT = 100;

auto start = std::chrono::steady_clock::now();
const std::chrono::seconds max_time = 30s;

std::shared_mutex npc_mutex;


void npc_move() {
    GameInstance &game = GameInstance::getInstance();

    while (true) {
        {
            std::lock_guard<std::shared_mutex> lock(npc_mutex);
            auto npcs = game.getNPCs();
            for (auto npc: npcs) {
                if (npc->isAlive()) {
                    npc->move(MAP_WIDTH, MAP_HEIGHT);
                }
            }

            for (auto npc: npcs) {
                for (auto other: npcs) {
                    if (other != npc && npc->isAlive() && other->isAlive() && npc->canKill(*other)) {
                        FightManager::getInstance().addEvent({npc, other});
                    }
                }
            }
            std::this_thread::sleep_for(1s);

        }

        auto end = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(end - start) >= max_time) break;
        std::this_thread::sleep_for(100ms);
    }
}

void npc_print() {
    GameInstance &game = GameInstance::getInstance();
    auto npcs = game.getNPCs();

    while (true) {
        std::cout << "Next iteration" << std::endl;
        {
            std::lock_guard<std::shared_mutex> lock(npc_mutex);
            game.printNPCs();
        }
        std::this_thread::sleep_for(1s);

        auto end = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(end - start) >= max_time) break;
    }
}


int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    GameInstance &game = GameInstance::getInstance();
    FileObserver fileObserver;
    ConsoleObserver consoleObserver;
    game.attach(&fileObserver);
    game.attach(&consoleObserver);
    game.setupGame(MAP_HEIGHT, MAP_WIDTH);

    std::thread fight_thread(std::ref(FightManager::getInstance()), (void *) &max_time);
    std::thread move_thread(npc_move);
    std::thread print_thread(npc_print);

    fight_thread.join();
    move_thread.join();
    print_thread.join();

    auto npcs = game.getNPCs();

    std::cout << "Game over. Survivors:" << std::endl;
    game.printNPCs();

    return 0;
}