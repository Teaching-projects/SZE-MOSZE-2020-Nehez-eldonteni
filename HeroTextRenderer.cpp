#include "HeroTextRenderer.h"

#include "Game.h"

void HeroTextRenderer::render(const Game& game) const{
    Map* gameMap = game.getMap();
    Game::unit gameHero = game.getHero();

    int mapWidth = gameMap->getWidth();
    int mapHeight = gameMap->getHeight();

    int light = dynamic_cast<Hero*>(gameHero.character)->getLightRadius();
    
    int left = gameHero.posx - light;
    int right = gameHero.posx + light;
    int top = gameHero.posy - light;
    int bot = gameHero.posy + light;

    if (left < 0) left = 0;
    if (top < 0) top = 0;
    if (right > mapWidth - 1) right = mapWidth - 1;
    if (bot > mapHeight - 1) bot = mapHeight - 1;

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