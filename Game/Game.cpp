/* File: Game.cpp */

#include <vector>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <limits>
#include <unistd.h>

#include "../Input_Validation/Input_Validation.hpp"
#include "../Keyboard/Keyboard.hpp"

#include "../Living/Monsters/Monster.hpp"
#include "../Living/Heroes/Hero.hpp"
#include "../Battle/Battle.hpp"
#include "../Market/Market.hpp"
#include "../Grid/Grid.hpp"
#include "Game.hpp"

using namespace std;

Game::Game(std::vector<Hero *>& allHeroes , Grid& givenGrid , Market& givenStore)
           : grid(givenGrid), market(givenStore), heroes(allHeroes)
{}

Game::~Game()
{}

char Game::GetInput()  //takes an input and it checks if it is acceptable
{
    char input;

    do{
        input = getch();
    }while(input != 'i' && input != 'q' && input != 'a' && input != 'w' && input != 's' && input != 'd');

    return input;
}

void Game::Play(void)
{
    bool gameover = false;

    while(gameover == false)
    {
        grid.DisplayGrid(heroes);

        char input = GetInput();

        if(input == 'i') //enters inventory
        {
            int herochoice = 1;
            int arrow = 0;

            cout << "Press 'e' to exit the inventory" << endl;

            if(heroes.size() != 1)
                cout << "Switch between heroes using numbers in range [1-" << heroes.size() << "]: ";

            cout << endl;

            while(true)
            {
                //char testAction;


                //if(heroes.size() == 1)
                //    herochoice = 1;
                //else
                //{
                    //do{
                        //testAction = getch();
                        /*if(testAction == 'e')
                            break;
                    }while(!isValid(&testAction,herochoice,1,heroes.size(),false));//checks if the hero chosen exists*/
                //}

                /*if(testAction == 'e')
                    break;
                else
                {*/
                    bool changeHero = false;
                    char selection = ' ';

                    /*do
                    {*/
                        //bool res = true;
                        //changeHero = false;

                        cout << "\nSelected Hero: " << heroes[herochoice - 1]->GetName() << endl << endl;
                        ///usleep(1500000);
                        //cout << "\033[s";

                        while(true)
                        {
                            if(selection == '\n')
                                cout << "\033[3A\033[J";

                            do //prints and handles the arrow menu
                            {
                                    /*
                            //    {
                                    //cout << "\033[u\033[J";
                                    //if(res == false)
                                    else
                                        cout << "\033[5A\033[J";
                                }*/

                                DisplayActions(arrow,true);

                                selection = getch();

                                if(selection == 'w' && arrow)
                                    arrow--;
                                else if(selection == 's' && arrow < 2)
                                    arrow++;
                                else if(selection > '0' && selection <= '0' + heroes.size())
                                {
                                    herochoice = selection - '0';
                                    changeHero = true;
                                    cout << "\033[3A";
                                }

                                if(selection != '\n')
                                    cout << "\033[3A\033[J";

                            }while(selection != 'e' && selection != '\n' && changeHero != true);

                            if(selection == 'e' || changeHero == true)
                                break;

                            OpenInventory(*heroes[herochoice - 1] , arrow + 1);
                        }
/*
                        cout << "\n\n\n\t\t\t\tCHANGE HERO = " << changeHero << "\n\n\n";
                        cout << "\n\n\n\t\t\t\t HEROCHOICE = " << herochoice << "\n\n\n";*/

                        if(selection == 'e')
                            break;

                    //}while(changeHero == true);
                //    cout << "\n\n\n\t\t\t\t CHECKPOINT\n\n\n";

                    /*if(selection == 'e')
                        break;*/
                //}
            }
        }
        else if(input == 'q')
        {
            char ch;
            cout << "Do you want to quit the game? [y/n]: " << endl;
            ch = getch();
            if(ch == 'y' || ch == 'Y' || ch == '\n')
                gameover = true;
        }
        else
        {
            bool moved = false;

            moved = grid.MoveHeroes(input);  //moves heroes according to input

            if(grid.IsInStore() == true)
            {
                Trade();  //if the heroes are inside the store then the store menu opens
                grid.HeroExitedStore();
            }
            else if(moved == true && grid.IsInStore() == false && Battle::BattleHappens() == true)
            {
                StartBattle(); //if the conditions are met a battle starts
            }
            else if(moved == true && grid.IsInStore() == false) /*if a battle does not happen then the heroes restore some of their HP and some of their MP*/
            {
                for(int k = 0; k < heroes.size(); k++)
                    heroes[k]->EndTurnRefill();
            }
        }
    }

    cout << "Thanks for playing!" << endl;
}

