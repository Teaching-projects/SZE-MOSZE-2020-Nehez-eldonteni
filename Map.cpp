#include "Map.h"




Map::mapType Map::readFile(const std::string filename){
    std::ifstream ifsMap(filename);

	if (ifsMap.fail())
		throw std::runtime_error("Couldn't open file");

    mapType fileMap;
	std::string line;

	while (std::getline(ifsMap, line)) {
        std::vector<type> lineMap;
		for (auto c : line){
            if (c == '#')
                lineMap.push_back(type::Wall);
            else if (c == ' ')
                lineMap.push_back(type::Free);
        }

        fileMap.push_back(lineMap);
	}

	ifsMap.close();

    return fileMap;
}