#include <gtest/gtest.h>

#include "../JSONParser.h"

TEST(MulTest, stringTest) {
	std::string JSONText = "{\"name\": \"Halis\",\"hp\": 8600,\"dmg\": 6900,\"attackcooldown\": 4.3}}";
	
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

TEST(MulTest, fileTest) {
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

TEST(MulTest, streamTest) {
	
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

TEST(MulTest, syntaxErrorTest) {
	try{
        std::string filename = "units/badkowa.json";
	
        std::map<std::string, std::string> actual;
        std::map<std::string, std::string> expected {
            {"name", "Kowa"},
            {"hp", "200"},
            {"dmg", "85"},
            {"attackcooldown", "5.5"}
        };
        
        actual = JSONParser::parseFile(filename);
    }
    catch (std::runtime_error& e){
        ASSERT_STREQ(e.what(), "Wrong JSON syntax!");
    }
}

int main(int argc, char* argv[]) {
	::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}