/* File: Living.hpp */

#ifndef __LIVING_HEADER__
#define __LIVING_HEADER__

#include <string>

class Living{

    protected:
        const std::string name;
        unsigned int healthPower;
        unsigned int maxHP;
        unsigned int level;
        bool faint;

    public:
        Living(const std::string &, const unsigned int &, const unsigned int &);

        virtual void LevelUp();
        virtual void ChangeHealth(unsigned int);

        std::string GetName(void) const;

        unsigned int GetLevel(void) const;
        unsigned int GetMaxHP(void) const;
        unsigned int GetHP(void) const;

        bool Fainted(void) const;
        void Revived(void);

        virtual ~Living() = 0;
};

#endif // __LIVING_HEADER__
