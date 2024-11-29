#include <gtest/gtest.h>
#include "GameInstance.h"
#include "NPC.h"
#include "Observer.h"
#include "Visitor.h"
#include <vector>
#include <string>

TEST(GameInstanceTest, AddNPC) {
    GameInstance& gameInstance = GameInstance::getInstance();
    NPC* warrior = NPCFactory::createNPC("Warrior", "Warrior1", 10, 20);
    gameInstance.addNPC(warrior);

    std::vector<NPC*> npcs = gameInstance.getNPCs();
    ASSERT_EQ(npcs.size(), 1);
    EXPECT_EQ(npcs[0]->getName(), "Warrior1");
    EXPECT_EQ(npcs[0]->getX(), 10);
    EXPECT_EQ(npcs[0]->getY(), 20);
}

TEST(GameInstanceTest, RemoveNPC) {
    GameInstance& gameInstance = GameInstance::getInstance();
    NPC* warrior = NPCFactory::createNPC("Warrior", "Warrior1", 10, 20);
    gameInstance.addNPC(warrior);

    gameInstance.removeNPC(warrior);
    std::vector<NPC*> npcs = gameInstance.getNPCs();
    ASSERT_EQ(npcs.size(), 0);
}

TEST(GameInstanceTest, StartBattle) {
    GameInstance& gameInstance = GameInstance::getInstance();
    NPC* warrior1 = NPCFactory::createNPC("Warrior", "Warrior1", 10, 20);
    NPC* warrior2 = NPCFactory::createNPC("Warrior", "Warrior2", 15, 25);
    gameInstance.addNPC(warrior1);
    gameInstance.addNPC(warrior2);

    gameInstance.startBattle(10);
    std::vector<NPC*> npcs = gameInstance.getNPCs();
    ASSERT_EQ(npcs.size(), 1);
}

TEST(NPCFactoryTest, CreateNPC) {
    NPC* warrior = NPCFactory::createNPC("Warrior", "Warrior1", 10, 20);
    ASSERT_NE(warrior, nullptr);
    EXPECT_EQ(warrior->getName(), "Warrior1");
    EXPECT_EQ(warrior->getX(), 10);
    EXPECT_EQ(warrior->getY(), 20);
    delete warrior;

    NPC* mage = NPCFactory::createNPC("Mage", "Mage1", 30, 40);
    ASSERT_NE(mage, nullptr);
    EXPECT_EQ(mage->getName(), "Mage1");
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

TEST(BattleVisitorTest, Visit) {
    GameInstance& gameInstance = GameInstance::getInstance();
    NPC* warrior1 = NPCFactory::createNPC("Warrior", "Warrior1", 10, 20);
    NPC* warrior2 = NPCFactory::createNPC("Warrior", "Warrior2", 15, 25);
    gameInstance.addNPC(warrior1);
    gameInstance.addNPC(warrior2);

    BattleVisitor visitor(10);
    warrior1->accept(&visitor);

    std::vector<NPC*> npcs = gameInstance.getNPCs();
    ASSERT_EQ(npcs.size(), 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}