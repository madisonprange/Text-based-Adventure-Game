#ifndef ACTION_H
#define ACTION_H

#include <string>
#include "inventory.h"
#include "Characters.h"
#include "StoryNode.h"
#include "Items.h"
#include "inventory.h"
#include <cstdlib>

class Action
{
private:
    Characters::Alice *alice;
    Inventory *inventory;

public:
    Action(Characters::Alice *alice, Inventory *inventory);
    ~Action();
    string handleDirection(const string &direction);
    void handlePickUp(const string &object);
    void handleObjects(const string &object);
    void handleDropping(const string &object);
    void displayList(const string &object);
};

#endif
