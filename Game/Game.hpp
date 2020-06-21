/* File: Game.hpp */

#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <vector>

class Grid;
class Hero;
class Market;
class Monster;

class Game{

    private:
        Grid& grid;
        Market& market;
        std::vector<Hero *>& heroes;

        char GetInput(void);

    public:
        Game(std::vector<Hero *> &, Grid &, Market &);
        ~Game();

        bool ChooseMonsterToAttack(std::vector<Monster *> &, short &);
        bool ChooseAction(Hero &, short, std::vector<Monster *> &);
        bool OpenInventory(Hero &, short);
        bool Trade(void);

        void StartBattle(void);
        void Play(void);

        void DisplayActions(const unsigned int &, bool = false);
        void DisplayMonstersStats(std::vector<Monster *> &);
        void DisplayAllStats(std::vector<Monster *> &);
        void DisplayHeroesStats(const unsigned short &);
};

#endif // __GAME_HPP__
