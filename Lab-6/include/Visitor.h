#pragma once

class Slaver;

class Druid;

class Ork;


class NPC;

class Visitor {
public:
    virtual void visit(Slaver *warrior) = 0;

    virtual void visit(Druid *mage) = 0;

    virtual void visit(Ork *ork) = 0;

    virtual ~Visitor() = default;
};

class BattleVisitor : public Visitor {
public:
    BattleVisitor(int range);

    void visit(Slaver *slaver) override;

    void visit(Druid *mage) override;

    void visit(Ork *ork) override;


private:
    int range;
};
