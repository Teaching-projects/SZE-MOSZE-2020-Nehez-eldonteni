#include "Map.h"


Map::type Map::get(int x, int y) const {
    if ((int)dataMap.size() < 0 || y < 0 || y >= (int)dataMap.size() || x < 0 || x >= (int)dataMap[y].size())
        throw WrongIndexException("The given coordinates are out of bound!");

    return dataMap[y][x];
}

Map::Map(const std::string filename){
    std::ifstream ifsMap(filename);

	if (ifsMap.fail())
		throw std::runtime_error("Couldn't open file");

    mapType fileMap;
	std::string line;
    int lc = 0;
	while (std::getline(ifsMap, line)) {
        std::vector<type> lineMap;
		for (auto c : line){
            if (c == '#')
                lineMap.push_back(type::Wall);
            else if (c == ' ')
                lineMap.push_back(type::Free);
        }
        lc++;
        fileMap.push_back(lineMap);
	}

	ifsMap.close();

    dataMap = fileMap;
}

int Map::getHeight() const{
    return dataMap.size();
}

int Map::getWidth() const{
    unsigned int max = 0;
    for (auto x:dataMap){
        if (x.size() > max)
            max = x.size();
    }

    return max;
}