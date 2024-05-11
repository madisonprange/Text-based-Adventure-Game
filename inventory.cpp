
#include "inventory.h"

void Inventory::addItem(const string &item)
{

    if (inventory.size() >= 4) // Modified condition to prevent adding more than 4 items
    {
        cout << "Your inventory is full. This could not be added." << endl;
        return;
    }

    if (!hasItem(item))
    {
        inventory.push_back(item);
        cout << item << " added to inventory." << endl;
    }
    else
    {
        cout << "You already have this item in your inventory." << endl;
    }
}

void Inventory::removeItem(const string &item)
{
    auto it = find(inventory.begin(), inventory.end(), item);
    if (it != inventory.end())
    {
        inventory.erase(it);
        cout << item << " removed from inventory." << endl;
    }
    else
    {
        cout << "This item could not be found in your inventory." << endl;
    }
}

// Check to see if the item is in inventory
bool Inventory::hasItem(const string &item) const
{
    return find(inventory.begin(), inventory.end(), item) != inventory.end();
}

// Checking for "Wonderful Winner" Case
bool Inventory::hasItems(const string &item1, const string &item2) const
{
    return (find(inventory.begin(), inventory.end(), item1) != inventory.end() &&
            find(inventory.begin(), inventory.end(), item2) != inventory.end());
}

void Inventory::display() const
{
    int vecsize = inventory.size();
    cout << endl;
    cout << "---------------------Inventory---------------------" << endl;
    int count = 1;
    for (const auto &item : inventory)
    {
        cout << count << ". " << item << endl;
        count++;
    }
    cout << endl
         << "You have " << vecsize << "/"
         << "4"
         << " items in your inventory." << endl;
    cout << "---------------------------------------------------" << endl;
}

void Inventory::addItemStored(const string &item)
{ // Adding to safe room inventory
    if (hasItem(item))
    {
        storedInventory.push_back(item);
        removeItem(item);
        // Display both inventories
        displayStored();
        display();
        cout << item << " added to safe room inventory." << endl;
    }

    else
    {
        cout << "You do not have this item in your inventory" << endl;
    }
}

void Inventory::removeItemStored(const string &item)
{ // Removing objects from safe room inventory
    auto it = find(storedInventory.begin(), storedInventory.end(), item);
    if (it != storedInventory.end())
    {
        storedInventory.erase(it);
        cout << item << " removed from inventory." << endl;
        addItem(item); // Add to regular inventory
        displayStored();
        display();
    }
    else
    {
        cout << "This item could not be found in your safe room inventory." << endl;
    }
}

void Inventory::displayStored() const
{
    cout << endl;
    cout << "---------------------SAFE ROOM Inventory---------------------" << endl;
    int count = 1;
    for (const auto &item : storedInventory)
    {
        cout << count << ". " << item << endl;
        count++;
    }
    cout << "---------------------------------------------------" << endl;
}
