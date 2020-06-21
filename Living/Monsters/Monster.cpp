/* File: Monster.cpp */

#include <cstdlib>

#include "../../Spells/Spell.hpp"
#include "Monster.hpp"

unsigned int Monster::baseHealth = 24;
unsigned int Monster::baseDamage = 8;
unsigned int Monster::baseDefence = 10;
float Monster::baseAvoidance = 0.101;

Monster::Monster(const std::string& name, const unsigned int& health, const unsigned int& lvl, const unsigned int& setMinDmg,
                 const unsigned int& setMaxDmg, const unsigned int& setDef, const float& setAvoidance)
                 : Living(name, health ,lvl), oldMinDamage(0), oldMaxDamage(0), oldDefence(0), oldAvoidance(0),
                   damageAffectedForRounds(0), defenceAffectedForRounds(0), avoidanceAffectedForRounds(0),
                   minDamage(setMinDmg), maxDamage(setMaxDmg), defence(setDef), avoidance(setAvoidance)
{}

Monster::~Monster()
{}

unsigned int Monster::MonsterGetBaseHP()
{
    return baseHealth;
}

unsigned int Monster::MonsterGetBaseDamage()
{
    return baseDamage;
}

unsigned int Monster::MonsterGetBaseDefence()
{
    return baseDefence;
}

float Monster::MonsterGetBaseAvoidance()
{
    return baseAvoidance;
}

unsigned int Monster::MonsterGetDamage()
{
        return (rand() % (maxDamage - minDamage + 1)) + minDamage;
}

unsigned int Monster::MonsterGetDefence()
{
    return defence;
}

float Monster::MonsterGetAvoidance()
{
    return avoidance;
}

void Monster::HitBySpell(Spell* hitSpell)
{
    unsigned int rounds;

    switch(hitSpell->ReduceStat(rounds))//gets the rounds of the effect
    {
        case 1:
            avoidanceAffectedForRounds += rounds;//adds the rounds of the effect

            if(((100 - (double)hitSpell ->GetAvoidanceReduction()) / 100) * avoidance < 0)//if the new avoidance is below 0 then it is set to 0
                avoidance = 0.0;
            else
            {
                oldAvoidance += avoidance;//stores the old avoidance so that it can be restored after the end of the effect
                avoidance = ((100 - (double)hitSpell ->GetAvoidanceReduction()) / 100) * avoidance;//reduces the avoidance
            }
            break;
        case 2:
            damageAffectedForRounds += rounds;//adds the rounds of the effect

            if(minDamage - hitSpell ->GetDamageReduction() < 0)//if the new damage is below 0 then it is set to 0
                minDamage = 0;
            else
            {
                oldMinDamage += minDamage;//stores the old damage so that it can be restored after the end of the effect
                minDamage = minDamage - hitSpell ->GetDamageReduction();//reduces the damage
            }

            if(maxDamage - hitSpell ->GetDamageReduction() < 0)
                maxDamage = 0;
            else
            {
                oldMaxDamage += maxDamage;
                maxDamage = maxDamage - hitSpell ->GetDamageReduction();
            }
            break;
        case 3:
            defenceAffectedForRounds += rounds;//adds the rounds of the effect

            if(defence - hitSpell ->GetDefenceReduction() < 0)//if the new damage is below 0 then it is set to 0
                defence = 0;
            else
            {
                oldDefence += defence;//stores the old damage so that it can be restored after the end of the effect
                defence = defence - hitSpell ->GetDefenceReduction();//reduces the damage
            }
            break;
    }
}

void Monster::EndRound(void)
{
    if(healthPower + (5 * healthPower) / 100 < maxHP)//monsters restore 5% health each turn
        healthPower = healthPower + (5 * healthPower) / 100;

    if(avoidanceAffectedForRounds > 0)//reduces the round the effect lasts after the end of a turn
    {
        avoidanceAffectedForRounds--;

        if(avoidanceAffectedForRounds == 0){//sets avoidance to its old value
            avoidance = oldAvoidance;
            oldAvoidance = 0;
        }
    }

    if(damageAffectedForRounds > 0)//reduces the round the effect lasts after the end of a turn
    {
        damageAffectedForRounds--;

        if (damageAffectedForRounds == 0){//sets damage to its old value
            minDamage = oldMinDamage;
            maxDamage = oldMaxDamage;
            oldMinDamage = 0;
            oldMaxDamage = 0;
        }
    }

    if(defenceAffectedForRounds > 0)//reduces the round the effect lasts after the end of a turn
    {
        defenceAffectedForRounds--;

        if (defenceAffectedForRounds == 0){//sets defence to its old value
            defence = oldDefence;
            oldDefence = 0;
        }
    }
}

const unsigned int Monster::GetMinDamage(void) const
{
    return minDamage;
}

const unsigned int Monster::GetMaxDamage(void) const
{
    return maxDamage;
}
