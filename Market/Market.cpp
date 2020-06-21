/* File: Market.cpp */

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>
#include <unistd.h>

#include "../Input_Validation/Input_Validation.hpp"
#include "../Items/Armor.hpp"
#include "../Items/Potion.hpp"
#include "../Items/Weapon.hpp"
#include "../Living/Heroes/Hero.hpp"
#include "../Spells/FireSpell.hpp"
#include "../Spells/IceSpell.hpp"
#include "../Spells/LightingSpell.hpp"
#include "../Spells/Spell.hpp"
#include "Market.hpp"

using namespace std;

void Market::RecalcMostItems(void)
{
    mostItems = 0;

    if (mostItems < lightingSpellsArray.size())
        mostItems = lightingSpellsArray.size();

    if (mostItems < fireSpellsArray.size())
        mostItems = fireSpellsArray.size();

    if (mostItems < iceSpellsArray.size())
        mostItems = iceSpellsArray.size();

    if (mostItems < weaponsArray.size())
        mostItems = weaponsArray.size();

    if (mostItems < potionsArray.size())
        mostItems = potionsArray.size();

    if (mostItems < armorsArray.size())
        mostItems = armorsArray.size();
}

void Market::ResetForSaleProds(void)
{
    lightingSpellsForSale = 0;
    fireSpellsForSale = 0;
    iceSpellsForSale = 0;
    weaponsForSale = 0;
    potionsForSale = 0;
    armorsForSale = 0;
}

bool Market::isValidForPurchase(string testSelections[], int& column, int& row, const int& buyState)
{
    if (!isValid(testSelections[0].c_str(),column,0,6))
        return false;

    if (!isNumeric(testSelections[1].c_str(),row))
        return false;

    if (buyState == 0 && column > 3) {
        if (weaponsForSale || potionsForSale || armorsForSale)
            cerr << endl << "\033[35mWarning:\033[0m There are no more available Item slots." << endl;
        else
            cerr << endl << "\033[35mWarning:\033[0m Sorry, there are no available Items for sale." << endl;
        return false;
    }

    if (buyState == 1 && column < 4) {
        if (lightingSpellsForSale || fireSpellsForSale || iceSpellsForSale)
            cerr << endl << "\033[35mWarning:\033[0m There are no more available Spell slots." << endl;
        else
            cerr << endl << "\033[35mWarning:\033[0m Sorry, there are no available Spells for sale." << endl;
        return false;
    }

    switch(column)
    {
        case 1:
            if (row == 0 || row > iceSpellsForSale) {
                cerr << "\n\033[31mError:\033[0m The input is invalid." << endl;
                cerr << "Please, try again!" << endl << endl;
                return false;
            }

            break;

        case 2:
            if (row == 0 || row > fireSpellsForSale) {
                cerr << "\n\033[31mError:\033[0m The input is invalid." << endl;
                cerr << "Please, try again!" << endl << endl;
                return false;
            }

            break;

        case 3:
            if (row == 0 || row > lightingSpellsForSale) {
                cerr << "\n\033[31mError:\033[0m The input is invalid." << endl;
                cerr << "Please, try again!" << endl << endl;
                return false;
            }

            break;

        case 4:
            if (row == 0 || row > weaponsForSale){
                cerr << "\n\033[31mError:\033[0m The input is invalid." << endl;
                cerr << "Please, try again!" << endl << endl;
                return false;
            }

            break;

        case 5:
            if (row == 0 || row > armorsForSale) {
                cerr << "\n\033[31mError:\033[0m The input is invalid." << endl;
                cerr << "Please, try again!" << endl << endl;
                return false;
            }

            break;

        case 6:
            if (row == 0 || row > potionsForSale) {
                cerr << "\n\033[31mError:\033[0m The input is invalid." << endl;
                cerr << "Please, try again!" << endl << endl;
                return false;
            }

            break;
    }
    return true;
}

Market::Market() : lightingSpellsForSale(0), fireSpellsForSale(0)   , iceSpellsForSale(0),
                   weaponsForSale(0)       , potionsForSale(0)      , armorsForSale(0)   , 
                   minSpellPrice(INT32_MAX), minItemPrice(INT32_MAX), minPrice(INT32_MAX), 
                   mostItems(0)            , prevLevel(0)
{
    AddLightingSpells(10);
    AddFireSpells(10);
    AddIceSpells(10);
    AddWeapons(10);
    AddPotions(10);
    AddArmors(10);
}

Market::~Market()
{
    for (int i = iceSpellsArray.size(); !iceSpellsArray.empty(); i--) {
        delete iceSpellsArray[i-1];
        iceSpellsArray.erase(iceSpellsArray.begin() + i-1);
    }

    for (int i = fireSpellsArray.size(); !fireSpellsArray.empty(); i--) {
        delete fireSpellsArray[i-1];
        fireSpellsArray.erase(fireSpellsArray.begin() + i-1);
    }

    for (int i = lightingSpellsArray.size(); !lightingSpellsArray.empty(); i--) {
        delete lightingSpellsArray[i-1];
        lightingSpellsArray.erase(lightingSpellsArray.begin() + i-1);
    }

    for (int i = weaponsArray.size(); !weaponsArray.empty(); i--) {
        delete weaponsArray[i-1];
        weaponsArray.erase(weaponsArray.begin() + i-1);
    }

    for (int i = armorsArray.size(); !armorsArray.empty(); i--) {
        delete armorsArray[i-1];
        armorsArray.erase(armorsArray.begin() + i-1);
    }

    for (int i = potionsArray.size(); !potionsArray.empty(); i--) {
        delete potionsArray[i-1];
        potionsArray.erase(potionsArray.begin() + i-1);
    }
}

void Market::AddLightingSpells(const int& num)
{
    string spellName;
    LightingSpell* tmpLightingSpell;

    for (int i = 0; i < num; i++)
    {
        unsigned int level;
        int tmpMinDamage;
        int tmpMaxDamage;

        if ( ((double)rand() / RAND_MAX) < 0.7 )
            level = rand() % 30 + 1;
        else
            level = rand() % 70 + 31;

        spellName = name.lightingSpellsNames[rand() % name.lightingSpellsNames.size()];

        do {
            tmpMinDamage = ((rand() % 2) + 2) * level;
            tmpMaxDamage = ((rand() % 4) + 2) * level;
        } while(tmpMinDamage == tmpMaxDamage);

        if (tmpMaxDamage < tmpMinDamage) {
            int temp     = tmpMinDamage;
            tmpMinDamage = tmpMaxDamage;
            tmpMaxDamage = temp;
        }

        tmpLightingSpell = new LightingSpell(spellName , ((rand() % 2) + 3) * level, (rand() % 4) + 1 , level, tmpMinDamage , tmpMaxDamage,
                                             ((rand() % 4) + 1) * level , (unsigned int)((rand() % 6) + 1) * ((level / 25) + 1));

        lightingSpellsArray.push_back(tmpLightingSpell);

        if (minSpellPrice > tmpLightingSpell->GetPrice())
            minSpellPrice = tmpLightingSpell->GetPrice();
    }

    if (mostItems < lightingSpellsArray.size())
        mostItems = lightingSpellsArray.size();

    if (minPrice > minSpellPrice)
        minPrice = minSpellPrice;
}

void Market::AddFireSpells(const int& num)
{
    string spellName;
    FireSpell* tmpFireSpell;

    for (int i = 0; i < num; i++)
    {
        unsigned int level;
        int tmpMinDamage;
        int tmpMaxDamage;

        if ( ((double)rand() / RAND_MAX) < 0.7 )
            level = rand() % 30 + 1;
        else
            level = rand() % 70 + 31;

        spellName = name.fireSpellsNames[rand() % name.fireSpellsNames.size()];

        do {
            tmpMinDamage = ((rand() % 2) + 2) * level;
            tmpMaxDamage = ((rand() % 4) + 2) * level;
        } while(tmpMinDamage == tmpMaxDamage);

        if (tmpMaxDamage < tmpMinDamage)
        {
            int temp     = tmpMinDamage;
            tmpMinDamage = tmpMaxDamage;
            tmpMaxDamage = temp;
        }

        tmpFireSpell = new FireSpell(spellName , ((rand() % 2) + 3) * level, (rand() % 4) + 1 , level, tmpMinDamage , tmpMaxDamage,
                                    ((rand() % 4) + 1) * level , (unsigned int)((3.0 / 2.0) * level));

        fireSpellsArray.push_back(tmpFireSpell);

        if (minSpellPrice > tmpFireSpell->GetPrice())
            minSpellPrice = tmpFireSpell->GetPrice();
    }

    if (mostItems < fireSpellsArray.size())
        mostItems = fireSpellsArray.size();

    if (minPrice > minSpellPrice)
        minPrice = minSpellPrice;
}

