#include "Editor.h"
#include "GameInstance.h"

void Editor::addNPC(const std::string& type, const std::string& name, int x, int y) {
    GameInstance::getInstance().addNPC(NPCFactory::createNPC(type, name, x, y));
}