/* File: Living.cpp */

#include "Living.hpp"

using namespace std;

Living::Living(const string& givenName, const unsigned int& setHealth, const unsigned int& setLevel)
               : name(givenName), healthPower(setHealth), maxHP(setHealth), level(setLevel), faint(false)
{}

Living::~Living()
{}

void Living::LevelUp()
{
    level++;
}

void Living::ChangeHealth(unsigned int difference)
{
    if(healthPower - difference == 0 || healthPower - difference > healthPower)//checks if the health power is smaller than 0 and if so it sets it to 0
    {
        healthPower = 0;
        faint = true;
    }
    else
    {
        healthPower -= difference;
    }
}

void Living::Revived(void)
{
    faint = false;
}

bool Living::Fainted(void) const
{
    return faint;
}

string Living::GetName(void) const
{
    return name;
}

unsigned int Living::GetLevel(void) const
{
    return level;
}

unsigned int Living::GetMaxHP(void) const
{
    return maxHP;
}

unsigned int Living::GetHP(void) const
{
    return healthPower;
}
