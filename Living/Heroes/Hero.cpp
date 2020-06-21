/* File: Hero.cpp */

#include <iostream>
#include <unistd.h>

#include "../../Input_Validation/Input_Validation.hpp"
#include "../../Keyboard/Keyboard.hpp"

#include "../../Spells/LightingSpell.hpp"
#include "../../Spells/FireSpell.hpp"
#include "../../Spells/IceSpell.hpp"
#include "../../Spells/Spell.hpp"

#include "../../Items/Weapon.hpp"
#include "../../Items/Potion.hpp"
#include "../../Items/Armor.hpp"
#include "../../Items/Items.hpp"

#include "Hero.hpp"

using namespace std;

unsigned int Hero::baseHealth = 50;
unsigned int Hero::baseMagicPower = 30;
unsigned int Hero::baseDexterity = 10;
unsigned int Hero::baseStrength = 10;
float Hero::baseAgility = 0.101;

Hero::Hero(const string& setName, const int& setHealth, const int& setLevel, const unsigned int& setMagic, const unsigned int& setStrength,
           const unsigned int& setDexterity, const float& setAgility, const unsigned int& startingMoney)
           : Living(setName,setHealth,setLevel), equippedWeaponRight(NULL), equippedWeaponLeft(NULL), equippedWeaponBoth(NULL), equippedArmor(NULL),
             availableSpellSlots(10), availableItemSlots(10), maxSpellsSlots(10), maxItemSlots(10), mostItems(0),/*totalSpells(0), totalItems(0),*/ weaponDamage(0),
             armorDefence(0), magicPower(setMagic), dexterity(setDexterity), strength(setStrength), money(startingMoney), maxMP(setMagic), XP(0),
             agility(setAgility), leftHand(false), rightHand(false)
{}

Hero::~Hero()
{}

unsigned int Hero::GetBaseMagicPower(void)
{
    return baseMagicPower;
}

unsigned int Hero::GetBaseDexterity(void)
{
    return baseDexterity;
}

unsigned int Hero::GetBaseStrength(void)
{
    return baseStrength;
}

unsigned int Hero::GetBaseHealth(void)
{
    return baseHealth;
}

float Hero::GetBaseAgility(void)
{
    return baseAgility;
}

void Hero::ReduceMagicPower(const unsigned int& value)
{
    magicPower -= value;
}

unsigned int Hero::GetStrength(void) const
{
    return strength;
}

unsigned int Hero::GetDexterity(void) const
{
    return dexterity;
}

float Hero::GetAgility(void) const
{
    return agility;
}

unsigned int Hero::GetAvailableSpellSlots(void) const
{
    return availableSpellSlots;
}

unsigned int Hero::GetAvailableItemSlots(void) const
{
    return availableItemSlots;
}

unsigned int Hero::GetMaxSpellsSlots(void) const
{
    return maxSpellsSlots;
}

unsigned int Hero::GetMaxItemsSlots(void) const
{
    return maxItemSlots;
}
/*
unsigned int Hero::GetTotalSpells(void) const
{
    return totalSpells;
}

unsigned int Hero::GetTotalItems(void) const
{
    return totalItems;
}
*/
unsigned int Hero::GetMagicPower(void) const
{
    return magicPower;
}

unsigned int Hero::GetMoney(void) const
{
    return money;
}

unsigned int Hero::GetXP(void) const
{
    return XP;
}

void Hero::RecalcMostItems(void)
{
    mostItems = 0;

    if(mostItems < lightingSpellsArray.size())
        mostItems = lightingSpellsArray.size();

    if(mostItems < fireSpellsArray.size())
        mostItems = fireSpellsArray.size();

    if(mostItems < iceSpellsArray.size())
        mostItems = iceSpellsArray.size();

    if(mostItems < weaponsArray.size())
        mostItems = weaponsArray.size();

    if(mostItems < potionsArray.size())
        mostItems = potionsArray.size();

    if(mostItems < armorsArray.size())
        mostItems = armorsArray.size();
}

bool Hero::UseSpell(Spell& spell) //checks if the hero has the required energy
{
    if(spell.GetReqEnergy() <= magicPower)
        return true;
    return false;
}

void Hero::AddNewSpell(IceSpell* spell)
{
    iceSpellsArray.push_back(spell);
    availableSpellSlots--;

    if(mostItems < iceSpellsArray.size())
        mostItems = iceSpellsArray.size();
}

void Hero::AddNewSpell(FireSpell* spell)
{
    fireSpellsArray.push_back(spell);
    availableSpellSlots--;

    if(mostItems < fireSpellsArray.size())
        mostItems = fireSpellsArray.size();
}

void Hero::AddNewSpell(LightingSpell* spell)
{
    lightingSpellsArray.push_back(spell);
    availableSpellSlots--;

    if(mostItems < lightingSpellsArray.size())
        mostItems = lightingSpellsArray.size();
}

void Hero::AddNewItem(Weapon* item)
{
    weaponsArray.push_back(item);
    availableItemSlots--;

    if(mostItems < weaponsArray.size())
        mostItems = weaponsArray.size();
}

void Hero::AddNewItem(Armor* item)
{
    armorsArray.push_back(item);
    availableItemSlots--;

    if(mostItems < armorsArray.size())
        mostItems = armorsArray.size();
}

void Hero::AddNewItem(Potion* item)
{
    potionsArray.push_back(item);
    availableItemSlots--;

    if(mostItems < potionsArray.size())
        mostItems = potionsArray.size();
}

void Hero::RemoveIceSpell(const unsigned int& row) //removes the spell and gets the money from itt(used when the spell is sold)
{
    money += iceSpellsArray[row]->GetPrice() / 2;
    delete iceSpellsArray[row];
    iceSpellsArray.erase(iceSpellsArray.begin() + row);
    availableSpellSlots++;

    RecalcMostItems();
}

void Hero::RemoveFireSpell(const unsigned int& row) //removes the spell and gets the money from itt(used when the spell is sold)
{
    money += fireSpellsArray[row]->GetPrice() / 2;

    delete fireSpellsArray[row];

    fireSpellsArray.erase(fireSpellsArray.begin() + row);
    availableSpellSlots++;

    RecalcMostItems();
}

void Hero::RemoveLightingSpell(const unsigned int& row) //removes the spell and gets the money from it(used when the spell is sold)
{
    money += lightingSpellsArray[row]->GetPrice() / 2;

    delete lightingSpellsArray[row];

    lightingSpellsArray.erase(lightingSpellsArray.begin() + row);
    availableSpellSlots++;

    RecalcMostItems();
}

