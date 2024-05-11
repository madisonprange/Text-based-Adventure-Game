#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>
#include <iostream>
#include "Characters.h"
#include <map>

using namespace std;

class Settings
{
private:
public:
    Settings(){};
    ~Settings(){};
    static bool readDescriptionFromFileSetting(map<string, StoryNode *> &storyMap);
};

#endif
