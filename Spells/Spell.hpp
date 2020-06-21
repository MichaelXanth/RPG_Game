/* File: Spell.hpp */

#ifndef __SPELL_HPP__
#define __SPELL_HPP__

#include <string>

class Hero;

class Spell{

    protected:
        const std::string  name;
        const unsigned int price;
        const unsigned int rounds;
        const unsigned int minDamage;
        const unsigned int maxDamage;
        const unsigned int minRequiredLevel;
        const unsigned int requiredMagicPower;

    public:
        Spell(const std::string &, const unsigned int &, const unsigned int &, const unsigned int &,
              const unsigned int &, const unsigned int &, const unsigned int &);

        virtual short ReduceStat(unsigned int&);

        void HeroRemoveEnegry(Hero &);
        /*void HeroAttacked(Hero &);*/

        unsigned int HeroDamage(Hero &);

        virtual const std::string  GetName(void) const;
        virtual const unsigned int GetPrice(void) const;
        virtual const unsigned int GetRounds(void) const;
        virtual const unsigned int GetMinDamage(void) const;
        virtual const unsigned int GetMaxDamage(void) const;
        virtual const unsigned int GetReqEnergy(void) const;
        virtual const unsigned int GetMinReqLevel(void) const;
        virtual const unsigned int GetDamageReduction(void) const;
        virtual const unsigned int GetDefenceReduction(void) const;
        virtual const unsigned int GetAvoidanceReduction(void) const;

        virtual ~Spell() = 0;
};

#endif // __SPELL_HPP__
