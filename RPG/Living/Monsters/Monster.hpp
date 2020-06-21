/* File: Monster.hpp */

#ifndef __MONSTER__HEADER__
#define __MONSTER__HEADER__

#include <string>

#include "../Living.hpp"

class Spell;

class Monster : public Living{

    private:
        unsigned int oldMinDamage;
        unsigned int oldMaxDamage;
        unsigned int oldDefence;
        float oldAvoidance;

    protected:
        static unsigned int baseHealth;
        static unsigned int baseDamage;
        static unsigned int baseDefence;
        static float baseAvoidance;

        unsigned int damageAffectedForRounds;
        unsigned int defenceAffectedForRounds;
        unsigned int avoidanceAffectedForRounds;
        unsigned int minDamage;
        unsigned int maxDamage;
        unsigned int defence;
        float avoidance;

    public:

        Monster(const std::string &, const unsigned int &, const unsigned int &, const unsigned int &,
                const unsigned int &, const unsigned int &, const float &);
        ~Monster();

        static unsigned int MonsterGetBaseDefence(void);
        static unsigned int MonsterGetBaseDamage(void);
        static unsigned int MonsterGetBaseHP(void);
        static float MonsterGetBaseAvoidance(void);

        unsigned int MonsterGetDefence(void);
        unsigned int MonsterGetDamage(void);
        float MonsterGetAvoidance(void);

        void HitBySpell(Spell *);
        void EndRound(void);

        const unsigned int GetMinDamage(void) const;
        const unsigned int GetMaxDamage(void) const;
};

#endif // __MONSTER__HEADER__
