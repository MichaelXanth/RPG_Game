/* File: Game.cpp */

#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <limits>
#include <unistd.h>
#include <vector>

#include "../Battle/Battle.hpp"
#include "../Grid/Grid.hpp"
#include "../Input_Validation/Input_Validation.hpp"
#include "../Keyboard/Keyboard.hpp"
#include "../Living/Heroes/Hero.hpp"
#include "../Living/Monsters/Monster.hpp"
#include "../Market/Market.hpp"
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

    do {
        input = getch();
    } while(input != 'i' && input != 'q' && input != 'a' && input != 'w' && input != 's' && input != 'd');

    return input;
}

void Game::Play(void)
{
    bool gameover = false;

    while(gameover == false) {

        grid.DisplayGrid(heroes);

        char input = GetInput();

        // Enters inventory
        if (input == 'i') {

            int herochoice = 1;
            int arrow      = 0;

            cout << "Press 'e' to exit the inventory" << endl;

            if (heroes.size() != 1)
                cout << "Switch between heroes using numbers in range [1-" << heroes.size() << "]: ";

            cout << endl;

            while(true) {
                bool changeHero = false;
                char selection = ' ';

                cout << "\nSelected Hero: \033[38;5;220m" << heroes[herochoice - 1]->GetName() << "\033[0m" << endl << endl;

                while(true) {
                    if (selection == '\n')
                        cout << "\033[3A\033[J";

                    // Prints and handles the arrow menu
                    do {

                        DisplayActions(arrow,true);

                        selection = getch();

                        if (selection == 'w' && arrow)
                            arrow--;
                        else if (selection == 's' && arrow < 2)
                            arrow++;
                        else if (selection > '0' && selection <= '0' + heroes.size()) {
                            herochoice = selection - '0';
                            changeHero = true;
                            cout << "\033[3A";
                        }

                        if (selection != '\n')
                            cout << "\033[3A\033[J";

                    } while(selection != 'e' && selection != '\n' && changeHero != true);

                    if (selection == 'e' || changeHero == true)
                        break;

                    OpenInventory(*heroes[herochoice - 1] , arrow + 1);
                }

                if (selection == 'e')
                    break;

            }
        
        } else if (input == 'q') {
            char ch;
            cout << "Do you want to quit the game? [y/n]: " << endl;
            ch = getch();
            if (ch == 'y' || ch == 'Y' || ch == '\n')
                gameover = true;
        
        } else {
            bool moved = false;

            moved = grid.MoveHeroes(input);  

            // If the heroes are inside the store then the store menu opens
            if (grid.IsInStore() == true) {
                Trade();  
                grid.HeroExitedStore();
            
            // If the conditions are met a battle starts
            } else if (moved == true && grid.IsInStore() == false && Battle::BattleHappens() == true) {
                StartBattle(); 
            
            /* If a battle does not happen then the heroes restore some of their HP and some of their MP*/
            } else if (moved == true && grid.IsInStore() == false) { 
                for (int k = 0; k < heroes.size(); k++)
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
    bool  battleOver  = false;
    short faints      = 0;
    bool  heroesWon   = false;
    bool  monstersWon = false;

    int  arrow     = 0;
    char selection = ' ';

    /* If the heroes are below level 5 then the number of monsters that appear 
     * is equal to the number of heroes. Over level 5 the number of monsters 
     * can be increased by 2 extra monsters.
     */
    if (heroes[0]->GetLevel() > 4)
        extraMonsters = rand() % 3;
    else
        extraMonsters = 0;

    for (short i = 0; i < heroes.size(); i++) {
        monsters.push_back(Battle::FindMonster(heroes[i]->GetLevel()));
        lvlOfEM += heroes[i]->GetLevel();
    }

    generalLvlOfMon += lvlOfEM;
    lvlOfEM = lvlOfEM / heroes.size(); /* calculates the average of the 3 heroes */

    for (short i = 0; i < extraMonsters; i++) {
        monsters.push_back(Battle::FindMonster(floor(lvlOfEM))); //creates a monster
        generalLvlOfMon += floor(lvlOfEM);
    }

    generalLvlOfMon = generalLvlOfMon / (extraMonsters + heroes.size()); //the average of all monsters

    unsigned int level = 0;

    while(battleOver == false) {
        bool res = true;

        for (short int j = 0; j < heroes.size(); j++) {
            if (res == true /*&& selection != 'c'*/) {
                cout << "\033[2J\033[1;1H";

                if (monsters.size() > heroes.size())
                    cout << "\033[" << ((monsters.size() - 1) * 31) / 2 + 7 << "C";
                else
                    cout << "\033[" << ((heroes.size() - 1) * 31) / 2 + 7 << "C";

                if (j == 0)
                    level++;

                cout << "---> Round " << level << " <---" << endl << endl;

                DisplayAllStats(monsters);
            }

            if (heroes[j]->Fainted() == false)
            {

                if (res == false && selection == 'c')
                    cout << "\033[3A";

                cout << "Press 'c' to skip this Hero" << endl;
                cout << "Hero " << j + 1 << ": \033[38;5;220m" << heroes[j]->GetName() << "\033[0m" << endl;
                cout << "\033[J" << endl;

                do {

                    if (res == false && selection == '\n') {
                        cout << "\033[6A";
                        cout << "\033[J";
                        cout << "Choose a new action: " << endl;
                    }

                    // Displays and handles the arrow menu
                    do {
                        DisplayActions(arrow);

                        selection = getch();

                        if (selection == 'w' && arrow)
                            arrow--;
                        else if (selection == 's' && arrow < 4)
                            arrow++;

                        if (selection != '\n')
                            cout << "\033[5A";

                        if (selection == 'c' && j == heroes.size() - 1)
                            cout << "\033[5B";

                    }while(selection != 'c' && selection != '\n');

                    if (selection == 'c')
                        break;

                } while((res = ChooseAction(*heroes[j],arrow + 1,monsters)) == false);

                if (selection == 'c') {
                    if (j < heroes.size() - 1) /* If a hero was skipped we disable the screen refresh */
                        res = false;          /* only if we are not at the last hero of the current round */
                    else
                        res = true;           /* We set the 'res' var to TRUE for enabling the screen refresh for the next round */

                    continue;
                }

                if (res == true)
                    cout << "\033[8A\033[J";

                // When the vector of monsters is empty then heroes won
                if (monsters.empty() == true) {
                    heroesWon = true;
                    monstersWon = false;
                    break;
                }
            
            } else {
                cout << "\033[35mWarning:\033[0m Hero \033[38;5;220m" << heroes[j]->GetName() << "\033[0m has fainted." << endl;
                usleep(1500000);
                cout << "\033[1A\033[K";
            }
        }

        for (short int j = 0 ; j < monsters.size() ; j++)
        {
            short chance = rand() % heroes.size();

            if (heroes[chance]->Fainted() == false) {
                Battle::MonsterAttack(*monsters[j], *heroes[chance]);//monster attacks a random hero

                if (heroes[chance]->Fainted() == true)
                    faints++;

                // If all heroes faint then monsters win
                if (faints == heroes.size()) {
                    monstersWon = true;
                    heroesWon = false;
                    break;
                }
            }
            else
                j--;
        }

        if (heroesWon == true && monstersWon == false) {
            battleOver = true;
            
            // When the heroes win then they gain experience and money
            for (int k = 0; k < heroes.size(); k++) {
                
                // If a hero faints the they are restored to half HP
                if (heroes[k]->Fainted() == true)
                    heroes[k]->RestoreToHalfHP();

                if (heroes[k]->GetLevel() < 100)
                    heroes[k]->GainXP(ceil((double)generalLvlOfMon * (extraMonsters + heroes.size()) / 10));
                heroes[k]->ChangeMoney(2 * generalLvlOfMon * (extraMonsters + heroes.size()));
            }
            break;
        
        } else if (heroesWon == false && monstersWon == true) {
            battleOver = true;
            
            // If the heroes lose then they lose half their money and are restore to half HP
            for (int k = 0; k < heroes.size(); k++) {
                heroes[k]->ChangeMoney(-(heroes[k]->GetMoney() / 2));
                heroes[k]->RestoreToHalfHP();
            }
            break;
        }

        // Heroes and monsters alike get back some of their HP
        for (int c = 0; c < heroes.size(); c++) {
            if (heroes[c]->Fainted() == false)
                heroes[c]->EndTurnRefill();
        }

        for (int c = 0; c < monsters.size(); c++)
            monsters[c]->EndRound();
    }

    // If monsters win then they are deleted since they are not needed anymore
    for (int i = monsters.size(); !monsters.empty(); i--) {
        delete monsters[i - 1];
        monsters.erase(monsters.begin() + i - 1);
    }
}

bool Game::Trade()
{
    if (market.EnterMarket(heroes) == false)
        return true;
    else
        return false;
}

void Game::DisplayMonstersStats(vector<Monster *>& monsters)
{
    int heroesNum = heroes.size();
    int monstersNum = monsters.size();

    if (monstersNum < heroesNum)
        cout << "\033[" << ((heroesNum - monstersNum) * 31) / 2 << "C";

    cout << "\033[" << ((monstersNum - 1) * 31) / 2 + 6 << "C";

    cout << "Monsters Statistics" << endl;

    if (monstersNum < heroesNum)
        cout << "\033[" << ((heroesNum - monstersNum) * 31) / 2 << "C";

    for (short int i = 0; i < monstersNum; i++)
        cout << "\033[1;33m+\033[0;34m==============================";

    cout << "\033[1;33m+\033[0m" << endl;

    if (monstersNum < heroesNum)
        cout << "\033[" << ((heroesNum - monstersNum) * 31) / 2 << "C";

    cout << "\033[34m|\033[0m";
    for (short i = 0; i < monstersNum; i++) {
        cout << "Name:         ";
        cout.width(16);
        cout << left << monsters[i]->GetName() << "\033[34m|\033[0m";
    }
    cout << endl;

    if (monstersNum < heroesNum)
        cout << "\033[" << ((heroesNum - monstersNum) * 31) / 2 << "C";

    cout << "\033[34m|\033[0m";
    for (short i = 0; i < monstersNum; i++) {
        cout << "Level:        ";
        cout.width(16);
        cout << left << monsters[i]->GetLevel() << "\033[34m|\033[0m";
    }
    cout << endl;

    if (monstersNum < heroesNum)
        cout << "\033[" << ((heroesNum - monstersNum) * 31) / 2 << "C";

    cout << "\033[34m|\033[0m";
    for (short i = 0; i < monstersNum; i++) {
        string str = to_string(monsters[i]->GetHP()) + "/" + to_string(monsters[i]->GetMaxHP());

        if (monsters[i]->GetHP() >= 2.0 / 3.0 * monsters[i]->GetMaxHP())
            cout << "HP:           \033[38;5;9m";
        else if (monsters[i]->GetHP() >= 1.0 / 3.0 * monsters[i]->GetMaxHP())
            cout << "HP:           \033[38;5;202m";
        else
            cout << "HP:           \033[38;5;2m";

        cout.width(16);
        cout << left << str << "\033[34m|\033[0m";
    }
    cout << endl;

    if (monstersNum < heroesNum)
        cout << "\033[" << ((heroesNum - monstersNum) * 31) / 2 << "C";

    cout << "\033[34m|\033[0m";
    for (short i = 0; i < monstersNum; i++) {
        string str = to_string(monsters[i]->GetMinDamage()) + "-" + to_string(monsters[i]->GetMaxDamage());
        cout << "Damage Range: ";
        cout.width(16);
        cout << left << str << "\033[34m|\033[0m";
    }
    cout << endl;

    if (monstersNum < heroesNum)
        cout << "\033[" << ((heroesNum - monstersNum) * 31) / 2 << "C";

    cout << "\033[34m|\033[0m";
    for (short i = 0; i < monstersNum; i++) {
        cout << "Defence:      ";
        cout.width(16);
        cout << left << monsters[i]->MonsterGetDefence() << "\033[34m|\033[0m";
    }
    cout << endl;

    if (monstersNum < heroesNum)
        cout << "\033[" << ((heroesNum - monstersNum) * 31) / 2 << "C";

    cout << "\033[34m|\033[0m";
    for (short i = 0; i < monstersNum; i++) {
        cout << "Avoidance:    ";
        cout.width(16);
        cout << left << monsters[i]->MonsterGetAvoidance() << "\033[34m|\033[0m";
    }
    cout << endl;

    if (monstersNum < heroesNum)
        cout << "\033[" << ((heroesNum - monstersNum) * 31) / 2 << "C";

    for (short int i = 0; i < monstersNum; i++)
        cout << "\033[1;33m+\033[0;34m==============================";

    cout << "\033[1;33m+\033[0m" << endl;
}

void Game::DisplayHeroesStats(const unsigned short& monstersNum)
{
    int heroesNum = heroes.size();

    cout << endl;

    if (monstersNum > heroesNum)
        cout << "\033[" << ((monstersNum - heroesNum) * 31) / 2 << "C";

    cout << "\033[" << ((heroesNum - 1) * 31) / 2 + 7 << "C";

    /*cout << endl << "       ";
    for (short i = 0; i < ((heroesNum - 1) * 31) / 2; i++)
        cout << " ";*/

    cout << "Heroes Statistics" << endl;

    if (monstersNum > heroesNum)
        cout << "\033[" << ((monstersNum - heroesNum) * 31) / 2 << "C";

    for (short int i = 0; i < heroesNum; i++)
        cout << "\033[1;33m+\033[0;34m==============================";

    cout << "\033[1;33m+\033[0m" << endl;

    if (monstersNum > heroesNum)
        cout << "\033[" << ((monstersNum - heroesNum) * 31) / 2 << "C";

    cout << "\033[34m|\033[0m";
    for (short i = 0; i < heroesNum; i++) {
        cout << "Name:          \033[38;5;220m";
        cout.width(15);
        cout << left << heroes[i]->GetName() << "\033[34m|\033[0m";
    }
    cout << endl;

    if (monstersNum > heroesNum)
        cout << "\033[" << ((monstersNum - heroesNum) * 31) / 2 << "C";

    cout << "\033[34m|\033[0m";
    for (short i = 0; i < heroesNum; i++) {
        cout << "Level:         ";
        cout.width(15);
        cout << left << heroes[i]->GetLevel() << "\033[34m|\033[0m";
    }
    cout << endl;

    if (monstersNum > heroesNum)
        cout << "\033[" << ((monstersNum - heroesNum) * 31) / 2 << "C";

    cout << "\033[34m|\033[0m";
    for (short i = 0; i < heroesNum; i++) {
        string str = to_string(heroes[i]->GetHP()) + "/" + to_string(heroes[i]->GetMaxHP());

        if (heroes[i]->GetHP() >= 2.0 / 3.0 * heroes[i]->GetMaxHP())
            cout << "HP:            \033[38;5;2m";
        else if (heroes[i]->GetHP() >= 1.0 / 3.0 * heroes[i]->GetMaxHP())
            cout << "HP:            \033[38;5;202m";
        else
            cout << "HP:            \033[38;5;9m";

        cout.width(15);
        cout << left << str << "\033[34m|\033[0m";
    }
    cout << endl;

    if (monstersNum > heroesNum)
        cout << "\033[" << ((monstersNum - heroesNum) * 31) / 2 << "C";

    cout << "\033[34m|\033[0m";
    for (short i = 0; i < heroesNum; i++) {
        cout << "Magic Power:   ";
        cout.width(15);
        cout << left << heroes[i]->GetMagicPower() << "\033[34m|\033[0m";
    }
    cout << endl;

    if (monstersNum > heroesNum)
        cout << "\033[" << ((monstersNum - heroesNum) * 31) / 2 << "C";

    cout << "\033[34m|\033[0m";
    for (short i = 0; i < heroesNum; i++) {
        cout << "Strength:      ";
        cout.width(15);
        cout << left << heroes[i]->GetStrength() << "\033[34m|\033[0m";
    }
    cout << endl;

    if (monstersNum > heroesNum)
        cout << "\033[" << ((monstersNum - heroesNum) * 31) / 2 << "C";

    cout << "\033[34m|\033[0m";
    for (short i = 0; i < heroesNum; i++) {
        cout << "Dexterity:     ";
        cout.width(15);
        cout << left << heroes[i]->GetDexterity() << "\033[34m|\033[0m";
    }
    cout << endl;

    if (monstersNum > heroesNum)
        cout << "\033[" << ((monstersNum - heroesNum) * 31) / 2 << "C";

    cout << "\033[34m|\033[0m";
    for (short i = 0; i < heroesNum; i++) {
        cout << "Agility:       ";
        cout.width(15);
        cout << left << heroes[i]->GetAgility() << "\033[34m|\033[0m";
    }
    cout << endl;

    if (monstersNum > heroesNum)
        cout << "\033[" << ((monstersNum - heroesNum) * 31) / 2 << "C";

    cout << "\033[34m|\033[0m";
    for (short i = 0; i < heroesNum; i++) {
        cout << "Armor Defence: ";
        cout.width(15);
        cout << left << heroes[i]->GetArmorDefence() << "\033[34m|\033[0m";
    }
    cout << endl;

    if (monstersNum > heroesNum)
        cout << "\033[" << ((monstersNum - heroesNum) * 31) / 2 << "C";

    cout << "\033[34m|\033[0m";
    for (short i = 0; i < heroesNum; i++) {
        cout << "Weapon Damage: ";
        cout.width(15);
        cout << left << heroes[i]->GetWeaponDamage() << "\033[34m|\033[0m";
    }
    cout << endl;

    if (monstersNum > heroesNum)
        cout << "\033[" << ((monstersNum - heroesNum) * 31) / 2 << "C";

    for (short int i = 0; i < heroesNum; i++)
        cout << "\033[1;33m+\033[0;34m==============================";

    cout << "\033[1;33m+\033[0m" << endl << endl;

    cout << "---------------------------" << endl << endl;
}

void Game::DisplayAllStats(vector<Monster *>& monsters)
{
    DisplayMonstersStats(monsters);
    DisplayHeroesStats(monsters.size());
}

void Game::DisplayActions(const unsigned int& arrow, bool inventoryActions)
{
    if (!inventoryActions && arrow == 0)
        cout << "\033[1;33m~> Attack\033[0m                        " << endl;
    else if (!inventoryActions)
        cout << "   Attack                        " << endl;

    if (!inventoryActions && arrow == 1)
        cout << "\033[1;33m~> Use Spell\033[0m                        " << endl;
    else if (!inventoryActions)
        cout << "   Use Spell                        " << endl;

    if ((!inventoryActions && arrow == 2) || (inventoryActions && arrow == 0))
        cout << "\033[1;33m~> Change Armor\033[0m                        " << endl;
    else
        cout << "   Change Armor                        " << endl;

    if ((!inventoryActions && arrow == 3) || (inventoryActions && arrow == 1))
        cout << "\033[1;33m~> Change Weapon\033[0m                        " << endl;
    else
        cout << "   Change Weapon                        " << endl;

    if ((!inventoryActions && arrow == 4) || (inventoryActions && arrow == 2))
        cout << "\033[1;33m~> Drink Potion\033[0m                        " << endl;
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

    do {
        testAction = getch();

        if (testAction == '0')
            break;

    } while(testAction < '1' || testAction > monSize); //checks if monster chosen exists

    cout << endl << "\033[3A";
    cout << "\033[J";

    if (testAction == '0')
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
            if (ChooseMonsterToAttack(monsters , monsterNum) == false)
                return false;

            // Hero attacks with their weapon or bare hands(savage!)
            Battle::AttackWithWeapon(hero,*monsters[monsterNum - 1]);

            // If the monster faints then it is deleted
            if (monsters[monsterNum - 1]->Fainted()) {
                delete monsters[monsterNum - 1];
                monsters.erase(monsters.begin() + monsterNum - 1);
            }

            return true;

        case 2:
            if (hero.GetAvailableSpellSlots() == hero.GetMaxSpellsSlots()) {
                cout << "\033[s";
                cout << endl << "Sorry, there are no available spells." << endl;

                usleep(1500000);

                cout << "\033[u";
                cout << "\033[J";

                return false;
            }

            if (ChooseMonsterToAttack(monsters , monsterNum) == false)
                return false;

            // Casts the chosen spell
            if (Battle::CastSpell(hero,*monsters[monsterNum - 1]) == false)
                return false;
            
            else {
                // If the monster faints then it is deleted
                if (monsters[monsterNum - 1]->Fainted()) {
                    delete monsters[monsterNum - 1];
                    monsters.erase(monsters.begin() + monsterNum - 1);
                }
            }

            return true;

        case 3:
            if (Battle::ChangeArmor(hero,true) == false)
                return false;
            return true;

        case 4:
            if (Battle::ChangeWeapon(hero,true) == false)
                return false;
            return true;

        case 5:
            if (Battle::UsePotion(hero,true) == false)
                return false;
            return true;
    }
}

bool Game::OpenInventory(Hero& hero, short action)
{
    switch(action)
    {
        case 1:
            if (Battle::ChangeArmor(hero) == false)
                return false;
            return true;
        case 2:
            if (Battle::ChangeWeapon(hero) == false)
                return false;
            return true;
        case 3:
            if (Battle::UsePotion(hero) == false)
                return false;
            return true;
    }
}
