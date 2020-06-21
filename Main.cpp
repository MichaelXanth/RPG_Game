
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#include "./Game/Game.hpp"
#include "./Grid/Grid.hpp"
#include "./Living/Heroes/Hero.hpp"
#include "./Living/Heroes/Paladin.hpp"
#include "./Living/Heroes/Sorcerer.hpp"
#include "./Living/Heroes/Warrior.hpp"
#include "./Market/Market.hpp"
#include "Names.hpp"

using namespace std;

int main(void)
{
    srand(time(NULL));
    Grid grid;
    Market market;
    Names name;
    vector<Hero*> heroes;

    grid.BuildGrid();

    heroes.push_back(new Paladin(name.names[rand() % name.names.size()],
                                 Hero::GetBaseHealth() , 1 , Hero::GetBaseMagicPower(),
                                 Hero::GetBaseDexterity() + (float(rand()) / RAND_MAX * 600), Hero::GetBaseStrength() + 2,
                                 Hero::GetBaseAgility(), 50));

    heroes.push_back(new Sorcerer(name.names[rand() % name.names.size()],
                                  Hero::GetBaseHealth() , 1 , Hero::GetBaseMagicPower(),
                                  Hero::GetBaseDexterity() + (float(rand()) / RAND_MAX * 800), Hero::GetBaseStrength(),
                                  Hero::GetBaseAgility() + (float(rand()) / RAND_MAX * 0.7), 50));

    heroes.push_back(new Warrior(name.names[rand() % name.names.size()],
                                 Hero::GetBaseHealth() , 1 , Hero::GetBaseMagicPower(),
                                 Hero::GetBaseDexterity() , Hero::GetBaseStrength() + 3,
                                 Hero::GetBaseAgility() + (float(rand()) / RAND_MAX * 0.8), 50));
    
    Game game(heroes , grid , market);
    game.Play();

    delete heroes[0];
    delete heroes[1];
    delete heroes[2];
}