void Game::StartBattle(void)
{
    vector<Monster *> monsters;
    short extraMonsters = rand() % 3;
    unsigned int lvlOfEM = 0;
    unsigned int generalLvlOfMon = 0;
    bool battleOver = false;
    short faints = 0;
    bool heroesWon = false;
    bool monstersWon = false;

    int arrow = 0;
    char selection = ' ';

    if(heroes[0]->GetLevel() > 4)/*if the heroes are below level 5 then
    the number of monsters that appear is equal to the number of heroes . Over level 5 the number of
    monsters can be increased by 2 extra monsters*/
        extraMonsters = rand() % 3;
    else
        extraMonsters = 0;

    for(short i = 0; i < heroes.size(); i++)
    {
        monsters.push_back(Battle::FindMonster(heroes[i]->GetLevel()));
        lvlOfEM += heroes[i]->GetLevel();
    }
    generalLvlOfMon += lvlOfEM;
    lvlOfEM = lvlOfEM / heroes.size(); /* calculates the average of the 3 heroes */

    for(short i = 0; i < extraMonsters; i++)
    {
        monsters.push_back(Battle::FindMonster(floor(lvlOfEM))); //creates a monster
        generalLvlOfMon += floor(lvlOfEM);
    }

    generalLvlOfMon = generalLvlOfMon / (extraMonsters + heroes.size()); //the average of all monsters

    unsigned int level = 0;

    while(battleOver == false)
    {
        bool res = true;

        for(short int j = 0; j < heroes.size(); j++)
        {
            if(res == true /*&& selection != 'c'*/)
            {
                cout << "\033[2J\033[1;1H";

                if(monsters.size() > heroes.size())
                    cout << "\033[" << ((monsters.size() - 1) * 31) / 2 + 7 << "C";
                else
                    cout << "\033[" << ((heroes.size() - 1) * 31) / 2 + 7 << "C";

                if(j == 0)
                    level++;

                cout << "---> Round " << level << " <---" << endl << endl;

                DisplayAllStats(monsters);

                /*if(i > 2)
                    cout << "\033[3B";*/

                /*cout << endl << "\t\t\t\t\t\tCHECKPOINT\n";
                usleep(1500000);
                cout << "\033[1A\033[K";
                cout << "\033[1A\033[K";*/
            }

            if(heroes[j]->Fainted() == false)
            {

                if(res == false && selection == 'c')
                    cout << "\033[3A";

                cout << "Press 'c' to skip this Hero" << endl;
                cout << "Hero " << j + 1 << ": " << heroes[j]->GetName() << endl;
                cout << "\033[J" << endl;
                ///usleep(1500000);
                //cout << "\033[s";

                do
                {
                //    cout << "\033[u";
                //    cout << "\033[J";
                //    cout << "\033[s";

                    if(res == false && selection == '\n')
                    //if(res == false && selection != 'c')
                    //if(selection == '\n')
                    {
                        cout << "\033[6A";
                        cout << "\033[J";
                        cout << "Choose a new action: " << endl;
                    }

                    do //displays and handles the arrow menu
                    {
                        DisplayActions(arrow);

                        selection = getch();

                        if(selection == 'w' && arrow)
                            arrow--;
                        else if(selection == 's' && arrow < 4)
                            arrow++;

                        if(selection != '\n')
                            cout << "\033[5A";

                        if(selection == 'c' && j == heroes.size() - 1)
                            cout << "\033[5B";

                    }while(selection != 'c' && selection != '\n');

                    if(selection == 'c')
                        break;

                }while((res = ChooseAction(*heroes[j],arrow + 1,monsters)) == false);

                //DisplayAllStats(monsters);

                //char test;
                //cin >> test;

                if(selection == 'c')
                {
                    if(j < heroes.size() - 1) /* If a hero was skipped we disable the screen refresh */
                        res = false;          /* only if we are not at the last hero of the current round */
                    else
                        //if(res == false) /* We increase the 'Round' level from here only if we are */
                            //level++;     /* at the last hero for the current round and the previous hero was skipped */

                        res = true; // We set the 'res' var to TRUE for enabling the screen refresh for the next round

                    continue;
                }

                if(res == true)
                    cout << "\033[8A\033[J";

                if(monsters.empty() == true) //when the vector of monsters is empty then heroes won
                {
                    heroesWon = true;
                    monstersWon = false;
                    break;
                }
            }
            else
            {
                cout << "Warning: Hero " << heroes[j]->GetName() << " has fainted." << endl;
                usleep(1500000);
                cout << "\033[1A\033[K";
            }
        }

        for(short int j = 0 ; j < monsters.size() ; j++)
        {
            short chance = rand() % heroes.size();

            if(heroes[chance]->Fainted() == false)
            {
                Battle::MonsterAttack(*monsters[j], *heroes[chance]);//monster attacks a random hero

                if(heroes[chance]->Fainted() == true)
                    faints++;

                if(faints == heroes.size())//if all heroes faint then monsters win
                {
                    monstersWon = true;
                    heroesWon = false;
                    break;
                }
            }
            else
                j--;
        }

        if(heroesWon == true && monstersWon == false)
        {
            battleOver = true;
            for(int k = 0; k < heroes.size(); k++)//when the heroes win then they gain experience and money
            {
                if(heroes[k]->Fainted() == true)//if a hero faints the they are restored to half HP
                    heroes[k]->RestoreToHalfHP();

                if(heroes[k]->GetLevel() < 100)
                    heroes[k]->GainXP(ceil((double)generalLvlOfMon * (extraMonsters + heroes.size()) / 10));
                heroes[k]->ChangeMoney(2 * generalLvlOfMon * (extraMonsters + heroes.size()));
            }
            break;
        }
        else if(heroesWon == false && monstersWon == true)
        {
            battleOver = true;
            for(int k = 0; k < heroes.size(); k++)//if the heroes lose then they lose half their money and are restore to half HP
            {
                heroes[k]->ChangeMoney(-(heroes[k]->GetMoney() / 2));
                heroes[k]->RestoreToHalfHP();
            }
            break;
        }

        for(int c = 0; c < heroes.size(); c++)//heroes and monsters alike get back some of their HP
        {
            if(heroes[c]->Fainted() == false)
                heroes[c]->EndTurnRefill();
        }

        for(int c = 0; c < monsters.size(); c++)
        {
                monsters[c]->EndRound();
        }
    }

    for(int i = monsters.size(); !monsters.empty(); i--)//if monsters win then they are deleted since they are not needed anymore
    {
        delete monsters[i - 1];
        monsters.erase(monsters.begin() + i - 1);
    }
}

