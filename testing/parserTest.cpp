#include <gtest/gtest.h>

#include "../JSONParser.h"
#include "../Character.h"
#include "../Adventurer.h"


// JSON tests

TEST(MulTest, stringJSONTest) {
	std::string JSONText = "{\"name\": \"Halis\",\"hp\": 8600,\"dmg\": 6900,\"attackcooldown\": 4.3}";
	
    std::map<std::string, std::string> actual;
    std::map<std::string, std::string> expected {
        {"name", "Halis"},
        {"hp", "8600"},
        {"dmg", "6900"},
        {"attackcooldown", "4.3"}
    };

    actual = JSONParser::parseString(JSONText);

    ASSERT_EQ(expected.size(), actual.size());

    for(auto data : expected){
        ASSERT_EQ(actual[data.first], data.second);
    }
}

TEST(MulTest, fileJSONTest) {
	std::string filename = "units/kowa.json";
	
	std::map<std::string, std::string> actual;
    std::map<std::string, std::string> expected {
        {"name", "Kowa"},
        {"hp", "200"},
        {"dmg", "85"},
        {"attackcooldown", "5.5"}
    };
	
    actual = JSONParser::parseFile(filename);
    
    ASSERT_EQ(expected.size(), actual.size());

    for(auto data : expected){
        ASSERT_EQ(actual[data.first], data.second);
    }
}

TEST(MulTest, streamJSONTest) {
	std::map<std::string, std::string> actual;
    std::map<std::string, std::string> expected {
        {"name", "Codos"},
        {"hp", "300"},
        {"dmg", "70"},
        {"attackcooldown", "12.5"}
    };
	std::fstream file("units/codos.json");
    
    actual = JSONParser::parseStream(file);

    ASSERT_EQ(expected.size(), actual.size());

    for(auto data : expected){
        ASSERT_EQ(actual[data.first], data.second);
    }
}

TEST(MulTest, missingQuotmarkJSONTest) {
	try{
        std::string filename = "units/badkowa.json";
        
        JSONParser::parseFile(filename);
    }
    catch (std::runtime_error& e){
        ASSERT_STREQ(e.what(), "Wrong JSON syntax!");
    }
}

TEST(MulTest, unnecessaryWhitespaceJSONTest) {
    std::string JSONText = "{\"name    \": \"  Halis   \",\"hp\": 8600   ,\" dmg   \": 6900,\"attackcooldown \": 4.3}";

    std::map<std::string, std::string> actual;
    std::map<std::string, std::string> expected {
    {"name", "Halis"},
    {"hp", "8600"},
    {"dmg", "6900"},
    {"attackcooldown", "4.3"}
    };

    actual = JSONParser::parseString(JSONText);

    ASSERT_EQ(expected.size(), actual.size());

    for(auto data : expected){
        ASSERT_EQ(actual[data.first], data.second);
    }
}

TEST(MulTest, shuffledDataJSONTest) {
	std::string JSONText = "{\"hp\": 8600,\"attackcooldown\": 4.3,\"dmg\": 6900,\"name\": \"Halis\"}";
	
    std::map<std::string, std::string> actual;
    std::map<std::string, std::string> expected {
        {"name", "Halis"},
        {"hp", "8600"},
        {"dmg", "6900"},
        {"attackcooldown", "4.3"}
    };

    actual = JSONParser::parseString(JSONText);

    ASSERT_EQ(expected.size(), actual.size());

    for(auto data : expected){
        ASSERT_EQ(actual[data.first], data.second);
    }
}

TEST(MulTest, missingCommaJSONTest) {
	try{
	    std::string JSONText = "{\"name\": \"Halis\"\"hp\": 8600,\"dmg\": 6900,\"attackcooldown\": 4.3}";

        JSONParser::parseString(JSONText);
    }
    catch (std::runtime_error& e){
        ASSERT_STREQ(e.what(), "Wrong JSON syntax!");
    }
}

TEST(MulTest, missingColonJSONTest) {
	try{
	    std::string JSONText = "{\"name\" \"Halis\",\"hp\": 8600,\"dmg\": 6900,\"attackcooldown\": 4.3}";
        
        JSONParser::parseString(JSONText);
    }
    catch (std::runtime_error& e){
        ASSERT_STREQ(e.what(), "Wrong JSON syntax!");
    }
}

// Character & Adventurer tests

TEST(MulTest, characterVScharacterTest) {
	Character ch1("Codos",300,70,12.5);
	Character ch2("Kowa",200,85,5.5);

    ch2.attackEnemy(ch1);

    ASSERT_EQ(ch1.getCurrentHP(), 215);
    ASSERT_EQ(ch2.getCurrentCooldown(), 11);
}

TEST(MulTest, characterVSadventurerTest) {
	Adventurer ch1("Codos",300,70,12.5);
	Character ch2("Kowa",200,85,5.5);

    ch2.attackEnemy(ch1);

    ASSERT_EQ(ch1.getCurrentHP(), 215);
    ASSERT_EQ(ch2.getCurrentCooldown(), 11);
}

TEST(MulTest, adventurerVScharacterTest) {
	Character ch1("Codos",300,70,12.5);
	Adventurer ch2("Kowa",200,85,5.5);

    ch2.attackEnemy(ch1);

    ASSERT_EQ(ch1.getCurrentHP(), 215);
    ASSERT_EQ(ch2.getCurrentCooldown(), 11);
}

TEST(MulTest, adventurerVSadventurerTest) {
	Adventurer ch1("Codos",300,70,12.5);
	Adventurer ch2("Kowa",200,85,5.5);

    ch2.attackEnemy(ch1);

    ASSERT_EQ(ch1.getCurrentHP(), 215);
    ASSERT_EQ(ch2.getCurrentCooldown(), 11);
}

TEST(MulTest, adventurerLevelupTest) {
	Adventurer ch1("Codos",300,70,12.5);
	Adventurer ch2("Kowa",200,100,5.5);

    ch2.attackEnemy(ch1);

    ASSERT_EQ(ch2.getMaxHP(), 220);
    ASSERT_EQ(ch2.getCurrentHP(), ch2.getMaxHP());
    ASSERT_EQ(ch2.getCooldown(), 4.95);
}

TEST(MulTest, adventurerMultipleLevelupTest) {
	Character ch1("Codos",300,70,12.5);
	Adventurer ch2("Kowa",200,215,5.5);

    ch2.attackEnemy(ch1);

    ASSERT_EQ(ch2.getMaxHP(), 242);
    ASSERT_EQ(ch2.getCurrentHP(), ch2.getMaxHP());
    ASSERT_EQ(ch2.getCooldown(), 4.455);
}

TEST(MulTest, adventurerXPGainOnEnemyKillTest) {
	Character ch1("Codos",60,70,12.5);
	Adventurer ch2("Kowa",200,100,5.5);

    int xp = ch2.attackEnemy(ch1);

    ASSERT_EQ(xp, 60);
}

TEST(MulTest, characterDoubleAttackTest) {
	Character ch1("Codos",150,70,12.5);
	Character ch2("Kowa",200,60,5.5);

    ch2.fight(ch1);

    ASSERT_TRUE(ch1.isDead());
    ASSERT_EQ(ch2.getCurrentHP(), 130); // 200-70 (both attack each other at the start)
}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}