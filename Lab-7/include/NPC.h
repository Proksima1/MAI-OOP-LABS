#pragma once

#include <string>
#include <vector>
#include "mutex"

class NPC {
public:
    NPC(std::string name, int x, int y);

    virtual ~NPC() = default;

    std::string getName() const;

    int getX();

    int getY();

    bool isAlive() const { return alive; }

    void move(int mapWidth, int mapHeight);

    bool canKill(const NPC &other);

    void setAlive(bool flag) { this->alive = flag; }

    static int throw_dice() noexcept;

    virtual bool accept(const NPC *attacker) = 0;

    virtual int getMoveRange() const { return moveRange; }

    virtual int getKillRange() const { return killRange; }

    friend std::ostream &operator<<(std::ostream &os, const NPC &npc);

    virtual void printType(std::ostream& os) const = 0;


protected:
    std::string name;
    int x, y;
    bool alive = true;
    int moveRange = 0, killRange = 0;
    std::mutex mutex;
};

class Slaver : public NPC {
public:
    Slaver(const std::string &name, int x, int y);

    bool accept(const NPC *attacker) override;

    int getMoveRange() const override { return 10; }

    int getKillRange() const override { return 10; }

    void printType(std::ostream& os) const override;
};

class Druid : public NPC {
public:
    Druid(const std::string &name, int x, int y);

    bool accept(const NPC *attacker) override;

    int getMoveRange() const override { return 10; }

    int getKillRange() const override { return 10; }

    void printType(std::ostream& os) const override;
};

class Ork : public NPC {
public:
    Ork(const std::string &name, int x, int y);

    bool accept(const NPC *attacker) override;

    int getMoveRange() const override { return 20; }

    int getKillRange() const override { return 10; }

    void printType(std::ostream& os) const override;
};

class NPCFactory {
public:
    static NPC *
    createNPC(const std::string &type, const std::string &name, int x, int y, int MAP_WIDTH, int MAP_HEIGHT);
};
