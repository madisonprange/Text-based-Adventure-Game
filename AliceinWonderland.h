#ifndef ALICEINWONDERLAND_H
#define ALICEINWONDERLAND_H

#include "Items.h"
#include "Characters.h"
#include "control.h"
#include "StoryNode.h"
#include "inventory.h"
#include "Settings.h"
#include "Action.h"
#include <iostream>
#include <limits>
#include <utility>
#include <algorithm>
#include <string>
#include <map>

class AliceinWonderland
{
private:
    int gameStart();
    void gameGoal();

    map<string, StoryNode *> storyMap;

    // Create nodes that are altered depending on object manipulation
    StoryNode *hole_rabbit;
    StoryNode *wonderland_Start;
    StoryNode *hole_Start;
    StoryNode *hole_garden;
    StoryNode *caterpillar_start;
    StoryNode *cathouse_start;
    StoryNode *gardenparty;
    StoryNode *queenmatch_start;

    Characters::Alice *alice;

public:
    AliceinWonderland(Characters::Alice *alice)
        : alice(alice), hole_rabbit(nullptr), wonderland_Start(nullptr),
          hole_Start(nullptr), hole_garden(nullptr), caterpillar_start(nullptr),
          cathouse_start(nullptr), gardenparty(nullptr), queenmatch_start(nullptr)
    {
    }

    ~AliceinWonderland()
    {
    }
    void run();
    static int main();
    StoryNode *buildMap();
};

#endif
