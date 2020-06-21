/* File: IceSpell.cpp */

#include "IceSpell.hpp"
#include "Spell.hpp"

IceSpell::IceSpell(const std::string& newName, const unsigned int& setPrice, const unsigned int& roundsAffected,
                   const unsigned int& setReqLevel, const unsigned int& setMinDamage, const unsigned int& setMaxDamage,
                   const unsigned int& setReqMagicPower, const unsigned int& damageReduction)
                   : Spell(newName,setPrice,roundsAffected,setMinDamage,setMaxDamage,setReqLevel,setReqMagicPower),
                     reduceDamageBy(damageReduction)
{}

IceSpell::~IceSpell()
{}

short IceSpell::ReduceStat(unsigned int& roundsAf)//returns 2 for its type and returns the rounds its effect lasts
{
    roundsAf = rounds;
    return 2;
}

const unsigned int IceSpell::GetDamageReduction(void) const
{
    return reduceDamageBy;
}
