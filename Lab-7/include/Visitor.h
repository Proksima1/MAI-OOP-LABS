#pragma once

#include "NPC.h"

class Slaver;

class Druid;

class Ork;


class NPC;

class Visitor {
public:
    virtual bool visit(Slaver &) const = 0;

    virtual bool visit(Druid &) const = 0;

    virtual bool visit(Ork &) const = 0;
};


class SlaverVisitor : public Visitor {
public:
    virtual bool visit(Slaver &) const override { return false; }

    virtual bool visit(Druid &) const override { return true; }

    virtual bool visit(Ork &) const override { return false; }
};

class DruidVisitor : public Visitor {
    virtual bool visit(Slaver &) const override { return false; }

    virtual bool visit(Druid &) const override { return false; }

    virtual bool visit(Ork &) const override { return false; }
};

class OrkVisitor : public Visitor {
    virtual bool visit(Slaver &) const override { return true; }

    virtual bool visit(Druid &) const override { return true; }

    virtual bool visit(Ork &) const override { return true; }
};


class VisitorFactory {
public:
    static Visitor *CreateVisitor(const NPC *type) {
        Visitor *result = nullptr;

        if (dynamic_cast<const Slaver *>(type)) {
            result = new SlaverVisitor();
        } else if (dynamic_cast<const Ork *>(type)) {
            result = new OrkVisitor();
        } else if (dynamic_cast<const Druid *>(type)) {
            result = new DruidVisitor();
        }
        return result;
    }
};