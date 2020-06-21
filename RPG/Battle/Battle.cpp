/* File: Battle.cpp */

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <unistd.h>

#include "../Grid/Grid.hpp"
#include "../Items/Armor.hpp"
#include "../Items/Potion.hpp"
#include "../Items/Weapon.hpp"
#include "../Living/Heroes/Hero.hpp"
#include "../Living/Monsters/Dragon.hpp"
#include "../Living/Monsters/Exoskeleton.hpp"
#include "../Living/Monsters/Monster.hpp"
#include "../Living/Monsters/Spirit.hpp"
#include "../Names.hpp"
#include "../Spells/Spell.hpp"
#include "Battle.hpp"

using namespace std;

// Determines if a battle will happen or not
bool Battle::BattleHappens(void) 
{
    float chanceToFight = 0.05;
    float determ = (double)rand() / RAND_MAX;

    if (chanceToFight > determ)
        return true;
    else
        return false;
}

// It randomly creates a monster and gives it stats according to its type and the heroes level
Monster* Battle::FindMonster(unsigned int heroLvl) 
{
    short monChance = rand() % 3;
    Monster* newMon = NULL;

    switch(monChance)
    {
        case 0:
            newMon = new Exoskeleton("Exoskeleton",/*increased defence*/
                                     Monster::MonsterGetBaseHP() + heroLvl * 4 , heroLvl,
                                     Monster::MonsterGetBaseDamage() + heroLvl,
                                     Monster::MonsterGetBaseDamage() + heroLvl * 2,
                                     Monster::MonsterGetBaseDefence() + heroLvl * 3,
                                     Monster::MonsterGetBaseAvoidance() + heroLvl * 0.001);
            break;
        case 1:
            newMon = new Spirit("Spirit",/*increased avoidance*/
                                Monster::MonsterGetBaseHP() + heroLvl * 4 , heroLvl,
                                Monster::MonsterGetBaseDamage() + heroLvl,
                                Monster::MonsterGetBaseDamage() + heroLvl * 2,
                                Monster::MonsterGetBaseDefence() + heroLvl * 2,
                                Monster::MonsterGetBaseAvoidance() + heroLvl * 0.0015);
            break;
        case 2:
            newMon = new Dragon("Dragon",/*increased damage*/
                                Monster::MonsterGetBaseHP() + heroLvl * 4 , heroLvl,
                                Monster::MonsterGetBaseDamage() + heroLvl,
                                Monster::MonsterGetBaseDamage() + heroLvl * 2,
                                Monster::MonsterGetBaseDefence() + heroLvl * 2,
                                Monster::MonsterGetBaseAvoidance() + heroLvl * 0.001);
            break;
    }
    return newMon;
}

// Determines if a monster will avoid the attack . If not the monster takes damage
bool Battle::AttackWithWeapon(Hero& hero, Monster& monster)
{
    unsigned int totalDamage = hero.GetWeaponDamage() + hero.GetStrength();

    if ((double)rand() / RAND_MAX > monster.MonsterGetAvoidance()) {
        monster.ChangeHealth(floor((double)(totalDamage * totalDamage) / (totalDamage + monster.MonsterGetDefence())));
        //changes the monster's health according to the function (damage*damage)/(damage + armor)
        return true;
    
    } else {
        cout << monster.Living::GetName() << " avoided the attack!" << endl;
        usleep(1500000);
        return false;
    }
}

// displays the spells and lets the user choose one. After the spell is chosen it is cast
bool Battle::CastSpell(Hero& hero, Monster& monster) 
{
    unsigned int totalDamage;
    unsigned int slotNumber;
    unsigned int typeOfSpell;
    Spell* chosenSpell;

    if (hero.DisplaySpells(chosenSpell , slotNumber , typeOfSpell) == false)
        return false;

    // Checks if the hero has enough magic power
    if (hero.UseSpell(*chosenSpell) == true) { 
        hero.ReduceMagicPower(chosenSpell->GetReqEnergy()); // Reduces the hero's magic power
        totalDamage = chosenSpell->HeroDamage(hero);        // Gets the total damage that will be caused
        monster.ChangeHealth(floor((double)(totalDamage * totalDamage) / (totalDamage + monster.MonsterGetDefence())));
        monster.HitBySpell(chosenSpell);                    // Applies the after attack effects of the spell
        hero.SpellUsed(slotNumber , typeOfSpell);           // Deletes the spell
        
        if (monster.Fainted()) {
            cout << "The hero " << hero.GetName() << " defeated the monster " << monster.GetName() << endl;
            return true;
        }
    }
    return true;
}

bool Battle::UsePotion(Hero& hero, bool isInBattle)//displays and uses the chosen potion
{
    if (hero.DisplayPotions(isInBattle) == false)
        return false;

    return true;
}

bool Battle::ChangeArmor(Hero& hero, bool isInBattle)//displays and wears the chosen armor
{
    if (hero.DisplayArmors(isInBattle) == false)
        return false;

    return true;
}

bool Battle::ChangeWeapon(Hero& hero, bool isInBattle)//displays and equips the chosen weapon
{
    if (hero.DisplayWeapons(isInBattle) == false)
        return false;

    return true;
}

bool Battle::MonsterAttack(Monster& monster ,Hero& hero)//the monster attacks the hero . If the hero doesn't avoid the attack they take damage
{
    unsigned int totalDamage = monster.MonsterGetDamage();

    if ((double)rand() / RAND_MAX > hero.GetAgility()) {
        hero.ChangeHealth(floor((double)(totalDamage * totalDamage) / (totalDamage + hero.GetArmorDefence())));
    
    } else {
        cout << endl << "\033[38;5;220m" << hero.Living::GetName() << "\033[0m avoided the attack!" << endl;
        usleep(1500000);
        cout << "\033[2A";
        cout << "\033[J";
    }
    return true;
}