void Hero::RemoveWeapon(const unsigned int& row) //removes the weapon and gets the money from it(used when the weapon is sold)
{
    money += weaponsArray[row]->GetPrice() / 2;

    delete weaponsArray[row];

    weaponsArray.erase(weaponsArray.begin() + row);
    availableItemSlots++;

    RecalcMostItems();
}

void Hero::RemoveArmor(const unsigned int& row) //removes the armor and gets the money from it(used when the armor is sold)
{
    money += armorsArray[row]->GetPrice() / 2;

    delete armorsArray[row];

    armorsArray.erase(armorsArray.begin() + row);
    availableItemSlots++;

    RecalcMostItems();
}

void Hero::RemovePotion(const unsigned int& row) //removes the potion and gets the money from it(used when the potion is sold)
{
    money += potionsArray[row]->GetPrice() / 2;

    delete potionsArray[row];

    potionsArray.erase(potionsArray.begin() + row);
    availableItemSlots++;

    RecalcMostItems();
}

void Hero::RestoreToHalfHP(void)
{
    healthPower = maxHP / 2;
    Revived();
}

void Hero::GainXP(const unsigned int experience) //adds experience to the hero
{
    XP += experience;

    if(XP >= level * level)
        LevelUp();
}

void Hero::ChangeMoney(const int credits)
{
    if(money + credits <= 0)
        money = 0;
    else
        money += credits;
}

unsigned int Hero::GetNumberOfSpells(unsigned int typeOfSpell) const
{
    switch(typeOfSpell)
    {
        case 1:
            return lightingSpellsArray.size();

        case 2:
            return iceSpellsArray.size();

        case 3:
            return fireSpellsArray.size();
    }
}

unsigned int Hero::GetNumberOfPotions(void) const
{
    return potionsArray.size();
}

unsigned int Hero::GetNumberOfWeapons(void) const
{
    return weaponsArray.size();
}

unsigned int Hero::GetNumberOfArmors(void) const
{
    return armorsArray.size();
}

void Hero::EndTurnRefill(void) //after the turn ends the hero restores 10% HP and MP
{
    if(magicPower + (10*magicPower) / 100 < maxMP)
        magicPower = magicPower + (10*magicPower) / 100;

    if(healthPower + (10*healthPower) / 100 < maxHP)
        healthPower = healthPower + (10*healthPower) / 100;
}

Spell* Hero::GetSpellFromSlot(const unsigned int slotNum, const unsigned int typeOfSpell) //checks if the spell exists and then it returns it
{
    switch(typeOfSpell)
    {
        case 1:
            return lightingSpellsArray[slotNum];

        case 2:
            return iceSpellsArray[slotNum];

        case 3:
            return fireSpellsArray[slotNum];
    }
}

bool Hero::isValidForSale(string testSelections[], int& column, int& row, const int& sellState) //checks if items is valid for sale
{
    if(sellState == 2)
    {
        if(!isValid(testSelections[0].c_str(),column,0,6))
            return false;
    }
    else
    {
        if(!isValid(testSelections[0].c_str(),column,0,3))
            return false;
    }

    if(!isNumeric(testSelections[1].c_str(),row))
        return false;

    switch(column)
    {
        case 1:
            if(sellState == 1)
            {
                if(row == 0 || row > weaponsArray.size())
                {
                    cerr << endl << "Error: The input is invalid." << endl;
                    cerr << "Please, try again!" << endl << endl;
                    return false;
                }
            }
            else
            {
                if(row == 0 || row > iceSpellsArray.size())
                {
                    cerr << endl << "Error: The input is invalid." << endl;
                    cerr << "Please, try again!" << endl << endl;
                    return false;
                }
            }

            break;

        case 2:
            if(sellState == 1)
            {
                if(row == 0 || row > armorsArray.size())
                {
                    cerr << endl << "Error: The input is invalid." << endl;
                    cerr << "Please, try again!" << endl << endl;
                    return false;
                }
            }
            else
            {
                if(row == 0 || row > fireSpellsArray.size())
                {
                    cerr << endl << "Error: The input is invalid." << endl;
                    cerr << "Please, try again!" << endl << endl;
                    return false;
                }
            }

            break;

        case 3:
            if(sellState == 1)
            {
                if(row == 0 || row > potionsArray.size())
                {
                    cerr << endl << "Error: The input is invalid." << endl;
                    cerr << "Please, try again!" << endl << endl;
                    return false;
                }
            }
            else
            {
                if(row == 0 || row > lightingSpellsArray.size())
                {
                    cerr << endl << "Error: The input is invalid." << endl;
                    cerr << "Please, try again!" << endl << endl;
                    return false;
                }
            }

            break;

        case 4:
            if(row == 0 || row > weaponsArray.size())
            {
                cerr << endl << "Error: The input is invalid." << endl;
                cerr << "Please, try again!" << endl << endl;
                return false;
            }

            break;

        case 5:
            if(row == 0 || row > armorsArray.size())
            {
                cerr << endl << "Error: The input is invalid." << endl;
                cerr << "Please, try again!" << endl << endl;
                return false;
            }

            break;

        case 6:
            if(row == 0 || row > potionsArray.size())
            {
                cerr << endl << "Error: The input is invalid." << endl;
                cerr << "Please, try again!" << endl << endl;
                return false;
            }

            break;
    }
    return true;
}

bool Hero::SpellUsed(const unsigned int slotNum , const unsigned int typeOfSpell) //deletes the used spell
{
    availableSpellSlots++;

    switch(typeOfSpell)
    {
        case 1:
            delete lightingSpellsArray[slotNum - 1];
            lightingSpellsArray.erase(lightingSpellsArray.begin() + slotNum - 1);

            return true;

        case 2:
            delete iceSpellsArray[slotNum - 1];
            iceSpellsArray.erase(iceSpellsArray.begin() + slotNum - 1);

            return true;

        case 3:
            delete fireSpellsArray[slotNum - 1];
            fireSpellsArray.erase(fireSpellsArray.begin() + slotNum - 1);

            return true;
    }
    return false;
}

Potion* Hero::GetPotionFromSlot(const unsigned int slotNum)
{
    return potionsArray[slotNum];
}

void Hero::DrinkPotion(const unsigned int slotNum) //adds the potion values to the hero
{

    strength += potionsArray[slotNum]->PotionIncreaseStrength();
    dexterity += potionsArray[slotNum]->PotionIncreaseDexterity();
    agility += potionsArray[slotNum]->PotionIncreaseAgility();

    delete potionsArray[slotNum];

    potionsArray.erase(potionsArray.begin() + slotNum);
    availableItemSlots++;

}

Armor* Hero::GetArmorFromSlot(const unsigned int slotNum)
{
    return armorsArray[slotNum];
}

