/* File: Input_Validation.cpp */

#include <cstdlib>
#include <iostream>
#include <limits>

#include "Input_Validation.hpp"

using namespace std;

bool isNumeric(const char* ch, int& action, bool info)         /** With that function we validate the user's input **/
{
    const char* tmpCh = ch;

    while(*ch) {
        if(!isdigit(*ch)) {
            if(info) {
                cerr << "\n\033[31mError:\033[0m A positive numeric argument should be given." << endl;
                cerr << "Please, try again!" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            return false;
        }
        ch++;
    }

    action = atoi(tmpCh);
    return true;
}

bool isValid(const char* testAction, int& action, const int& lowerRangeLimit, const int& upperRangeLimit, bool info)
{
    if(!isNumeric(testAction,action,info))
        return false;
    
    else if(action < lowerRangeLimit || action > upperRangeLimit) {
        if(info) {
            cerr << "\n\033[31mError:\033[0m The input is invalid." << endl;
            cerr << "Please, try again!" << endl;
        }
        return false;
    }

    return true;
}
