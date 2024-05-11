#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <string>
#include "Characters.h"

class Items
{
public:
    static bool readDescriptionFromFileItems(map<string, StoryNode *> &storyMap);
    virtual void action() {}
    Items(){};
    ~Items(){};
};

class Shovel : public Items
{
public:
    void action() override;
};

class Blanket : public Items
{
public:
    void action() override;
};

class Potion : public Items
{
public:
    void action() override;
};

class Cake : public Items
{
public:
    void action() override;
};

class Fan : public Items
{
public:
    void action() override;
};
class waterBottle : public Items
{
public:
    void action() override;
};
class Mushroom : public Items
{
public:
    void action() override;
};

class gardenKey : public Items
{
public:
    void action() override;
};

#endif