bool Game::Trade()
{
    if(market.EnterMarket(heroes) == false)
        return true;
    else
        return false;
}

void Game::DisplayMonstersStats(vector<Monster *>& monsters)
{
    int heroesNum = heroes.size();
    int monstersNum = monsters.size();

    if(monstersNum < heroesNum)
        cout << "\033[" << ((heroesNum - monstersNum) * 31) / 2 << "C";

    cout << "\033[" << ((monstersNum - 1) * 31) / 2 + 6 << "C";

    cout << "Monsters Statistics" << endl;

    if(monstersNum < heroesNum)
        cout << "\033[" << ((heroesNum - monstersNum) * 31) / 2 << "C";

    for(short int i = 0; i < monstersNum; i++)
        cout << "+==============================";

    cout << "+" << endl;

    if(monstersNum < heroesNum)
        cout << "\033[" << ((heroesNum - monstersNum) * 31) / 2 << "C";

    cout << "|";
    for(short i = 0; i < monstersNum; i++)
    {
        cout << "Name:         ";
        cout.width(16);
        cout << left << monsters[i]->GetName() << "|";
    }
    cout << endl;

    if(monstersNum < heroesNum)
        cout << "\033[" << ((heroesNum - monstersNum) * 31) / 2 << "C";

    cout << "|";
    for(short i = 0; i < monstersNum; i++)
    {
        cout << "Level:        ";
        cout.width(16);
        cout << left << monsters[i]->GetLevel() << "|";
    }
    cout << endl;

    if(monstersNum < heroesNum)
        cout << "\033[" << ((heroesNum - monstersNum) * 31) / 2 << "C";

    cout << "|";
    for(short i = 0; i < monstersNum; i++)
    {
        string str = to_string(monsters[i]->GetHP()) + "/" + to_string(monsters[i]->GetMaxHP());

        cout << "HP:           ";

        cout.width(16);
        cout << left << str << "|";
    }
    cout << endl;

    if(monstersNum < heroesNum)
        cout << "\033[" << ((heroesNum - monstersNum) * 31) / 2 << "C";

    cout << "|";
    for(short i = 0; i < monstersNum; i++)
    {
        string str = to_string(monsters[i]->GetMinDamage()) + "-" + to_string(monsters[i]->GetMaxDamage());
        cout << "Damage Range: ";
        cout.width(16);
        cout << left << str << "|";
    }
    cout << endl;

    if(monstersNum < heroesNum)
        cout << "\033[" << ((heroesNum - monstersNum) * 31) / 2 << "C";

    cout << "|";
    for(short i = 0; i < monstersNum; i++)
    {
        cout << "Defence:      ";
        cout.width(16);
        cout << left << monsters[i]->MonsterGetDefence() << "|";
    }
    cout << endl;

    if(monstersNum < heroesNum)
        cout << "\033[" << ((heroesNum - monstersNum) * 31) / 2 << "C";

    cout << "|";
    for(short i = 0; i < monstersNum; i++)
    {
        cout << "Avoidance:    ";
        cout.width(16);
        cout << left << monsters[i]->MonsterGetAvoidance() << "|";
    }
    cout << endl;

    if(monstersNum < heroesNum)
        cout << "\033[" << ((heroesNum - monstersNum) * 31) / 2 << "C";

    for(short int i = 0; i < monstersNum; i++)
        cout << "+==============================";

    cout << "+" << endl;
}

