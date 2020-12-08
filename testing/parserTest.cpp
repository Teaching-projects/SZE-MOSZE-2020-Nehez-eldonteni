#include <gtest/gtest.h>

#include "../JSON.h"
#include "../Monster.h"
#include "../Hero.h"
#include "../Map.h"
#include "../MarkedMap.h"
#include "../Game.h"

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

// Monster/Hero tests

TEST(MulTest, MonsterData) {
    Monster ch1("Kowa",200,85,13,5.5,5,"test.json");

    ASSERT_EQ(ch1.getName(), "Kowa");
    ASSERT_EQ(ch1.getAttackCoolDown(), 5.5);
    ASSERT_EQ(ch1.getCurrentCooldown(), 5.5);
    ASSERT_EQ(ch1.getDefense(), 5);
    ASSERT_EQ(ch1.getMaxHealthPoints(), 200);
    ASSERT_EQ(ch1.getHealthPoints(), 200);
    ASSERT_EQ(ch1.getPhysicalDamage(), 85);
    ASSERT_EQ(ch1.getMagicalDamage(), 13);
    ASSERT_EQ(ch1.getTexture(), "test.json");
}

TEST(MulTest, HeroData) {
    Hero ch1("Kowa",200,85,12,5.5,11,2,1,100,10,5,5,0.9,3,"nevergonnagiveyouup.json");

    ASSERT_EQ(ch1.getName(), "Kowa");
    ASSERT_EQ(ch1.getAttackCoolDown(), 5.5);
    ASSERT_EQ(ch1.getCurrentCooldown(), 5.5);
    ASSERT_EQ(ch1.getDefense(), 11);
    ASSERT_EQ(ch1.getMaxHealthPoints(), 200);
    ASSERT_EQ(ch1.getHealthPoints(), 200);
    ASSERT_EQ(ch1.getPhysicalDamage(), 85);
    ASSERT_EQ(ch1.getMagicalDamage(), 12);
    ASSERT_EQ(ch1.getLevel(), 1);
    ASSERT_EQ(ch1.getLightRadius(), 2);
    ASSERT_EQ(ch1.getTexture(), "nevergonnagiveyouup.json");
}

TEST(MulTest, HeroLevelupTest) {
    Hero ch1("Kowa",200,75,15,5.5,11,2,1,50,10,5,5,0.9,3,"");
    Monster ch2("Codos",300,70,11,12.5,1,"");

    ASSERT_EQ(ch1.getLevel(), 1);

    ch1.attackEnemy(ch2);

    ASSERT_EQ(ch1.getLevel(), 2);

    ASSERT_EQ(ch1.getAttackCoolDown(), 4.95);
    ASSERT_EQ(ch1.getDefense(), 14);
    ASSERT_EQ(ch1.getMaxHealthPoints(), 210);
    ASSERT_EQ(ch1.getHealthPoints(), 210);
    ASSERT_EQ(ch1.getPhysicalDamage(), 80);
    ASSERT_EQ(ch1.getMagicalDamage(), 20);
    ASSERT_EQ(ch1.getLightRadius(), 3);

    ch1.attackEnemy(ch2);

    ASSERT_EQ(ch1.getLevel(), 4);
}

TEST(MulTest, HeroVSHeroTest) {
    Hero ch1("Codos",300,70,10,12.5,15,2,1,100,10,5,5,0.9,3,"");
    Hero ch2("Kowa",200,85,12,5.5,11,2,1,100,10,5,5,0.9,3,"");

    ch1.fightTilDeath(ch2);

    ASSERT_TRUE(!ch1.isAlive());
    ASSERT_EQ(ch2.getHealthPoints(), 230);
}

TEST(MulTest, HeroVSMonsterTest) {
    Hero ch1("Codos",300,70,10,12.5,15,2,1,100,10,5,5,0.9,3,"");
    Monster ch2("Kowa",200,85,13,5.5,5,"");

    ch1.fightTilDeath(ch2);

    ASSERT_TRUE(!ch1.isAlive());
    ASSERT_EQ(ch2.getHealthPoints(), 125);
}

TEST(MulTest, MonsterVSHeroTest) {
    Monster ch1("Codos",60,70,11,12.5,4,"");
    Hero ch2("Kowa",200,85,12,5.5,11,2,1,100,10,5,5,0.9,3,"");

    ch1.fightTilDeath(ch2);

    ASSERT_TRUE(!ch1.isAlive());
    ASSERT_EQ(ch2.getHealthPoints(), 200);
}

TEST(MulTest, MonsterVSMonsterTest) {
    Monster ch1("Codos",60,70,11,12.5,4,"");
    Monster ch2("Kowa",200,85,13,5.5,5,"");

    ch1.fightTilDeath(ch2);

    ASSERT_TRUE(!ch1.isAlive());
    ASSERT_EQ(ch2.getHealthPoints(), 200);
}

// Game/Map tests

TEST(MulTest, MapTest) {
    Map m("../map1.txt");
    
    ASSERT_EQ(m.getHeight(), 7);
    ASSERT_EQ(m.getWidth(), 20);

    ASSERT_EQ(m.get(1,0), Map::type::Wall);
    ASSERT_EQ(m.get(1,1), Map::type::Free);
}

TEST(MulTest, MarkedMapTest) {
    MarkedMap mm("../markedmap1.txt");
    
    ASSERT_EQ(mm.getHeight(), 7);
    ASSERT_EQ(mm.getWidth(), 20);

    ASSERT_EQ(mm.get(1,0), Map::type::Wall);
    ASSERT_EQ(mm.get(1,1), Map::type::Free);

    ASSERT_EQ(mm.getHeroPosition().posx, 1);
    ASSERT_EQ(mm.getHeroPosition().posy, 1);
}

TEST(MulTest, GameTest) {
    Game g("../map1.txt");

    Monster ch1("Codos",60,70,11,12.5,4,"");
    Hero ch2("Kowa",200,85,12,5.5,11,2,1,100,10,5,5,0.9,3,""); 

    g.putHero(ch2, 1, 2);
    g.putMonster(ch1, 1, 5);
    
    ASSERT_EQ(g.getMap()->getHeight(), 7);
    ASSERT_EQ(g.getMap()->getWidth(), 20);

    ASSERT_EQ(g.getHero().character->getName(), "Kowa");
    ASSERT_EQ(g.getHero().posx, 1);
    ASSERT_EQ(g.getHero().posy, 2);

    ASSERT_EQ(g.getMonsterNameInPos(1, 5), "Codos");
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}