void Hero::WearArmor(unsigned int slotNum)
{
    equippedArmor = armorsArray[slotNum];
    armorDefence = equippedArmor->GetDamageReduction();
}

Weapon* Hero::GetWeaponFromSlot(unsigned int slotNum)
{
    return weaponsArray[slotNum];
}

bool Hero::EquipWeapon(Weapon* chosen , const short handGiven) //equips a chosen weapon
{
    if(handGiven == 1)
    {
        if(chosen == equippedWeaponRight)
            return true;

        if(equippedWeaponRight != NULL) //removes the damage from the previous weapon
            weaponDamage -= equippedWeaponRight->GetDamage();

        //if(chosen == equippedWeaponLeft) //removes the damage from the previous weapon
        /*{
            weaponDamage -= equippedWeaponLeft->GetDamage();
            equippedWeaponLeft = NULL;
        }*/

        if(equippedWeaponBoth != NULL) //removes the damage from the previous weapon
        {
            weaponDamage -= equippedWeaponBoth->GetDamage();
            equippedWeaponBoth = NULL;
            equippedWeaponLeft = NULL;
            leftHand = false;
        }

        equippedWeaponRight = chosen;
        rightHand = true;

        weaponDamage += chosen->GetDamage();
    }
    else if(handGiven == 2)
    {
        if(chosen == equippedWeaponLeft)
            return true;

        if(equippedWeaponLeft != NULL) //removes the damage from the previous weapon
            weaponDamage -= equippedWeaponLeft->GetDamage();

        //if(chosen == equippedWeaponRight) //removes the damage from the previous weapon
        /*{
            weaponDamage -= equippedWeaponRight->GetDamage();
            equippedWeaponRight = NULL;
        }*/

        if(equippedWeaponBoth != NULL) //removes the damage from the previous weapon
        {
            weaponDamage -= equippedWeaponBoth->GetDamage();
            equippedWeaponBoth = NULL;
            equippedWeaponRight = NULL;
            rightHand = false;
        }

        equippedWeaponLeft = chosen;
        leftHand = true;

        weaponDamage += chosen->GetDamage();
    }
    else if(handGiven == 3)
    {
        if(chosen == equippedWeaponBoth)
            return true;

        if(equippedWeaponBoth != NULL)
            weaponDamage -= equippedWeaponBoth->GetDamage();

        if(equippedWeaponLeft != NULL) //removes the damage from the previous weapon
            weaponDamage -= equippedWeaponLeft->GetDamage();

        if(equippedWeaponRight != NULL) //removes the damage from the previous weapon
            weaponDamage -= equippedWeaponRight->GetDamage();

        equippedWeaponBoth = chosen;
        equippedWeaponLeft = NULL;
        equippedWeaponRight = NULL;
        rightHand = true;
        leftHand = true;

        weaponDamage += chosen->GetDamage();
    }

    return true;
}

unsigned int Hero::GetWeaponDamage(void) const
{
    if(!leftHand && !rightHand)
        return 0;
    return weaponDamage;
}

unsigned int Hero::GetArmorDefence(void) const
{
    return armorDefence;
}

