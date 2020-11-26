#include <iostream>
#include <map>
#include <string>
#include <filesystem>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <list>
#include <vector>

#include "JSON.h"
#include "Hero.h"
#include "Monster.h"
#include "Game.h"




struct characterData
{
    std::string name;
    int x;
    int y;
};

const std::map<int,std::string> error_messages = {
    { 1 , "Bad number of arguments. Only a single scenario file should be provided." },
    { 2 , "The provided scenario file is not accessible." },
    { 3 , "The provided scenario file is invalid." },
    { 4 , "Parsing error." }
};

void bad_exit(int exitcode){
    std::cerr 
        << (error_messages.count(exitcode) ? error_messages.at(exitcode) : "Unknown error")
        << std::endl;
    exit(exitcode);
}

characterData separateData(std::string data) {
    std::stringstream hero(data);
    std::string segment;
    std::vector<std::string> seglist;

    while(std::getline(hero, segment, ';')){
        seglist.push_back(segment);
    }

    return characterData( {seglist[0], std::stoi(seglist[1]), std::stoi(seglist[2])} );
}


int main(int argc, char** argv){
    if (argc != 2) bad_exit(1);
    if (!std::filesystem::exists(argv[1])) bad_exit(2);

    std::string mapName;
    characterData heroData;
    std::list<characterData> monstersData;

    try {
        JSON scenario = JSON::parseFromFile(argv[1]); 
        if (!(scenario.count("map")&&scenario.count("hero")&&scenario.count("monsters"))) bad_exit(3);
        else {
            mapName = scenario.get<std::string>("map");

            heroData = separateData(scenario.get<std::string>("hero"));
            
            JSON::list monster_list=scenario.get<JSON::list>("monsters");
            
            for (auto x: monster_list){
                monstersData.push_back(separateData(std::get<std::string>(x)));
            }
        }
    } catch (const JSON::ParseException& e) {bad_exit(4);}

    try {
        Hero hero{Hero::parse(heroData.name)};

        Game game(mapName);

        game.putHero(hero, heroData.x, heroData.y);

        for (const auto& monster : monstersData){
            game.putMonster(Monster::parse(monster.name), monster.x, monster.y);
        }

        game.run();

    } catch (const JSON::ParseException& e) {bad_exit(4);}
    return 0;
}
