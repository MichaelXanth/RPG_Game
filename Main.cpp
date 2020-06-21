
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

#include "./Living/Heroes/Sorcerer.hpp"
#include "./Living/Heroes/Paladin.hpp"
#include "./Living/Heroes/Warrior.hpp"
#include "./Living/Heroes/Hero.hpp"
#include "./Market/Market.hpp"
#include "./Game/Game.hpp"
#include "./Grid/Grid.hpp"
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
                                 Hero::GetBaseHealth() , 100 , Hero::GetBaseMagicPower(),
                                 Hero::GetBaseDexterity() + 600 , Hero::GetBaseStrength() + 2,
                                 Hero::GetBaseAgility(),5000));

    heroes.push_back(new Sorcerer(name.names[rand() % name.names.size()],
                                  Hero::GetBaseHealth() , 100 , Hero::GetBaseMagicPower(),
                                  Hero::GetBaseDexterity() + 800 , Hero::GetBaseStrength(),
                                  Hero::GetBaseAgility() + 0.15,5000));

    heroes.push_back(new Warrior(name.names[rand() % name.names.size()],
                                 Hero::GetBaseHealth() , 100 , Hero::GetBaseMagicPower(),
                                 Hero::GetBaseDexterity() , Hero::GetBaseStrength() + 3,
                                 Hero::GetBaseAgility() + 0.2,5000));

    Game game(heroes , grid , market);
    game.Play();

    delete heroes[0];
    delete heroes[1];
    delete heroes[2];
}
