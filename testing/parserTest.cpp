#include <gtest/gtest.h>

#include "../JSONParser.h"

TEST(MulTest, stringTest) {
	std::string JSONText = "{\"name\": \"Halis\",\"hp\": 8600,\"dmg\": 6900}";
	
    std::map<std::string, std::string> actual;
    std::map<std::string, std::string> expected{
        {"name", "Halis"},
        {"hp", "8600"},
        {"dmg", "6900"}
    };

    actual = JSONParser::parseString(JSONText);

    ASSERT_EQ(expected.size(), actual.size());

    for(auto data : expected){
        ASSERT_EQ(actual[data.first], data.second);
    }
}

TEST(MulTest, fileTest) {
	std::string filename = "units/badkowa.json";
	
	std::map<std::string, std::string> actual;
    std::map<std::string, std::string> expected{
        {"name", "Kowa"},
        {"hp", "4500"},
        {"dmg", "6000"}
    };
	
    actual = JSONParser::parseFile(filename);
    
    ASSERT_EQ(expected.size(), actual.size());

    for(auto data : expected){
        ASSERT_EQ(actual[data.first], data.second);
    }
}

TEST(MulTest, streamTest) {
	
	std::map<std::string, std::string> actual;
    std::map<std::string, std::string> expected{
        {"name", "Codos"},
        {"hp", "9000"},
        {"dmg", "5500"}
    };
	std::fstream file("units/codos.json");
    
    actual = JSONParser::parseStream(file);

    ASSERT_EQ(expected.size(), actual.size());

    for(auto data : expected){
        ASSERT_EQ(actual[data.first], data.second);
    }
}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}