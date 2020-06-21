/* File: FireSpell.hpp */

#ifndef __FIRESPELL_HPP__
#define __FIRESPELL_HPP__

#include "Spell.hpp"

class FireSpell : public Spell{

    private:
        const unsigned int reduceDefenceBy;

    public:
        FireSpell(const std::string &, const unsigned int &, const unsigned int &, const unsigned int &,
                  const unsigned int &, const unsigned int &, const unsigned int &, const unsigned int &);
        ~FireSpell();
        
        short ReduceStat(unsigned int&);
        /*void ReduceDefence(Living&);*/

        const unsigned int GetDefenceReduction(void) const;
};

#endif
