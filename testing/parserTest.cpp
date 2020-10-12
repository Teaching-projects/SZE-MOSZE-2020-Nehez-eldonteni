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

    actual = JSONParser::parse(JSONText);

    for(auto data : actual){
        ASSERT_EQ(expected[data.first], data.second);
    }
}

TEST(MulTest, fileTest) {
	std::string filename = "units/halis.json";
	
	std::map<std::string, std::string> actual;
    std::map<std::string, std::string> expected{
        {"name", "Halis"},
        {"hp", "8600"},
        {"dmg", "6900"}
    };
	
    actual = JSONParser::parse(filename);

    for(auto data : actual){
        ASSERT_EQ(expected[data.first], data.second);
    }
}

TEST(MulTest, streamTest) {
	
	std::map<std::string, std::string> actual;
    std::map<std::string, std::string> expected{
        {"name", "Halis"},
        {"hp", "8600"},
        {"dmg", "6900"}
    };
	std::fstream file("units/halis.json");
    actual = JSONParser::parse(file);

    for(auto data : actual){
        ASSERT_EQ(expected[data.first], data.second);
    }
}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}