void Hero::DisplayProdsForSale(const bool& showInfo, const int& sellState)
{
    cout << "\033[2J\033[1;1H";

    if(sellState == 2)
        cout << "+=========================================================================================================================================================================================+" << endl;
    else
        cout << "+============================================================================================+" << endl;

    if(showInfo)
    {
        if(sellState == 2)
            cout << "|\033[64C\033[4mAvailable Actions\033[0m: 1. Proceed, 2. Disable Info, 3. Cancel\033[64C|" << endl;
        else
            cout << "|                 \033[4mAvailable Actions\033[0m: 1. Proceed, 2. Disable Info, 3. Cancel                  |" << endl;
    }
    else
    {
        if(sellState == 2)
            cout << "|\033[68C\033[4mAvailable Actions\033[0m: 1. Proceed, 2. Info, 3. Cancel\033[68C|" << endl;
        else
            cout << "|                      \033[4mAvailable Actions\033[0m: 1.Proceed, 2. Info, 3. Cancel                      |" << endl;
    }

    if(sellState == 2)
        cout << "+=========================================================================================================================================================================================+" << endl;
    else
        cout << "+============================================================================================+" << endl;

    if(sellState == 2)
        cout << "|                                           Spells                                           |                                           Items                                            |" << endl;
    else if(sellState == 1)
        cout << "|                                           Items                                            |" << endl;
    else
        cout << "|                                           Spells                                           |" << endl;

    if(showInfo)
    {
        if(sellState == 2)
        {
            cout << "|--------------------------------------------------------------------------------------------+--------------------------------------------------------------------------------------------|" << endl;
            cout << "|    --> Spells are representing a magic attack that a hero can perform                      |    --> There are items that a hero can use for attacking enemies, avoiding their attacks   |" << endl;
            cout << "|    --> They cause an amount of damage according to the hero's dexterity                    |        and items that increase some of his features                                        |" << endl;
            cout << "|    --> They require a specific Magic Power that the hero must have in order to use them    |    --> Some of them can be used one time only                                              |" << endl;
            cout << "|    --> After the use of a spell the Hero's Magic Power will be reduced                     |                                                                                            |" << endl;
        }
        else if(sellState == 1)
        {
            cout << "|--------------------------------------------------------------------------------------------|" << endl;
            cout << "|    --> There are items that a hero can use for attacking enemies, avoiding their attacks   |" << endl;
            cout << "|        and items that increase some of his features                                        |" << endl;
            cout << "|    --> Some of them can be used one time only                                              |" << endl;
        }
        else
        {
            cout << "|--------------------------------------------------------------------------------------------+" << endl;
            cout << "|    --> Spells are representing a magic attack that a hero can perform                      |" << endl;
            cout << "|    --> They cause an amount of damage according to the hero's dexterity                    |" << endl;
            cout << "|    --> They require a specific Magic Power that the hero must have in order to use them    |" << endl;
            cout << "|    --> After the use of a spell the Hero's Magic Power will be reduced                     |" << endl;
        }
    }

    if(sellState == 2)
        cout << "+===+==========================+===+==========================+===+==========================+===+==========================+===+==========================+===+==========================+" << endl;
    else
        cout << "+===+==========================+===+==========================+===+==========================+" << endl;

    if(sellState == 2)
        cout << "| # |        Ice Spells        | # |       Fire Spells        | # |     Lighting Spells      | # |         Weapons          | # |          Armors          | # |         Potions          |" << endl;
    else if(sellState == 1)
        cout << "| # |         Weapons          | # |          Armors          | # |         Potions          |" << endl;
    else
        cout << "| # |        Ice Spells        | # |       Fire Spells        | # |     Lighting Spells      |" << endl;

    if(showInfo)
    {
        if(sellState == 2)
        {
            cout << "+---+--------------------------+---+--------------------------+---+--------------------------+---+--------------------------+---+--------------------------+---+--------------------------|" << endl;
            cout << "|(i)|    Ice Spells reduce     |(i)|    Fire Spells reduce    |(i)|  Lighting Spells reduce  |(i)|   Weapons cause damage   |(i)|    Armors reduce the     |(i)|     Potions increase     |" << endl;
            cout << "|(i)|   enemy's damage range   |(i)|     enemy's defence      |(i)|    enemy's chance to     |(i)|    to the enemies and    |(i)|     received damage      |(i)|    a hero's specific     |" << endl;
            cout << "|   |                          |   |                          |(i)|     avoid an attack      |(i)|     they require one     |   |                          |(i)|     feature and can      |" << endl;
            cout << "|   |                          |   |                          |   |                          |(i)|       or two hands       |   |                          |(i)|    be used only once     |" << endl;
        }
        else if(sellState == 1)
        {
            cout << "+---+--------------------------+---+--------------------------+---+--------------------------|" << endl;
            cout << "|(i)|   Weapons cause damage   |(i)|    Armors reduce the     |(i)|     Potions increase     |" << endl;
            cout << "|(i)|    to the enemies and    |(i)|     received damage      |(i)|    a hero's specific     |" << endl;
            cout << "|(i)|     they require one     |   |                          |(i)|     feature and can      |" << endl;
            cout << "|(i)|       or two hands       |   |                          |(i)|    be used only once     |" << endl;
        }
        else
        {
            cout << "+---+--------------------------+---+--------------------------+---+--------------------------|" << endl;
            cout << "|(i)|    Ice Spells reduce     |(i)|    Fire Spells reduce    |(i)|  Lighting Spells reduce  |" << endl;
            cout << "|(i)|   enemy's damage range   |(i)|     enemy's defence      |(i)|    enemy's chance to     |" << endl;
            cout << "|   |                          |   |                          |(i)|     avoid an attack      |" << endl;
            cout << "|   |                          |   |                          |   |                          |" << endl;
        }
    }

    if(sellState == 2)
        cout << "+===+==========================+===+==========================+===+==========================+===+==========================+===+==========================+===+==========================+" << endl;
    else
        cout << "+===+==========================+===+==========================+===+==========================+" << endl;

    for(unsigned int i = 0; i < mostItems; i++)
    {
        if(i < iceSpellsArray.size())
        {
            if(i < 9)         cout << "| " << i+1 << " ";
            else if(i < 99)   cout << "| " << i+1;
            else if(i < 999)  cout << "|"  << i+1;

            cout << "| \u2022 ";

            if(showInfo)
                cout << "";

            cout.width(23);
            cout << left << iceSpellsArray[i]->GetName() << "";
        }
        else if(sellState != 1)
            cout << "|   |\033[26C";

        if(i < fireSpellsArray.size())
        {
            if(i < 9)         cout << "| " << i+1 << " ";
            else if(i < 99)   cout << "| " << i+1;
            else if(i < 999)  cout << "|"  << i+1;

            cout << "| \u2022 ";

            if(showInfo)
                cout << "";

            cout.width(23);
            cout << left << fireSpellsArray[i]->GetName() << "";
        }
        else if(sellState != 1)
            cout << "|   |\033[26C";

        if(i < lightingSpellsArray.size())
        {
            if(i < 9)         cout << "| " << i+1 << " ";
            else if(i < 99)   cout << "| " << i+1;
            else if(i < 999)  cout << "|"  << i+1;

            cout << "| \u2022 ";

            if(showInfo)
                cout << "";

            cout.width(23);
            cout << left << lightingSpellsArray[i]->GetName() << "";
        }
        else if(sellState != 1)
            cout << "|   |\033[26C";

        if(sellState == 0)
            cout << "|";

        if(i < weaponsArray.size())
        {
            if(i < 9)         cout << "| " << i+1 << " ";
            else if(i < 99)   cout << "| " << i+1;
            else if(i < 999)  cout << "|"  << i+1;

            cout << "| \u2022 ";

            if(showInfo)
                cout << "";

            cout.width(23);
            cout << left << weaponsArray[i]->GetName() << "";
        }
        else if(sellState != 0)
            cout << "|   |\033[26C";

        if(i < armorsArray.size())
        {
            if(i < 9)         cout << "| " << i+1 << " ";
            else if(i < 99)   cout << "| " << i+1;
            else if(i < 999)  cout << "|"  << i+1;

            cout << "| \u2022 ";

            if(showInfo)
                cout << "";

            cout.width(23);
            cout << left << armorsArray[i]->GetName() << "";
        }
        else if(sellState != 0)
            cout << "|   |\033[26C";

        if(i < potionsArray.size())
        {
            if(i < 9)         cout << "| " << i+1 << " ";
            else if(i < 99)   cout << "| " << i+1;
            else if(i < 999)  cout << "|"  << i+1;

            cout << "| \u2022 ";

            if(showInfo)
                cout << "";

            cout.width(23);
            cout << left << potionsArray[i]->GetName() << "|";
        }
        else if(sellState != 0)
            cout << "|   |\033[26C|";

        cout << endl;


        if(showInfo)
        {
    /* ------------------------------- Start of 1st Line ------------------------------- */

            if(i < iceSpellsArray.size())
            {
                cout << "|(i)| ~> Selling Price: ";
                cout.width(7);
                cout << left << iceSpellsArray[i]->GetPrice() / 2;
            }
            else if(sellState != 1)
                cout << "|   |\033[26C";

            if(i < fireSpellsArray.size())
            {
                cout << "|(i)| ~> Selling Price: ";
                cout.width(7);
                cout << left << fireSpellsArray[i]->GetPrice() / 2;
            }
            else if(sellState != 1)
                cout << "|   |\033[26C";

            if(i < lightingSpellsArray.size())
            {
                cout << "|(i)| ~> Selling Price: ";
                cout.width(7);
                cout << left << lightingSpellsArray[i]->GetPrice() / 2 << "|";
            }
            else if(sellState != 1)
                cout << "|   |\033[26C|";

            if(sellState == 1)
                cout << "|";

            if(i < weaponsArray.size())
            {
                cout << "(i)| ~> Selling Price: ";
                cout.width(7);
                cout << left << weaponsArray[i]->GetPrice() / 2;
            }
            else if(sellState != 0)
                cout << "   |\033[26C";

            if(i < armorsArray.size())
            {
                cout << "|(i)| ~> Selling Price: ";
                cout.width(7);
                cout << left << armorsArray[i]->GetPrice() / 2;
            }
            else if(sellState != 0)
                cout << "|   |\033[26C";

            if(i < potionsArray.size())
            {
                cout << "|(i)| ~> Selling Price: ";
                cout.width(7);
                cout << left << potionsArray[i]->GetPrice() / 2 << "|";
            }
            else if(sellState != 0)
                cout << "|   |\033[26C|";

            cout << endl;

    /* -------------------------------- End of 1st Line -------------------------------- */

    /* ------------------------------- Start of 2nd Line ------------------------------- */

            if(i < iceSpellsArray.size())
            {
                string str = to_string(iceSpellsArray[i]->GetMinDamage()) + "-" + to_string(iceSpellsArray[i]->GetMaxDamage());
                cout << "|(i)| ~> Damage Range: ";
                cout.width(8);
                cout << left << str;
            }
            else if(sellState != 1)
                cout << "|   |\033[26C";

            if(i < fireSpellsArray.size())
            {
                string str = to_string(fireSpellsArray[i]->GetMinDamage()) + "-" + to_string(fireSpellsArray[i]->GetMaxDamage());
                cout << "|(i)| ~> Damage Range: ";
                cout.width(8);
                cout << left << str;
            }
            else if(sellState != 1)
                cout << "|   |\033[26C";

            if(i < lightingSpellsArray.size())
            {
                string str = to_string(lightingSpellsArray[i]->GetMinDamage()) + "-" + to_string(lightingSpellsArray[i]->GetMaxDamage());
                cout << "|(i)| ~> Damage Range: ";
                cout.width(8);
                cout << left << str << "|";
            }
            else if(sellState != 1)
                cout << "|   |\033[26C|";

            if(sellState == 1)
                cout << "|";

            if(i < weaponsArray.size())
            {
                cout << "(i)| ~> Damage: ";
                cout.width(14);
                cout << left << weaponsArray[i]->GetDamage();
            }
            else if(sellState != 0)
                cout << "   |\033[26C";

            if(i < armorsArray.size())
            {
                cout << "|(i)| ~> Damage Reduction: ";
                cout.width(4);
                cout << left << armorsArray[i]->GetDamageReduction();
            }
            else if(sellState != 0)
                cout << "|   |\033[26C";

            if(i < potionsArray.size())
            {
                string str;
                cout << "|(i)| ~> Power-Up: ";
                cout.width(12);
                if(potionsArray[i]->PotionIncreaseStrength())
                {
                    str = "+" + to_string(potionsArray[i]->PotionIncreaseStrength()) + " str/th";
                    cout << str << "|";
                }
                else if(potionsArray[i]->PotionIncreaseDexterity())
                {
                    str = "+" + to_string(potionsArray[i]->PotionIncreaseDexterity()) + " dext/ty";
                    cout << str << "|";
                }
                else
                {
                    str = "+" + to_string((int)potionsArray[i]->PotionIncreaseAgility()) + " agility";
                    cout << str << "|";
                }
            }
            else if(sellState != 0)
                cout << "|   |\033[26C|";

            cout << endl;

    /* -------------------------------- End of 2nd Line -------------------------------- */

    /* ------------------------------- Start of 3rd Line ------------------------------- */

            if(i < iceSpellsArray.size())
            {
                cout << "|(i)| ~> Enemy Damage . ";
                cout.width(7);
                cout << left << (to_string(iceSpellsArray[i]->GetDamageReduction()) + " HP");
            }
            else if(sellState != 1)
                cout << "|   |\033[26C";

            if(i < fireSpellsArray.size())
            {
                cout << "|(i)| ~> Enemy Defence . ";
                cout.width(6);
                cout << left << fireSpellsArray[i]->GetDefenceReduction();
            }
            else if(sellState != 1)
                cout << "|   |\033[26C";

            if(i < lightingSpellsArray.size())
            {
                cout << "|(i)| ~> Enemy Avoidance . ";
                cout.width(4);
                cout << left << (to_string(lightingSpellsArray[i]->GetAvoidanceReduction()) + "%") << "|";
            }
            else if(sellState != 1)
                cout << "|   |\033[26C|";

            if(sellState == 1)
                cout << "|";

            if(i < weaponsArray.size())
            {
                cout << "(i)| ~> Required Hands: ";
                cout.width(6);
                if(weaponsArray[i]->TwoHanded())
                    cout << left << "2";
                else
                    cout << left << "1";
            }
            else if(sellState != 0)
                cout << "   |\033[26C";

            if(sellState != 0)
                cout << "|   |\033[26C";

            if(sellState != 0)
                cout << "|   |\033[26C|";

            cout << endl;

    /* -------------------------------- End of 3rd Line -------------------------------- */

    /* ------------------------------- Start of 4th Line ------------------------------- */

            if(i < iceSpellsArray.size())
                cout << "|(i)|    Reduction    ·        ";
            else if(sellState != 1)
                cout << "|   |\033[26C";

            if(i < fireSpellsArray.size())
                cout << "|(i)|    Reduction     ·       ";
            else if(sellState != 1)
                cout << "|   |\033[26C";

            if(i < lightingSpellsArray.size())
                cout << "|(i)|    Reduction       ·     |";
            else if(sellState != 1)
                cout << "|   |\033[26C|";

            if(sellState == 1)
                cout << "|";

            if(sellState != 0)
                cout << "   |\033[26C";

            if(sellState != 0)
                cout << "|   |\033[26C";

            if(sellState != 0)
                cout << "|   |\033[26C|";

            cout << endl;

    /* -------------------------------- End of 4th Line -------------------------------- */

    /* ------------------------------- Start of 5th Line ------------------------------- */

            if(i < iceSpellsArray.size())
            {
                cout << "|(i)| ~> Applies to: ";
                cout.width(10);
                cout << left << (to_string(iceSpellsArray[i]->GetRounds()) + " rounds");
            }
            else if(sellState != 1)
                cout << "|   |\033[26C";

            if(i < fireSpellsArray.size())
            {
                cout << "|(i)| ~> Applies to: ";
                cout.width(10);
                cout << left << (to_string(fireSpellsArray[i]->GetRounds()) + " rounds");
            }
            else if(sellState != 1)
                cout << "|   |\033[26C";

            if(i < lightingSpellsArray.size())
            {
                cout << "|(i)| ~> Applies to: ";
                cout.width(10);
                cout << left << (to_string(lightingSpellsArray[i]->GetRounds()) + " rounds") << "|";
            }
            else if(sellState != 1)
                cout << "|   |\033[26C|";

            if(sellState == 1)
                cout << "|";

            if(sellState != 0)
                cout << "   |\033[26C";

            if(sellState != 0)
                cout << "|   |\033[26C";

            if(sellState != 0)
                cout << "|   |\033[26C|";

            cout << endl;

    /* -------------------------------- End of 5th Line -------------------------------- */

            if(sellState == 1)
                cout << "\033[2A\033[J";

            if(sellState == 2)
                cout << "|   |\033[26C|   |\033[26C|   |\033[26C|   |\033[26C|   |\033[26C|   |\033[26C|" << endl;
            else
                cout << "|   |\033[26C|   |\033[26C|   |\033[26C|" << endl;
        }

        usleep(40000);
    }

    if(showInfo)
        cout << "\033[1A";

    if(sellState == 2)
        cout << "+===+==========================+===+==========================+===+==========================+===+==========================+===+==========================+===+==========================+" << endl;
    else
        cout << "+===+==========================+===+==========================+===+==========================+" << endl;

    cout << endl;
    cout << "  Hero: " << name << endl;
    cout << " Money: " << money << endl;
    cout << " Items: (" << maxItemSlots - availableItemSlots << "/" << maxItemSlots << ")" << endl;
    cout << "Spells: (" << maxSpellsSlots - availableSpellSlots << "/" << maxSpellsSlots << ")" << endl;
}

