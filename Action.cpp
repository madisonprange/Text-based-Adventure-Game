#include "Action.h"

Action::Action(Characters::Alice *alice, Inventory *inventory)
{
    this->alice = alice;
    this->inventory = inventory;
}
// Default destructor
Action::~Action() {}

string Action::handleDirection(const string &destination)
{

    if (destination == "n" || destination == "north")
    {
        return "north";
    }
    else if (destination == "s" || destination == "south")
    {
        return "south";
    }
    else if (destination == "e" || destination == "east")
    {
        return "east";
    }
    else if (destination == "w" || destination == "west")
    {
        return "west";
    }
    else
    {
        cout << "Invalid action. Please enter a valid action." << endl;
        return "";
    }
}

void Action::handlePickUp(const string &object)
{

    if (object == "shovel")
    {
        if (alice->getNode()->name == "safe room")
        {
            inventory->removeItemStored(object); // Remove the item from the safe room
        }
        else
        {
            if (!alice->gethasusedshovel())
            {
                if (alice->getNode()->name == "shovel location")
                {
                    inventory->addItem(object);
                    inventory->display();
                    alice->sethaspickedshovel(true);
                }
                else
                {
                    cout << "This item does not exist here." << endl;
                }
            }
            else
            {
                cout << "This item no longer exists here." << endl;
            }
        }
    }

    else if (object == "blanket")
    {
        if (alice->getNode()->name == "safe room")
        {
            inventory->removeItemStored(object);
        }
        else
        {
            if (!alice->gethasusedblanket())
            {
                if (alice->getNode()->name == "house location")
                {
                    alice->sethaspickedblanket(true);
                    inventory->addItem(object);
                    inventory->display();
                }
                else
                {
                    cout << "This item does not exist here." << endl;
                }
            }
            else
            {
                cout << "This item no longer exists here." << endl;
            }
        }
    }

    else if (object == "potion")
    {

        if (!alice->getHasEatenPotion())
        {
            if (alice->getNode()->name == "Potion and cake")
            {
                alice->sethaspickedpotion(true);
                inventory->addItem(object);
                inventory->display();
            }
            else
            {
                cout << "This item does not exist here." << endl;
            }
        }
        else
        {
            cout << "This object no longer exists." << endl;
        }
    }
    else if (object == "cake")
    {
        if (!alice->gethasEatenCake())
        {
            if (alice->getNode()->name == "Potion and cake")
            {
                if (alice->getisSmall())
                {
                    inventory->addItem(object);
                    inventory->display();
                    alice->sethaspickedcake(true);
                }
                else
                {
                    cout << "You are not the right size to pick up this item." << endl;
                }
            }
            else
            {
                cout << "This item does not exist here.";
            }
        }
        else
        {
            cout << "This item no longer exists." << endl;
        }
    }
    else if (object == "fan")
    {
        if (!alice->gethasusedfan())
        {
            if (alice->getNode()->name == "Rabbit appearance in rabbit hole")
            {
                if (alice->gethasEatenCake())
                {
                    inventory->addItem(object);
                    inventory->display();
                    alice->sethaspickedfan(true);
                }
                else
                {
                    cout << "Action not permitted." << endl;
                }
            }
            else
            {
                cout << "This item does not exist here." << endl;
            }
        }
        else
        {
            cout << "You cannot use this item. " << endl;
        }
    }
    else if (object == "water")
    {
        if (alice->getNode()->name == "safe room")
        {
            inventory->removeItemStored(object);
        }
        else
        {
            if (!alice->gethasusedwater())
            {
                if (alice->getNode()->name == "forest waterbottle" || alice->getNode()->name == "Rabbithouse kitchen")
                {
                    alice->sethaspickedwater(true);
                    inventory->addItem(object);
                    inventory->display();
                }
                else
                {
                    cout << "This item does not exist here." << endl;
                }
            }
            else
            {
                cout << "You have already used this item." << endl;
            }
        }
    }
    else if (object == "plush")
    {
        if (alice->getNode()->name == "safe room")
        {
            inventory->removeItemStored(object);
        }
        else
        {
            if (alice->getNode()->name == "Rabbithouse room")
            {
                alice->sethaspickedupplush(true);
                inventory->addItem(object);
                inventory->display();
            }
            else
            {
                cout << "This item does not exist here." << endl;
            }
        }
    }
    else if (object == "mushroom")
    {
        if (alice->getNode()->name == "safe room")
        {
            inventory->removeItemStored(object);
        }
        else
        {
            if (alice->gethaspickedmushroom())
            {
                cout << "You don't follow the rules, the caterpillar gets mad and you lose the game!" << endl;
                exit(0);
            }
            else
            {
                if (alice->getNode()->name == "caterpillar start")
                {
                    alice->sethaspickedmushroom(true);
                    inventory->addItem(object);
                    inventory->display();
                }
                else
                {
                    cout << "This item does not exist here." << endl;
                }
            }
        }
    }
    else if (object == "key")
    {
        if (alice->getNode()->name == "safe room")
        {
            inventory->removeItemStored(object);
        }
        else
        {
            if (!alice->gethasusedkey())
            {
                if (alice->getNode()->name == "garden party")
                {
                    alice->sethaspickedkey(true);
                    inventory->addItem(object);
                    inventory->display();
                }
                else
                {
                    cout << "This item does not exist here." << endl;
                }
            }
            else
            {
                cout << "This cannot be done." << endl;
            }
        }
    }
    else if (object == "cup")
    {
        if (alice->getNode()->name == "safe room")
        {
            inventory->removeItemStored(object);
        }
        if (alice->getNode()->name == "garden cup")
        {
            inventory->addItem(object);
            inventory->display();
            alice->sethaspickedcup(true);
        }
        else
        {
            cout << "This item does not exist here." << endl;
        }
    }
    else
    {
        cout << "This is not a valid item." << endl;
    }
}

