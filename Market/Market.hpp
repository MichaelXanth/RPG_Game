/* File: Market.hpp */

#ifndef __MARKET_HPP__
#define __MARKET_HPP__

#include <iostream>
#include <vector>

#include "../Names.hpp"

class LightingSpell;
class FireSpell;
class IceSpell;
class Weapon;
class Potion;
class Armor;
class Spell;
class Hero;
class Item;

class Market{

    private:
        Names name;

        std::vector<LightingSpell *> lightingSpellsArray;
        std::vector<FireSpell *> fireSpellsArray;
        std::vector<IceSpell *> iceSpellsArray;
        std::vector<Weapon *> weaponsArray;
        std::vector<Potion *> potionsArray;
        std::vector<Armor *> armorsArray;

        std::vector<int> lightingSpellsIndexes;
        std::vector<int> fireSpellsIndexes;
        std::vector<int> iceSpellsIndexes;
        std::vector<int> weaponsIndexes;
        std::vector<int> potionsIndexes;
        std::vector<int> armorsIndexes;

        unsigned int lightingSpellsForSale;
        unsigned int fireSpellsForSale;
        unsigned int iceSpellsForSale;
        unsigned int weaponsForSale;
        unsigned int potionsForSale;
        unsigned int armorsForSale;

        unsigned int minSpellPrice;
        unsigned int minItemPrice;
        unsigned int minPrice;

        unsigned int mostItems;
        unsigned int prevLevel;

        void DisplayMarket(const bool & = false, const Hero * = NULL, const int = -1);
        void ResetForSaleProds(void);
        void RecalcMostItems(void);

        bool isValidForPurchase(std::string *, int &, int &, const int &);
        bool canBeBought(const Spell *, const Hero *);
        bool canBeBought(const Item *, const Hero *);

         int isAbleToBuy(const Hero *, const bool &);
        void Purchase(Hero &, const int &);
        void Buy(std::vector<Hero *> &);

         int isAbleToSell(const Hero *, const bool &);
        void Sale(Hero &, const int &);
        void Sell(std::vector<Hero *> &);

        void NewStuff(std::vector<Hero *> &);

        void AddLightingSpells(const int &);
        void AddFireSpells(const int &);
        void AddIceSpells(const int &);
        void AddWeapons(const int &);
        void AddPotions(const int &);
        void AddArmors(const int &);


    public:
        Market();
        ~Market();

        bool EnterMarket(std::vector<Hero *> &);
};

#endif // __MARKET_HPP__
