#pragma once

#include <string>
#include <vector>

class NPC {
public:
    NPC(const std::string &name, int x, int y);

    virtual ~NPC() = default;

    std::string getName() const;

    int getX() const;

    int getY() const;

    bool isAlive() const { return alive; }

    void setAlive(bool flag) { this->alive = flag; }

    virtual void accept(class Visitor *visitor) = 0;

protected:
    std::string name;
    int x, y;
    bool alive = true;
};

class Slaver : public NPC {
public:
    Slaver(const std::string &name, int x, int y);

    void accept(Visitor *visitor) override;
};

class Druid : public NPC {
public:
    Druid(const std::string &name, int x, int y);

    void accept(Visitor *visitor) override;
};

class Ork : public NPC {
public:
    Ork(const std::string &name, int x, int y);

    void accept(Visitor *visitor) override;
};

class NPCFactory {
public:
    static NPC *createNPC(const std::string &type, const std::string &name, int x, int y);

    static std::vector<NPC *> loadNPCsFromFile(const std::string &filename);

    static void saveNPCsToFile(const std::string &filename, const std::vector<NPC *> &npcs);
};
