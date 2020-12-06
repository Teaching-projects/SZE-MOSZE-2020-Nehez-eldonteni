#include "Game.h"


Game::Game(const std::string mapfilename) :isMapSet(false), isHeroSet(false), isMonstersSet(false), isGameStarted(false), gameHero() {
    Map m(mapfilename);
    setMap(m);
}

Game::~Game(){
    delete gameHero.character;
    delete gameMap;
    for (auto m:gameMonsters){
        delete m.character;
    }

    for (auto r : renderers){
        delete r;
    }
}

void Game::setMap(const Map map){
    if (isGameStarted)
        throw GameAlreadyStartedException("Cannot change map: the game has already started!");
    
    if (isHeroSet || isMonstersSet)
        throw AlreadyHasUnitsException("The current map has units already so it cannot be changed!");
    
    gameMap = new Map(map);

    isMapSet = true;
}

void Game::setWallTexture(const std::string filename) {

    std::ifstream ifs(filename);

    if (ifs.is_open()) {
        std::string fullTexture = "";
        std::string line = "";
        while (std::getline(ifs, line))
        {
            unsigned int j = 0;
            while (j < line.length() - 5 && line.substr(j,5) != "image") j++;
            if (j < line.length() - 5)
                fullTexture = line;
        }

        wallTexture = fullTexture;
    }
    else
    {
        throw std::runtime_error("SVG file not found!");
    }
}

void Game::setFreeTexture(const std::string filename){

    std::ifstream ifs(filename);

    if (ifs.is_open()) {
        std::string fullTexture = "";
        std::string line = "";
        while (std::getline(ifs, line))
        {
            unsigned int j = 0;
            while (j < line.length() - 5 && line.substr(j,5) != "image") j++;
            if (j < line.length() - 5)
                fullTexture = line;
        }

        freeTexture = fullTexture;
    }
    else
    {
        throw std::runtime_error("SVG file not found!");
    } 
}

std::map<std::string, std::string> Game::getEveryMonsterNameAndTexture() const{
    std::map<std::string, std::string> textures;

    for (auto m: gameMonsters) {
        std::string closeName = "";
        for (auto c: m.character->getName()){
            if (c != ' ')
                closeName += c;
        }
        std::pair<std::string, std::string> tt = {closeName, m.character->getTexture()};
        
        unsigned int j = 0;
        for (auto texture: textures){
            if (texture.first != tt.first)
                j++;
        }
        if (j >= textures.size()){
            textures[tt.first] = tt.second;
        }
    }

    return textures;
}

std::string Game::getMonsterNameInPos(const int x, const int y) const{
    unsigned int i = 0;
    while (i < gameMonsters.size() && (gameMonsters[i].posx != x || gameMonsters[i].posy != y)) {
        i++;
    }
    if (i < gameMonsters.size()){
        std::string closeName = "";
        for (auto c: gameMonsters[i].character->getName()){
            if (c != ' ')
                closeName += c;
        }
        return closeName;
    }
    else
        return "";    
}

void Game::setMap(Map* map){
    if (isGameStarted)
        throw GameAlreadyStartedException("Cannot change map: the game has already started!");
    
    if (isHeroSet || isMonstersSet)
        throw AlreadyHasUnitsException("The current map has units already so it cannot be changed!");
    
    gameMap = map;

    isMapSet = true;
}

void Game::putHero(const Hero hero, const int x, const int y){
    if (isGameStarted)
        throw GameAlreadyStartedException("Cannot put hero: the game has already started!");
    
    if (!isMapSet)
        throw Map::WrongIndexException("No map has been assigned!");
    
    if (isHeroSet)
        throw AlreadyHasHeroException("Hero has been already set!");

    if (gameMap->get(x,y) == Map::type::Wall)
        throw OccupiedException("The position is occupied!");
    
    gameHero.character = new Hero(hero);

    gameHero.posx = x;
    gameHero.posy = y;

    isHeroSet = true;
}

void Game::putMonster(const Monster monster, const int x, const int y){ 
    if (!isMapSet)
        throw Map::WrongIndexException("No map has been assigned!");
    
    if (gameMap->get(x,y) == Map::type::Wall)
        throw OccupiedException("The position is occupied!");
    
    gameMonsters.push_back({new Monster(monster), x, y});

    isMonstersSet = true;
}

void Game::registerRenderer(Renderer* r){
    renderers.push_back(r);
}

std::vector<int> Game::getEveryMonsterIdxInPos(int x, int y) const{
    std::vector<int> monsterIdx;
    for (unsigned int i = 0; i < gameMonsters.size(); i++) {
        if (gameMonsters[i].posx == x && gameMonsters[i].posy == y)
            monsterIdx.push_back(i);
    }

    return monsterIdx;
}

void Game::drawMap(){
    for (auto x : renderers){
        x->render(*this);
    }
}

void Game::fightMonsters(){
    std::vector<int> monstersInPos = getEveryMonsterIdxInPos(gameHero.posx, gameHero.posy);

    if (monstersInPos.size() > 0) {
        int j = 0;
        while (gameHero.character->isAlive() && j < (int)monstersInPos.size()){
            gameHero.character->fightTilDeath(*gameMonsters[monstersInPos[j]].character);

            j++;
        }

        std::sort(monstersInPos.begin(), monstersInPos.end());

        j = j - 1;
        while (j >= 0) {
            delete gameMonsters[monstersInPos[j]].character;
            gameMonsters.erase(gameMonsters.begin() + monstersInPos[j]);

            j--;
        }
    }
}

void Game::run(){
    if (!isMapSet || !isHeroSet || !isMonstersSet)
        throw NotInitializedException("The game has not been initialized!");
    
    isGameStarted = true;
    bool isTerminated = false;

    fightMonsters();

    drawMap();

    std::string input = "";
    do
    {
        std::cin >> input;

        bool wrongInput = true;

        if (input == "north" && gameMap->get(gameHero.posx, gameHero.posy - 1) == Map::type::Free){
            gameHero.posy -= 1;
            wrongInput = false;
        }
        else if (input == "south" && gameMap->get(gameHero.posx, gameHero.posy + 1) == Map::type::Free){
            gameHero.posy += 1;
            wrongInput = false;
        }
        else if (input == "east" && gameMap->get(gameHero.posx + 1, gameHero.posy) == Map::type::Free){
            gameHero.posx += 1;
            wrongInput = false;
        }
        else if (input == "west" && gameMap->get(gameHero.posx - 1, gameHero.posy) == Map::type::Free){
            gameHero.posx -= 1;
            wrongInput = false;
        }
        else if (input == "quit"){
            std::cout << "quiting " << std::endl;
            isTerminated = true;
        }


        if (!wrongInput)
            fightMonsters();

        drawMap();

    } while (!isTerminated && (gameHero.character->isAlive() && gameMonsters.size() > 0));
    
    if (isTerminated){
        std::cout << "Run terminated by user!" << std::endl;
    }
    else if (gameHero.character->isAlive())
        std::cout << gameHero.character->getName() << " cleared the map." << std::endl;
    else
        std::cout << gameHero.character->getName() << " died." << std::endl;
}