bool Hero::DisplaySpells(Spell*& chosenSpell , unsigned int& slotNum , unsigned int& type)
{
    int arrow = 0;
    int column;
    int lines;
    char selection;

    if(!iceSpellsArray.empty())
        column = 0;
    else if(!fireSpellsArray.empty())
        column = 1;
    else if(!lightingSpellsArray.empty())
        column = 2;

    if(iceSpellsArray.size() >= fireSpellsArray.size() && iceSpellsArray.size() >= lightingSpellsArray.size())
        lines = 5 * (iceSpellsArray.size() + 1) - 1;

    if(fireSpellsArray.size() >= iceSpellsArray.size() && fireSpellsArray.size() >= lightingSpellsArray.size())
        lines = 5 * (fireSpellsArray.size() + 1) - 1;

    if(lightingSpellsArray.size() >= iceSpellsArray.size() && lightingSpellsArray.size() >= fireSpellsArray.size())
        lines = 5 * (lightingSpellsArray.size() + 1) - 1;

    do{
        cout << "+==============================+==============================+==============================+" << endl;
        cout << "|          Ice Spells          |         Fire Spells          |       Lighting Spells        |" << endl;
        cout << "+------------------------------+------------------------------+------------------------------+";

        for(unsigned int i = 0; i < iceSpellsArray.size() || i < fireSpellsArray.size() || i < lightingSpellsArray.size(); i++)
        {
            if(!i)
                cout << endl;
            else
                cout << "|                              |                              |                              |" << endl;

            if(i < iceSpellsArray.size())
            {
                if(column == 0 && arrow == i)
                    cout << "| ~> ";
                else
                    cout << "|    ";

                cout.width(26);
                cout << left << iceSpellsArray[i]->GetName() << "|" << endl;
                cout << "|    \u2022 Damage Range: ";
                cout.width(10);
                string str = to_string(iceSpellsArray[i]->GetMinDamage()) + "-" + to_string(iceSpellsArray[i]->GetMaxDamage());
                cout << left << str << "|" << endl;
                cout << "|    \u2022 Damage Reduction: ";
                cout.width(6);
                cout << left << iceSpellsArray[i]->GetDamageReduction() << "|" << endl;
                cout << "|    \u2022 Affected Rounds: ";
                cout.width(7);
                cout << left << iceSpellsArray[i]->GetRounds() << "|" << endl;
            }
            else
            {
                cout << "|\033[30C|" << endl;
                cout << "|\033[30C|" << endl;
                cout << "|\033[30C|" << endl;
                cout << "|\033[30C|" << endl;
            }

            cout << "\033[4A";

            if(i < fireSpellsArray.size())
            {
                if(column == 1 && arrow == i)
                    cout << "\033[32C ~> ";
                else
                    cout << "\033[32C    ";

                cout.width(26);
                cout << left << fireSpellsArray[i]->GetName() << "|" << endl;
                cout << "\033[32C    \u2022 Damage Range: ";
                cout.width(10);
                string str = to_string(fireSpellsArray[i]->GetMinDamage()) + "-" + to_string(fireSpellsArray[i]->GetMaxDamage());
                cout << left << str << "|" << endl;
                cout << "\033[32C    \u2022 Defence Reduction: ";
                cout.width(5);
                cout << left << fireSpellsArray[i]->GetDefenceReduction() << "|" << endl;
                cout << "\033[32C    \u2022 Affected Rounds: ";
                cout.width(7);
                cout << left << fireSpellsArray[i]->GetRounds() << "|" << endl;
            }
            else
            {
                cout << "\033[62C|" << endl;
                cout << "\033[62C|" << endl;
                cout << "\033[62C|" << endl;
                cout << "\033[62C|" << endl;
            }

            cout << "\033[4A";

            if(i < lightingSpellsArray.size())
            {
                if(column == 2 && arrow == i)
                    cout << "\033[63C ~> ";
                else
                    cout << "\033[63C    ";

                cout.width(26);
                cout << left << lightingSpellsArray[i]->GetName() << "|" << endl;
                cout << "\033[63C    \u2022 Damage Range: ";
                cout.width(10);
                string str = to_string(lightingSpellsArray[i]->GetMinDamage()) + "-" + to_string(lightingSpellsArray[i]->GetMaxDamage());
                cout << left << str << "|" << endl;
                cout << "\033[63C    \u2022 Avoidance Reduction: ";
                cout.width(3);
                cout << left << lightingSpellsArray[i]->GetAvoidanceReduction() << "|" << endl;
                cout << "\033[63C    \u2022 Affected Rounds: ";
                cout.width(7);
                cout << left << lightingSpellsArray[i]->GetRounds() << "|" << endl;
            }
            else
            {
                cout << "\033[93C|" << endl;
                cout << "\033[93C|" << endl;
                cout << "\033[93C|" << endl;
                cout << "\033[93C|" << endl;
            }
        }
        cout << "+==============================+==============================+==============================+" << endl;
        cout << "Press 'e' to cancel" << endl;

        selection = getch();

        if(selection == 'e')
        {
            cout << "\033[" << lines << "A";
            cout << "\033[J";

            //for(int i = 0; i < lines; i++)
            //    cout << "\033[1A\033[K";

            return false;
        }
        else if(selection == 'w' && arrow) //navigates the menu arrow
            arrow--;
        else if(selection == 'a' && column)
        {
            if(column == 2)
            {
                if(fireSpellsArray.size())
                {
                    column--;

                    if(arrow > fireSpellsArray.size() - 1)
                        arrow = fireSpellsArray.size() - 1;
                }
                else if(iceSpellsArray.size())
                {
                    column -= 2;

                    if(arrow > iceSpellsArray.size() - 1)
                        arrow = iceSpellsArray.size() - 1;
                }
            }
            else if(column == 1)
            {
                if(iceSpellsArray.size())
                {
                    column --;

                    if(arrow > iceSpellsArray.size() - 1)
                        arrow = iceSpellsArray.size() - 1;
                }
            }
        }
        else if(selection == 's')
        {
            if(column == 0 && arrow < iceSpellsArray.size() - 1) //navigates the menu arrow
                arrow++;
            else if(column == 1 && arrow < fireSpellsArray.size() - 1)
                arrow++;
            else if(column == 2 && arrow < lightingSpellsArray.size() - 1)
                arrow++;
        }
        else if(selection == 'd' && column < 2)
        {
            if(column == 0)
            {
                if(fireSpellsArray.size())
                {
                    column++;

                    if(arrow > fireSpellsArray.size() - 1)
                        arrow = fireSpellsArray.size() - 1;
                }
                else if(lightingSpellsArray.size())
                {
                    column += 2;

                    if(arrow > lightingSpellsArray.size() - 1)
                        arrow = lightingSpellsArray.size() - 1;
                }
            }
            else if(column == 1)
            {
                if(lightingSpellsArray.size())
                {
                    column ++;

                    if(arrow > lightingSpellsArray.size() - 1)
                        arrow = lightingSpellsArray.size() - 1;
                }
            }
        }

        if(selection != '\n')
            cout << "\033[" << lines << "A";

    }while(selection != '\n');

    switch(column)
    {
        case 0:
            chosenSpell = iceSpellsArray[arrow];
            type = 2;
            slotNum = arrow + 1;

            break;

        case 1:
            chosenSpell = fireSpellsArray[arrow];
            type = 3;
            slotNum = arrow + 1;

            break;

        case 2:
            chosenSpell = lightingSpellsArray[arrow];
            type = 1;
            slotNum = arrow + 1;

            break;
    }

    cout << "\033[" << lines + 10 << "A";
    cout << "\033[J";

    //for(int i = 0; i < lines + 10; i++)
    //    cout << "\033[1A\033[K";

    return true;
}

