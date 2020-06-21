/* File: Battle.hpp */

#ifndef __BATTLE_HPP__
#define __BATTLE_HPP__

#include <vector>

class Monster;
class Hero;

class Battle{

    public:
        static bool AttackWithWeapon(Hero &, Monster &);
        static bool MonsterAttack(Monster &, Hero &);
        static bool CastSpell(Hero &, Monster &);
        static bool ChangeWeapon(Hero &, bool = false);
        static bool ChangeArmor(Hero &, bool = false);
        static bool UsePotion(Hero &, bool = false);
        static bool BattleHappens(void);
        static Monster* FindMonster(unsigned int);//return a pointer to a random monster
};

#endif // __BATTLE_HPP__
