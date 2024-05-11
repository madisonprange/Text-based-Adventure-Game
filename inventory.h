// inventory header file
#ifndef INVENTORY_H
#define INVENTORY_H

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Inventory
{
private:
    vector<string> inventory;
    vector<string> storedInventory;

public:
    Inventory() : inventory(), storedInventory() {}

    ~Inventory() {}

    // For "regular" inventory
    void addItem(const string &item);
    void removeItem(const string &item);
    bool hasItem(const string &item) const;
    void display() const;

    // For "safe room" inventory
    void addItemStored(const string &item);
    void removeItemStored(const string &item);
    void displayStored() const;

    bool hasItems(const string &item1, const string &item2) const;
};

#endif