bool Hero::DisplayWeapons(bool isInBattle)
{
    int arrow = 0;
    int lines;

    Weapon* prevWeaponBoth = equippedWeaponBoth;
    Weapon* prevWeaponLeft = equippedWeaponLeft;
    Weapon* prevWeaponRight = equippedWeaponRight;

    lines = 4 * weaponsArray.size();

    if(!weaponsArray.size())
    {
        cout << "\033[s";
        cout << endl << "Sorry, there are no available weapons." << endl;

        usleep(1500000);

        cout << "\033[u";
        cout << "\033[J";

        return false;
    }

    if(isInBattle)
        cout << endl << "Press 'b' to cancel, 'c' to confirm, 'enter' to equip or unequip a weapon and 'u' to unequip all equipped weapons" << endl << endl;
    else
        cout << endl << "Press 'b' to go back and confirm, 'c' to cancel, 'enter' to equip or unequip a weapon and 'u' to unequip all equipped weapons" << endl << endl;

    while(true)
    {
        char selection;

        for(unsigned int i = 0; i < weaponsArray.size(); i++)
        {
            if(arrow == i)
                cout << " ~> ";
            else
                cout << "    ";

            cout << weaponsArray[i]->GetName() << "";

            if(equippedWeaponLeft == weaponsArray[i])
                cout << " (equiped on the left hand) ";
            else if(equippedWeaponRight == weaponsArray[i])
                cout << " (equiped on the right hand)";
            else if(equippedWeaponBoth == weaponsArray[i])
                cout << " (equiped on both hands)    ";
            else
                cout << "                            ";

            cout << endl;

            cout << "    \u2022 Damage: " << weaponsArray[i]->GetDamage() << endl;
            if(weaponsArray[i]->TwoHanded())
                cout << "    \u2022 Hands:  Both hands required" << endl << endl;
            else
                cout << "    \u2022 Hands:  1 hand required" << endl << endl;
        }

        selection = getch();

        if((isInBattle && selection == 'b') || (!isInBattle && selection == 'c'))
        {
            if (equippedWeaponBoth != NULL)
            {
                weaponDamage -= equippedWeaponBoth->GetDamage();
                equippedWeaponBoth = NULL;
            }

            if (equippedWeaponRight != NULL)
            {
                weaponDamage -= equippedWeaponRight->GetDamage();
                equippedWeaponRight = NULL;
            }

            if (equippedWeaponLeft != NULL)
            {
                weaponDamage -= equippedWeaponLeft->GetDamage();
                equippedWeaponLeft = NULL;
            }

            equippedWeaponBoth = prevWeaponBoth;
            equippedWeaponLeft = prevWeaponLeft;
            equippedWeaponRight = prevWeaponRight;

            weaponDamage = 0;

            if(equippedWeaponBoth != NULL)
                weaponDamage += equippedWeaponBoth->GetDamage();

            if(equippedWeaponRight != NULL)
                weaponDamage += equippedWeaponRight->GetDamage();

            if(equippedWeaponLeft != NULL)
                weaponDamage += equippedWeaponLeft->GetDamage();
        }

        if(selection == 'b')
        {
            cout << "\033[" << lines + 3 << "A";
            cout << "\033[J";
            /*for(int i = 0; i < lines + 6; i++)
                cout << "\033[1A\033[K";
            cout << "\033[5B";*/
            return false;
        }
        else if(selection == 'c')
        {
            /*if(isInBattle)
            {
                cout << "\033[" << lines + 11 << "A";
                cout << "\033[J";
                cout << "\t\t\t\tCHECKPOINT\n";
                usleep(1500000);
                cout << "\033[1A\033[K";
            }
            else
            {*/
                cout << "\033[" << lines + 3 << "A";
                cout << "\033[J";
            //}

            /*for(int i = 0; i < lines + 11; i++)
                cout << "\033[1A\033[K";*/

            return true;
        }
        else if(selection == 'u')
        {
            equippedWeaponBoth = NULL;
            equippedWeaponRight = NULL;
            equippedWeaponLeft = NULL;

            weaponDamage = 0;
        }
        else if(selection == '\n')
        {
            if(weaponsArray[arrow] == equippedWeaponBoth)
            {
                weaponDamage -= equippedWeaponBoth->GetDamage();
                equippedWeaponBoth = NULL;
            }
            else if(weaponsArray[arrow] == equippedWeaponRight)
            {
                weaponDamage -= equippedWeaponRight->GetDamage();
                equippedWeaponRight = NULL;
            }
            else if(weaponsArray[arrow] == equippedWeaponLeft)
            {
                weaponDamage -= equippedWeaponLeft->GetDamage();
                equippedWeaponLeft = NULL;
            }
            else
            {
                int selectedHand;
                char newSelection = ' ';

                if(weaponsArray[arrow]->TwoHanded() == true)
                {
                    selectedHand = 3;
                }
                else
                {
                    cout << "Press 'c' to cancel!" << endl;
                    cout << "Press 1 for right hand or 2 for left hand: ";

                    do{
                        newSelection = getch();

                        if(newSelection == 'c')
                            break;
                    }while(newSelection < '1' || newSelection > '2');

                    selectedHand = newSelection - '0';

                    cout << endl << "\033[2A\033[J";
                }

                if(newSelection != 'c')
                    EquipWeapon(weaponsArray[arrow],selectedHand);
            }
        }
        else if(selection == 'w' && arrow)
            arrow--;
        else if(selection == 's' && arrow < weaponsArray.size() - 1)
            arrow++;

        cout << "\033[" << lines << "A";
    }
}

