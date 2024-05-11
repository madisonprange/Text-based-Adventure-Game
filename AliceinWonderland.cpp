#include "AliceinWonderland.h"

StoryNode *AliceinWonderland::buildMap()
{
    // Create nodes for the overworld
    StoryNode *overworld_Start = new StoryNode();
    storyMap.insert({"FIELD", overworld_Start});

    StoryNode *overworld_Shovel = new StoryNode();
    overworld_Shovel->name = "shovel location";
    storyMap.insert({"OVERWORLD_SHOVEL", overworld_Shovel});

    StoryNode *overworld_House = new StoryNode();
    overworld_House->name = "house location";
    storyMap.insert({"OVERWORLD_HOUSE", overworld_House});

    StoryNode *overworld_Field = new StoryNode();
    overworld_Field->name = "field location";
    storyMap.insert({"OVERWORLD_NOTHING", overworld_Field});

    // Connect nodes in the overworld
    overworld_Start->bindStoryNorth(overworld_House);
    overworld_Start->bindStoryEast(overworld_Field);
    overworld_Start->bindStoryWest(overworld_Shovel);

    // Create nodes for the hole
    hole_Start = new StoryNode();

    overworld_Start->bindStorySouth(hole_Start);
    hole_Start->name = "hole start";
    storyMap.insert({"HOLE_START", hole_Start});

    StoryNode *hole_PotionandCake = new StoryNode();
    hole_PotionandCake->name = "Potion and cake";
    storyMap.insert({"HOLE_POTION", hole_PotionandCake});

    hole_rabbit = new StoryNode();
    hole_rabbit->name = "Rabbit appearance in rabbit hole";
    storyMap.insert({"HOLE_RABBIT", hole_rabbit});

    hole_garden = new StoryNode();
    hole_garden->name = "hole garden";
    storyMap.insert({"HOLE_WEST", hole_garden});

    // Connect nodes in the hole
    hole_Start->bindStoryNorth(hole_PotionandCake);
    hole_Start->bindStoryEast(hole_rabbit);

    // Create nodes for Wonderland
    wonderland_Start = new StoryNode();

    wonderland_Start->name = "wonderland start";
    storyMap.insert({"WONDERLAND_START", wonderland_Start});

    // Create nodes for Rabbit House
    StoryNode *rabbithouse_start = new StoryNode();
    rabbithouse_start->name = "rabbit house";
    storyMap.insert({"RABBIT_START", rabbithouse_start});

    // Create nodes for Forest
    StoryNode *forest_start = new StoryNode();
    forest_start->name = "forest";
    storyMap.insert({"FOREST_START", forest_start});

    // Connect nodes in Wonderland
    wonderland_Start->bindStoryWest(forest_start);
    wonderland_Start->bindStoryEast(rabbithouse_start);

    StoryNode *rabbithouse_room = new StoryNode();
    rabbithouse_room->name = "Rabbithouse room";
    storyMap.insert({"RABBIT_ROOM", rabbithouse_room});

    StoryNode *rabbithouse_kitchen = new StoryNode();
    rabbithouse_kitchen->name = "Rabbithouse kitchen";
    storyMap.insert({"RABBIT_KITCHEN", rabbithouse_kitchen});

    // Connect nodes in Rabbit House
    rabbithouse_start->bindStorySouth(rabbithouse_room);
    rabbithouse_start->bindStoryEast(rabbithouse_kitchen);

    StoryNode *forest_waterbottle = new StoryNode();
    forest_waterbottle->name = "forest waterbottle";
    storyMap.insert({"FOREST_WATER", forest_waterbottle});

    // Connect nodes in Forest
    forest_start->bindStoryNorth(forest_waterbottle);

    caterpillar_start = new StoryNode;
    storyMap.insert({"CATERPILLAR_START", caterpillar_start});

    forest_start->bindStorySouth(caterpillar_start);

    caterpillar_start->name = "caterpillar start";

    forest_start->bindStorySouth(caterpillar_start);

    // Create nodes for Cat house
    cathouse_start = new StoryNode;
    cathouse_start->name = "cat house";
    storyMap.insert({"CAT_START", cathouse_start});

    StoryNode *safeRoom = new StoryNode;
    safeRoom->name = "safe room";
    storyMap.insert({"SAFEROOM", safeRoom});

    // Connect nodes in Cat house
    cathouse_start->bindStoryWest(safeRoom);

    gardenparty = new StoryNode;
    gardenparty->name = "garden party";
    storyMap.insert({"GARDEN_START", gardenparty});

    cathouse_start->bindStoryEast(gardenparty);

    // Create nodes for Garden Party
    StoryNode *gardenparty_cup = new StoryNode;
    gardenparty_cup->name = "garden party cup";
    storyMap.insert({"GARDEN_CUP", gardenparty_cup});

    // Connect nodes in Garden Party
    gardenparty->bindStoryEast(gardenparty_cup);

    // Create nodes for Queen Match
    queenmatch_start = new StoryNode;
    queenmatch_start->name = "queen match";
    storyMap.insert({"MATCH_START", queenmatch_start});
    cout << queenmatch_start->characterAppearance;

    // Create nodes for Castle
    StoryNode *castle_start = new StoryNode;
    storyMap.insert({"CASTLE_START", castle_start});

    // Connect nodes in Castle
    queenmatch_start->bindStorySouth(castle_start);

    StoryNode *fake_crown = new StoryNode;
    storyMap.insert({"CASTLE_WRONG", fake_crown});

    castle_start->bindStoryWest(fake_crown);

    StoryNode *real_crown = new StoryNode;
    storyMap.insert({"CASTLE_RIGHT", real_crown});

    castle_start->bindStoryEast(real_crown);

    // Load files as game starts
    Settings::readDescriptionFromFileSetting(storyMap);
    Characters::readDescriptionFromFileCharacter(storyMap);
    Items::readDescriptionFromFileItems(storyMap);
    Control::initializeFromFile();

    return overworld_Start; // Return the starting node of the map
}