void Market::AddIceSpells(const int& num)
{
    string spellName;
    IceSpell* tmpIceSpell;

    for (int i = 0; i < num; i++)
    {
        unsigned int level;
        int tmpMinDamage;
        int tmpMaxDamage;

        if ( ((double)rand() / RAND_MAX) < 0.7 )
            level = rand() % 30 + 1;
        else
            level = rand() % 70 + 31;

        spellName = name.iceSpellsNames[rand() % name.iceSpellsNames.size()];

        do {
            tmpMinDamage = ((rand() % 2) + 2) * level;
            tmpMaxDamage = ((rand() % 4) + 2) * level;
        } while(tmpMinDamage == tmpMaxDamage);

        if (tmpMaxDamage < tmpMinDamage)
        {
            int temp    = tmpMinDamage;
            tmpMinDamage = tmpMaxDamage;
            tmpMaxDamage = temp;
        }

        tmpIceSpell = new IceSpell(spellName , ((rand() % 2) + 3) * level, (rand() % 4) + 1 , level, tmpMinDamage , tmpMaxDamage,
                                  ((rand() % 4) + 1) * level , ((rand() % 2) + 1) * level);

        iceSpellsArray.push_back(tmpIceSpell);

        if (minSpellPrice > tmpIceSpell->GetPrice())
            minSpellPrice = tmpIceSpell->GetPrice();
    }

    if (mostItems < iceSpellsArray.size())
        mostItems = iceSpellsArray.size();

    if (minPrice > minSpellPrice)
        minPrice = minSpellPrice;
}

void Market::AddWeapons(const int& num)
{
    string weaponName;
    Weapon* tmpWeapon;

    for (int i = 0; i < num; i++)
    {
        unsigned int level;
        bool hand = rand() % 2;
        int wdamage;

        if ( ((double)rand() / RAND_MAX) < 0.7 )
            level = rand() % 30 + 1;
        else
            level = rand() % 70 + 31;

        weaponName = name.weaponsNames[rand() % name.weaponsNames.size()];

        wdamage = (unsigned int)((hand + 1.0) * level * ((double)(rand() % 2) + 1) / 2.0);

        tmpWeapon = new Weapon(weaponName , ((rand() % 2) + 3) * level , level , wdamage , hand);

        weaponsArray.push_back(tmpWeapon);

        if (minItemPrice > tmpWeapon->GetPrice())
            minItemPrice = tmpWeapon->GetPrice();
    }

    if (mostItems < weaponsArray.size())
        mostItems = weaponsArray.size();

    if (minPrice > minItemPrice)
        minPrice = minItemPrice;
}

void Market::AddPotions(const int& num)
{
    string potionName;
    Potion* tmpPotion;

    for (int i = 0; i < num; i++)
    {
        unsigned int level;
        float posibility;

        if ( ((double)rand() / RAND_MAX) < 0.7 )
            level = rand() % 30 + 1;
        else
            level = rand() % 70 + 31;

        potionName = name.potionsNames[rand() % name.potionsNames.size()];

        if ((double)(posibility = rand() % 100) < 100.0 / 3)
            tmpPotion = new Potion(potionName , ((rand() % 2) + 2) * level , level , (unsigned int)(((rand() % 6) + 1.0) * (level / 10.0) + 1) , 0 , 0);
        else if ((double)posibility < 200.0 / 3)
            tmpPotion = new Potion(potionName , ((rand() % 2) + 2) * level , level , 0 , (unsigned int)(((rand() % 6) + 1.0) * (level / 10.0) + 1) , 0);
        else
            tmpPotion = new Potion(potionName , ((rand() % 2) + 2) * level , level , 0 , 0 , (float)(3.0 * ((level / 25.0) + 1)) / 100.0);

        potionsArray.push_back(tmpPotion);

        if (minItemPrice > tmpPotion->GetPrice())
            minItemPrice = tmpPotion->GetPrice();
    }

    if (mostItems < potionsArray.size())
        mostItems = potionsArray.size();

    if (minPrice > minItemPrice)
        minPrice = minItemPrice;
}

void Market::AddArmors(const int& num)
{
    string armorName;
    Armor* tmpArmor;

    for (int i = 0; i < num; i++)
    {
        unsigned int level;

        if ( ((double)rand() / RAND_MAX) < 0.7 )
            level = rand() % 30 + 1;
        else
            level = rand() % 70 + 31;

        armorName = name.armorsNames[rand() % name.armorsNames.size()];

        tmpArmor = new Armor(armorName , ((rand() % 2) + 3) * level , level , (unsigned int)(level * (4.0 / 2.0)));

        armorsArray.push_back(tmpArmor);

        if (minItemPrice > tmpArmor->GetPrice())
            minItemPrice = tmpArmor->GetPrice();
    }

    if (mostItems < armorsArray.size())
        mostItems = armorsArray.size();

    if (minPrice > minItemPrice)
        minPrice = minItemPrice;
}

void Market::NewStuff(vector<Hero *>& heroes)
{
    if (heroes.size() == 1)
    {
        if (heroes[0]->Living::GetLevel() < prevLevel + 2)
            return;

        prevLevel = heroes[0]->Living::GetLevel();
    
    } else {
        unsigned int averageLevel = 0;

        for (unsigned int i = 0; i < heroes.size(); i++)
            averageLevel += heroes[i]->Living::GetLevel();
        
        averageLevel /= heroes.size();

        if (averageLevel < prevLevel + 2)
            return;

        prevLevel = averageLevel;
    }

    if (rand() % prevLevel < prevLevel / 6)
        AddLightingSpells(rand() % 10);

    if (rand() % prevLevel < prevLevel / 6)
        AddFireSpells(rand() % 10);

    if (rand() % prevLevel < prevLevel / 6)
        AddIceSpells(rand() % 10);

    if (rand() % prevLevel < prevLevel / 6)
        AddWeapons(rand() % 10);

    if (rand() % prevLevel < prevLevel / 6)
        AddPotions(rand() % 10);

    if (rand() % prevLevel < prevLevel / 6)
        AddArmors(rand() % 10);
}

int Market::isAbleToBuy(const Hero* hero, const bool& info = true)
{
    int buyState = 2;
    bool found = false;

    if (hero->GetMoney() == 0) {
        if (info) {
            if (lightingSpellsForSale || fireSpellsForSale || iceSpellsForSale || weaponsForSale || potionsForSale || armorsForSale) {
                
                DisplayMarket(false, hero, 3);
                cerr << endl;
                cerr << "-------------------------------" << endl << endl;
                cerr << "\033[35mWarning:\033[0m Hero \033[38;5;220m" << hero->Living::GetName() << "\033[0m has no money. The minimum required amount is: " << minPrice << endl;
                usleep(2500000);
            
            } else
                cerr << endl << "\033[31mError:\033[0m Hero \033[38;5;220m" << hero->Living::GetName() << "\033[0m has no money. The minimum required amount is: " << minPrice << endl;
        }
        return -1;
    }

    if (hero->GetMoney() < minPrice) {
        if (info) {
            if (lightingSpellsForSale || fireSpellsForSale || iceSpellsForSale || weaponsForSale || potionsForSale || armorsForSale) {

                DisplayMarket(false,hero,3);
                cerr << endl;
                cerr << "-------------------------------" << endl << endl;
                cerr << "\033[35mWarning:\033[0m Hero \033[38;5;220m" << hero->Living::GetName() << "\033[0m doesn't have enough money. The minimum required amount is: " << minPrice << endl;
                usleep(2500000);
            
            } else
                cerr << endl << "\033[31mError:\033[0m Hero \033[38;5;220m" << hero->Living::GetName() << "\033[0m doesn't have enough money. The minimum required amount is: " << minPrice << endl;
        }
        return -1;
    }

    if (hero->GetAvailableItemSlots() == 0 || hero->GetMoney() < minItemPrice) {
        if (hero->GetAvailableSpellSlots() == 0 || hero->GetMoney() < minSpellPrice) {
            if (info) {
                if (lightingSpellsForSale || fireSpellsForSale || iceSpellsForSale || weaponsForSale || potionsForSale || armorsForSale) {
                    
                    DisplayMarket(false,hero,3);
                    cerr << endl;
                    cerr << "-------------------------------" << endl << endl;
                    cerr << "\033[35mWarning:\033[0m Hero \033[38;5;220m" << hero->Living::GetName() << "\033[0m doesn't have any other available Item and Spell slots." << endl;
                    usleep(2500000);
                
                } else
                    cerr << endl << "\033[31mError:\033[0m Hero \033[38;5;220m" << hero->Living::GetName() << "\033[0m doesn't have enough money. The minimum required amount is: " << minPrice << endl;
            }
            return -1;
        }
        buyState = 0;   //Means that he can buy Spells only
    
    } else if (hero->GetAvailableSpellSlots() == 0 || hero->GetMoney() < minSpellPrice) {
        buyState = 1;   //Means that he can buy Items only
    }

    if (buyState != 1) {
        
        unsigned int i;

        for (i = 0; i < iceSpellsArray.size() && !canBeBought(iceSpellsArray[i],hero); i++)
            ;
        if (i < iceSpellsArray.size())
            found = true;

        for (i = 0; i < fireSpellsArray.size() && !canBeBought(fireSpellsArray[i],hero); i++)
            ;
        if (i < fireSpellsArray.size())
            found = true;

        for (i = 0; i < lightingSpellsArray.size() && !canBeBought(lightingSpellsArray[i],hero); i++)
            ;
        if (i < lightingSpellsArray.size())
            found = true;
    }

    if (buyState != 0) {

        unsigned int i;

        for (i = 0; i < weaponsArray.size() && !canBeBought(weaponsArray[i],hero); i++)
            ;
        if (i < weaponsArray.size())
            found = true;

        for (i = 0; i < armorsArray.size() && !canBeBought(armorsArray[i],hero); i++)
            ;
        if (i < armorsArray.size())
            found = true;

        for (i = 0; i < potionsArray.size() && !canBeBought(potionsArray[i],hero); i++)
            ;
        if (i < potionsArray.size())
            found = true;
    }

    if (!found) {
        if (info) {
            cerr << endl << "\033[31mError:\033[0m There are no available Items or Spells for Hero \033[38;5;220m" << hero->Living::GetName() << "\033[0m to buy." << endl;
            usleep(3000000);
        }
        return -1;
    }

    return buyState;
}