bool Hero::DisplayArmors(bool isInBattle)
{
    int arrow = 0;
    int lines;

    Armor* prevArmor = equippedArmor;

    lines = 3 * armorsArray.size();

    if(!armorsArray.size())
    {
        cout << "\033[s";
        cout << endl << "Sorry, there are no available armors." << endl;

        usleep(1500000);

        cout << "\033[u";
        cout << "\033[J";

        return false;
    }

    if(isInBattle)
        cout << endl << "Press 'b' to cancel, 'c' to confirm, 'enter' to equip or unequip an armor" << endl << endl;
    else
        cout << endl << "Press 'b' to go back and confirm, 'c' to cancel, 'enter' to equip or unequip an armor" << endl << endl;

    while(true)
    {
        char selection;

        for(unsigned int i = 0; i < armorsArray.size(); i++)
        {
            if(arrow == i)
                cout << " ~> ";
            else
                cout << "    ";

            cout << armorsArray[i]->GetName() << "";

            if(equippedArmor == armorsArray[i])
                cout << " (equiped)";
            else
                cout << "          ";

            cout << endl;

            cout << "    \u2022 Damage Reduction: " << armorsArray[i]->GetDamageReduction() << endl << endl;
        }

        selection = getch();

        if((isInBattle && selection == 'b') || (!isInBattle && selection == 'c'))
        {
            equippedArmor = prevArmor;
            if(equippedArmor != NULL)
                armorDefence = equippedArmor->GetDamageReduction();
            else
                armorDefence = 0;
        }

        if(selection == 'b')
        {
            /*if(isInBattle)
            {*/
                cout << "\033[" << lines + 3 << "A";
                cout << "\033[J";
            /*}
            else
            {
                cout << "\033[" << lines + 6 << "A";
                cout << "\033[5B";
                cout << "\033[J";
            }*/
            //for(int i = 0; i < lines + 6; i++)
            //    cout << "\033[1A\033[K";

            return false;
        }
        else if(selection == 'c')
        {
            if(isInBattle)
            {
                cout << "\033[" << lines + 11 << "A";
                cout << "\033[J";
            }
            else
            {
                cout << "\033[" << lines + 3 << "A";
                cout << "\033[J";
            }
            //for(int i = 0; i < lines + 11; i++)
            //    cout << "\033[1A\033[K";

            return true;
        }
        else if(selection == '\n')
        {
            if(armorsArray[arrow] == equippedArmor)
            {
                equippedArmor = NULL;
                armorDefence = 0;
            }
            else
                WearArmor(arrow);
        }
        else if(selection == 'w' && arrow)
            arrow--;
        else if(selection == 's' && arrow < armorsArray.size() - 1)
            arrow++;

        cout << "\033[" << lines << "A";
    }
}

