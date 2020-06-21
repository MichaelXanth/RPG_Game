/* File: Grid.cpp */

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "../Living/Heroes/Hero.hpp"
#include "Grid.hpp"

using namespace std;

Grid::Grid() : horizontalSize(50), verticalSize(30)
{
    grid = new char*[verticalSize];

    for(int i = 0; i < verticalSize; i++)
        grid[i] = new char[horizontalSize];

    marketBlocks = new int[2];
    heroLoc[0]   = -1;
    heroLoc[1]   = -1;
    heroInStore  = false;

    MakeEmpty(grid , verticalSize , horizontalSize); // it fills the grid with spaces
}

Grid::~Grid()
{
    for(int i = 0; i < verticalSize; i++)
        delete[] grid[i];
    delete[] grid;
    delete[] marketBlocks;
}

void Grid::MakeEmpty(char** array ,int vSize ,int hSize)//the function fill the grid with spaces
{
    for (int i = 0; i < vSize; i++)
        for (int j = 0 ; j < hSize ; j++)
            array[i][j] = ' ';
}

void Grid::BuildGrid(void)
{
    int marketP[2];
    // Detemines how many lines and rows the market will have
    marketBlocks[0] = (rand() % 4) + 1;
    marketBlocks[1] = (rand() % 5) + 1;
    marketP[0]      =  rand() % (verticalSize   - marketBlocks[0] + 1);
    marketP[1]      =  rand() % (horizontalSize - marketBlocks[1] + 1);

    // Marks the spaces the market fills with 'M'
    for (int i = marketP[0]; i < marketBlocks[0] + marketP[0]; i++)
        for (int j = marketP[1]; j < marketBlocks[1] + marketP[1]; j++)
            grid[i][j] = 'M';

    int  heroP[2];
    bool heroPlaced = false;

    // Detemines the hero location
    while(heroPlaced != true) {
        heroP[0] = rand() % verticalSize;
        heroP[1] = rand() % horizontalSize;

        if (grid[heroP[0]][heroP[1]] == ' ') {
            grid[heroP[0]][heroP[1]] = 'H';
            heroLoc[0] = heroP[0];
            heroLoc[1] = heroP[1];
            heroPlaced = true;
        }
    }

    // Determines where non-accessible blocks are placed
    for(int i = 0; i < verticalSize; i++) {
        float chance = 0.1;

        for(int j = 0; j < horizontalSize; j++)
            if (grid[i][j] == ' ' && (double)rand() / RAND_MAX < chance)
                grid[i][j] = 'X';
    }
}

void Grid::DisplayGrid(vector<Hero *>& heroes)/*displays non-accessible blocks with red , the market with yellow and the heroes with green*/
{
    cout << "\033[2J\033[1;1H";
    cout << "\033[s";
    cout << "\033[1;33m+\033[0;34m====================================================================================================\033[1;33m+\033[34m" << endl;
    
    for(int i = 0; i < verticalSize; i++) {
        cout << "\033[0;34m|\033[0m";
        for(int j = 0; j < horizontalSize; j++) {
            if(grid[i][j] == ' ')
                cout << "  ";
            else if(grid[i][j] == 'X')
                cout << "\033[48;5;9m  \033[0m";
            else if(grid[i][j] == 'M')
                cout << "\033[48;5;11m  \033[0m";
            else
                cout << "\033[48;5;70m  \033[0m";
        }
        cout << "\033[34m|\033[0m" << endl;
    }
    
    cout << "\033[1;33m+\033[0;34m====================================================================================================\033[1;33m+\033[34m" << endl;
    cout << "\033[0;34m|\033[0m \033[48;5;9m  \033[0m -> Non-accessible, \033[48;5;11m  \033[0m -> Market, \033[48;5;70m  \033[0m -> Heroes \033[34m|\033[0m";
    cout << "       Press: \033[1;33mi\033[0m for inventory or \033[1;33mq\033[0m to quit       \033[34m|\033[0m" << endl;
    cout << "\033[1;33m+\033[0;34m--------------------------------------------------\033[1;33m+\033[0;34m-------------------------------------------------\033[1;33m+\033[0m" << endl;

    cout << "\033[u";

    for(int  i = 0; i < heroes.size(); i++)
    {
        cout << "\033[104C\033[1;33m+\033[0;34m==============================\033[1;33m+\033[0m" << endl;

        cout << "\033[104C\033[34m|\033[0m";
        cout << "Name:          \033[38;5;220m";
        cout.width(15);
        cout << left << heroes[i]->GetName() << "\033[34m|\033[0m" << endl;

        cout << "\033[104C\033[34m|\033[0m";
        cout << "Level:         ";
        cout.width(15);
        cout << left << heroes[i]->GetLevel() << "\033[34m|\033[0m" << endl;

        cout << "\033[104C\033[34m|\033[0m";
        string str = to_string(heroes[i]->GetHP()) + "/" + to_string(heroes[i]->GetMaxHP());

        if(heroes[i]->GetHP() >= 2.0 / 3.0 * heroes[i]->GetMaxHP())
            cout << "HP:            \033[38;5;2m";
        else if(heroes[i]->GetHP() >= 1.0 / 3.0 * heroes[i]->GetMaxHP())
            cout << "HP:            \033[38;5;202m";
        else
            cout << "HP:            \033[38;5;9m";

        cout.width(15);
        cout << left << str << "\033[34m|\033[0m" << endl;

        cout << "\033[104C\033[34m|\033[0m";
        cout << "Magic Power:   ";
        cout.width(15);
        cout << left << heroes[i]->GetMagicPower() << "\033[34m|\033[0m" << endl;

        cout << "\033[104C\033[34m|\033[0m";
        cout << "Money:         ";
        cout.width(15);
        cout << left << heroes[i]->GetMoney() << "\033[34m|\033[0m" << endl;

        cout << "\033[104C\033[34m|\033[0m";
        cout << "Strength:      ";
        cout.width(15);
        cout << left << heroes[i]->GetStrength() << "\033[34m|\033[0m" << endl;

        cout << "\033[104C\033[34m|\033[0m";
        cout << "Dexterity:     ";
        cout.width(15);
        cout << left << heroes[i]->GetDexterity() << "\033[34m|\033[0m" << endl;

        cout << "\033[104C\033[34m|\033[0m";
        cout << "Agility:       ";
        cout.width(15);
        cout << left << heroes[i]->GetAgility() << "\033[34m|\033[0m" << endl;

        cout << "\033[104C\033[34m|\033[0m";
        cout << "Armor Defence: ";
        cout.width(15);
        cout << left << heroes[i]->GetArmorDefence() << "\033[34m|\033[0m" << endl;

        cout << "\033[104C\033[34m|\033[0m";
        cout << "Weapon Damage: ";
        cout.width(15);
        cout << left << heroes[i]->GetWeaponDamage() << "\033[34m|\033[0m" << endl;

    }
    cout << "\033[104C\033[1;33m+\033[0;34m==============================\033[1;33m+\033[0m" << endl;

    cout << "\033[" << 33 - 11 * heroes.size() << "B";

    if(heroes.size() == 3)
        cout << "\033[1A";
}

