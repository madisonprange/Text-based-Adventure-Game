#ifndef CHARACTERS_H
#define CHARACTERS_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "StoryNode.h"
#include <map>
using namespace std;

class Characters
{

public:
    static bool readDescriptionFromFileCharacter(map<string, StoryNode *> &storyMap);

    class Alice
    {
    private:
        StoryNode *node;
        int health;
        vector<string> inventory;
        bool haspickedpotion = false;
        bool haspickedcake = false;
        bool haspickedfan = false;
        bool hasDrankPotion = false;
        bool hasEatenCake = false;
        bool hasUsedFan = false;
        bool haspickedShovel = false;
        bool haspickedBlanket = false;
        bool isSmall = false;
        bool hasusedshovel = false;
        bool hasusedblanket = false;
        bool hasusedMushroom = false;
        bool hasUsedKey = false;
        bool haspickedmushroom = false;
        bool haspickedupwater = false;
        bool hasusedwater = false;
        bool haspickedupplush = false;
        bool haspickedupcup = false;
        bool haspickedupkey = false;

    public:
        Alice();
        ~Alice()
        {
            delete node;
        }
        Alice(StoryNode *start);
        void aliceHealth(int healthChange);
        int getCurrentHealth() const;
        void setNode(StoryNode *n)
        {
            if (n != nullptr)
            {
                node = n;
            }
        }

        StoryNode *getNode()
        {
            if (node != nullptr)
            {
                return node;
            }
            else
            {
                return nullptr;
            }
        }
        bool getHasEatenPotion() const
        {
            return hasDrankPotion;
        }
        void setHasEatenPotion(bool value)
        {
            hasDrankPotion = value;
        }

        bool gethasEatenCake() const
        {
            return hasEatenCake;
        }
        void setHasEatenCake(bool value)
        {
            hasEatenCake = value;
        }
        bool gethasusedfan() const
        {
            return hasUsedFan;
        }
        void sethasusedFan(bool value)
        {
            hasUsedFan = value;
        }
        bool gethaspickedshovel() const
        {
            return haspickedShovel;
        }
        void sethaspickedshovel(bool value)
        {
            haspickedShovel = value;
        }
        bool gethaspickeblanket() const
        {
            return haspickedBlanket;
        }
        void sethaspickedblanket(bool value)
        {
            haspickedBlanket = value;
        }
        bool gethasusedshovel() const
        {
            return hasusedshovel;
        }
        void sethasusedshovel(bool value)
        {
            hasusedshovel = value;
        }

        bool gethasusedblanket() const
        {
            return hasusedblanket;
        }
        void sethasusedblanket(bool value)
        {
            hasusedblanket = value;
        }

        bool getisSmall() const
        {
            return isSmall;
        }
        void setisSmall(bool value)
        {
            isSmall = value;
        }
        void sethaspickedfan(bool value)
        {
            haspickedfan = value;
        }
        bool gethaspickedfan() const
        {
            return haspickedfan;
        }
        void sethaspickedpotion(bool value)
        {
            haspickedpotion = value;
        }
        bool gethaspickedpotion() const
        {
            return haspickedpotion;
        }
        void sethaspickedcake(bool value)
        {
            haspickedcake = value;
        }
        bool gethaspickedcake() const
        {
            return haspickedcake;
        }
        void sethasusedmushroom(bool value)
        {
            hasusedMushroom = value;
        }
        bool gethasusedmushroom() const
        {
            return hasusedMushroom;
        }
        bool gethasusedkey() const
        {
            return hasUsedKey;
        }
        void sethasusedkey(bool value)
        {
            hasUsedKey = value;
        }
        void sethaspickedmushroom(bool value)
        {
            haspickedmushroom = value;
        }
        bool gethaspickedmushroom() const
        {
            return haspickedmushroom;
        }
        void sethaspickedwater(bool value)
        {
            haspickedupwater = value;
        }
        bool gethaspickedwater() const
        {
            return haspickedupwater;
        }
        void sethaspickedupplush(bool value)
        {
            haspickedupplush = value;
        }
        bool gethaspickedplush() const
        {
            return haspickedupplush;
        }
        void sethaspickedcup(bool value)
        {
            haspickedupcup = value;
        }
        bool gethaspickedcup() const
        {
            return haspickedupcup;
        }
        void sethaspickedkey(bool value)
        {
            haspickedupkey = value;
        }
        bool gethaspickedkey() const
        {
            return haspickedupkey;
        }
        void sethasusedwater(bool value)
        {
            hasusedwater = value;
        }
        bool gethasusedwater() const
        {
            return hasusedwater;
        }
    };
};

#endif
