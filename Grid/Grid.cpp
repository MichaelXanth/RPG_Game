/* File: Grid.cpp */

#include <ctime>
#include <cstdlib>
#include <cmath>
#include <iostream>

#include "../Living/Heroes/Hero.hpp"
#include "Grid.hpp"

using namespace std;

Grid::Grid() : horizontalSize(50), verticalSize(30)
{
    grid = new char*[verticalSize];

    for(int i = 0; i < verticalSize; i++)
    {
        grid[i] = new char[horizontalSize];
    }

    marketBlocks = new int[2];
    heroLoc[0] = -1;
    heroLoc[1] = -1;
    heroInStore = false;

    MakeEmpty(grid , verticalSize , horizontalSize); // it fills the grid with spaces
}

Grid::~Grid()
{
    for(int i = 0; i < verticalSize; i++)
    {
        delete[] grid[i];
    }
    delete[] grid;
    delete[] marketBlocks;
}

void Grid::MakeEmpty(char** array ,int vSize ,int hSize)//the function fill the grid with spaces
{
    for (int i = 0; i < vSize; i++)
    {
        for (int j = 0 ; j < hSize ; j++)
        {
            array[i][j] = ' ';
        }
    }
}

void Grid::BuildGrid(void)
{
    int marketP[2];
    marketBlocks[0] = (rand() % 4) + 1;//detemines how many lines and rows the market will have
    marketBlocks[1] = (rand() % 5) + 1;
    marketP[0] = rand() % (verticalSize - marketBlocks[0] + 1);
    marketP[1] = rand() % (horizontalSize - marketBlocks[1] + 1);

    for (int i = marketP[0]; i < marketBlocks[0] + marketP[0]; i++)//marks the spaces the market fills with 'M'
    {
        for (int j = marketP[1]; j < marketBlocks[1] + marketP[1]; j++)
        {
            grid[i][j] = 'M';
        }
    }

    int heroP[2];
    bool heroPlaced = false;

    while(heroPlaced != true)//detemines the hero location
    {
        heroP[0] = rand() % verticalSize;
        heroP[1] = rand() % horizontalSize;

        if (grid[heroP[0]][heroP[1]] == ' ')
        {
            grid[heroP[0]][heroP[1]] = 'H';
            heroLoc[0] = heroP[0];
            heroLoc[1] = heroP[1];
            heroPlaced = true;
        }
    }

    for(int i = 0; i < verticalSize; i++)//determines where non-accessible blocks are placed
    {
        float chance = 0.1;

        for(int j = 0; j < horizontalSize; j++)
        {
            if (grid[i][j] == ' ' && (double)rand() / RAND_MAX < chance)
            {
                grid[i][j] = 'X';
            }
        }
    }
}

