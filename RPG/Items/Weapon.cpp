/* File: Weapon.cpp */

#include "Weapon.hpp"

Weapon::Weapon(const std::string& newName, const unsigned int& setPrice, const unsigned int& setMinReqLevel,
               const unsigned int& dmg, const bool& twoHands)
               : Item(newName, setPrice, setMinReqLevel), damage(dmg), twoHanded(twoHands)
{}

Weapon::~Weapon()
{}    

const unsigned int Weapon::GetDamage(void)  const
{
    return damage;
}

const bool Weapon::TwoHanded(void) const
{
    return twoHanded;
}
