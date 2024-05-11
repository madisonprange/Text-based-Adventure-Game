#ifndef STORYNODE_H
#define STORYNODE_H

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

class StoryNode
{
private:
    // Nodes for the directions
    StoryNode *north;
    StoryNode *south;
    StoryNode *east;
    StoryNode *west;

public:
    StoryNode()
    {
        north = nullptr;
        south = nullptr;
        west = nullptr;
        east = nullptr;
    }
    ~StoryNode();

public:
    StoryNode *moveDirection(const string &direction);
    void getMoveDirection();
    // Functions for binding the directions
    void bindStoryNorth(StoryNode *n);
    void bindStorySouth(StoryNode *s);
    void bindStoryEast(StoryNode *e);
    void bindStoryWest(StoryNode *w);

    void unbindStoryWest();

    // Strings that can be appended to the location nodes
    string mainDescription;
    string name;
    string characterAppearance;
    string firstSpeakingLine;
    string secondSpeakingLine;
    string objectName;
    bool visited = false;

    void markVisited()
    {
        visited = true;
    }
    bool isVisited() const
    {
        return visited;
    }
};
#endif