void Grid::DisplayGrid(vector<Hero *>& heroes)/*displays non-accessible blocks with red , the market with yellow and the heroes with green*/
{
    cout << "\033[2J\033[1;1H";
    cout << "\033[s";
    cout << "+====================================================================================================+" << endl;
    for(int i = 0; i < verticalSize; i++)
    {
        cout << "|";
        for(int j = 0; j < horizontalSize; j++)
        {
            if(grid[i][j] == ' ')
                cout << "  ";
            else if(grid[i][j] == 'X')
                cout << "\033[48;5;9m  \033[0m";
            else if(grid[i][j] == 'M')
                cout << "\033[48;5;11m  \033[0m";
            else
                cout << "\033[48;5;70m  \033[0m";
        }
        cout << "|" << endl;
    }
    cout << "+====================================================================================================+" << endl;
    cout << "| \033[48;5;9m  \033[0m -> Non-accessible, \033[48;5;11m  \033[0m -> Market, \033[48;5;70m  \033[0m -> Heroes |";
    cout << "       Press: i for inventory or q to quit       |" << endl;
    cout << "+--------------------------------------------------+-------------------------------------------------+" << endl;

    cout << "\033[u";

    for(int  i = 0; i < heroes.size(); i++)
    {
        cout << "\033[104C+==============================+" << endl;

        cout << "\033[104C|";
        cout << "Name:          ";
        cout.width(15);
        cout << left << heroes[i]->GetName() << "|" << endl;

        cout << "\033[104C|";
        cout << "Level:         ";
        cout.width(15);
        cout << left << heroes[i]->GetLevel() << "|" << endl;

        cout << "\033[104C|";
        string str = to_string(heroes[i]->GetHP()) + "/" + to_string(heroes[i]->GetMaxHP());

        cout << "HP:            ";

        cout.width(15);
        cout << left << str << "|" << endl;

        cout << "\033[104C|";
        cout << "Magic Power:   ";
        cout.width(15);
        cout << left << heroes[i]->GetMagicPower() << "|" << endl;

        cout << "\033[104C|";
        cout << "Money:         ";
        cout.width(15);
        cout << left << heroes[i]->GetMoney() << "|" << endl;

        cout << "\033[104C|";
        cout << "Strength:      ";
        cout.width(15);
        cout << left << heroes[i]->GetStrength() << "|" << endl;

        cout << "\033[104C|";
        cout << "Dexterity:     ";
        cout.width(15);
        cout << left << heroes[i]->GetDexterity() << "|" << endl;

        cout << "\033[104C|";
        cout << "Agility:       ";
        cout.width(15);
        cout << left << heroes[i]->GetAgility() << "|" << endl;

        cout << "\033[104C|";
        cout << "Armor Defence: ";
        cout.width(15);
        cout << left << heroes[i]->GetArmorDefence() << "|" << endl;

        cout << "\033[104C|";
        cout << "Weapon Damage: ";
        cout.width(15);
        cout << left << heroes[i]->GetWeaponDamage() << "|" << endl;

    }
    cout << "\033[104C+==============================+" << endl;

    cout << "\033[" << 33 - 11 * heroes.size() << "B";

    if(heroes.size() == 3)
        cout << "\033[1A";
}

bool Grid::MoveHeroes(char movement)
{
    bool heroMoved = false; //it exists so that we can define if a battle is going to happen or not

    switch(movement)
    {
        case 'a':
        case 'A':/*determines if the heroes can move left*/
            if (heroLoc[1] != 0)
            {
                if (grid[heroLoc[0]][heroLoc[1] - 1] == ' ')
                {
                    grid[heroLoc[0]][heroLoc[1] - 1] = 'H';
                    grid[heroLoc[0]][heroLoc[1]] = ' ';
                    heroLoc[1] = heroLoc[1] - 1;
                    heroMoved = true;
                    break;
                }
                else if (grid[heroLoc[0]][heroLoc[1] - 1] == 'M')
                {
                    heroInStore = true;
                    break;
                }
            }
        break;

        case 'd':
        case 'D':/*determines if the heroes can move right*/
            if (heroLoc[1] != horizontalSize - 1)
            {
                if (grid[heroLoc[0]][heroLoc[1] + 1] == ' ')
                {
                    grid[heroLoc[0]][heroLoc[1] + 1] = 'H';
                    grid[heroLoc[0]][heroLoc[1]] = ' ';
                    heroLoc[1] = heroLoc[1] + 1;
                    heroMoved = true;
                    break;
                }
                else if (grid[heroLoc[0]][heroLoc[1] + 1] == 'M')
                {
                    heroInStore = true;
                    break;
                }
            }
            break;

        case 'w':
        case 'W':/*determines if the heroes can move up*/
            if (heroLoc[0] != 0){
                if (grid[heroLoc[0] - 1][heroLoc[1]] == ' ')
                {
                    grid[heroLoc[0] - 1][heroLoc[1]] = 'H';
                    grid[heroLoc[0]][heroLoc[1]] = ' ';
                    heroLoc[0] = heroLoc[0] - 1;
                    heroMoved = true;
                    break;
                }
                else if (grid[heroLoc[0] - 1][heroLoc[1]] == 'M')
                {
                    heroInStore = true;
                    break;
                }
            }
            break;

        case 's':
        case 'S':/*determines if the heroes can move down*/
            if(heroLoc[0] != verticalSize - 1)
            {
                if(grid[heroLoc[0] + 1][heroLoc[1]] == ' ')
                {
                    grid[heroLoc[0] + 1][heroLoc[1]] = 'H';
                    grid[heroLoc[0]][heroLoc[1]] = ' ';
                    heroLoc[0] = heroLoc[0] + 1;
                    heroMoved = true;
                    break;
                }
                else if(grid[heroLoc[0] + 1][heroLoc[1]] == 'M')
                {
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
