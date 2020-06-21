/* File: Items.hpp */

#ifndef __ITEMS_HEADER__
#define __ITEMS_HEADER__

#include <string>

class Item{

    private:
        const std::string name;
        const unsigned int price;
        const unsigned int minRequiredLevel;

    public:
        Item(const std::string &, const unsigned int &, const unsigned int &);

        virtual const std::string  GetName(void) const;
        virtual const unsigned int GetPrice(void) const;
        virtual const unsigned int GetMinReqLevel(void) const;

        virtual ~Item() = 0;
};

#endif // __ITEMS_HEADER__
