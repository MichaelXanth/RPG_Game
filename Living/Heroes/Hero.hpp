/* File: Hero.hpp */

#ifndef __HERO_HEADER__
#define __HERO_HEADER__

#include <vector>
#include <string>

#include "../Living.hpp"

class LightingSpell;
class FireSpell;
class IceSpell;
class Weapon;
class Potion;
class Armor;
class Spell;
class Item;

class Hero : public Living{

    protected:
        std::vector<LightingSpell *> lightingSpellsArray;
        std::vector<FireSpell *> fireSpellsArray;
        std::vector<IceSpell *> iceSpellsArray;

        std::vector<Weapon *> weaponsArray;
        std::vector<Potion *> potionsArray;
        std::vector<Armor *> armorsArray;

        Weapon* equippedWeaponRight;
        Weapon* equippedWeaponLeft;
        Weapon* equippedWeaponBoth;
        Armor* equippedArmor;

        static unsigned int baseMagicPower;
        static unsigned int baseDexterity;
        static unsigned int baseStrength;
        static unsigned int baseHealth;
        static float baseAgility;

        unsigned int availableSpellSlots;
        unsigned int availableItemSlots;
        unsigned int maxSpellsSlots;
        unsigned int maxItemSlots;
        unsigned int mostItems;
        //unsigned int totalSpells;
        //unsigned int totalItems;

        unsigned int weaponDamage;
        unsigned int armorDefence;

        unsigned int magicPower;
        unsigned int dexterity;
        unsigned int strength;
        unsigned int money;
        unsigned int maxMP;
        unsigned int XP;
        float agility;

        bool leftHand;
        bool rightHand;

    public:
        Hero(const std::string& setName, const int& setHealth, const int& setLevel, const unsigned int &,
             const unsigned int &, const unsigned int &, const float &, const unsigned int &);

        void ReduceMagicPower(const unsigned int &);
        void ChangeMoney(const int);
        void GainXP(const unsigned int);
        void RestoreToHalfHP(void);

        void AddNewSpell(LightingSpell *);
        void AddNewSpell(FireSpell *);
        void AddNewSpell(IceSpell *);
        void AddNewItem(Weapon *);
        void AddNewItem(Potion *);
        void AddNewItem(Armor *);

        void RemoveLightingSpell(const unsigned int &);
        void RemoveFireSpell(const unsigned int &);
        void RemoveIceSpell(const unsigned int &);
        void RemoveWeapon(const unsigned int &);
        void RemovePotion(const unsigned int &);
        void RemoveArmor(const unsigned int &);

        bool isValidForSale(std::string *, int &, int &, const int &);

        unsigned int GetNumberOfSpells(unsigned int) const;
        unsigned int GetAvailableSpellSlots(void) const;
        unsigned int GetAvailableItemSlots(void) const;
        unsigned int GetNumberOfPotions(void) const;
        unsigned int GetNumberOfWeapons(void) const;
        unsigned int GetNumberOfArmors(void) const;
        unsigned int GetMaxSpellsSlots(void) const;
        unsigned int GetMaxItemsSlots(void) const;
        unsigned int GetWeaponDamage(void) const;
        unsigned int GetArmorDefence(void) const;
        //unsigned int GetTotalSpells(void) const;
        //unsigned int GetTotalItems(void) const;
        unsigned int GetMagicPower(void) const;
        unsigned int GetDexterity(void) const;
        unsigned int GetStrength(void) const;
        unsigned int GetDefence(void) const;
        unsigned int GetMoney(void) const;
        unsigned int GetXP(void) const;
        float GetAgility(void) const;
        void RecalcMostItems(void);

        void EndTurnRefill(void);

        Spell* GetSpellFromSlot(const unsigned int, const unsigned int);
        bool SpellUsed(const unsigned int, const unsigned int);

        Potion* GetPotionFromSlot(const unsigned int);
        void DrinkPotion(const unsigned int);

        Armor* GetArmorFromSlot(const unsigned int);
        void WearArmor(const unsigned int);

        Weapon* GetWeaponFromSlot(unsigned int);
        bool EquipWeapon(Weapon *, const short);

        bool UseSpell(Spell &);

        void DisplayProdsForSale(const bool & = false, const int & = -1);

        bool DisplaySpells(Spell*& , unsigned int& , unsigned int&);
        bool DisplayWeapons(bool = false);
        bool DisplayPotions(bool = false);
        bool DisplayArmors(bool = false);

        static unsigned int GetBaseMagicPower(void);
        static unsigned int GetBaseDexterity(void);
        static unsigned int GetBaseStrength(void);
        static unsigned int GetBaseHealth(void);
        static float GetBaseAgility(void);

        virtual ~Hero() = 0;
};

#endif // __HERO_HEADER__
