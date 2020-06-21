/* File: Potion.hpp */

#ifndef __POTION_HEADER__
#define __POTION_HEADER__

#include "Items.hpp"

class Potion : public Item{

    private:
        const unsigned int increaseStrength;
        const unsigned int increaseDexterity;
        const float increaseAgility;

    public:
        Potion(const std::string &, const unsigned int &, const unsigned int &,
               const unsigned int &, const unsigned int &, const float &);
        ~Potion();

        unsigned int PotionIncreaseStrength(void) const;
        unsigned int PotionIncreaseDexterity(void) const;
        float PotionIncreaseAgility(void) const;
};

#endif // __POTION_HEADER__
