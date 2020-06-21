/* File: Armor.cpp */

#include "Armor.hpp"

Armor::Armor(const std::string& newName, const unsigned int& setPrice, const unsigned int& setMinReqLevel,
             const unsigned int& dmgRed)
             : Item(newName, setPrice, setMinReqLevel), damageReduction(dmgRed)
{}

Armor::~Armor()
{}

const unsigned int Armor::GetDamageReduction(void) const
{
    return damageReduction;
}
