#include "Character.h"
#include "Visitor.h"
#include "Observer.h"
#include "Factory.h"
#include "World.h"
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

TEST(WorldTest, World) {
    World w;
    Visitor v(10.0);
    ConsoleObserver ob;

    EXPECT_NO_THROW(w.AddCharacter("Dragon", "Nasty Joe", 0.0, 0.0));
    EXPECT_NO_THROW(w.AddCharacter("Bull", "His Meat", 0.0, 10.0));

    EXPECT_NO_THROW(v.AddObserver(&ob));

    EXPECT_NO_THROW(w.Engage(v));
}

TEST(FileOperationsTest, SaveAndLoadNPCs) {
    World w;

    w.AddCharacter("Bull", "Bull1", 10.0, 10.0);
    w.AddCharacter("Dragon", "Dragon1", 30.0, 40.0);

    const std::string filename = "npcs.txt";

    w.Serialize(filename);

    World w2;

    w2.Deserialize(filename);
    auto loaded_npcs = *reinterpret_cast<std::vector<std::shared_ptr<Character>>*>(&w2);
    ASSERT_EQ(loaded_npcs.size(), 2);
    EXPECT_EQ(loaded_npcs[0]->GetType(), "Bull");
    EXPECT_EQ(loaded_npcs[0]->GetName(), "Bull1");
    EXPECT_EQ(loaded_npcs[1]->GetType(), "Dragon");
    EXPECT_EQ(loaded_npcs[1]->GetName(), "Dragon1");

}