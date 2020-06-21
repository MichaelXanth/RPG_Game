/* File: Spell.cpp */

#include <cstdlib>
#include <iostream>

#include "../Living/Heroes/Hero.hpp"
#include "Spell.hpp"

using namespace std;

Spell::Spell(const string& newName, const unsigned int& setPrice, const unsigned int& setRounds, const unsigned int& setMinDamage,
             const unsigned int& setMaxDamage, const unsigned int& setMinReqLevel, const unsigned int& setReqMP)
             : name(newName), price(setPrice), rounds(setRounds), minDamage(setMinDamage), maxDamage(setMaxDamage),
               minRequiredLevel(setMinReqLevel), requiredMagicPower(setReqMP)
{}

Spell::~Spell()
{}

short Spell::ReduceStat(unsigned int& rounds)
{}

void Spell::HeroRemoveEnegry(Hero& attackingHero)
{
    attackingHero.ReduceMagicPower(requiredMagicPower);//reduces hero's magic power in order for the spell to be used
}

unsigned int Spell::HeroDamage(Hero& attackingHero)//returns the hero damage caused by a spell
{
    unsigned int spellDmg = rand() % (GetMaxDamage() - GetMinDamage()) + GetMinDamage();
    return spellDmg + attackingHero.GetDexterity();
}

const unsigned int Spell::GetDamageReduction(void) const
{}

const unsigned int Spell::GetDefenceReduction(void) const
{}

const unsigned int Spell::GetAvoidanceReduction(void) const
{}

const string Spell::GetName(void) const
{
    return name;
}

const unsigned int Spell::GetPrice(void) const
{
    return price;
}

const unsigned int Spell::GetRounds(void) const
{
    return rounds;
}

const unsigned int Spell::GetMinDamage(void) const
{
    return minDamage;
}

const unsigned int Spell::GetMaxDamage(void) const
{
    return maxDamage;
}

const unsigned int Spell::GetReqEnergy(void) const
{
    return requiredMagicPower;
}

const unsigned int Spell::GetMinReqLevel(void) const
{
    return minRequiredLevel;
}