void Market::Purchase(Hero& hero, const int& buyState)
{
    int  column, row;
    char confirmation;
    bool errFlag = false;
    string testSelections[2];

    cout << endl;
    cout << "-------------------------------" << endl << endl;
    cout << "(Type 0 to cancel)" << endl;

    if (buyState == 0) {
        cout << "Choose a Spell by selecting its position in the table(e.g.: \033[1;34m<\033[1;33mcolumn\033[1;34m> <\033[1;33mrow\033[1;34m>\033[0m): ";

        cout << "\n\n\n\n\n\n\n\n";
        cout << "\033[8A\033[77C";
    
    } else if (buyState == 1) {
        cout << "Choose an Item by selecting its position in the table(e.g.: \033[1;34m<\033[1;33mcolumn\033[1;34m> <\033[1;33mrow\033[1;34m>\033[0m): ";

        cout << "\n\n\n\n\n\n\n\n";
        cout << "\033[8A\033[77C";
    
    } else {
        cout << "Choose an Item or a Spell by selecting its position in the table(e.g.: \033[1;34m<\033[1;33mcolumn\033[1;34m> <\033[1;33mrow\033[1;34m>\033[0m): ";

        cout << "\n\n\n\n\n\n\n\n";
        cout << "\033[8A\033[88C";
    }

    cout << "\033[s";

    do {
        if (errFlag)
            usleep(1800000);

        cout << "\033[u";
        cout << "\033[J";
        cout << "\033[s";

        errFlag = true;

        cin >> testSelections[0];

        if (testSelections[0] == "0") {
            column = 0;
            break;
        }

        cin >> testSelections[1];
    } while(!isValidForPurchase(testSelections,column,row,buyState));

    if (column == 0) {
        cout << endl << "\033[1;32mInfo:\033[0m The purchase was canceled." << endl << endl;
        return;
    }

    switch(column)
    {
        case 1:
            cout << endl << "Are you sure you want to buy \"\033[1m\033[38;5;32m" << iceSpellsArray[iceSpellsIndexes[row - 1]]->GetName() << "\033[0m\" Ice Spell? [y/n]: ";

            do {
                cin >> confirmation;
            } while(confirmation != 'y' && confirmation != 'Y' && confirmation != 'n' && confirmation != 'N');

            if (confirmation == 'n' || confirmation == 'N')
                break;

            hero.ChangeMoney(-iceSpellsArray[iceSpellsIndexes[row - 1]]->GetPrice());
            hero.AddNewSpell(iceSpellsArray[iceSpellsIndexes[row - 1]]);
            iceSpellsArray.erase(iceSpellsArray.begin() + iceSpellsIndexes[row - 1]);
            RecalcMostItems();

            break;

        case 2:
            cout << endl << "Are you sure you want to buy \"\033[1m\033[1;31m" << fireSpellsArray[fireSpellsIndexes[row - 1]]->GetName() << "\033[0m\" Fire Spell? [y/n]: ";

            do {
                cin >> confirmation;
            } while(confirmation != 'y' && confirmation != 'Y' && confirmation != 'n' && confirmation != 'N');

            if (confirmation == 'n' || confirmation == 'N')
                break;

            hero.ChangeMoney(-fireSpellsArray[fireSpellsIndexes[row - 1]]->GetPrice());
            hero.AddNewSpell(fireSpellsArray[fireSpellsIndexes[row - 1]]);
            fireSpellsArray.erase(fireSpellsArray.begin() + fireSpellsIndexes[row - 1]);
            RecalcMostItems();

            break;

        case 3:
            cout << endl << "Are you sure you want to buy \"\033[1m\033[38;5;15m" << lightingSpellsArray[lightingSpellsIndexes[row - 1]]->GetName() << "\033[0m\" Lighting Spell? [y/n]: ";

            do {
                cin >> confirmation;
            } while(confirmation != 'y' && confirmation != 'Y' && confirmation != 'n' && confirmation != 'N');

            if (confirmation == 'n' || confirmation == 'N')
                break;

            hero.ChangeMoney(-lightingSpellsArray[lightingSpellsIndexes[row - 1]]->GetPrice());
            hero.AddNewSpell(lightingSpellsArray[lightingSpellsIndexes[row - 1]]);
            lightingSpellsArray.erase(lightingSpellsArray.begin() + lightingSpellsIndexes[row - 1]);
            RecalcMostItems();

            break;

        case 4:
            cout << endl << "Are you sure you want to buy \"\033[1m\033[38;5;166m" << weaponsArray[weaponsIndexes[row - 1]]->GetName() << "\033[0m\" Weapon? [y/n]: ";

            do {
                cin >> confirmation;
            } while(confirmation != 'y' && confirmation != 'Y' && confirmation != 'n' && confirmation != 'N');

            if (confirmation == 'n' || confirmation == 'N')
                break;

            hero.ChangeMoney(-weaponsArray[weaponsIndexes[row - 1]]->GetPrice());
            hero.AddNewItem(weaponsArray[weaponsIndexes[row - 1]]);
            weaponsArray.erase(weaponsArray.begin() + weaponsIndexes[row - 1]);
            RecalcMostItems();

            break;

        case 5:
            cout << endl << "Are you sure you want to buy \"\033[1m\033[38;5;28m" << armorsArray[armorsIndexes[row - 1]]->GetName() << "\033[0m\" Armor? [y/n]: ";

            do {
                cin >> confirmation;
            } while(confirmation != 'y' && confirmation != 'Y' && confirmation != 'n' && confirmation != 'N');

            if (confirmation == 'n' || confirmation == 'N')
                break;

            hero.ChangeMoney(-(armorsArray[armorsIndexes[row - 1]]->GetPrice()));
            hero.AddNewItem(armorsArray[armorsIndexes[row - 1]]);
            armorsArray.erase(armorsArray.begin() + armorsIndexes[row - 1]);
            RecalcMostItems();

            break;

        case 6:
            cout << endl << "Are you sure you want to buy \"\033[1m\033[38;5;90m" << potionsArray[potionsIndexes[row - 1]]->GetName() << "\033[0m\" Potion? [y/n]: ";

            do {
                cin >> confirmation;
            } while(confirmation != 'y' && confirmation != 'Y' && confirmation != 'n' && confirmation != 'N');

            if (confirmation == 'n' || confirmation == 'N')
                break;

            hero.ChangeMoney(-potionsArray[potionsIndexes[row - 1]]->GetPrice());
            hero.AddNewItem(potionsArray[potionsIndexes[row - 1]]);
            potionsArray.erase(potionsArray.begin() + potionsIndexes[row - 1]);
            RecalcMostItems();

            break;
    }
}