bool Grid::MoveHeroes(char movement)
{
    // It exists so that we can define if a battle is going to happen or not
    bool heroMoved = false; 

    switch(movement)
    {
        // Going left
        case 'a':
        case 'A':
            if (heroLoc[1] != 0) {
                if (grid[heroLoc[0]][heroLoc[1] - 1] == ' ') {
                    grid[heroLoc[0]][heroLoc[1] - 1] = 'H';
                    grid[heroLoc[0]][heroLoc[1]] = ' ';
                    heroLoc[1] = heroLoc[1] - 1;
                    heroMoved = true;
                    break;
                
                } else if (grid[heroLoc[0]][heroLoc[1] - 1] == 'M') {
                    heroInStore = true;
                    break;
                }
            }
        break;

        // Going right
        case 'd':
        case 'D':
            if (heroLoc[1] != horizontalSize - 1) {
                if (grid[heroLoc[0]][heroLoc[1] + 1] == ' ') {
                    grid[heroLoc[0]][heroLoc[1] + 1] = 'H';
                    grid[heroLoc[0]][heroLoc[1]] = ' ';
                    heroLoc[1] = heroLoc[1] + 1;
                    heroMoved = true;
                    break;
                
                } else if (grid[heroLoc[0]][heroLoc[1] + 1] == 'M') {
                    heroInStore = true;
                    break;
                }
            }
            break;
        
        // Going Up
        case 'w':
        case 'W':
            if (heroLoc[0] != 0){
                if (grid[heroLoc[0] - 1][heroLoc[1]] == ' ')
                {
                    grid[heroLoc[0] - 1][heroLoc[1]] = 'H';
                    grid[heroLoc[0]][heroLoc[1]] = ' ';
                    heroLoc[0] = heroLoc[0] - 1;
                    heroMoved = true;
                    break;
                
                } else if (grid[heroLoc[0] - 1][heroLoc[1]] == 'M') {
                    heroInStore = true;
                    break;
                }
            }
            break;
        
        // Going Down
        case 's':
        case 'S':
            if(heroLoc[0] != verticalSize - 1) {
                if(grid[heroLoc[0] + 1][heroLoc[1]] == ' ') {
                    grid[heroLoc[0] + 1][heroLoc[1]] = 'H';
                    grid[heroLoc[0]][heroLoc[1]] = ' ';
                    heroLoc[0] = heroLoc[0] + 1;
                    heroMoved = true;
                    break;
                
                } else if(grid[heroLoc[0] + 1][heroLoc[1]] == 'M') {
                    heroInStore = true;
                    break;
                }
            }
            break;
    }

    return heroMoved;
}

bool Grid::IsInStore()
{
    return heroInStore;
}

void Grid::HeroExitedStore()
{
    heroInStore = false;
}
