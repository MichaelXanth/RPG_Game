/* File: FireSpell.cpp */

#include "FireSpell.hpp"
#include "Spell.hpp"

FireSpell::FireSpell(const std::string& newName, const unsigned int& setPrice, const unsigned int& roundsAffected,
                     const unsigned int& setReqLevel, const unsigned int& setMinDamage, const unsigned int& setMaxDamage,
                     const unsigned int& setReqMagicPower, const unsigned int& defenceReduction)
                     : Spell(newName,setPrice,roundsAffected,setMinDamage,setMaxDamage,setReqLevel,setReqMagicPower),
                       reduceDefenceBy(defenceReduction)
{}

FireSpell::~FireSpell()
{}

short FireSpell::ReduceStat(unsigned int& roundsAf)//returns 3 for its type and returns the rounds its effect lasts
{
    roundsAf = rounds;
    return 3;
}

const unsigned int FireSpell::GetDefenceReduction(void) const
{
    return reduceDefenceBy;
}
