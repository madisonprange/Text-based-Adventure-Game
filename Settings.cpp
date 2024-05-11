#include "Settings.h"

bool Settings::readDescriptionFromFileSetting(map<string, StoryNode *> &storyMap)
{
    string filename = "settings.txt";
    ifstream file(filename);
    if (file.is_open())
    {
        
        string line;
        string currentSetting;
        int Counter = 0;

        while (getline(file, line))
        {
            if (Counter++ % 2 == 0) //Every even line(every other one)
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
                it->second->mainDescription = line;
            }
        }
        file.close();
        return true;
    }
    else
    {
        cout << "Unable to open "<< filename << endl;
        return false;
    }
}
