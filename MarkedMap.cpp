#include "MarkedMap.h"


MarkedMap::MarkedMap(const std::string filename){
    std::ifstream ifsMap(filename);

	if (ifsMap.fail())
		throw std::runtime_error("Couldn't open file");

    mapType fileMap;
	std::string line;
    int y = 0;
	while (std::getline(ifsMap, line)) {
        std::vector<type> lineMap;
		int x = 0;
        for (auto c : line){
            if (c == '#')
                lineMap.push_back(type::Wall);
            else if (c == ' ')
                lineMap.push_back(type::Free);
            else if (c == 'H'){
                hero.type = 'H';
                hero.posx = x;
                hero.posy = y;

                lineMap.push_back(type::Free);
            }
            else if (c != '\r') {
                monsters.push_back({x,y,c});
                
                unsigned int j = 0;
                while (j < monsterChars.size() && monsterChars[j] != c)
                    j++;
                
                if (j>= monsterChars.size())
                    monsterChars.push_back(c);

                lineMap.push_back(type::Free);
            }

            x++;
        }

        fileMap.push_back(lineMap);

        y++;
	}

	ifsMap.close();

    dataMap = fileMap;
}

std::vector<MarkedMap::unitPos> MarkedMap::getMonsterPositions(char c) const {
    std::vector<unitPos> results;
    for (auto m : monsters) {
        if (m.type == c)
            results.push_back(m);
    }
    
    return results;
}