void AliceinWonderland::run()
{

    int start = gameStart();
    if (start == 1)
    {

        Inventory inventory;
        Control control(alice, &inventory);

        gameGoal();
        alice->setNode(buildMap());
        cout << alice->getNode()->mainDescription << endl;
        cout << alice->getNode()->characterAppearance << endl;
        cout << alice->getNode()->firstSpeakingLine << endl;
        alice->getNode()->markVisited();

        bool GameRunning = true;
        while (GameRunning)
        {

            StoryNode *direction = alice->getNode();
            direction->getMoveDirection();
            pair<int, string> actionResult = control.actionCall();

            int actionType = actionResult.first;        // Extract the action type from the result
            string actionDetails = actionResult.second; // Extract the action details from the result

            switch (actionType)
            {
            case 1:
            {
                StoryNode *next = direction->moveDirection(actionDetails);
                if (next == nullptr)
                {
                    cout << "You can't go that way." << endl;
                    break;
                }
                if (next->isVisited()) // If location has already been visited
                {
                    cout << "------------------------------" << endl;
                    cout << "Welcome back to this location!" << endl;
                    cout << "------------------------------" << endl;

                    if (next->name == "shovel location")
                    {
                        cout << next->mainDescription;
                        if (!alice->gethaspickedshovel())
                        {
                            cout << next->objectName;
                        }
                        alice->setNode(next);
                    }
                    else if (next->name == "house location")
                    {
                        cout << next->mainDescription;
                        if (!alice->gethaspickeblanket())
                        {
                            cout << next->objectName;
                        }
                        alice->setNode(next);
                    }
                    else if (next->name == "Potion and cake")
                    {
                        cout << next->mainDescription;
                        if (!alice->gethaspickedpotion())
                        {
                            cout << next->objectName;
                        }
                        alice->setNode(next);
                    }
                    else if (next->name == "Rabbit appearance in rabbit hole")
                    {
                        cout << next->mainDescription;
                        cout << next->characterAppearance;
                        if (!alice->gethaspickedfan())
                        {
                            if (alice->gethasEatenCake())
                            {
                                cout << next->secondSpeakingLine;
                                cout << next->objectName;
                            }
                        }
                        alice->setNode(next);
                    }
                    else if (next->name == "rabbit kitchen")
                    {
                        cout << next->mainDescription;
                        if (!alice->gethaspickedwater())
                        {
                            cout << next->objectName;
                        }
                        alice->setNode(next);
                    }
                    else if (next->name == "rabbit room")
                    {
                        cout << next->mainDescription;
                        if (!alice->gethaspickedplush())
                        {
                            cout << next->objectName;
                        }
                        alice->setNode(next);
                    }
                    else if (next->name == "caterpillar start")
                    {
                        cout << next->mainDescription;
                        if (!alice->gethaspickedmushroom())
                        {
                            cout << next->objectName;
                        }
                        else if (alice->gethaspickedmushroom())
                        {
                            cout << next->objectName;
                            cout << next->secondSpeakingLine;
                        }
                    }
                    else if (next->name == "garden party cup")
                    {
                        cout << next->mainDescription;
                        if (!alice->gethaspickedcup())
                        {
                            cout << next->objectName;
                        }
                    }
                    else if (next->name == "garden party")
                    {
                        cout << next->mainDescription;
                        if (!alice->gethaspickedkey())
                        {
                            cout << next->secondSpeakingLine;
                            cout << next->objectName;
                        }
                    }
                    else if (next->name == "forest waterbottle" || next->name == "rabbit kitchen")
                    {
                        cout << next->mainDescription;
                        if (!alice->gethaspickedwater())
                        {
                            cout << next->objectName;
                        }
                    }

                    else
                    {
                        cout << "Here is the description again in case you forgot: " << '\n'
                             << next->mainDescription;
                    }
                    alice->setNode(next);
                }
                else
                {
                    if (next->name == "hole start")
                    {
                        cout << "As you took a hit while falling down the rabbit hole, you lose health." << endl;
                        alice->aliceHealth(-2);
                        alice->getCurrentHealth();
                        cout << next->mainDescription;
                    }
                    else if (next->name == "Rabbit appearance in rabbit hole")
                    {
                        if (alice->gethasEatenCake())
                        {
                            cout << next->secondSpeakingLine;
                            cout << next->objectName;
                        }
                        else
                        {
                            cout << next->mainDescription;
                            cout << next->characterAppearance;
                        }
                    }
                    else if (next->name == "garden party")
                    {
                        cout << next->mainDescription;
                        cout << next->characterAppearance;
                        cout << next->firstSpeakingLine;
                        cout << next->secondSpeakingLine;
                        cout << next->objectName;
                        cout << "As you have been travelling on your feet all this time, you begin to feel tired." << endl;
                        alice->aliceHealth(-1);
                        alice->getCurrentHealth();
                    }
                    else if (next->name == "caterpillar start")
                    {
                        cout << next->mainDescription;
                        cout << next->characterAppearance;
                        cout << next->firstSpeakingLine;
                        cout << next->secondSpeakingLine;
                        cout << next->objectName;
                    }
                    else if (next->name == "queen match")
                    {
                        cout << next->mainDescription;
                        cout << next->characterAppearance;
                        cout << next->firstSpeakingLine;
                        cout << next->secondSpeakingLine;
                    }
                    else
                    {
                        cout << next->mainDescription << endl;
                        cout << next->characterAppearance << endl;
                        cout << next->firstSpeakingLine << endl;
                        cout << next->objectName << endl;
                    }
                    next->markVisited(); // Mark the node as visited
                    alice->setNode(next);
                }
                break;
            }

            case 2: // Binding to Garden case
                if (alice->getisSmall())
                {
                    hole_Start->bindStoryWest(hole_garden);
                }
                break;

            case 3: // Cake case
            {

                hole_Start->unbindStoryWest(); // Can no longer go to the garden- has eaten cake and grown
                break;
            }

            case 4:
                if (alice->gethasusedfan())
                {
                    hole_Start->bindStorySouth(wonderland_Start); // After fan was used, bind hole to the south
                }

            case 5: // Mushroom case
                if (alice->gethasusedmushroom())
                {
                    caterpillar_start->bindStorySouth(cathouse_start);
                }

                break;

            case 6: // Key case
                if (alice->gethasusedkey())
                {
                    gardenparty->bindStorySouth(queenmatch_start);
                }
                else
                {
                    cout << "You can't unlock the door until you use the key." << endl;
                }
                break;

            case 7: // Lose case
                cout << "You picked up the wrong crown, and have lost the game. Better luck next time!" << endl;
                GameRunning = false;
                break;

            case 8: // Win case
                if (alice->getCurrentHealth() > 4)
                {
                    cout << "You have picked up the right crown! Congratulations!" << endl;
                    cout << "You have been declared a winner." << endl;
                    if (inventory.hasItems("plush", "cup"))
                    {
                        cout << "Both special items are in your inventory, and you have been declared a Wonderful Winner! Congratulations!" << endl;
                    }
                    else
                    {
                        cout << "You are missing the two special items in your inventory, or else you would have been declared a Wonderful Winner." << endl;
                    }

                    GameRunning = false;
                }
                else
                {
                    cout << "Your health levels are not high enough to leave Wonderland, and the strength of the crown strikes you, and you have lost the game." << endl;
                    cout << "Better luck next time!" << endl;
                    GameRunning = false;
                }
            default:
                break;
            }
        }
    }
}

