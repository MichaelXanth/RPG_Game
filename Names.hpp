/* File: Names.hpp */

#ifndef __NAMES_DATABASE_HEADER__
#define __NAMES_DATABASE_HEADER__

#include <vector>
#include <string>

class Names{
    public:
        Names();
        std::vector<std::string> names;
        std::vector<std::string> weaponsNames;
        std::vector<std::string> armorsNames;
        std::vector<std::string> potionsNames;
        std::vector<std::string> iceSpellsNames;
        std::vector<std::string> fireSpellsNames;
        std::vector<std::string> lightingSpellsNames;
};

#endif // __NAMES_DATABASE_HEADER__
