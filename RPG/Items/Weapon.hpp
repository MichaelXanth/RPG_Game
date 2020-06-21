/* File: Weapon.hpp */

#ifndef __WEAPON_HEADER__
#define __WEAPON_HEADER__

#include "Items.hpp"

class Weapon : public Item{

    private:
        const unsigned int damage;
        const bool twoHanded;

    public:
        Weapon(const std::string &, const unsigned int &, const unsigned int &, const unsigned int &, const bool &);
        ~Weapon();

        const unsigned int GetDamage(void) const;
        const bool TwoHanded(void) const;
};

#endif // __WEAPON_HEADER__