int AliceinWonderland::gameStart()
{
    char userInput;
    cout << "----------------------------------- WELCOME TO THE ALICE IN WONDERLAND GAME-----------------------------------" << endl;
    cout << "Would you like to play? (Y/N): ";
    cin >> userInput;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while (userInput != 'Y' && userInput != 'N' && userInput != 'n' && userInput != 'y')
    {
        cout << "Would you like to play? (Y/N): ";
        cin >> userInput;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (userInput == 'N' || userInput == 'n')
    {
        return -1; // End the program
    }

    if (userInput == 'Y' || userInput == 'y')
    {
        return 1; // Start the game
    }
    return 0;
}

void AliceinWonderland::gameGoal()
{
    cout << "Welcome to the Alice in Wonderland Game! You are playing the character Alice. The goal of this game is to escape Wonderland. This means that you must survive " << endl
         << "until the very end and make the right choices. You are going to be exploring a large map, with many different rooms, objects, and characters. Interact with these" << '\n'
         << " elements carefully, as their can be consequences. Pay close attention to your health levels, as consuming certain items and going to certain locations can lower them. However, don't threat!" << '\n'
         << "You can pick up and use objects to raise your health. "
            "You can only hold 4 items at a time. You can either drop or use the items to lose them from inventory. You may also display your health and inventory at any time. There is a safe room further in the game that you can use to store these items if needed."
         << endl
         << " Listen closely to characters and their helpful advice. Good luck playing! "
         << endl;
    cout << "You can quit the game at any time by typing quit." << endl;
    cout << "-------------------------------------------------GAME START-------------------------------------------------" << endl
         << endl;
}

int AliceinWonderland::main()
{
    Characters::Alice alice;
    AliceinWonderland alicegame(&alice);
    alicegame.run();
    return 0;
}
