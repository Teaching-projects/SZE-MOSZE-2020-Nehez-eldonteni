#include <gtest/gtest.h>

#include "../JSON.h"

TEST(MulTest, stringTest) {
	std::string JSONText = "{\"name\": \"Halis\",\"health_points\": 8600,\"damage\": 6900,\"attack_cooldown\": 4.3}}";
	
    JSON actual = JSON::parseFromString(JSONText);

    ASSERT_EQ(actual.get<std::string>("name"), "Halis");
    ASSERT_EQ(actual.get<int>("health_points"), 8600);
    ASSERT_EQ(actual.get<int>("damage"), 6900);
    ASSERT_EQ(actual.get<double>("attack_cooldown"), 4.3);
}

TEST(MulTest, fileTest) {
	std::string filename = "units/kowa.json";
	
    JSON actual = JSON::parseFromFile(filename);

    ASSERT_EQ(actual.get<std::string>("name"), "Kowa");
    ASSERT_EQ(actual.get<int>("health_points"), 200);
    ASSERT_EQ(actual.get<int>("damage"), 85);
    ASSERT_EQ(actual.get<double>("attack_cooldown"), 5.5);
}

TEST(MulTest, streamTest) {
	std::fstream file("units/codos.json");
    
    JSON actual = JSON::parseFromStream(file);

    ASSERT_EQ(actual.get<std::string>("name"), "Codos");
    ASSERT_EQ(actual.get<int>("health_points"), 300);
    ASSERT_EQ(actual.get<int>("damage"), 70);
    ASSERT_EQ(actual.get<double>("attack_cooldown"), 12.5);
}

TEST(MulTest, syntaxErrorTest) {
	try{
        std::string filename = "units/badkowa.json";
        
        JSON actual = JSON::parseFromFile(filename);
        
        ASSERT_TRUE(false);
    }
    catch (JSON::ParseException& e){
        ASSERT_TRUE(true);
    }
}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}