#include "Control.h"

Control::~Control()
{
    delete action;
}

unordered_set<string> Control::wordsInFile;

Control::Control(Characters::Alice *alice, Inventory *inventory)
{
    action = new Action(alice, inventory);
}

pair<int, string> Control::actionCall()
{
    string userInput;

    cout << "Enter your next action> ";
    getline(cin, userInput);
    transform(userInput.begin(), userInput.end(), userInput.begin(), ::tolower);

    istringstream iss(userInput);
    string firstWord;
    iss >> firstWord;

    // File check
    if (!checkWordInFile(firstWord))
    {
        cout << "Invalid action word." << endl;
        return {0, ""}; // Return error code and empty string
    }
    else
    {
        int actionType = 0;
        string actionDetails;

        if (firstWord == "n" || firstWord == "w" || firstWord == "e" || firstWord == "s" || firstWord == "north" || firstWord == "east" || firstWord == "south" || firstWord == "west")
        {
            actionDetails = action->handleDirection(firstWord);
            actionType = 1;
        }
        else if (firstWord == "quit")
        {
            exit(0);
        }

        else if (userInput.find("go") != string::npos)
        {
            string destination;
            stringstream ss(userInput);
            ss >> userInput >> destination;
            actionDetails = action->handleDirection(destination);
            actionType = 1;
        }
        else if (userInput.find("use") != string::npos)
        {
            string object;
            stringstream ss(userInput);
            ss >> userInput >> object;
            action->handleObjects(object);
            if (object == "potion")
            {
                actionType = 2;
            }
            else if (object == "fan")
            {
                actionType = 4;
            }
            else if (object == "cake")
            {
                actionType = 3;
            }
            else if (object == "mushroom")
            {
                actionType = 5;
            }
            else if (object == "key")
            {
                actionType = 6;
            }
        }
        else if (userInput.find("drop") != string::npos)
        {
            string object;
            stringstream ss(userInput);
            ss >> userInput >> object;
            action->handleDropping(object);
        }
        else if (userInput.find("pick up") != string::npos)
        {
            string object;
            stringstream ss(userInput);
            ss >> userInput >> userInput >> object;
            action->handlePickUp(object);
            if (object == "tiara")
            {
                actionType = 7;
            }
            else if (object == "crown")
            {
                actionType = 8;
            }
        }
        else if (userInput.find("display") != string::npos)
        {
            string object;
            stringstream ss(userInput);
            ss >> userInput >> object;
            action->displayList(object);
        }
        else
        {
            // Invalid input
            cout << "Invalid action. Please enter a valid action." << endl;
            return make_pair(0, ""); // Return default action
        }

        return make_pair(actionType, actionDetails);
    }
}