void Game::DisplayHeroesStats(const unsigned short& monstersNum)
{
    int heroesNum = heroes.size();

    cout << endl;

    if(monstersNum > heroesNum)
        cout << "\033[" << ((monstersNum - heroesNum) * 31) / 2 << "C";

    cout << "\033[" << ((heroesNum - 1) * 31) / 2 + 7 << "C";

    /*cout << endl << "       ";
    for(short i = 0; i < ((heroesNum - 1) * 31) / 2; i++)
        cout << " ";*/

    cout << "Heroes Statistics" << endl;

    if(monstersNum > heroesNum)
        cout << "\033[" << ((monstersNum - heroesNum) * 31) / 2 << "C";

    for(short int i = 0; i < heroesNum; i++)
        cout << "+==============================";

    cout << "+" << endl;

    if(monstersNum > heroesNum)
        cout << "\033[" << ((monstersNum - heroesNum) * 31) / 2 << "C";

    cout << "|";
    for(short i = 0; i < heroesNum; i++)
    {
        cout << "Name:          ";
        cout.width(15);
        cout << left << heroes[i]->GetName() << "|";
    }
    cout << endl;

    if(monstersNum > heroesNum)
        cout << "\033[" << ((monstersNum - heroesNum) * 31) / 2 << "C";

    cout << "|";
    for(short i = 0; i < heroesNum; i++)
    {
        cout << "Level:         ";
        cout.width(15);
        cout << left << heroes[i]->GetLevel() << "|";
    }
    cout << endl;

    if(monstersNum > heroesNum)
        cout << "\033[" << ((monstersNum - heroesNum) * 31) / 2 << "C";

    cout << "|";
    for(short i = 0; i < heroesNum; i++)
    {
        string str = to_string(heroes[i]->GetHP()) + "/" + to_string(heroes[i]->GetMaxHP());

        cout << "HP:            ";

        cout.width(15);
        cout << left << str << "|";
    }
    cout << endl;

    if(monstersNum > heroesNum)
        cout << "\033[" << ((monstersNum - heroesNum) * 31) / 2 << "C";

    cout << "|";
    for(short i = 0; i < heroesNum; i++)
    {
        cout << "Magic Power:   ";
        cout.width(15);
        cout << left << heroes[i]->GetMagicPower() << "|";
    }
    cout << endl;

    if(monstersNum > heroesNum)
        cout << "\033[" << ((monstersNum - heroesNum) * 31) / 2 << "C";

    cout << "|";
    for(short i = 0; i < heroesNum; i++)
    {
        cout << "Strength:      ";
        cout.width(15);
        cout << left << heroes[i]->GetStrength() << "|";
    }
    cout << endl;

    if(monstersNum > heroesNum)
        cout << "\033[" << ((monstersNum - heroesNum) * 31) / 2 << "C";

    cout << "|";
    for(short i = 0; i < heroesNum; i++)
    {
        cout << "Dexterity:     ";
        cout.width(15);
        cout << left << heroes[i]->GetDexterity() << "|";
    }
    cout << endl;

    if(monstersNum > heroesNum)
        cout << "\033[" << ((monstersNum - heroesNum) * 31) / 2 << "C";

    cout << "|";
    for(short i = 0; i < heroesNum; i++)
    {
        cout << "Agility:       ";
        cout.width(15);
        cout << left << heroes[i]->GetAgility() << "|";
    }
    cout << endl;

    if(monstersNum > heroesNum)
        cout << "\033[" << ((monstersNum - heroesNum) * 31) / 2 << "C";

    cout << "|";
    for(short i = 0; i < heroesNum; i++)
    {
        cout << "Armor Defence: ";
        cout.width(15);
        cout << left << heroes[i]->GetArmorDefence() << "|";
    }
    cout << endl;

    if(monstersNum > heroesNum)
        cout << "\033[" << ((monstersNum - heroesNum) * 31) / 2 << "C";

    cout << "|";
    for(short i = 0; i < heroesNum; i++)
    {
        cout << "Weapon Damage: ";
        cout.width(15);
        cout << left << heroes[i]->GetWeaponDamage() << "|";
    }
    cout << endl;

    if(monstersNum > heroesNum)
        cout << "\033[" << ((monstersNum - heroesNum) * 31) / 2 << "C";

    for(short int i = 0; i < heroesNum; i++)
        cout << "+==============================";

    cout << "+" << endl << endl;

    cout << "---------------------------" << endl << endl;
}