bool Hero::DisplayPotions(bool isInBattle)
{
    int arrow = 0;

    if(!potionsArray.size())
    {
        cout << "\033[s";
        cout << endl << "Sorry, there are no available potions." << endl;

        usleep(1500000);

        cout << "\033[u";
        cout << "\033[J";

        return false;
    }

    cout << endl << "Press 'b' to go back, 'enter' to drink the potion" << endl << endl;

    while(true)
    {
        int lines;
        char selection;

        if(!potionsArray.size())
        {
            cout << "\033[s";
            cout << endl << "Sorry, there are no available potions." << endl;

            usleep(1500000);

            cout << "\033[u";
            cout << "\033[J";
            cout << "\033[1B";

            selection = 'b';
        }

        lines = 3 * potionsArray.size();

        for(unsigned int i = 0; i < potionsArray.size(); i++)
        {
            if(arrow == i)
                cout << " ~> ";
            else
                cout << "    ";

            cout << potionsArray[i]->GetName() << "            " << endl;
            if(potionsArray[i]->PotionIncreaseStrength())
                cout << "    \u2022 Power-Up: +" << potionsArray[i]->PotionIncreaseStrength() << " in strength" << endl << endl;
            else if(potionsArray[i]->PotionIncreaseDexterity())
                cout << "    \u2022 Power-Up: +" << potionsArray[i]->PotionIncreaseDexterity() << " in dexterity" << endl << endl;
            else
                cout << "    \u2022 Power-Up: +" << potionsArray[i]->PotionIncreaseAgility() << " in agility" << endl << endl;
        }

        if(potionsArray.size())
            selection = getch();

        if(selection == 'b')
        {
            cout << "\033[" << lines + 3 << "A";
            cout << "\033[J";

            /*for(int i = 0; i < lines + 6; i++)
                cout << "\033[1A\033[K";
            cout << "\033[5B";*/

            return false;
        }/**
        else if(selection == 'c')
        {
            cout << "\033[" << lines + 3 << "A";
            cout << "\033[J";*/

            //for(int i = 0; i < lines + 11; i++)
            //    cout << "\033[1A\033[K";

            /*return true;
        }*/
        else if(selection == '\n')
        {
            DrinkPotion(arrow);

            if(arrow == potionsArray.size())
                arrow--;

            cout << "\033[3A";
            cout << "\033[J";

            lines = 3 * potionsArray.size();

            if(isInBattle)
                return true;
        }
        else if(selection == 'w' && arrow)
            arrow--;
        else if(selection == 's' && arrow < potionsArray.size() - 1)
            arrow++;

        cout << "\033[" << lines << "A";
        cout << "\033[J";
    }
}
