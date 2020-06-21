/* File: LightingSpell.hpp */

#ifndef __LIGHTING_HPP__
#define __LIGHTING_HPP__

#include "Spell.hpp"

class LightingSpell : public Spell{

    private:
        const unsigned int reduceAvoidanceBy;

    public:
        LightingSpell(const std::string &, const unsigned int &, const unsigned int &, const unsigned int &,
                      const unsigned int &, const unsigned int &, const unsigned int &, const unsigned int &);
        ~LightingSpell();

        short ReduceStat(unsigned int&);
        /*void ReduceAvoidance(Living &);*/

        const unsigned int GetAvoidanceReduction(void) const;
};

#endif
