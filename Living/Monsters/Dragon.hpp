/* File: Dragon.hpp */

#ifndef __DRAGON__HEADER__
#define __DRAGON__HEADER__

#include "Monster.hpp"

class Dragon : public Monster{

    public:
        Dragon(const std::string &, const unsigned int &, const unsigned int &,const unsigned int &,
               const unsigned int &, const unsigned int &, const float &);
        ~Dragon();
};

#endif // __DRAGON__HEADER__
