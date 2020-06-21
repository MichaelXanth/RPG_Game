/* File: Sorcerer.hpp */

#ifndef __SORCERER_HEADER__
#define __SORCERER_HEADER__

#include "Hero.hpp"

class Sorcerer : public Hero{

    public:
        Sorcerer(const std::string &, const int &, const int &, const unsigned int &, const unsigned int &,
                 const unsigned int &, const float &, const unsigned int &);
        ~Sorcerer();

        void LevelUp(void);
};

#endif // __SORCERER_HEADER__
