#include "Game.h"


Game::Game(std::string mapfilename) :isMapSet(false), isHeroSet(false), isMonstersSet(false), isGameStarted(false), gameHero() {
    Map m(mapfilename);
    setMap(m);
}

Game::~Game(){
    delete gameHero.character;
    delete gameMap;
    for (auto m:gameMonsters){
        delete m.character;
    }
}

void Game::setMap(Map map){
    if (isGameStarted)
        throw GameAlreadyStartedException("Cannot change map: the game has already started!");
    
    if (isHeroSet || isMonstersSet)
        throw AlreadyHasUnitsException("The current map has units already so it cannot be changed!");
    
    gameMap = new Map(map);

    isMapSet = true;
}

void Game::setMap(Map* map){
    if (isGameStarted)
        throw GameAlreadyStartedException("Cannot change map: the game has already started!");
    
    if (isHeroSet || isMonstersSet)
        throw AlreadyHasUnitsException("The current map has units already so it cannot be changed!");
    
    gameMap = map;

    isMapSet = true;
}

void Game::putHero(Hero hero, int x, int y){
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

void Game::putMonster(Monster monster, int x, int y){ 
    if (!isMapSet)
        throw Map::WrongIndexException("No map has been assigned!");
    
    if (gameMap->get(x,y) == Map::type::Wall)
        throw OccupiedException("The position is occupied!");
    
    gameMonsters.push_back({new Monster(monster), x, y});

    isMonstersSet = true;
}

std::vector<int> Game::getEveryMonsterIdxInPos(int x, int y){
    std::vector<int> monsterIdx;
    for (unsigned int i = 0; i < gameMonsters.size(); i++) {
        if (gameMonsters[i].posx == x && gameMonsters[i].posy == y)
            monsterIdx.push_back(i);
    }

    return monsterIdx;
}

void Game::drawMap(){
    int mapWidth = gameMap->getWidth();
    int mapHeight = gameMap->getHeight();

    std::cout << "╔";
    for (int i = 0; i < mapWidth; i++)
        std::cout << "══";
    
    std::cout << "╗" << std::endl;

    for (int i = 0; i < mapHeight; i++) {
        std::cout << "║";
        for (int j = 0; j < mapWidth; j++) {
            try
            {
                if (gameMap->get(j,i) == Map::type::Wall)
                    std::cout << "██";
                else if (gameHero.posx == j && gameHero.posy == i)
                    std::cout << "┣┫";
                else{
                    int monsterCountInPos = getEveryMonsterIdxInPos(j, i).size();
                    if (monsterCountInPos == 1)
                        std::cout << "M░";
                    else if (monsterCountInPos > 1)
                        std::cout << "MM";
                    else
                        std::cout << "░░";
                }
            }
            catch (Map::WrongIndexException& e){
                std::cout << "██";
            }
            
        }
        std::cout << "║" << std::endl;
    }

    std::cout << "╚";
    for (int i = 0; i < mapWidth; i++)
        std::cout << "══";
    
    std::cout << "╝" << std::endl;
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