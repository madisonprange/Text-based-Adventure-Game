#include "Characters.h"

Characters::Alice::Alice() : health(8), node(nullptr) {} //Initalize health at 8

Characters::Alice::Alice(StoryNode *start) : node(start), health(8) {}

bool Characters::readDescriptionFromFileCharacter(map<string, StoryNode *> &storyMap)
{
    string filename ="characters.txt";
    ifstream file(filename);

    if (file.is_open())
    {
        string line;
        string desc;
        string line1;
        string line2;
        string name;
        int Counter = 0;
        while (getline(file, line))
        {
            int idx = Counter++ % 4;//4 Lines for each Node
            if (idx == 0)
            {
                auto it = storyMap.find(name);
                if (it != storyMap.end())
                {
                    it->second->characterAppearance = desc;
                    it->second->firstSpeakingLine = line1;
                    it->second->secondSpeakingLine = line2;
                }
                name = line;
            }
            else if (idx == 1)
            {
                desc = line;
            }
            else if (idx == 2)
            {
                line1 = line;
            }
            else if (idx == 3)
            {
                line2 = line;
            }
        }
        file.close();
        return true;
    }
    else
    {
        cout << "Unable to open "<< filename <<endl;
        return false;
    }
}

void Characters::Alice::aliceHealth(int healthChange)
{
    if (health <= 0)
    {
        cout << "Alice has lost all her health and the game is over." << endl;
        exit(0);
    }
    else
    {
        health += healthChange;
        if (health <= 0)
        {
            cout << "Alice has lost all her health and the game is over." << endl;
            exit(0);
        }
        else if (health >= 8)
        {
            cout << "Your health is full." << endl;
            health = 8;
        }
    }
}

int Characters::Alice::getCurrentHealth() const
{
    cout << "------------------Health------------------" << endl;
    cout << "Alice's current health is " << health << "/"<< "8" << endl;
    cout << "------------------------------------------" << endl;
    cout << endl;
    return health;
}