void Market::Buy(vector<Hero *>& heroes)
{
    unsigned int i;

    int action;
    string testAction;
    bool infoState     = false;
    Hero* selectedHero = NULL;

    if (heroes.size() == 1 && isAbleToBuy(heroes[0]) == -1) {
        usleep(2500000);
        DisplayMarket();
        return;
    
    } else {
        for (i = 0; i < heroes.size() && isAbleToBuy(heroes[i],false) == -1; i++)
            ;

        if (i == heroes.size()) {
            cerr << endl << "\033[31mError:\033[0m No one of the heroes are able to buy any Items or Spells from the Market.";
            usleep(2500000);
            DisplayMarket();
            return;
        }
    }

    while(true) {
        
        int buyState;

        if (heroes.size() == 1) {
            selectedHero = heroes[0];
        
        } else {
        
            for (i = 0; i < heroes.size() && isAbleToBuy(heroes[i],false) == -1; i++)
                ;

            if (i == heroes.size()) {
                cerr << endl << "-------------------------------" << endl << endl;
                cerr << "\033[35mWarning:\033[0m There are no other heroes able to buy any Items or Spells from the Market.";
                usleep(3000000);
                DisplayMarket();
                return;
            }

            while(selectedHero == NULL) {
                //bool errorFlag = false;
                cout << endl;
                cout << "-------------------------------" << endl << endl;
                cout << "(Type 0 to cancel)" << endl;
                cout << "Choose a Hero (1 - " << heroes.size() << "): ";

                cout << "\n\n\n\n\n";
                cout << "\033[5A\033[23C";

                while(true) {

                    bool errFlag = false;
                    cout << "\033[s";

                    do {
                        if (errFlag)
                            usleep(1800000);

                        cout << "\033[u";
                        cout << "\033[J";
                        cout << "\033[s";

                        cin >> testAction;

                        errFlag = true;
                    } while(!isNumeric(testAction.c_str(),action));

                    if (action < 0 || action > heroes.size()) {
                        cerr << endl << "\033[31mError:\033[0m Please choose a number in the given range." << endl;

                        usleep(1800000);

                        cout << "\033[u";
                        cout << "\033[J";

                        //cout << "\033[K";
                        //cout << "\033[1A\033[K";
                        //cout << "\033[1A\033[K";

                        //if (errorFlag)
                        //    cout << "\033[1A\033[K";

                        //errorFlag = true;
                    } else {
                        if (!action) {
                            DisplayMarket();
                            return;
                        }
                        selectedHero = heroes[action - 1];
                        break;
                    }
                }
            }
        }

        if ((buyState = isAbleToBuy(selectedHero)) != -1) {
            bool errFlag = false;

            DisplayMarket(infoState,selectedHero,buyState);

            cout << endl;
            cout << "-------------------------------" << endl << endl;
            cout << "Choose an action: ";

            cout << "\n\n\n\n\n";
            cout << "\033[5A\033[18C";
            cout << "\033[s";

            do {
                if (errFlag)
                    usleep(1800000);

                cout << "\033[u";
                cout << "\033[J";
                cout << "\033[s";

                cin >> testAction;

                errFlag = true;
            } while(!isValid(testAction.c_str(),action,1,3));

            switch(action)
            {
                case 1:
                    Purchase(*selectedHero,buyState);
                    break;
                case 2:
                    infoState = !infoState;
                    // DisplayMarket(infoState,selectedHero,buyState);
                    break;
                case 3:
                    DisplayMarket();
                    return;
            }
        
        } else if (heroes.size() == 1) {
            usleep(2500000);
            DisplayMarket();
            return;
        }

        if (buyState == -1) {
            DisplayMarket();
            return;
        }
    //        selectedHero = NULL;
    }
}

int Market::isAbleToSell(const Hero* hero, const bool& info = true)
{
    int sellState = 2;

    if (hero->GetAvailableItemSlots() == hero->GetMaxItemsSlots()) {
        if (hero->GetAvailableSpellSlots() == hero->GetMaxSpellsSlots()) {
            if (info) {
                cerr << endl << "\033[31mError:\033[0m Hero \033[38;5;220m" << hero->Living::GetName() << "\033[0m doesn't have any Items or Spells for sale." << endl;
                usleep(2500000);
            }
            return -1;
        }
        sellState = 0;   //Means that he can sell Spells only
    
    } else if (hero->GetAvailableSpellSlots() == hero->GetMaxSpellsSlots()) {
        sellState = 1;   //Means that he can buy Items only
    }

    return sellState;
}

void Market::Sale(Hero& hero, const int& sellState)
{
    int  column, row;
    char confirmation;
    bool errFlag = false;
    string testSelections[2];

    cout << endl;
    cout << "-------------------------------" << endl << endl;
    cout << "(Type 0 to cancel)" << endl;

    if (sellState == 0) {
        cout << "Choose a Spell by selecting its position in the table(e.g.: \033[1;34m<\033[1;33mcolumn\033[1;34m> <\033[1;33mrow\033[1;34m>\033[0m): ";

        cout << "\n\n\n\n\n\n\n\n";
        cout << "\033[8A\033[77C";
    
    } else if (sellState == 1) {
        cout << "Choose an Item by selecting its position in the table(e.g.: \033[1;34m<\033[1;33mcolumn\033[1;34m> <\033[1;33mrow\033[1;34m>\033[0m): ";

        cout << "\n\n\n\n\n\n\n\n";
        cout << "\033[8A\033[77C";
    
    } else {
        cout << "Choose an Item or a Spell by selecting its position in the table(e.g.: \033[1;34m<\033[1;33mcolumn\033[1;34m> <\033[1;33mrow\033[1;34m>\033[0m): ";

        cout << "\n\n\n\n\n\n\n\n";
        cout << "\033[8A\033[88C";
    }

    cout << "\033[s";

    do {
        if (errFlag)
            usleep(1800000);

        cout << "\033[u";
        cout << "\033[J";
        cout << "\033[s";

        errFlag = true;

        cin >> testSelections[0];

        if (testSelections[0] == "0") {
            column = 0;
            break;
        }

        cin >> testSelections[1];
    } while(!hero.isValidForSale(testSelections,column,row,sellState));

    if (column == 0) {
        cout << endl << "\033[1;32mInfo:\033[0m The sale operation was canceled." << endl << endl;
        return;
    }

    switch(column)
    {
        case 1:
            if (sellState == 1) {
                cout << endl << "Are you sure you want to sell \"\033[1m\033[38;5;166m" << hero.GetWeaponFromSlot(row - 1)->GetName() << "\033[0m\" Weapon? [y/n]: ";

                do {
                    cin >> confirmation;
                } while(confirmation != 'y' && confirmation != 'Y' && confirmation != 'n' && confirmation != 'N');

                if (confirmation == 'n' || confirmation == 'N')
                    break;

                hero.RemoveWeapon(row - 1);
            
            } else {
                cout << endl << "Are you sure you want to sell \"\033[1m\033[38;5;32m" << hero.GetSpellFromSlot(row - 1, 2)->GetName() << "\033[0m\" Ice Spell? [y/n]: ";

                do {
                    cin >> confirmation;
                } while(confirmation != 'y' && confirmation != 'Y' && confirmation != 'n' && confirmation != 'N');

                if (confirmation == 'n' || confirmation == 'N')
                    break;

                hero.RemoveIceSpell(row - 1);
            }

            break;

        case 2:
            if (sellState == 1) {
                cout << endl << "Are you sure you want to sell \"\033[1m\033[38;5;28m" << hero.GetArmorFromSlot(row - 1)->GetName() << "\033[0m\" Armor? [y/n]: ";

                do {
                    cin >> confirmation;
                } while(confirmation != 'y' && confirmation != 'Y' && confirmation != 'n' && confirmation != 'N');

                if (confirmation == 'n' || confirmation == 'N')
                    break;

                hero.RemoveArmor(row - 1);
            
            } else {
                cout << endl << "Are you sure you want to sell \"\033[1m\033[1;31m" << hero.GetSpellFromSlot(row - 1, 3)->GetName() << "\033[0m\" Fire Spell? [y/n]: ";

                do {
                    cin >> confirmation;
                } while(confirmation != 'y' && confirmation != 'Y' && confirmation != 'n' && confirmation != 'N');

                if (confirmation == 'n' || confirmation == 'N')
                    break;

                hero.RemoveFireSpell(row - 1);
            }

            break;

        case 3:
            if (sellState == 1) {
                cout << endl << "Are you sure you want to sell \"\033[1m\033[38;5;90m" << hero.GetPotionFromSlot(row - 1)->GetName() << "\033[0m\" Potion? [y/n]: ";

                do {
                    cin >> confirmation;
                } while(confirmation != 'y' && confirmation != 'Y' && confirmation != 'n' && confirmation != 'N');

                if (confirmation == 'n' || confirmation == 'N')
                    break;

                hero.RemovePotion(row - 1);
            
            } else {
                cout << endl << "Are you sure you want to sell \"\033[1m\033[38;5;15m" << hero.GetSpellFromSlot(row - 1, 1)->GetName() << "\033[0m\" Lighting Spell? [y/n]: ";

                do {
                    cin >> confirmation;
                } while(confirmation != 'y' && confirmation != 'Y' && confirmation != 'n' && confirmation != 'N');

                if (confirmation == 'n' || confirmation == 'N')
                    break;

                hero.RemoveLightingSpell(row - 1);
            }

            break;

        case 4:
            cout << endl << "Are you sure you want to sell \"\033[1m\033[38;5;166m" << hero.GetWeaponFromSlot(row - 1)->GetName() << "\033[0m\" Weapon? [y/n]: ";

            do {
                cin >> confirmation;
            } while(confirmation != 'y' && confirmation != 'Y' && confirmation != 'n' && confirmation != 'N');

            if (confirmation == 'n' || confirmation == 'N')
                break;

            hero.RemoveWeapon(row - 1);

            break;

        case 5:
            cout << endl << "Are you sure you want to sell \"\033[1m\033[38;5;28m" << hero.GetArmorFromSlot(row - 1)->GetName() << "\033[0m\" Armor? [y/n]: ";

            do {
                cin >> confirmation;
            } while(confirmation != 'y' && confirmation != 'Y' && confirmation != 'n' && confirmation != 'N');

            if (confirmation == 'n' || confirmation == 'N')
                break;

            hero.RemoveArmor(row - 1);

            break;

        case 6:
            cout << endl << "Are you sure you want to sell \"\033[1m\033[38;5;90m" << hero.GetPotionFromSlot(row - 1)->GetName() << "\033[0m\" Potion? [y/n]: ";

            do {
                cin >> confirmation;
            } while(confirmation != 'y' && confirmation != 'Y' && confirmation != 'n' && confirmation != 'N');

            if (confirmation == 'n' || confirmation == 'N')
                break;

            hero.RemovePotion(row - 1);

            break;
    }
}

