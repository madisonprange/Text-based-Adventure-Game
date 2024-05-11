#include "StoryNode.h"

StoryNode ::~StoryNode()
{
    delete north;
    delete south;
    delete east;
    delete west;
}

StoryNode *StoryNode::moveDirection(const string &direction)
{
    if (direction == "north")
    {
        return north;
    }
    if (direction == "south")
    {
        return south;
    }
    if (direction == "west")
    {
        return west;
    }
    if (direction == "east")
    {
        return east;
    }
    return nullptr;
}

void StoryNode ::getMoveDirection()
{
    cout << "You can go in the following directions:" << endl;
    if (north != nullptr)
    {
        cout << "You can go north." << endl;
    }
    if (east != nullptr)
    {
        cout << "You can go east." << endl;
    }
    if (west != nullptr)
    {
        cout << "You can go west." << endl;
    }
    if (south != nullptr)
    {
        cout << "You can go south." << endl;
    }
}

void StoryNode::bindStoryNorth(StoryNode *n)
{
    north = n;
    if (n != nullptr)
    {
        n->south = this;
    }
}

void StoryNode::bindStoryEast(StoryNode *e)
{
    east = e;
    if (e != nullptr)
    {
        e->west = this;
    }
}

void StoryNode::bindStoryWest(StoryNode *w)
{
    west = w;
    if (w != nullptr)
    {
        w->east = this;
    }
}

void StoryNode::bindStorySouth(StoryNode *s)
{
    south = s;
    if (s != nullptr)
    {
        s->north = this;
    }
}

void StoryNode::unbindStoryWest()
{
    if (west)
    {
        west->east = nullptr;
        west = nullptr;
    }
}
