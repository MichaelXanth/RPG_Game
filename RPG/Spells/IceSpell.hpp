/* File: IceSpell.hpp */

#ifndef __ICESPELL_HPP__
#define __ICESPELL_HPP__

#include "Spell.hpp"

class IceSpell : public Spell{

    private:
        const unsigned int reduceDamageBy;

    public:
        IceSpell(const std::string &, const unsigned int &, const unsigned int &, const unsigned int &,
                 const unsigned int &, const unsigned int &, const unsigned int &, const unsigned int &);
        ~IceSpell();

        short ReduceStat(unsigned int&);
        //void ReduceDamage(Living&);

        const unsigned int GetDamageReduction(void) const;
};

#endif
