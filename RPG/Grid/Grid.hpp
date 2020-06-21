/* File: Grid.hpp */

#ifndef __GRID_HEADER__
#define __GRID_HEADER__

#include <vector>
class Hero;

class Grid{

    private:
        const int horizontalSize;
        const int verticalSize;
        int* marketBlocks;//determines the blocks the market will get
        char** grid;
        int heroLoc[2];//hero location
        bool heroInStore;

    public:
        Grid();
        ~Grid();
        void MakeEmpty(char **, int, int);
        void HeroExitedStore(void);
        void DisplayGrid(std::vector<Hero *> &);
        void BuildGrid(void);

        bool MoveHeroes(char);
        bool IsInStore(void);
};

#endif // __GRID_HEADER__
