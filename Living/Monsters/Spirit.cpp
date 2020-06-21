/* File: Spirit.cpp */

#include "Spirit.hpp"

Spirit::Spirit(const std::string& name, const unsigned int& health, const unsigned int& lvl,
               const unsigned int& setMinDmg, const unsigned int& setMaxDmg,
               const unsigned int& setDef, const float& setAvoidance)
               : Monster(name, health, lvl, setMinDmg, setMaxDmg, setDef, setAvoidance)
{}

Spirit::~Spirit()
{}
