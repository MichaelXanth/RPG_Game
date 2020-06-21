/* File: Warrior.cpp */

#include "../../Spells/LightingSpell.hpp"
#include "../../Spells/FireSpell.hpp"
#include "../../Spells/IceSpell.hpp"
#include "../../Items/Weapon.hpp"
#include "../../Items/Potion.hpp"
#include "../../Items/Armor.hpp"
#include "Warrior.hpp"

Warrior::Warrior(const std::string& setName, const int& setHealth, const int& setLevel, const unsigned int& setMagic,
                 const unsigned int& setDexterity, const unsigned int& setStrength, const float& setAgility,
                 const unsigned int& startingMoney)
                 : Hero(setName, setHealth, setLevel, setMagic, setStrength, setDexterity, setAgility, startingMoney)
{}

Warrior::~Warrior()
{
    for(int i = iceSpellsArray.size(); !iceSpellsArray.empty(); i--)
    {
        delete iceSpellsArray[i - 1];
        iceSpellsArray.erase(iceSpellsArray.begin() + i - 1);
    }

    for(int i = fireSpellsArray.size(); !fireSpellsArray.empty(); i--)
    {
        delete fireSpellsArray[i - 1];
        fireSpellsArray.erase(fireSpellsArray.begin() + i - 1);
    }

    for(int i = lightingSpellsArray.size(); !lightingSpellsArray.empty(); i--)
    {
        delete lightingSpellsArray[i - 1];
        lightingSpellsArray.erase(lightingSpellsArray.begin() + i - 1);
    }

    for(int i = weaponsArray.size(); !weaponsArray.empty(); i--)
    {
        delete weaponsArray[i - 1];
        weaponsArray.erase(weaponsArray.begin() + i - 1);
    }

    for(int i = armorsArray.size(); !armorsArray.empty(); i--)
    {
        delete armorsArray[i - 1];
        armorsArray.erase(armorsArray.begin() + i - 1);
    }

    for(int i = potionsArray.size(); !potionsArray.empty(); i--)
    {
        delete potionsArray[i - 1];
        potionsArray.erase(potionsArray.begin() + i - 1);
    }
}

void Warrior::LevelUp(void)
{
    Living::LevelUp();
    maxMP += 5;
    maxHP += 5;
    healthPower += 5;
    strength += 5;
    dexterity += 3;
    agility += 0.015;
}