void Game::DisplayAllStats(vector<Monster *>& monsters)
{
    DisplayMonstersStats(monsters);
    DisplayHeroesStats(monsters.size());
}

void Game::DisplayActions(const unsigned int& arrow, bool inventoryActions)
{
    if(!inventoryActions && arrow == 0)
        cout << "~> Attack                        " << endl;
    else if(!inventoryActions)
        cout << "   Attack                        " << endl;

    if(!inventoryActions && arrow == 1)
        cout << "~> Use Spell                        " << endl;
    else if(!inventoryActions)
        cout << "   Use Spell                        " << endl;

    if((!inventoryActions && arrow == 2) || (inventoryActions && arrow == 0))
        cout << "~> Change Armor                        " << endl;
    else
        cout << "   Change Armor                        " << endl;

    if((!inventoryActions && arrow == 3) || (inventoryActions && arrow == 1))
        cout << "~> Change Weapon                        " << endl;
    else
        cout << "   Change Weapon                        " << endl;

    if((!inventoryActions && arrow == 4) || (inventoryActions && arrow == 2))
        cout << "~> Drink Potion                        " << endl;
    else
        cout << "   Drink Potion                        " << endl;
    cout << "                                           " << endl;
    cout << "                                           \n\033[2A";
}

bool Game::ChooseMonsterToAttack(vector<Monster *>& monsters, short& mNum)//the user chooses which monster to attack
{
    char testAction;
    char monSize = '0' + monsters.size();

    cout << endl;
    cout << "Press '0' to cancel the attack" << endl;
    cout << "Choose which monster to attack (1-" << monsters.size() << "): ";

    do
    {
        testAction = getch();

        if(testAction == '0')
            break;

    }while(testAction < '1' || testAction > monSize); //checks if monster chosen exists

    cout << endl << "\033[3A";
    cout << "\033[J";

    if(testAction == '0')
        return false;

    mNum = testAction - '0';

    return true;
}

bool Game::ChooseAction(Hero& hero, short action, vector<Monster *>& monsters)
{
    short monsterNum;

    switch(action)
    {
        case 1:
            if(ChooseMonsterToAttack(monsters , monsterNum) == false)
                return false;

            Battle::AttackWithWeapon(hero,*monsters[monsterNum - 1]);//hero attacks with their weapon or bare hands(savage!)

            if(monsters[monsterNum - 1]->Fainted())//if the monster faints then it is deleted
            {
                delete monsters[monsterNum - 1];
                monsters.erase(monsters.begin() + monsterNum - 1);
            }

            return true;

        case 2:
            if(hero.GetAvailableSpellSlots() == hero.GetMaxSpellsSlots())
            {
                cout << "\033[s";
                cout << endl << "Sorry, there are no available spells." << endl;

                usleep(1500000);

                cout << "\033[u";
                cout << "\033[J";

                return false;
            }

            if(ChooseMonsterToAttack(monsters , monsterNum) == false)
                return false;

            if(Battle::CastSpell(hero,*monsters[monsterNum - 1]) == false)//casts the spell chosen
                return false;
            else
            {
                if(monsters[monsterNum - 1]->Fainted())//if the monster faints then it is deleted
                {
                    delete monsters[monsterNum - 1];
                    monsters.erase(monsters.begin() + monsterNum - 1);
                }
            }

            return true;

        case 3:
            if(Battle::ChangeArmor(hero,true) == false)
                return false;
            return true;

        case 4:
            if(Battle::ChangeWeapon(hero,true) == false)
                return false;
            return true;

        case 5:
            if(Battle::UsePotion(hero,true) == false)
                return false;
            return true;
    }
}

bool Game::OpenInventory(Hero& hero, short action)
{
    switch(action)
    {
        case 1:
            if(Battle::ChangeArmor(hero) == false)
                return false;
            return true;
        case 2:
            if(Battle::ChangeWeapon(hero) == false)
                return false;
            return true;
        case 3:
            if(Battle::UsePotion(hero) == false)
                return false;
            return true;
    }
}
