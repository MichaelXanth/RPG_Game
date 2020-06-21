/* File: Dragon.cpp */

#include "Dragon.hpp"

Dragon::Dragon(const std::string& name, const unsigned int& health, const unsigned int& lvl,
               const unsigned int& setMinDmg, const unsigned int& setMaxDmg,
               const unsigned int& setDef, const float& setAvoidance)
               : Monster(name, health, lvl, setMinDmg, setMaxDmg, setDef, setAvoidance)
{}

Dragon::~Dragon()
{}
