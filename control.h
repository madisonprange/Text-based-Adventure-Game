#ifndef CONTROL_H
#define CONTROL_H

#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <limits>
#include <algorithm>
#include <unordered_set>
#include "Action.h"

class Control
{
private:
    Action *action;
    static unordered_set<string> wordsInFile;

public:
    ~Control();
    Control(Characters::Alice *alice, Inventory *inventory);
    pair<int, string> actionCall();

    static void initializeFromFile()
    {
        string filename = "actions.txt";
        ifstream file(filename);

        if (!file.is_open())
        {
            cout << "Unable to open " << filename << endl;
            return;
        }

        string line;
        while (getline(file, line))
        {
            Control::wordsInFile.insert(line);
        }

        file.close();
    }

    static bool checkWordInFile(const string &userInput)
    {
        return Control::wordsInFile.find(userInput) != Control::wordsInFile.end();
    }
};

#endif
