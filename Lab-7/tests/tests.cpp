#include <gtest/gtest.h>
#include "GameInstance.h"
#include "NPC.h"
#include "Observer.h"
#include "FightManager.h"
#include <vector>
#include <string>

TEST(GameInstanceTest, AddNPC) {
    GameInstance &gameInstance = GameInstance::getInstance();
    NPC *warrior = NPCFactory::createNPC("Slaver", "Slaver1", 10, 20, 100, 100);
    gameInstance.addNPC(warrior);

    std::vector<NPC *> npcs = gameInstance.getNPCs();
    ASSERT_EQ(npcs.size(), 1);
    EXPECT_EQ(npcs[0]->getName(), "Slaver1");
    EXPECT_EQ(npcs[0]->getX(), 10);
    EXPECT_EQ(npcs[0]->getY(), 20);
    gameInstance.removeNPC(warrior);
}

TEST(GameInstanceTest, RemoveNPC) {
    GameInstance &gameInstance = GameInstance::getInstance();
    NPC *warrior = NPCFactory::createNPC("Slaver", "Slaver1", 10, 20, 100, 100);
    gameInstance.addNPC(warrior);

    gameInstance.removeNPC(warrior);
    std::vector<NPC *> npcs = gameInstance.getNPCs();
    ASSERT_EQ(npcs.size(), 0);
}


TEST(NPCFactoryTest, CreateNPC) {
    NPC *warrior = NPCFactory::createNPC("Slaver", "Slaver1", 10, 20, 100, 100);
    ASSERT_NE(warrior, nullptr);
    EXPECT_EQ(warrior->getName(), "Slaver1");
    EXPECT_EQ(warrior->getX(), 10);
    EXPECT_EQ(warrior->getY(), 20);
    delete warrior;

    NPC *mage = NPCFactory::createNPC("Ork", "Ork1", 30, 40, 100, 100);
    ASSERT_NE(mage, nullptr);
    EXPECT_EQ(mage->getName(), "Ork1");
    EXPECT_EQ(mage->getX(), 30);
    EXPECT_EQ(mage->getY(), 40);
    delete mage;
}

TEST(ObserverTest, Update) {
    FileObserver fileObserver;
    ConsoleObserver consoleObserver;

    std::string event = "Test event";
    testing::internal::CaptureStdout();
    fileObserver.update(event);
    consoleObserver.update(event);

    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find(event), std::string::npos);
}

TEST(NPCTest, MoveNPC) {
    NPC *druid = NPCFactory::createNPC("Druid", "Druid1", 50, 50, 100, 100);
    ASSERT_NE(druid, nullptr);
    int initialX = druid->getX();
    int initialY = druid->getY();
    druid->move(100, 100);
    EXPECT_NE(druid->getX(), initialX);
    EXPECT_NE(druid->getY(), initialY);
    delete druid;
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}