void Market::Sell(vector<Hero *>& heroes)
{
    unsigned int i;

    int action;
    string testAction;
    bool infoState     = false;
    Hero* selectedHero = NULL;

    if (heroes.size() == 1 && isAbleToSell(heroes[0]) == -1) {
        usleep(2500000);
        DisplayMarket();
        return;
    
    } else {
        for (i = 0; i < heroes.size() && isAbleToSell(heroes[i],false) == -1; i++)
            ;

        if (i == heroes.size()) {
            cerr << endl << "\033[31mError:\033[0m No one of the heroes have any Items or Spells for sale.";
            usleep(2500000);
            DisplayMarket();
            return;
        }
    }

    while(true) {
        int sellState;

        if (heroes.size() == 1) {
            selectedHero = heroes[0];
        
        } else {
            for (i = 0; i < heroes.size() && isAbleToSell(heroes[i],false) == -1; i++)
                ;

            if (i == heroes.size()) {
                cerr << endl << "-------------------------------" << endl << endl;
                cerr << "\033[35mWarning:\033[0m No one of the heroes have any Items or Spells left for sale.";
                usleep(2500000);
                DisplayMarket();
                return;
            }

            while(selectedHero == NULL) {
                //bool errorFlag = false;
                cout << endl;
                cout << "-------------------------------" << endl << endl;
                cout << "(Type 0 to cancel)" << endl;
                cout << "Choose a Hero (1 - " << heroes.size() << "): ";

                cout << "\n\n\n\n\n";
                cout << "\033[5A\033[23C";

                while(true) {
                    bool errFlag = false;

                    cout << "\033[s";

                    do {
                        if (errFlag)
                            usleep(1800000);

                        cout << "\033[u";
                        cout << "\033[J";
                        cout << "\033[s";

                        cin >> testAction;

                        errFlag = true;
                    } while(!isNumeric(testAction.c_str(),action));

                    if (action < 0 || action > heroes.size()) {
                        cerr << endl << "\033[31mError:\033[0m Please choose a number in the given range." << endl;


                        usleep(1800000);

                        cout << "\033[u";
                        cout << "\033[J";

                        //cout << "\033[K";
                        //cout << "\033[1A\033[K";
                        //cout << "\033[1A\033[K";

                        //if (errorFlag)
                        //    cout << "\033[1A\033[K";

                        //errorFlag = true;
                    
                    } else {
                        if (!action) {
                            DisplayMarket();
                            return;
                        }
                        selectedHero = heroes[action - 1];
                        break;
                    }
                }
            }
        }

        if ((sellState = isAbleToSell(selectedHero)) != -1) {
            bool errFlag = false;

            selectedHero->DisplayProdsForSale(infoState,sellState);

            cout << endl;
            /*if (sellState == 0 || sellState == 1)
            {
                cout << "\033[44C-------------------------------" << endl << endl;
                cout << "\033[44CChoose an action: ";
            
            } else {*/
                cout << "-------------------------------" << endl << endl;
                cout << "Choose an action: ";
            //}

            cout << "\n\n\n\n\n";
            cout << "\033[5A\033[18C";

            cout << "\033[s";

            do {
                if (errFlag)
                    usleep(1800000);

                cout << "\033[u";
                cout << "\033[J";
                cout << "\033[s";

                cin >> testAction;

                errFlag = true;
            } while(!isValid(testAction.c_str(),action,1,3));

            switch(action)
            {
                case 1:
                    Sale(*selectedHero,sellState);
                    break;
                case 2:
                    infoState = !infoState;
                    //selectedHero->DisplayProdsForSale(infoState,sellState);
                    break;
                case 3:
                    DisplayMarket();
                    return;
            }
        
        } else if (heroes.size() == 1) {
            usleep(2500000);
            DisplayMarket();
            return;
        }

        if (sellState == -1) {
            DisplayMarket();
            return;
        }
    }
}

bool Market::EnterMarket(vector<Hero *>& heroes)
{
    int action;
    //int buyState;
    string testAction;
    bool infoState = false;

    NewStuff(heroes);

    DisplayMarket();

    while(true){

        bool errFlag = false;

        cout << endl;
        cout << "-------------------------------" << endl << endl;
        cout << "Choose an action: ";

        cout << "\n\n\n\n\n";
        cout << "\033[5A\033[18C";

        cout << "\033[s";

        do {
            if (errFlag)
                usleep(1800000);

            cout << "\033[u";
            cout << "\033[J";
            cout << "\033[s";

            cin >> testAction;

            errFlag = true;
        } while(!isValid(testAction.c_str(),action,1,4));

        switch(action)
        {
            case 1:
                Buy(heroes);
                break;
            case 2:
                Sell(heroes);
                break;
            case 3:
                infoState = !infoState;
                DisplayMarket(infoState);
                break;
            case 4:
                return false;
        }
    }
}

bool Market::canBeBought(const Item* item, const Hero* hero)
{
    if (hero->GetMoney() < item->GetPrice())
        return false;

    if (hero->Living::GetLevel() < item->GetMinReqLevel())
        return false;

    return true;
}

bool Market::canBeBought(const Spell* spell, const Hero* hero)
{
    if (hero->GetMoney() < spell->GetPrice())
        return false;

    if (hero->Living::GetLevel() < spell->GetMinReqLevel())
        return false;

    return true;
}

