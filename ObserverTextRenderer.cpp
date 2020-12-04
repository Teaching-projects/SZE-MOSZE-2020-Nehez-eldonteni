#include "ObserverTextRenderer.h"
#include "Game.h"

void ObserverTextRenderer::render(const Game& game) const{
    Map* gameMap = game.getMap();
    Game::unit gameHero = game.getHero();

    int mapWidth = gameMap->getWidth();
    int mapHeight = gameMap->getHeight();
    
    int left = 0;
    int right = mapWidth - 1;
    int top = 0;
    int bot = mapHeight - 1;
    
    *outputStream << "╔";
    for (int i = left; i <= right; i++)
        *outputStream << "══";
    
    *outputStream << "╗" << std::endl;
    
    for (int i = top; i <= bot; i++) {
        *outputStream << "║";
        for (int j = left; j <= right; j++) {
            try
            {
                if (gameMap->get(j,i) == Map::type::Wall)
                    *outputStream << "██";
                else if (gameHero.posx == j && gameHero.posy == i)
                    *outputStream << "┣┫";
                else{
                    int monsterCountInPos = game.getEveryMonsterIdxInPos(j, i).size();
                    if (monsterCountInPos == 1)
                        *outputStream << "M░";
                    else if (monsterCountInPos > 1)
                        *outputStream << "MM";
                    else
                        *outputStream << "░░";
                }
            }
            catch (Map::WrongIndexException& e){
                *outputStream << "██";
            }
            
        }
        *outputStream << "║" << std::endl;
    }

    *outputStream << "╚";
    for (int i = left; i <= right; i++)
        *outputStream << "══";
    
    *outputStream << "╝" << std::endl;
}