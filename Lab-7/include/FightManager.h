#pragma once

#include <memory>
#include <chrono>
#include <optional>
#include <shared_mutex>
#include "queue"
#include "GameInstance.h"
#include "sstream"

#include "NPC.h"

using namespace std::chrono_literals;


struct FightEvent {
    NPC *attacker;
    NPC *defender;
};

class FightManager {
private:
    std::queue<FightEvent> events;
    std::shared_mutex mutex;

    FightManager() = default;

    FightManager(const FightManager &) = delete;

    FightManager &operator=(const FightManager &) = delete;

public:
    static FightManager &getInstance() {
        static FightManager instance;
        return instance;
    }

    void addEvent(FightEvent &&event) {
        std::lock_guard<std::shared_mutex> lock(mutex);
        events.push(event);
    }

    void operator()(void *args) {
        auto start = std::chrono::steady_clock::now();
        auto max_time = (std::chrono::seconds *) args;

        while (true) {
            std::optional<FightEvent> event;

            {
                std::lock_guard<std::shared_mutex> lock(mutex);
                if (!events.empty()) {
                    event = events.front();
                    events.pop();
                }
            }

            if (event) {
                if (event->attacker->isAlive() && event->defender->isAlive() &&
                    event->attacker->throw_dice() > event->defender->throw_dice() &&
                    event->defender->accept(event->attacker)) {
                    event->defender->setAlive(false);
                    std::ostringstream oss;
                    oss << *event->defender << " was killed by " << *event->attacker;
                    GameInstance::getInstance().notify(oss.str());
                    std::this_thread::sleep_for(1s);
                }
            } else {
                std::this_thread::sleep_for(10ms);
            }

            auto end = std::chrono::steady_clock::now();
            if (std::chrono::duration_cast<std::chrono::seconds>(end - start) >= *max_time) break;
        }
    }
};