void Market::DisplayMarket(const bool& showInfo, const Hero* hero, const int buyState)
{
    cout << "\033[2J\033[1;1H";
    cout << "\033[1;33m+\033[0;34m=========================================================================================================================================================================================\033[1;33m+\033[0m" << endl;
    cout << "\033[34m|\033[0m                                                                                  Welcome to the Market                                                                                  \033[34m|\033[0m" << endl;
    cout << "\033[1;33m+\033[0;34m=========================================================================================================================================================================================\033[1;33m+\033[0m" << endl;
    
    if (buyState != -1) {
        if (showInfo)
            cout << "\033[34m|\033[0m                                                               \033[4mAvailable Actions\033[0m: 1. Purchase, 2. Disable Info, 3. Cancel                                                                \033[34m|\033[0m" << endl;
        else
            cout << "\033[34m|\033[0m                                                                   \033[4mAvailable Actions\033[0m: 1. Purchase, 2. Info, 3. Cancel                                                                    \033[34m|\033[0m" << endl;
    
    } else {
        if (showInfo)
            cout << "\033[34m|\033[0m                                                              \033[4mAvailable Actions\033[0m: 1. Buy, 2. Sell, 3. Disable Info, 4. Exit                                                               \033[34m|\033[0m" << endl;
        else
            cout << "\033[34m|\033[0m                                                                  \033[4mAvailable Actions\033[0m: 1. Buy, 2. Sell, 3. Info, 4. Exit                                                                   \033[34m|\033[0m" << endl;
    }

    cout << "\033[1;33m+\033[0;34m=========================================================================================================================================================================================\033[1;33m+\033[0m" << endl;
    cout << "\033[34m|\033[0m                                           Spells                                           \033[34m|\033[0m                                           Items                                            \033[34m|\033[0m" << endl;

    if (showInfo) {
        cout << "\033[34m|--------------------------------------------------------------------------------------------\033[1;33m+\033[0;34m--------------------------------------------------------------------------------------------|\033[0m" << endl;
        cout << "\033[34m|\033[0m    --> Spells are representing a magic attack that a hero can perform                      \033[34m|\033[0m    --> There are items that a hero can use for attacking enemies, avoiding their attacks   \033[34m|\033[0m" << endl;
        cout << "\033[34m|\033[0m    --> They cause an amount of damage according to the hero's dexterity                    \033[34m|\033[0m        and items that increase some of his features                                        \033[34m|\033[0m" << endl;
        cout << "\033[34m|\033[0m    --> They require a specific Magic Power that the hero must have in order to use them    \033[34m|\033[0m    --> Some of them can be used one time only                                              \033[34m|\033[0m" << endl;
        cout << "\033[34m|\033[0m    --> After the use of a spell the Hero's Magic Power will be reduced                     \033[34m|\033[0m                                                                                            \033[34m|\033[0m" << endl;
    }

    cout << "\033[1;33m+\033[0;34m===\033[1;33m+\033[0;34m==========================\033[1;33m+\033[0;34m===\033[1;33m+\033[0;34m==========================\033[1;33m+\033[0;34m===\033[1;33m+\033[0;34m==========================\033[1;33m+\033[0;34m===\033[1;33m+\033[0;34m==========================\033[1;33m+\033[0;34m===\033[1;33m+\033[0;34m==========================\033[1;33m+\033[0;34m===\033[1;33m+\033[0;34m==========================\033[1;33m+\033[0m" << endl;
    cout << "\033[34m|\033[0m # \033[34m|\033[0m        \033[38;5;32mIce Spells\033[0m        \033[34m|\033[0m # \033[34m|\033[0m       \033[1;31mFire Spells\033[0m        \033[34m|\033[0m # \033[34m|\033[0m     \033[38;5;15mLighting Spells\033[0m      \033[34m|\033[0m # \033[34m|\033[0m         \033[38;5;166mWeapons\033[0m          \033[34m|\033[0m # \033[34m|\033[0m          \033[38;5;28mArmors\033[0m          \033[34m|\033[0m # \033[34m|\033[0m         \033[38;5;90mPotions\033[0m          \033[34m|\033[0m" << endl;

    if (showInfo) {
        cout << "\033[1;33m+\033[0;34m---\033[1;33m+\033[0;34m--------------------------\033[1;33m+\033[0;34m---\033[1;33m+\033[0;34m--------------------------\033[1;33m+\033[0;34m---\033[1;33m+\033[0;34m--------------------------\033[1;33m+\033[0;34m---\033[1;33m+\033[0;34m--------------------------\033[1;33m+\033[0;34m---\033[1;33m+\033[0;34m--------------------------\033[1;33m+\033[0;34m---\033[1;33m+\033[0;34m--------------------------|\033[0m" << endl;
        cout << "\033[34m|\033[1;33m(i)\033[0;34m|\033[0m    Ice Spells reduce     \033[34m|\033[1;33m(i)\033[0;34m|\033[0m    Fire Spells reduce    \033[34m|\033[1;33m(i)\033[0;34m|\033[0m  Lighting Spells reduce  \033[34m|\033[1;33m(i)\033[0;34m|\033[0m   Weapons cause damage   \033[34m|\033[1;33m(i)\033[0;34m|\033[0m    Armors reduce the     \033[34m|\033[1;33m(i)\033[0;34m|\033[0m     Potions increase     \033[34m|\033[0m" << endl;
        cout << "\033[34m|\033[1;33m(i)\033[0;34m|\033[0m   enemy's damage range   \033[34m|\033[1;33m(i)\033[0;34m|\033[0m     enemy's defence      \033[34m|\033[1;33m(i)\033[0;34m|\033[0m    enemy's chance to     \033[34m|\033[1;33m(i)\033[0;34m|\033[0m    to the enemies and    \033[34m|\033[1;33m(i)\033[0;34m|\033[0m     received damage      \033[34m|\033[1;33m(i)\033[0;34m|\033[0m    a hero's specific     \033[34m|\033[0m" << endl;
        cout << "\033[34m|   |                          |   |                          |\033[1;33m(i)\033[0;34m|\033[0m     avoid an attack      \033[34m|\033[1;33m(i)\033[0;34m|\033[0m     they require one     \033[34m|   |                          |\033[1;33m(i)\033[0;34m|\033[0m     feature and can      \033[34m|\033[0m" << endl;
        cout << "\033[34m|   |                          |   |                          |   |                          |\033[1;33m(i)\033[0;34m|\033[0m       or two hands       \033[34m|   |                          |\033[1;33m(i)\033[0;34m|\033[0m    be used only once     \033[34m|\033[0m" << endl;
    }
    cout << "\033[1;33m+\033[0;34m===\033[1;33m+\033[0;34m==========================\033[1;33m+\033[0;34m===\033[1;33m+\033[0;34m==========================\033[1;33m+\033[0;34m===\033[1;33m+\033[0;34m==========================\033[1;33m+\033[0;34m===\033[1;33m+\033[0;34m==========================\033[1;33m+\033[0;34m===\033[1;33m+\033[0;34m==========================\033[1;33m+\033[0;34m===\033[1;33m+\033[0;34m==========================\033[1;33m+\033[0m" << endl;

    if (buyState != -1)
        ResetForSaleProds();

    for (unsigned int i = 0, ice_i = 0, fire_i = 0, light_i = 0, wpn_i = 0, arm_i = 0, ptn_i = 0; 
                      i < mostItems; 
                      i++, ice_i++, fire_i++, light_i++, wpn_i++, arm_i++, ptn_i++)
    {
        short terminationState = 0;

        if (buyState != -1) {
            while(ice_i < iceSpellsArray.size() && !canBeBought(iceSpellsArray[ice_i],hero))
                ice_i++;
        }

        if (ice_i < iceSpellsArray.size()) {
            if      (i < 9)    cout << "\033[34m|\033[0m " << i+1 << " ";
            else if (i < 99)   cout << "\033[34m|\033[0m " << i+1;
            else if (i < 999)  cout << "\033[34m|\033[0m"  << i+1;

            iceSpellsIndexes.insert(iceSpellsIndexes.begin() + i , ice_i);

            cout << "\033[34m| \033[0m\u2022 ";

            if (showInfo)
                cout << "\033[1;33m";

            if (buyState == 1 || buyState == 3)
                cout << "\033[1;31m";

            cout.width(23);
            iceSpellsForSale++;
            cout << left << iceSpellsArray[ice_i]->GetName() << "\033[0m";
        
        } else {
            if (terminationState == 0)
                terminationState++;

            cout << "\033[34m|   |\033[0m\033[26C";
        }

        if (buyState != -1) {
            while(fire_i < fireSpellsArray.size() && !canBeBought(fireSpellsArray[fire_i],hero))
                fire_i++;
        }

        if (fire_i < fireSpellsArray.size()) {
            if      (i < 9)    cout << "\033[34m|\033[0m " << i+1 << " ";
            else if (i < 99)   cout << "\033[34m|\033[0m " << i+1;
            else if (i < 999)  cout << "\033[34m|\033[0m"  << i+1;

            fireSpellsIndexes.insert(fireSpellsIndexes.begin() + i , fire_i);

            cout << "\033[34m| \033[0m\u2022 ";

            if (showInfo)
                cout << "\033[1;33m";

            if (buyState == 1 || buyState == 3)
                cout << "\033[1;31m";

            cout.width(23);
            fireSpellsForSale++;
            cout << left << fireSpellsArray[fire_i]->GetName() << "\033[0m";
        
        } else {
            if (terminationState == 1)
                terminationState++;

            cout << "\033[34m|   |\033[0m\033[26C";
        }

        if (buyState != -1) {
            while(light_i < lightingSpellsArray.size() && !canBeBought(lightingSpellsArray[light_i],hero))
                light_i++;
        }

        if (light_i < lightingSpellsArray.size()) {
            if      (i < 9)    cout << "\033[34m|\033[0m " << i+1 << " ";
            else if (i < 99)   cout << "\033[34m|\033[0m " << i+1;
            else if (i < 999)  cout << "\033[34m|\033[0m"  << i+1;

            lightingSpellsIndexes.insert(lightingSpellsIndexes.begin() + i , light_i);

            cout << "\033[34m| \033[0m\u2022 ";

            if (showInfo)
                cout << "\033[1;33m";

            if (buyState == 1 || buyState == 3)
                cout << "\033[1;31m";

            cout.width(23);
            lightingSpellsForSale++;
            cout << left << lightingSpellsArray[light_i]->GetName() << "\033[0m";
        
        } else {
            if (terminationState == 2)
                terminationState++;

            cout << "\033[34m|   |\033[0m\033[26C";
        }

        if (buyState != -1) {
            while(wpn_i < weaponsArray.size() && !canBeBought(weaponsArray[wpn_i],hero))
                wpn_i++;
        }

        if (wpn_i < weaponsArray.size()) {
            if      (i < 9)    cout << "\033[34m|\033[0m " << i+1 << " ";
            else if (i < 99)   cout << "\033[34m|\033[0m " << i+1;
            else if (i < 999)  cout << "\033[34m|\033[0m"  << i+1;

            weaponsIndexes.insert(weaponsIndexes.begin() + i , wpn_i);

            cout << "\033[34m| \033[0m\u2022 ";

            if (showInfo)
                cout << "\033[1;33m";

            if (buyState == 0 || buyState == 3)
                cout << "\033[1;31m";

            cout.width(23);
            weaponsForSale++;
            cout << left << weaponsArray[wpn_i]->GetName() << "\033[0m";
        
        } else {
            if (terminationState == 3)
                terminationState++;

            cout << "\033[34m|   |\033[0m\033[26C"; // \033[23C
        }

        if (buyState != -1) {
            while(arm_i < armorsArray.size() && !canBeBought(armorsArray[arm_i],hero))
                arm_i++;
        }

        if (arm_i < armorsArray.size()) {
            if      (i < 9)    cout << "\033[34m|\033[0m " << i+1 << " ";
            else if (i < 99)   cout << "\033[34m|\033[0m " << i+1;
            else if (i < 999)  cout << "\033[34m|\033[0m"  << i+1;

            armorsIndexes.insert(armorsIndexes.begin() + i , arm_i);

            cout << "\033[34m| \033[0m\u2022 ";

            if (showInfo)
                cout << "\033[1;33m";

            if (buyState == 0 || buyState == 3)
                cout << "\033[1;31m";

            cout.width(23);
            armorsForSale++;
            cout << left << armorsArray[arm_i]->GetName() << "\033[0m";
        
        } else {
            if (terminationState == 4)
                terminationState++;

            cout << "\033[34m|   |\033[0m\033[26C"; //\033[22C
        }

        if (buyState != -1) {
            while(ptn_i < potionsArray.size() && !canBeBought(potionsArray[ptn_i],hero))
                ptn_i++;
        }

        if (ptn_i < potionsArray.size()) {
            if      (i < 9)    cout << "\033[34m|\033[0m " << i+1 << " ";
            else if (i < 99)   cout << "\033[34m|\033[0m " << i+1;
            else if (i < 999)  cout << "\033[34m|\033[0m"  << i+1;

            potionsIndexes.insert(potionsIndexes.begin() + i , ptn_i);

            cout << "\033[34m| \033[0m\u2022 ";

            if (showInfo)
                cout << "\033[1;33m";

            if (buyState == 0 || buyState == 3)
                cout << "\033[1;31m";

            cout.width(23);
            potionsForSale++;
            cout << left << potionsArray[ptn_i]->GetName() << "\033[0;34m|\033[0m" << endl;
        
        } else {
            if (terminationState == 5)
                terminationState++;

            cout << "\033[34m|   |\033[26C|\033[0m" << endl; //\033[21C
        }

        if (terminationState == 6) {
            cout << "\033[1A";
            break;
        }
/*
        if (ice_i >= iceSpellsArray.size() && fire_i >= fireSpellsArray.size() && light_i >= lightingSpellsArray.size() &&
           wpn_i >= weaponsArray.size() && arm_i >= armorsArray.size() && ptn_i >= potionsArray.size())
        {
            if (showInfo)
                cout << "\033[2A";
            else
                cout << "\033[1A";
            cout << "\033[1;33m+\033[0;34m===\033[1;33m+\033[0;34m==========================\033[1;33m+\033[0;34m===\033[1;33m+\033[0;34m==========================\033[1;33m+\033[0;34m===\033[1;33m+\033[0;34m==========================\033[1;33m+\033[0;34m===\033[1;33m+\033[0;34m==========================\033[1;33m+\033[0;34m===\033[1;33m+\033[0;34m==========================\033[1;33m+\033[0;34m===\033[1;33m+\033[0;34m==========================\033[1;33m+\033[0m" << endl;

            if (showInfo)
            {
                cout << "                                                                                                                                                                                           " << endl;
                cout << "\033[1A";
            }

            if (buyState != -1)
            {
                cout << endl << "\033[38;5;220m Hero: \033[0m" << hero->GetName() << endl;
                cout << "\033[38;5;220mLevel: \033[0m" << hero->GetLevel() << endl;
                cout << "\033[38;5;220mMoney: \033[0m" << hero->GetMoney() << endl;
            }


            cout << endl << "\t\t\t\t MOST ITEMS 1 = " << mostItems << endl;

            return;
        }*/

        if (showInfo) {
    /* ------------------------------- Start of 1st Line ------------------------------- */
            if (ice_i < iceSpellsArray.size()) {
                cout << "\033[34m|\033[1;33m(i)\033[0;34m|\033[0m ~> Price: ";
                cout.width(15);
                cout << left << iceSpellsArray[ice_i]->GetPrice();
            
            } else
                cout << "\033[34m|   |\033[0m\033[26C";

            if (fire_i < fireSpellsArray.size()) {
                cout << "\033[34m|\033[1;33m(i)\033[0;34m|\033[0m ~> Price: ";
                cout.width(15);
                cout << left << fireSpellsArray[fire_i]->GetPrice();
            
            } else
                cout << "\033[34m|   |\033[0m\033[26C";

            if (light_i < lightingSpellsArray.size()) {
                cout << "\033[34m|\033[1;33m(i)\033[0;34m|\033[0m ~> Price: ";
                cout.width(15);
                cout << left << lightingSpellsArray[light_i]->GetPrice();
            
            } else
                cout << "\033[34m|   |\033[0m\033[26C";

            if (wpn_i < weaponsArray.size()) {
                cout << "\033[34m|\033[1;33m(i)\033[0;34m|\033[0m ~> Price: ";
                cout.width(15);
                cout << left << weaponsArray[wpn_i]->GetPrice();
            
            } else
                cout << "\033[34m|   |\033[0m\033[26C";

            if (arm_i < armorsArray.size()) {
                cout << "\033[34m|\033[1;33m(i)\033[0;34m|\033[0m ~> Price: ";
                cout.width(15);
                cout << left << armorsArray[arm_i]->GetPrice();
            
            } else
                cout << "\033[34m|   |\033[0m\033[26C";

            if (ptn_i < potionsArray.size()) {
                cout << "\033[34m|\033[1;33m(i)\033[0;34m|\033[0m ~> Price: ";
                cout.width(15);
                cout << left << potionsArray[ptn_i]->GetPrice() << "\033[34m|\033[0m" << endl;
            
            } else
                cout << "\033[34m|   |\033[26C|\033[0m" << endl;

    /* -------------------------------- End of 1st Line -------------------------------- */

    /* ------------------------------- Start of 2nd Line ------------------------------- */

            if (ice_i < iceSpellsArray.size()) {
                cout << "\033[34m|\033[1;33m(i)\033[0;34m|\033[0m ~> Required Level: ";
                cout.width(6);
                cout << left << iceSpellsArray[ice_i]->GetMinReqLevel();
            
            } else
                cout << "\033[34m|   |\033[0m\033[26C";

            if (fire_i < fireSpellsArray.size()) {
                cout << "\033[34m|\033[1;33m(i)\033[0;34m|\033[0m ~> Required Level: ";
                cout.width(6);
                cout << left << fireSpellsArray[fire_i]->GetMinReqLevel();
            
            } else
                cout << "\033[34m|   |\033[0m\033[26C";

            if (light_i < lightingSpellsArray.size()) {
                cout << "\033[34m|\033[1;33m(i)\033[0;34m|\033[0m ~> Required Level: ";
                cout.width(6);
                cout << left << lightingSpellsArray[light_i]->GetMinReqLevel();
            
            } else
                cout << "\033[34m|   |\033[0m\033[26C";

            if (wpn_i < weaponsArray.size()) {
                cout << "\033[34m|\033[1;33m(i)\033[0;34m|\033[0m ~> Required Level: ";
                cout.width(6);
                cout << left << weaponsArray[wpn_i]->GetMinReqLevel();
            
            } else
                cout << "\033[34m|   |\033[0m\033[26C";

            if (arm_i < armorsArray.size()) {
                cout << "\033[34m|\033[1;33m(i)\033[0;34m|\033[0m ~> Required Level: ";
                cout.width(6);
                cout << left << armorsArray[arm_i]->GetMinReqLevel();
            
            } else
                cout << "\033[34m|   |\033[0m\033[26C";

            if (ptn_i < potionsArray.size()) {
                cout << "\033[34m|\033[1;33m(i)\033[0;34m|\033[0m ~> Required Level: ";
                cout.width(6);
                cout << left << potionsArray[ptn_i]->GetMinReqLevel() << "\033[34m|\033[0m" << endl;
            
            } else
                cout << "\033[34m|   |\033[26C|\033[0m" << endl;

    /* -------------------------------- End of 2nd Line -------------------------------- */

    /* ------------------------------- Start of 3rd Line ------------------------------- */

            if (ice_i < iceSpellsArray.size()) {
                cout << "\033[34m|\033[1;33m(i)\033[0;34m|\033[0m ~> Required MP: ";
                cout.width(9);
                cout << left << iceSpellsArray[ice_i]->GetReqEnergy();
            
            } else
                cout << "\033[34m|   |\033[0m\033[26C";

            if (fire_i < fireSpellsArray.size()) {
                cout << "\033[34m|\033[1;33m(i)\033[0;34m|\033[0m ~> Required MP: ";
                cout.width(9);
                cout << left << fireSpellsArray[fire_i]->GetReqEnergy();
            
            } else
                cout << "\033[34m|   |\033[0m\033[26C";

            if (light_i < lightingSpellsArray.size()) {
                cout << "\033[34m|\033[1;33m(i)\033[0;34m|\033[0m ~> Required MP: ";
                cout.width(9);
                cout << left << lightingSpellsArray[light_i]->GetReqEnergy();
            
            } else
                cout << "\033[34m|   |\033[0m\033[26C";

            if (wpn_i < weaponsArray.size()) {
                cout << "\033[34m|\033[1;33m(i)\033[0;34m|\033[0m ~> Damage: ";
                cout.width(14);
                cout << left << weaponsArray[wpn_i]->GetDamage();
            
            } else
                cout << "\033[34m|   |\033[0m\033[26C";

            if (arm_i < armorsArray.size()) {
                cout << "\033[34m|\033[1;33m(i)\033[0;34m|\033[0m ~> Damage Reduction: ";
                cout.width(4);
                cout << left << armorsArray[arm_i]->GetDamageReduction();
            
            } else
                cout << "\033[34m|   |\033[0m\033[26C";

            if (ptn_i < potionsArray.size()) {
                cout << "\033[34m|\033[1;33m(i)\033[0;34m|\033[0m ~> Power-Up: ";

                cout.width(12);
                if (potionsArray[ptn_i]->PotionIncreaseStrength()) {
                    string str = "+" + to_string(potionsArray[ptn_i]->PotionIncreaseStrength()) + " str/th";
                    cout << str << "\033[34m|\033[0m" << endl;
                
                } else if (potionsArray[ptn_i]->PotionIncreaseDexterity()) {
                    string str = "+" + to_string(potionsArray[ptn_i]->PotionIncreaseDexterity()) + " dext/ty";
                    cout << str << "\033[34m|\033[0m" << endl;
                
                } else {
                    string str = "+" + to_string((int)(potionsArray[ptn_i]->PotionIncreaseAgility() * 100)) + "\% agility";
                    cout << str << "\033[34m|\033[0m" << endl;
                }
            
            } else
                cout << "\033[34m|   |\033[26C|\033[0m" << endl;

    /* -------------------------------- End of 3rd Line -------------------------------- */

    /* ------------------------------- Start of 4th Line ------------------------------- */

            if (ice_i < iceSpellsArray.size()) {
                string str = to_string(iceSpellsArray[ice_i]->GetMinDamage()) + "-" + to_string(iceSpellsArray[ice_i]->GetMaxDamage());
                cout << "\033[34m|\033[1;33m(i)\033[0;34m|\033[0m ~> Damage Range: ";
                cout.width(8);
                cout << left << str;
            
            } else
                cout << "\033[34m|   |\033[0m\033[26C";

            if (fire_i < fireSpellsArray.size()) {
                string str = to_string(fireSpellsArray[fire_i]->GetMinDamage()) + "-" + to_string(fireSpellsArray[fire_i]->GetMaxDamage());
                cout << "\033[34m|\033[1;33m(i)\033[0;34m|\033[0m ~> Damage Range: ";
                cout.width(8);
                cout << left << str;
            
            } else
                cout << "\033[34m|   |\033[0m\033[26C";

            if (light_i < lightingSpellsArray.size()) {
                string str = to_string(lightingSpellsArray[light_i]->GetMinDamage()) + "-" + to_string(lightingSpellsArray[light_i]->GetMaxDamage());
                cout << "\033[34m|\033[1;33m(i)\033[0;34m|\033[0m ~> Damage Range: ";
                cout.width(8);
                cout << left << str;
            
            } else
                cout << "\033[34m|   |\033[0m\033[26C";

            if (wpn_i < weaponsArray.size()) {
                cout << "\033[34m|\033[1;33m(i)\033[0;34m|\033[0m ~> Required Hands: ";
                cout.width(6);
                if (weaponsArray[wpn_i]->TwoHanded())
                    cout << left << "2";
                else
                    cout << left << "1";
            
            } else
                cout << "\033[34m|   |\033[0m\033[26C";

            cout << "\033[34m|   |\033[26C";
            cout << "|   |\033[26C|\033[0m" << endl;

    /* -------------------------------- End of 4th Line -------------------------------- */

    /* ------------------------------- Start of 5th Line ------------------------------- */

            if (ice_i < iceSpellsArray.size()) {
                cout << "\033[34m|\033[1;33m(i)\033[0;34m|\033[0m ~> Enemy Damage . ";
                cout.width(7);
                cout << left << (to_string(iceSpellsArray[ice_i]->GetDamageReduction()) + " HP");
            
            } else
                cout << "\033[34m|   |\033[0m\033[26C";

            if (fire_i < fireSpellsArray.size()) {
                cout << "\033[34m|\033[1;33m(i)\033[0;34m|\033[0m ~> Enemy Defence . ";
                cout.width(6);
                cout << left << fireSpellsArray[fire_i]->GetDefenceReduction();
            
            } else
                cout << "\033[34m|   |\033[0m\033[26C";

            if (light_i < lightingSpellsArray.size()) {
                cout << "\033[34m|\033[1;33m(i)\033[0;34m|\033[0m ~> Enemy Avoidance . ";
                cout.width(4);
                cout << left << (to_string(lightingSpellsArray[light_i]->GetAvoidanceReduction()) + "%");
            
            } else
                cout << "\033[34m|   |\033[0m\033[26C";

            cout << "\033[34m|   |\033[26C";
            cout << "|   |\033[26C";
            cout << "|   |\033[26C|\033[0m" << endl;

    /* -------------------------------- End of 5th Line -------------------------------- */

    /* ------------------------------- Start of 6th Line ------------------------------- */

            if (ice_i < iceSpellsArray.size())
                cout << "\033[34m|\033[1;33m(i)\033[0;34m|\033[0m    Reduction    ·        ";
            else
                cout << "\033[34m|   |\033[0m\033[26C";

            if (fire_i < fireSpellsArray.size())
                cout << "\033[34m|\033[1;33m(i)\033[0;34m|\033[0m    Reduction     ·       ";
            else
                cout << "\033[34m|   |\033[0m\033[26C";

            if (light_i < lightingSpellsArray.size())
                cout << "\033[34m|\033[1;33m(i)\033[0;34m|\033[0m    Reduction       ·     ";
            else
                cout << "\033[34m|   |\033[0m\033[26C";

            cout << "\033[34m|   |\033[26C";
            cout << "|   |\033[26C";
            cout << "|   |\033[26C|\033[0m" << endl;

    /* -------------------------------- End of 6th Line -------------------------------- */

    /* ------------------------------- Start of 7th Line ------------------------------- */

            if (ice_i < iceSpellsArray.size()) {
                cout << "\033[34m|\033[1;33m(i)\033[0;34m|\033[0m ~> Applies to: ";

                cout.width(10);
                if (iceSpellsArray[ice_i]->GetRounds() == 1)
                    cout << left << (to_string(iceSpellsArray[ice_i]->GetRounds()) + " round");
                else
                    cout << left << (to_string(iceSpellsArray[ice_i]->GetRounds()) + " rounds");
            
            } else
                cout << "\033[34m|   |\033[0m\033[26C";

            if (fire_i < fireSpellsArray.size()) {
                cout << "\033[34m|\033[1;33m(i)\033[0;34m|\033[0m ~> Applies to: ";

                cout.width(10);
                if (fireSpellsArray[fire_i]->GetRounds() == 1)
                    cout << left << (to_string(fireSpellsArray[fire_i]->GetRounds()) + " round");
                else
                    cout << left << (to_string(fireSpellsArray[fire_i]->GetRounds()) + " rounds");
            
            } else
                cout << "\033[34m|   |\033[0m\033[26C";

            if (light_i < lightingSpellsArray.size()) {
                cout << "\033[34m|\033[1;33m(i)\033[0;34m|\033[0m ~> Applies to: ";

                cout.width(10);
                if (lightingSpellsArray[light_i]->GetRounds() == 1)
                    cout << left << (to_string(lightingSpellsArray[light_i]->GetRounds()) + " round");
                else
                    cout << left << (to_string(lightingSpellsArray[light_i]->GetRounds()) + " rounds");
            
            } else
                cout << "\033[34m|   |\033[0m\033[26C";

            cout << "\033[34m|   |\033[26C";
            cout << "|   |\033[26C";
            cout << "|   |\033[26C|\033[0m" << endl;

    /* -------------------------------- End of 7th Line -------------------------------- */

            cout << "\033[34m|   |\033[26C|   |\033[26C|   |\033[26C|   |\033[26C|   |\033[26C|   |\033[26C|\033[0m" << endl;
        }

        if (hero == NULL)
            usleep(40000);
    }

    if (showInfo)
        cout << "\033[K\033[1A\033[K";

    cout << "\033[1;33m+\033[0;34m===\033[1;33m+\033[0;34m==========================\033[1;33m+\033[0;34m===\033[1;33m+\033[0;34m==========================\033[1;33m+\033[0;34m===\033[1;33m+\033[0;34m==========================\033[1;33m+\033[0;34m===\033[1;33m+\033[0;34m==========================\033[1;33m+\033[0;34m===\033[1;33m+\033[0;34m==========================\033[1;33m+\033[0;34m===\033[1;33m+\033[0;34m==========================\033[1;33m+\033[0m" << endl;

    if (hero != NULL) {
        cout << endl;
        cout << "\033[38;5;220m  Hero: \033[0m"  << hero->GetName()  << endl;
        cout << "\033[38;5;220m Level: \033[0m"  << hero->GetLevel() << endl;
        cout << "\033[38;5;220m Money: \033[0m"  << hero->GetMoney() << endl;
        cout << "\033[38;5;220m Items: \033[0m(" << hero->GetMaxItemsSlots()  - hero->GetAvailableItemSlots()  << "/" << hero->GetMaxItemsSlots()  << ")" << endl;
        cout << "\033[38;5;220mSpells: \033[0m(" << hero->GetMaxSpellsSlots() - hero->GetAvailableSpellSlots() << "/" << hero->GetMaxSpellsSlots() << ")" << endl;
    }
}
