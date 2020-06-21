/* File: Paladin.hpp */

#ifndef __PALADIN_HEADER__
#define __PALADIN_HEADER__

#include "Hero.hpp"

class Paladin : public Hero{

    public:
        Paladin(const std::string &, const int &, const int &, const unsigned int &, const unsigned int &,
                const unsigned int &, const float &, const unsigned int &);
        ~Paladin();

        void LevelUp(void);
};

#endif // __PALADIN_HEADER__
