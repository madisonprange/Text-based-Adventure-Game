#include "Items.h"

using namespace std;

void Shovel::action()
{
    cout << "You try to dig, but fail. Your shovel broke in the process and it is lost from inventory." << endl;
}

void Blanket::action()
{
    cout << "You take a nap to boost energy levels. After your nap, the blanket becomes dirty so you throw it away." << endl;
}

void Potion::action()
{
    cout << "You drink the liquid and become very tiny. You cannot stay like this to survive!" << endl;
}

void Cake::action()
{
    cout << "You eat the cake and grow VERY LARGE! How will you ever leave the hole?" << endl;
}

void Fan::action()
{
    cout << "You use the fan, and notice that it shrinks you back down to a very small figure. You throw away the fan once you are done." << endl;
}

void waterBottle::action()
{
    cout << "You drink from the watter bottle.You finish the water so you can no longer use it." << endl;
}

void Mushroom ::action()
{
    cout << "You eat the mushroom, and immediately grow back to your normal size! You eat the whole piece." << endl;
}

void gardenKey::action()
{
    cout << "You use the key to unlock the door. It vanishes right after you use it." << endl;
}

bool Items::readDescriptionFromFileItems(map<string, StoryNode *> &storyMap)
{
    string filename ="items.txt";
    ifstream file(filename);
    if (file.is_open())
    {
        string line;
        string currentSetting;

        int Counter = 0;

        while (getline(file, line))
        {
            if (Counter++ % 2 == 0)
            {
                currentSetting = line;
            }
            else
            {
                auto it = storyMap.find(currentSetting);
                if (it == storyMap.end())
                {
                    continue;
                }
                it->second->objectName = line;
            }
        }
        file.close();
        return true;
    }
    else
    {
        cout << "Unable to open " << filename << endl;
        return false;
    }
}