void Action::handleObjects(const string &object)
{
    if (object == "blanket")
    {
        if (inventory->hasItem(object))
        {
            if (alice->getNode()->name == "hole garden")
            {
                Blanket blanket;
                blanket.action();
                inventory->removeItem(object);
                alice->aliceHealth(+2);
                alice->getCurrentHealth();
            }
            else
            {
                cout << "You cannot do this here." << endl;
            }
        }
        else
        {
            cout << "You do not have this item." << endl;
        }
    }
    else if (object == "shovel")
    {
        if (inventory->hasItem(object))
        {
            if (alice->getNode()->name == "hole start")
            {
                Shovel shovel;
                shovel.action();
                inventory->removeItem(object);
                alice->aliceHealth(-1);
                alice->getCurrentHealth();
            }
            else
            {
                cout << "You cannot do this here." << endl;
            }
        }
        else
        {
            cout << "You do not have this item." << endl;
        }
    }

    else if (object == "potion")
    {
        if (alice->getNode()->name == "Potion and cake")
        {

            if (inventory->hasItem(object))
            {

                Potion potion;
                potion.action(); 
                alice->setisSmall(true);
                alice->aliceHealth(+1);
                alice->getCurrentHealth();
                inventory->removeItem(object);
                alice->setHasEatenPotion(true);
            }
            else
            {
                cout << "You do not have this item." << endl;
            }
        }
        else
        {
            cout << "You cannot do this here." << endl;
        }
    }
    else if (object == "cake")
    {
        if (alice->getisSmall())
        {
            if (inventory->hasItem(object))
            {
                if (alice->getNode()->name == "Potion and cake")
                {
                    alice->setHasEatenCake(true);
                    alice->setisSmall(false);
                    Cake cake;
                    cake.action();
                    inventory->removeItem(object);
                    cout << "You notice a loud noise coming from the east part of the hole." << endl;
                }
                else
                {
                    cout << "You cannot do this here." << endl;
                }
            }
            else
            {
                cout << "You have not picked up this item." << endl;
            }
        }
        else
        {
            cout << "You are not the right size to pick up this item." << endl;
        }
    }
    else if (object == "fan")
    {
        if (inventory->hasItem(object))
        {
            if (alice->gethasEatenCake())
            {
                if (alice->getNode()->name == "hole start" ||
                    alice->getNode()->name == "hole garden" ||
                    alice->getNode()->name == "Rabbit appearance in rabbit hole" ||
                    alice->getNode()->name == "Potion and cake")
                {
                    alice->sethasusedFan(true);
                    inventory->removeItem(object);
                    Fan fan;
                    fan.action();
                }
                else
                {
                    cout << "You cannot do this here." << endl;
                }
            }
            else
            {
                cout << "This item does not exist." << endl;
            }
        }
        else
        {
            cout << "You do not have this item." << endl;
        }
    }
    else if (object == "water")
    {
        if (inventory->hasItem(object))
        {
            waterBottle waterbottle;
            waterbottle.action();
            inventory->removeItem(object);
            alice->aliceHealth(+1);
            alice->getCurrentHealth();
        }
    }
    else if (object == "mushroom")
    {
        if (inventory->hasItem(object))
        {
            if (alice->getNode()->name == "caterpillar start")
            {
                alice->sethasusedmushroom(true);
                Mushroom mushroom;
                mushroom.action();
                inventory->removeItem(object);
                cout << "The magic mushroom does have health side effects.." << endl;
                alice->aliceHealth(-2);
                alice->getCurrentHealth();
            }
            else
            {
                cout << "You cannot do this action here." << endl;
            }
        }
        else
        {
            cout << "This item does not exist here." << endl;
        }
    }
    else if (object == "key")
    {
        if (inventory->hasItem(object))
        {
            if (alice->getNode()->name == "garden party")
            {
                alice->sethasusedkey(true);
                inventory->removeItem(object);
                gardenKey key;
                key.action();
            }
            else
            {
                cout << "You cannot do this here." << endl;
            }
        }
        else
        {
            cout << "You do not have this item." << endl;
        }
    }
    else {
        cout<< "This is invalid." <<endl;
    }
}

void Action::handleDropping(const string &object)
{
    // Check if Alice is in the safe room
    if (alice->getNode()->name == "safe room")
    {
        // Add the object to the safe room's inventory
        inventory->addItemStored(object);
    }
    else
    {

        // Remove the object from the player's inventory
        inventory->removeItem(object);

        // Display the updated inventory
        inventory->display();

        // If dropped object, ensure that the flag is also switched so user can pick up object again

        if (object == "blanket")
        {
            alice->sethaspickedblanket(false);
        }
        if (object == "shovel")
        {
            alice->sethaspickedshovel(false);
        }
        if (object == "potion")
        {
            alice->sethaspickedpotion(false);
        }
        if (object == "cake")
        {
            alice->sethaspickedcake(false);
        }
        if (object == "fan")
        {
            alice->sethaspickedfan(false);
        }
        if (object == "water")
        {
            alice->sethaspickedwater(false);
        }
        if (object == "plush")
        {
            alice->sethaspickedupplush(false);
        }
        if (object == "mushroom")
        {
            alice->sethaspickedmushroom(false);
        }
        if (object == "key")
        {
            alice->sethaspickedkey(false);
        }
        if (object == "cup")
        {
            alice->sethaspickedcup(false);
        }
    }
}

void Action::displayList(const string &object)
{
    if (object == "inventory")
    {
        inventory->display();
    }
    else if (object == "health")
    {
        alice->getCurrentHealth();
    }
    else
    {
        cout << "You cannot display this." << endl;
    }
}