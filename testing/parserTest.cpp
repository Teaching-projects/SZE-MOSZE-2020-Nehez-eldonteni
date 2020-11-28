#include <gtest/gtest.h>

#include "../JSON.h"
#include "../Monster.h"
#include "../Hero.h"


// JSON tests

TEST(MulTest, stringJSONTest) {
	std::string JSONText = "{\"name\": \"Halis\",\"health_points\": 8600,\"damage\": 6900,\"attack_cooldown\": 4.3}}";
	
    JSON actual = JSON::parseFromString(JSONText);

    ASSERT_EQ(actual.get<std::string>("name"), "Halis");
    ASSERT_EQ(actual.get<int>("health_points"), 8600);
    ASSERT_EQ(actual.get<int>("damage"), 6900);
    ASSERT_EQ(actual.get<double>("attack_cooldown"), 4.3);
}

TEST(MulTest, fileJSONTest) {
	std::string filename = "units/kowa.json";
	
    JSON actual = JSON::parseFromFile(filename);

    ASSERT_EQ(actual.get<std::string>("name"), "Kowa");
    ASSERT_EQ(actual.get<int>("health_points"), 200);
    ASSERT_EQ(actual.get<int>("damage"), 85);
    ASSERT_EQ(actual.get<double>("attack_cooldown"), 5.5);
}

TEST(MulTest, streamJSONTest) {
	std::fstream file("units/codos.json");
    
    JSON actual = JSON::parseFromStream(file);

    ASSERT_EQ(actual.get<std::string>("name"), "Codos");
    ASSERT_EQ(actual.get<int>("health_points"), 300);
    ASSERT_EQ(actual.get<int>("damage"), 70);
    ASSERT_EQ(actual.get<double>("attack_cooldown"), 12.5);
}

TEST(MulTest, missingQuotmarkJSONTest) {
	try{
        std::string filename = "units/badkowa.json";
        
        JSON actual = JSON::parseFromFile(filename);
        
        ASSERT_TRUE(false);
    }
    catch (JSON::ParseException& e){
        ASSERT_TRUE(true);
    }
}

TEST(MulTest, unnecessaryWhitespaceJSONTest) {
    std::string JSONText = "{\"name    \": \"  Halis   \",\"health_points\": 8600   ,\" damage   \": 6900,\"attack_cooldown \": 4.3}";

    JSON actual = JSON::parseFromString(JSONText);

    ASSERT_EQ(actual.get<std::string>("name"), "Halis");
    ASSERT_EQ(actual.get<int>("health_points"), 8600);
    ASSERT_EQ(actual.get<int>("damage"), 6900);
    ASSERT_EQ(actual.get<double>("attack_cooldown"), 4.3);
}

TEST(MulTest, shuffledDataJSONTest) {
	std::string JSONText = "{\"health_points\": 8600,\"attack_cooldown\": 4.3,\"damage\": 6900,\"name\": \"Halis\"}";
	
    JSON actual = JSON::parseFromString(JSONText);

    ASSERT_EQ(actual.get<std::string>("name"), "Halis");
    ASSERT_EQ(actual.get<int>("health_points"), 8600);
    ASSERT_EQ(actual.get<int>("damage"), 6900);
    ASSERT_EQ(actual.get<double>("attack_cooldown"), 4.3);
}

TEST(MulTest, missingCommaJSONTest) {
	try{
	    std::string JSONText = "{\"name\": \"Halis\"\"health_points\": 8600,\"damage\": 6900,\"attack_cooldown\": 4.3}";

        JSON::parseFromString(JSONText);

        ASSERT_TRUE(false);
    }
    catch (JSON::ParseException& e){
        ASSERT_TRUE(true);
    }
}

TEST(MulTest, missingColonJSONTest) {
	try{
	    std::string JSONText = "{\"name\" \"Halis\",\"health_points\": 8600,\"damage\": 6900,\"attack_cooldown\": 4.3}";
        
        JSON::parseFromString(JSONText);
    }
    catch (JSON::ParseException& e){
        ASSERT_TRUE(true);
    }
}

// Character & Adventurer tests

TEST(MulTest, HeroVSHeroTest) {
	Hero ch1("Codos",300,70,10,12.5,15,100,10,5,5,0.9,3);
	Hero ch2("Kowa",200,85,12,5.5,11,100,10,5,5,0.9,3);

    ch1.fightTilDeath(ch2);

    ASSERT_TRUE(!ch1.isAlive());
    ASSERT_EQ(ch2.getHealthPoints(), 230);
}

TEST(MulTest, HeroVSMonsterTest) {
	Hero ch1("Codos",300,70,10,12.5,15,100,10,5,5,0.9,3);
	Monster ch2("Kowa",200,85,13,5.5,5);

    ch1.fightTilDeath(ch2);

    ASSERT_TRUE(!ch1.isAlive());
    ASSERT_EQ(ch2.getHealthPoints(), 125);
}

TEST(MulTest, MonsterVSHeroTest) {
	Monster ch1("Codos",60,70,11,12.5,4);
	Hero ch2("Kowa",200,85,12,5.5,11,100,10,5,5,0.9,3);

    ch1.fightTilDeath(ch2);

    ASSERT_TRUE(!ch1.isAlive());
    ASSERT_EQ(ch2.getHealthPoints(), 200);
}

TEST(MulTest, MonsterVSMonsterTest) {
	Monster ch1("Codos",60,70,11,12.5,4);
	Monster ch2("Kowa",200,85,13,5.5,5);

    ch1.fightTilDeath(ch2);

    ASSERT_TRUE(!ch1.isAlive());
    ASSERT_EQ(ch2.getHealthPoints(), 200);
}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}