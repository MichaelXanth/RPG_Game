/* File: LightingSpell.cpp */

#include "LightingSpell.hpp"
#include "Spell.hpp"

LightingSpell::LightingSpell(const std::string& newName, const unsigned int& setPrice, const unsigned int& roundsAffected,
                             const unsigned int& setReqLevel, const unsigned int& setMinDamage, const unsigned int& setMaxDamage,
                             const unsigned int& setReqMagicPower, const unsigned int& avoidanceReduction)
                             : Spell(newName,setPrice,roundsAffected,setMinDamage,setMaxDamage,setReqLevel,setReqMagicPower),
                               reduceAvoidanceBy(avoidanceReduction)
{}

LightingSpell::~LightingSpell()
{}

short LightingSpell::ReduceStat(unsigned int& roundsAf)//returns 1 for its type and returns the rounds its effect lasts
{
    roundsAf = rounds;
    return 1;
}

const unsigned int LightingSpell::GetAvoidanceReduction(void) const
{
    return reduceAvoidanceBy;
}
