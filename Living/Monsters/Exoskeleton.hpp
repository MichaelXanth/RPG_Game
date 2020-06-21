/* File: Exoskeleton.hpp */

#ifndef __EXOSKELETON__HEADER__
#define __EXOSKELETON__HEADER__

#include "Monster.hpp"

class Exoskeleton : public Monster{

    public:
        Exoskeleton(const std::string &, const unsigned int &, const unsigned int &, const unsigned int &,
                    const unsigned int &, const unsigned int &, const float &);
        ~Exoskeleton();
};

#endif // __EXOSKELETON__HEADER__
