/* File: Potion.cpp */

#include "Potion.hpp"

Potion::Potion(const std::string& newName, const unsigned int& setPrice, const unsigned int& setMinReqLevel,
               const unsigned int& setStrength, const unsigned int& setDexterity, const float& setAgility)
               : Item(newName, setPrice, setMinReqLevel),
                 increaseStrength(setStrength), increaseDexterity(setDexterity), increaseAgility(setAgility)
{}

Potion::~Potion()
{}

unsigned int Potion::PotionIncreaseStrength(void) const
{
    return increaseStrength;
}

unsigned int Potion::PotionIncreaseDexterity(void) const
{
    return increaseDexterity;
}

float Potion::PotionIncreaseAgility(void) const
{
    return increaseAgility;
}
