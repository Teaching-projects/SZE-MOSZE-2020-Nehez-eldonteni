#include "CharacterSVGRenderer.h"

#include "Game.h"

void CharacterSVGRenderer::render(const Game& game) const{
    Map* gameMap = game.getMap();
    Game::unit gameHero = game.getHero();

    int mapWidth = gameMap->getWidth();
    int mapHeight = gameMap->getHeight();

    std::string walltexture = game.getWallTexture();
    std::string freetexture = game.getFreeTexture();

    std::string herotexture = gameHero.character->getTexture();

    int light = dynamic_cast<Hero*>(gameHero.character)->getLightRadius();
    
    int left = gameHero.posx - light;
    int right = gameHero.posx + light;
    int top = gameHero.posy - light;
    int bot = gameHero.posy + light;

    if (left < 0) left = 0;
    if (top < 0) top = 0;
    if (right > mapWidth - 1) right = mapWidth - 1;
    if (bot > mapHeight - 1) bot = mapHeight - 1;
    
    std::ofstream ofs(filename);

    ofs << "<svg xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink= \"http://www.w3.org/1999/xlink\" width=\"" << mapWidth*10 << "\" height=\"" << mapHeight*10 << "\">\n";


    ofs << "<pattern id=\"wall\" width=\"10\" height=\"10\">";
    if (walltexture != "")
        ofs << walltexture << "\n";
    else
        ofs << "<image id=\"wall\" width=\"10\" height=\"10\" xlink:href=\"data:img/png;base64,iVBORw0KGgoAAAANSUhEUgAAAAoAAAAKCAYAAACNMs+9AAAAHElEQVQYlWNkYGD4z0AEYCJGEcOoQuooZGBgAACmFwETVLv3XgAAAABJRU5ErkJggg==\"/>\n";
    ofs << "</pattern>";


    ofs << "<pattern id=\"free\" width=\"10\" height=\"10\">";
    if (freetexture != "")
        ofs << freetexture << "\n";
    else
        ofs << "<image id=\"free\" width=\"10\" height=\"10\" xlink:href=\"data:img/png;base64,iVBORw0KGgoAAAANSUhEUgAAAAoAAAAKCAYAAACNMs+9AAAAHElEQVQYlWNkYGD4z0AEYCJGEcOoQuooZGBgAACmFwETVLv3XgAAAABJRU5ErkJggg==\"/>\n";
    ofs << "</pattern>";
    

    ofs << "<pattern id=\"hero\" width=\"10\" height=\"10\">";
    if (herotexture != "")
        ofs << herotexture << "\n";
    else
        ofs << "<image id=\"hero\" width=\"10\" height=\"10\" xlink:href=\"data:img/png;base64,iVBORw0KGgoAAAANSUhEUgAAAAoAAAAKCAYAAACNMs+9AAAAHElEQVQYlWNkYGD4z0AEYCJGEcOoQuooZGBgAACmFwETVLv3XgAAAABJRU5ErkJggg==\"/>\n";
    ofs << "</pattern>";


    std::map<std::string, std::string> monsterTextures = game.getEveryMonsterNameAndTexture();

    for (auto mt: monsterTextures){
        ofs << "<pattern id=\"" << mt.first << "\" width=\"10\" height=\"10\">";
        if (mt.second != "")
            ofs << mt.second << "\n";
        else
            ofs << "<image id=\"" << mt.first << "\" width=\"10\" height=\"10\" xlink:href=\"data:img/png;base64,iVBORw0KGgoAAAANSUhEUgAAAAoAAAAKCAYAAACNMs+9AAAAHElEQVQYlWNkYGD4z0AEYCJGEcOoQuooZGBgAACmFwETVLv3XgAAAABJRU5ErkJggg==\"/>\n";
        ofs << "</pattern>";
    }
    

    for (int i = top; i <= bot; i++) {
        int x = i-top;
        for (int j = left; j <= right; j++) {
            int y = j-left;
            try
            {
                if (gameMap->get(j,i) == Map::type::Wall)
                    ofs << "<rect x=\"" << y*10 << "\" y=\"" << x*10 << "\" width=\"10\" height=\"10\" style=\"fill:url(#" << "wall" << ")\"/>\n";
                else if (gameHero.posx == j && gameHero.posy == i)
                    ofs << "<rect x=\"" << y*10 << "\" y=\"" << x*10 << "\" width=\"10\" height=\"10\" style=\"fill:url(#" << "hero" << ")\"/>\n";
                else{
                    int monsterCountInPos = game.getEveryMonsterIdxInPos(j, i).size();
                    
                    if (monsterCountInPos >= 1)
                        ofs << "<rect x=\"" << y*10 << "\" y=\"" << x*10 << "\" width=\"10\" height=\"10\" style=\"fill:url(#" << game.getMonsterNameInPos(j,i) << ")\"/>\n";
                    else
                        ofs << "<rect x=\"" << y*10 << "\" y=\"" << x*10 << "\" width=\"10\" height=\"10\" style=\"fill:url(#" << "free" << ")\"/>\n";
                }
            }
            catch (Map::WrongIndexException& e){
                ofs << "<rect x=\"" << y*10 << "\" y=\"" << i*10 << "\" width=\"10\" height=\"10\" style=\"fill:url(#" << "wall" << ")\"/>\n";
            }
            
        }
    }

    ofs << "</svg>";

    ofs.flush();
    ofs.close();
}