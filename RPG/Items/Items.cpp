/* File: Items.cpp */

#include "Items.hpp"

Item::Item(const std::string& nm, const unsigned int& pr, const unsigned int& minReqLev)
           : name(nm), price(pr), minRequiredLevel(minReqLev)
{}

Item::~Item()
{}

const std::string Item::GetName(void) const
{
    return name;
}

const unsigned int Item::GetPrice(void) const
{
    return price;
}

const unsigned int Item::GetMinReqLevel(void) const
{
    return minRequiredLevel;
}
