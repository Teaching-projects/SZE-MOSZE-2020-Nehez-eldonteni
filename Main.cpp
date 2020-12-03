#include <iostream>
#include <map>
#include <string>
#include <filesystem>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <list>
#include <vector>
#include <ostream>
#include <fstream>

#include "PreparedGame.h"
#include "HeroTextRenderer.h"
#include "ObserverTextRenderer.h"
#include "CharacterSVGRenderer.h"
#include "ObserverSVGRenderer.h"


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


int main(int argc, char** argv){
    if (argc != 2) bad_exit(1);
    if (!std::filesystem::exists(argv[1])) bad_exit(2);

    try {
        PreparedGame pg(argv[1]);
        
        pg.registerRenderer(new HeroTextRenderer());
        pg.registerRenderer(new HeroTextRenderer(new std::ofstream("log.txt")));
        pg.registerRenderer(new ObserverTextRenderer(new std::ofstream("logo.txt")));
        pg.registerRenderer(new CharacterSVGRenderer("output.svg"));
        pg.registerRenderer(new ObserverSVGRenderer("outputo.svg"));

        pg.run();

    } catch (const JSON::ParseException& e) {
        bad_exit(4);
    }
    catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
