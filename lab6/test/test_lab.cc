#include "Character.h"
#include "Visitor.h"
#include "Observer.h"
#include "Factory.h"
#include <gtest/gtest.h>
#include <vector>
#include <memory>
#include <sstream>

TEST(NPCTest, CreateAndAccess) {
    Position coords = { 10.0f, 20.0f };
    Bull bull("Bull1", coords.x, coords.y);

    EXPECT_EQ(bull.GetType(), "Bull");
    EXPECT_EQ(bull.GetName(), "Bull1");
    EXPECT_FLOAT_EQ(bull.GetPosX(), 10.0f);
    EXPECT_FLOAT_EQ(bull.GetPosY(), 20.0f);
}

TEST(ObserverTest, NotifyObservers) {
    auto console_observer = std::make_shared<ConsoleObserver>();
    Bull bull({ 100.0f, 200.0f }, "Bull1");
    bull.addObserver(console_observer);

    testing::internal::CaptureStdout();
    bull.notifyObservers("Enemy");
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "Bull1 defeated Enemy\n");
}

TEST(FileOperationsTest, SaveAndLoadNPCs) {
    std::vector<std::unique_ptr<NPC>> npcs;
    npcs.push_back(std::make_unique<Bull>(Coordinates{ 10.0, 20.0 }, "Bull1"));
    npcs.push_back(std::make_unique<Dragon>(Coordinates{ 30.0, 40.0 }, "Dragon1"));

    const std::string filename = "data/pre_created_npcs/npcs.txt";
    save_npc_to_file(npcs, filename);

    auto loaded_npcs = load_npcs_from_file(filename);
    ASSERT_EQ(loaded_npcs.size(), npcs.size());
    EXPECT_EQ(loaded_npcs[0]->GetType(), "Bull");
    EXPECT_EQ(loaded_npcs[0]->GetName(), "Bull1");
    EXPECT_EQ(loaded_npcs[1]->GetType(), "Dragon");
    EXPECT_EQ(loaded_npcs[1]->GetName(), "Dragon1");

    // Удаление временного файла
    std::remove(filename.c_str());
}