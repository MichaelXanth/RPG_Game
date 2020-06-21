/* File: Spirit.hpp */

#ifndef __SPIRIT__HEADER__
#define __SPIRIT__HEADER__

#include "Monster.hpp"

class Spirit : public Monster{

    public:
        Spirit(const std::string &, const unsigned int &, const unsigned int &,const unsigned int &,
               const unsigned int &, const unsigned int &, const float &);
        ~Spirit();
};

#endif // __SPIRIT__HEADER__
