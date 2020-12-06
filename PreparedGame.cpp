#include "PreparedGame.h"

void PreparedGame::loadGame(const std::string fileName) {
    JSON gameJSON = JSON::parseFromFile(fileName);

    this->setMap(new MarkedMap(gameJSON.get<std::string>("map")));
    
    MarkedMap* mm = dynamic_cast<MarkedMap*>(gameMap);

    this->putHero(Hero::parse(gameJSON.get<std::string>("hero")), mm->getHeroPosition().posx,mm->getHeroPosition().posy);
    
    std::vector<char> monsterChars = mm->getMonsterChars();
    
    for (auto mc : monsterChars) {
        std::vector<MarkedMap::unitPos> mpos = mm->getMonsterPositions(mc);

        for (auto m : mpos) {
            std::string monsterKey = "monster-";
            monsterKey += mc;
            
            Monster mcMonster = Monster::parse(gameJSON.get<std::string>(monsterKey));
            this->putMonster(mcMonster, m.posx, m.posy);
        }
    }

    std::string wallFilename;
    std::string freeFilename;
    try{
        wallFilename = gameJSON.get<std::string>("wall_texture");
        freeFilename = gameJSON.get<std::string>("free_texture");
    } catch (const std::exception& e){
        std::cout << "asd";
        wallFilename = "";
        freeFilename = "";
    }

    this->setWallTexture(wallFilename);
    this->setFreeTexture(freeFilename);
}

void PreparedGame::registerRenderer(Renderer* r){
    renderers.push_back(r);
}