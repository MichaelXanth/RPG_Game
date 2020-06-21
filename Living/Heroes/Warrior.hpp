/* File: Warrior.hpp */

#ifndef __WARRIOR_HEADER__
#define __WARRIOR_HEADER__

#include "Hero.hpp"

class Warrior : public Hero{

    public:
        Warrior(const std::string &, const int &, const int &, const unsigned int &, const unsigned int &,
                const unsigned int &, const float &, const unsigned int &);
        ~Warrior();

        void LevelUp(void);
};

#endif // __WARRIOR_HEADER__
