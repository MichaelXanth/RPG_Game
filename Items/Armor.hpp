/* File: Armor.hpp */

#ifndef __ARMOR_HEADER__
#define __ARMOR_HEADER__

#include "Items.hpp"

class Armor : public Item{

    private:
        const unsigned int damageReduction;

    public:
        Armor(const std::string &, const unsigned int &, const unsigned int &, const unsigned int &);
        ~Armor();

        const unsigned int GetDamageReduction(void) const;
};



#endif // __ARMOR_HEADER__
