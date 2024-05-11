//Assignment4.cpp

/*
 Title: Assignment4.cpp
 Description: This game is to be an adaptation of the book "Alice in Wonderland" written by Lewis Carroll.
 In this game, Alice, the main character, sees various scenes and characters, and can interact with them and with the items found in their vicinity.

 Date: April 21st 2024.
 Author: Madison Prange
 Student ID #3681548
 Version: 1.0
 Copyright: 2024 Madison Prange
 Parts of code used from:
 plasmacel from stack overflow: https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
 kaya3 from stack overflow: https://stackoverflow.com/questions/25020129/cin-ignorenumeric-limitsstreamsizemax-n
 Geeks for Geeks: https://www.geeksforgeeks.org/switch-statement-in-cpp/
 Geeks for Geeks:https://www.geeksforgeeks.org/pair-in-cpp-stl/
 devPtr: https://devptr.com/find-elements-in-a-vector-in-c-stl/#:~:text=To%20find%20an%20element%20in%20a%20vector%2C%20we,searching%20for.%20auto%20it%20%3D%20std%3A%3Afind%28start_iterator%2C%20end_iterator%2C%20value%29%3B
Code With C: https://www.codewithc.com/c-dictionary-like-python-creating-key-value-pairs/#google_vignette
Geeks for Geeks: https://www.geeksforgeeks.org/unordered_set-in-cpp-stl/
Geeks for Geeks: https://www.geeksforgeeks.org/given-linked-list-representation-of-complete-tree-convert-it-to-linked-representation/
*/

/*
 DOCUMENTATION
Program Purpose:
The purpose of this program is to write an interactive adventure game based on the book, "Alice in Wonderland". This program implements object-oriented programming to adapt the story, characters,
items, and settings from the book into this game. Handling user input correctly, managing inventory, and building + changing a map is implemented with careful detail to sucessfully create this game.
There is a minimum of 5 characters interacted with, 12 items that can be interacted with, at minimum 5 locations, with one having 3 exits. The goal for Alice is stated at the beginning of the game,
and the items, characters, location descriptions and action words are contained in seperate text files which are opened and loaded in order to build the map for the user.

 Compile: g++ aliceinwonderland.cpp characters.cpp control.cpp inventory.cpp action.cpp  items.cpp settings.cpp storynode.cpp Assignment4.cpp -o aliceinwonderland
 Execution: ./aliceinwonderland

 Classes
 Action: If an Action is allowed, then the methods in this class are called on the action involved.
 These methods are: handeDirection (handles actions for movement), handlePickUp (for handling user pick up), handleDropping (handle user dropping objects), handleObjects (for when the user uses the object).
 This class also has pointers to Alice and Inventory obejcts as these are manipualted frequently in this class, for health and inventory manipulation.
 AliceinWonderland: This is the highest class, it is the finished game. This class has a main method that creates an instance of the game and invokes it for game execution.
 Methods include builmap() which builds the map of the game. This is done through the use of StoryNode class, and also through loading the text files.
The run() method contains the while loop of the running game, where the storyline happens. In the run() function, a switch statement is used to control certain locations, and story line events.
A pointer to the Alice object is once again used, and a constructor sets all member nodes to null. A map is created under private to read from the text files and print them in the correct places in buildMap().
 Characters: This class is in charge of the character Alice (the main character), her health of type int, and getting + setting her current node.There is many bools created uner private that are set to false, as they are the picking up and using of each object.
 These bools also have corresponding to get and set methods used for checking in both Action and AliceinWonderland to complete the storyline. The destructor deletes the node created of type storyNode. There is also a method created to read from the text file
 and correctly append the text to the correct member variable of storyNode to build the map.
 Control: This class reads user input and checks the input against valid actions. These valid actions are validated by checking the action.txt file by using an unordered set member variable that stores the lines of the file, and then a method (initializeFile)  that is loaded when the game runs and creates this set.
 checkWordsinFile is used to validate user input. A pointer to the Action object is created under private.
 Objects: Child classes for most objects are created here to display their action which is an overloaded function. This action is printed in Action when the object is used.
 Method to read and print from text files correctly is created by creating a map.
 Inventory: This class is responsible for managing inventory and the Safe room's inventory, done through the Action class. The addItem method adds a new object to inventory, done through a vector declared as a member variable.
 removeItem removes the object from inventory. hasItem checks to see if that user already has this item in inventory. Display simply displays the inventory. The safe rooms inventory is mostly the exact same, used with a vector, but with opposite logic.
 Settings: This class is responsible for printing the descriptions of the locations. This is done through a method that reads from the file and print texts through a map.
 StoryNode: This class allows the user to traverse the map, by having methods to bind and unbind locations, creating storyNodes for each direction (north, south, west and east). This file also contains member variables for all the strings that are appended to the node
 (either through text file methods or straight from AliceinWonderland.)

Variables: This game uses a lot of variables. I have highlighted the most important ones below:
Destination: type string used in Action and Control when a direction action is identified from the user.
actionType: type int that declares which case it should go to in the AliceinWonderland switch statement. This is essential for story building. This is sent through a pair with actionDetails.
actionDetails: type string that stores either the desintation or object name that is then handled in the Action class passed through by Control. If needed, it is sent through a pair with actionType.
userInput: type string to get the input from the user: used in AliceinWonderland to start the game and also Control to identify the action.
node(s): all of type StoryNode. These are created several times in some of the classes. A StoryNode is created for each location. A node is created under Alice's class to get, set, and delete. This is used to see which node Alice is currently at.
bools in Alice: All of these bools are created for get and set methods that flag if all of the objects have been picked up, or in some cases, used. These checks are used in Action and AliceinWonderland.
health: type int created in Alice that is returned and altered based on health changes that she goes through.
inventory: type vector that stores Alice's inventory through Action and using pushback() for every object that is picked up. This is the same for storedInventory.
map: defines a map structure where the keys are of type string and the values are pointers to StoryNode objects. This is used in settings, objects, characters, and items to read and output from the file.

*/

/*
 TEST PLAN

 Normal case 1: Normal Game Run with no Bad Inputs
 ----------------------------------- WELCOME TO THE ALICE IN WONDERLAND GAME-----------------------------------
Would you like to play? (Y/N): y
Welcome to the Alice in Wonderland Game! You are playing the character Alice. The goal of this game is to escape Wonderland. This means that you must survive
until the very end and make the right choices. You are going to be exploring a large map, with many different rooms, objects, and characters. Interact with these
 elements carefully, as their can be consequences. Pay close attention to your health levels, as consuming certain items and going to certain locations can lower them. However, don't threat!
You can pick up and use objects to raise your health. You can only hold 4 items at a time. You can either drop or use the items to lose them from inventory. You may also display your health and inventory at any time. There is a safe room further in the game that you can use to store these items if needed.
 Listen closely to characters and their helpful advice. Good luck playing!
-------------------------------------------------GAME START-------------------------------------------------

You find yourself standing in a verdant open meadow. You shiver as the cool breeze sways the tall grass, and the leaves on the trees.
You see a White Rabbit wearing a waistcoat, carrying a pocket watch, and seemingly in a great hurry. He is running off to the south, about to jump into a rabbit hole.
Rabbit: "I am going to be late!"
You can go in the following directions:
You can go north.
You can go east.
You can go west.
You can go south.
Enter your next action> s
As you took a hit while falling down the rabbit hole, you lose health.
------------------Health------------------
Alice's current health is 6/8
------------------------------------------

You are now in the rabbit hole. You cannot return back to the field. You notice the decorations and the furniture of this long hallway in the hole. You see many mini doors, fit for a rabbit, but not you.You can go in the following directions:
You can go north.
You can go east.
Enter your next action> n
You find a table, with a few items on it. You move towards it to get a closer look.


You have found a Potion with a label DRINK ME. You also find miniature Cake with a label EAT ME. However, you are not the right size to eat this cake as your current form! These can only be consumed in this location.
You can go in the following directions:
You can go south.
Enter your next action> pick up potion
potion added to inventory.

---------------------Inventory---------------------
1. potion

You have 1/4 items in your inventory.
---------------------------------------------------
You can go in the following directions:
You can go south.
Enter your next action> use potion
You drink the liquid and become very tiny. You cannot stay like this to survive!
------------------Health------------------
Alice's current health is 7/8
------------------------------------------

potion removed from inventory.
You can go in the following directions:
You can go south.
Enter your next action> pick up cake
cake added to inventory.

---------------------Inventory---------------------
1. cake

You have 1/4 items in your inventory.
---------------------------------------------------
You can go in the following directions:
You can go south.
Enter your next action> use cake
You eat the cake and grow VERY LARGE! How will you ever leave the hole?
cake removed from inventory.
You notice a loud noise coming from the east part of the hole.
You can go in the following directions:
You can go south.
Enter your next action> go s
------------------------------
Welcome back to this location!
------------------------------
Here is the description again in case you forgot:
You are now in the rabbit hole. You cannot return back to the field. You notice the decorations and the furniture of this long hallway in the hole. You see many mini doors, fit for a rabbit, but not you.You can go in the following directions:
You can go north.
You can go east.
Enter your next action> e
Rabbit: "Oh, but what a large creature you are!". He drops a fan and scurries away, leaving the miniature south door unlocked on the way out.You have found a Fan. Maybe this can help you leave the rabbit hole...You can go in the following directions:
You can go west.
Enter your next action> pick up fan
fan added to inventory.

---------------------Inventory---------------------
1. fan

You have 1/4 items in your inventory.
---------------------------------------------------
You can go in the following directions:
You can go west.
Enter your next action> use fan
fan removed from inventory.
You use the fan, and notice that it shrinks you back down to a very small figure. You throw away the fan once you are done.
You can go in the following directions:
You can go west.
Enter your next action> w
------------------------------
Welcome back to this location!
------------------------------
Here is the description again in case you forgot:
You are now in the rabbit hole. You cannot return back to the field. You notice the decorations and the furniture of this long hallway in the hole. You see many mini doors, fit for a rabbit, but not you.You can go in the following directions:
You can go north.
You can go east.
You can go south.
Enter your next action> s
You enter Wonderland. You look around, amazed by the bright colors, the tall trees, and the surrounding nature. You feel the warm weather on your skin, and take in the sunlight. What a marvelous place!



You can go in the following directions:
You can go north.
You can go east.
You can go west.
Enter your next action> w
You have entered the forest. The forest has many trees and plants. You hear birds chirping in the distance.



You can go in the following directions:
You can go north.
You can go east.
You can go south.
Enter your next action> s
You walk into a field of mushrooms! As you are still a tiny size, these mushrooms seem to be like large trees.You find a colourful Caterpillar, sitting on a mushroom. He is smoking a hookah lazily.Caterpillar: You are very tiny for a human! Look around, these are all magic mushrooms. Take and use them to grow larger. You must grow larger to go any further.Caterpillar: And before I forget...don't you dare take more than one magic mushroom, or bad things will happen, dear.You have found Magic Mushrooms.You can go in the following directions:
You can go north.
Enter your next action> pick up mushroom
mushroom added to inventory.

---------------------Inventory---------------------
1. mushroom

You have 1/4 items in your inventory.
---------------------------------------------------
You can go in the following directions:
You can go north.
Enter your next action> use mushroom
You eat the mushroom, and immediately grow back to your normal size! You eat the whole piece.
mushroom removed from inventory.
The magic mushroom does have health side effects..
------------------Health------------------
Alice's current health is 5/8
------------------------------------------

You can go in the following directions:
You can go north.
You can go south.
Enter your next action> s
You walk into a house, made of bricks, that has a large balcony. It is a rather dull house.



You can go in the following directions:
You can go north.
You can go east.
You can go west.
Enter your next action> e
You see a long table, filled with fancy teacups and decorations on top a shiny tablecloth.You find a funny looking person sitting at one end of the table. He wears a green, oversized top hat, and seems to be quite elderly. He sips his tea and slowly glances up at you. The Hare, another funny looking rabbit in Wonderland. He has large, floppy ears, and his eyes can't seem to focus. He is loud, and quite the opposite of a gentleman.Hatter: You don't seem as you belong here. It is rather frustrating seeing random people interrupt out tea party. Isn't that right, Hare? Hare: Oh yes indeed! Well guess what, strange person! You can leave Wonderland by touching the Queen's crown. Oh, but be so careful, as there are traps.Hatter: Well, we will help you. We have a key here that unlocks the tree door to the south.You have found a Key. As you have been travelling on your feet all this time, you begin to feel tired.
------------------Health------------------
Alice's current health is 4/8
------------------------------------------

You can go in the following directions:
You can go east.
You can go west.
Enter your next action> pick up key
key added to inventory.

---------------------Inventory---------------------
1. key

You have 1/4 items in your inventory.
---------------------------------------------------
You can go in the following directions:
You can go east.
You can go west.
Enter your next action> use key
key removed from inventory.
You use the key to unlock the door. It vanishes right after you use it.
You can go in the following directions:
You can go east.
You can go west.
You can go south.
Enter your next action> s
You open the door and are immediately blinded by the strong light and loud noise. You are now at the queens croquet match. As you see everyone is distracted, this might be the perfect time to sneak into the castleYou easily spot her. the Queen of Hearts is easily recognized by her iconic red, black, and gold color schemeΓÇöas well as her motif of hearts and playing cards.Queen: Get to your places! Shouted the Queen in a voice of thunder, and people began running about in all directions, tumbling up against each other; however, they got settled down in a minute or two, and the game began.You thought you had never seen such a curious croquet-ground in her life; it was all ridges and furrows; the balls were live hedgehogs, the mallets live flamingoes, and the soldiers had to double themselves up and to stand on their hands and feet, to make the arches.You can go in the following directions:
You can go north.
You can go south.
Enter your next action> go s
You walk into the castle, seeming to somehow sneak past the guards.



You can go in the following directions:
You can go north.
You can go east.
You can go west.
Enter your next action> e
You find a glass case containing an item. You sneak past the alarm system to get a better look.


You have found a Crown.
You can go in the following directions:
You can go west.
Enter your next action> pick up crown
This is not a valid item.
------------------Health------------------
Alice's current health is 4/8
------------------------------------------

Your health levels are not high enough to leave Wonderland, and the strength of the crown strikes you, and you have lost the game.
Better luck next time!


 Bad Data case 1 (bad input)
Would you like to play? (Y/N): k
Would you like to play? (Y/N): y
Welcome to the Alice in Wonderland Game! You are playing the character Alice. The goal of this game is to escape Wonderland. This means that you must survive
until the very end and make the right choices. You are going to be exploring a large map, with many different rooms, objects, and characters. Interact with these
 elements carefully, as their can be consequences. Pay close attention to your health levels, as consuming certain items and going to certain locations can lower them. However, don't threat!
You can pick up and use objects to raise your health. You can only hold 4 items at a time. You can either drop or use the items to lose them from inventory. You may also display your health and inventory at any time. There is a safe room further in the game that you can use to store these items if needed.
 Listen closely to characters and their helpful advice. Good luck playing!
-------------------------------------------------GAME START-------------------------------------------------

You find yourself standing in a verdant open meadow. You shiver as the cool breeze sways the tall grass, and the leaves on the trees.
You see a White Rabbit wearing a waistcoat, carrying a pocket watch, and seemingly in a great hurry. He is running off to the south, about to jump into a rabbit hole.
Rabbit: "I am going to be late!"
You can go in the following directions:
You can go north.
You can go east.
You can go west.
You can go south.
Enter your next action> quit

 Bad Data case 2 (null direction)
	----------------------------------- WELCOME TO THE ALICE IN WONDERLAND GAME-----------------------------------
Would you like to play? (Y/N): y
Welcome to the Alice in Wonderland Game! You are playing the character Alice. The goal of this game is to escape Wonderland. This means that you must survive
until the very end and make the right choices. You are going to be exploring a large map, with many different rooms, objects, and characters. Interact with these
 elements carefully, as their can be consequences. Pay close attention to your health levels, as consuming certain items and going to certain locations can lower them. However, don't threat!
You can pick up and use objects to raise your health. You can only hold 4 items at a time. You can either drop or use the items to lose them from inventory. You may also display your health and inventory at any time. There is a safe room further in the game that you can use to store these items if needed.
 Listen closely to characters and their helpful advice. Good luck playing!
-------------------------------------------------GAME START-------------------------------------------------

You find yourself standing in a verdant open meadow. You shiver as the cool breeze sways the tall grass, and the leaves on the trees.
You see a White Rabbit wearing a waistcoat, carrying a pocket watch, and seemingly in a great hurry. He is running off to the south, about to jump into a rabbit hole.
Rabbit: "I am going to be late!"
You can go in the following directions:
You can go north.
You can go east.
You can go west.
You can go south.
Enter your next action> go w
You find a garden, filled with gardening tools.


You have found a Shovel.
You can go in the following directions:
You can go east.
Enter your next action> go w
You can't go that way.
You can go in the following directions:
You can go east.
Enter your next action> quit

 Bad Data case 3 (picking up an object that's not there)
----------------------------------- WELCOME TO THE ALICE IN WONDERLAND GAME-----------------------------------
Would you like to play? (Y/N): y
Welcome to the Alice in Wonderland Game! You are playing the character Alice. The goal of this game is to escape Wonderland. This means that you must survive
until the very end and make the right choices. You are going to be exploring a large map, with many different rooms, objects, and characters. Interact with these
 elements carefully, as their can be consequences. Pay close attention to your health levels, as consuming certain items and going to certain locations can lower them. However, don't threat!
You can pick up and use objects to raise your health. You can only hold 4 items at a time. You can either drop or use the items to lose them from inventory. You may also display your health and inventory at any time. There is a safe room further in the game that you can use to store these items if needed.
 Listen closely to characters and their helpful advice. Good luck playing!
-------------------------------------------------GAME START-------------------------------------------------

You find yourself standing in a verdant open meadow. You shiver as the cool breeze sways the tall grass, and the leaves on the trees.
You see a White Rabbit wearing a waistcoat, carrying a pocket watch, and seemingly in a great hurry. He is running off to the south, about to jump into a rabbit hole.
Rabbit: "I am going to be late!"
You can go in the following directions:
You can go north.
You can go east.
You can go west.
You can go south.
Enter your next action> go n
You find a large house, sitting on the edge of a valley.


You have found a Blanket.
You can go in the following directions:
You can go south.
Enter your next action> pick up shovel
This item does not exist here.
You can go in the following directions:
You can go south.
Enter your next action> quit

 Bad Data case 4 (picking up an object already in inventory)
	----------------------------------- WELCOME TO THE ALICE IN WONDERLAND GAME-----------------------------------
Would you like to play? (Y/N): y
Welcome to the Alice in Wonderland Game! You are playing the character Alice. The goal of this game is to escape Wonderland. This means that you must survive
until the very end and make the right choices. You are going to be exploring a large map, with many different rooms, objects, and characters. Interact with these
 elements carefully, as their can be consequences. Pay close attention to your health levels, as consuming certain items and going to certain locations can lower them. However, don't threat!
You can pick up and use objects to raise your health. You can only hold 4 items at a time. You can either drop or use the items to lose them from inventory. You may also display your health and inventory at any time. There is a safe room further in the game that you can use to store these items if needed.
 Listen closely to characters and their helpful advice. Good luck playing!
-------------------------------------------------GAME START-------------------------------------------------

You find yourself standing in a verdant open meadow. You shiver as the cool breeze sways the tall grass, and the leaves on the trees.
You see a White Rabbit wearing a waistcoat, carrying a pocket watch, and seemingly in a great hurry. He is running off to the south, about to jump into a rabbit hole.
Rabbit: "I am going to be late!"
You can go in the following directions:
You can go north.
You can go east.
You can go west.
You can go south.
Enter your next action> go n
You find a large house, sitting on the edge of a valley.


You have found a Blanket.
You can go in the following directions:
You can go south.
Enter your next action> pick up blanket
blanket added to inventory.

---------------------Inventory---------------------
1. blanket

You have 1/4 items in your inventory.
---------------------------------------------------
You can go in the following directions:
You can go south.
Enter your next action> go s
------------------------------
Welcome back to this location!
------------------------------
Here is the description again in case you forgot:
You find yourself standing in a verdant open meadow. You shiver as the cool breeze sways the tall grass, and the leaves on the trees.You can go in the following directions:
You can go north.
You can go east.
You can go west.
You can go south.
Enter your next action> go n
------------------------------
Welcome back to this location!
------------------------------
You find a large house, sitting on the edge of a valley.You can go in the following directions:
You can go south.
Enter your next action> pick up blanket
You already have this item in your inventory.

---------------------Inventory---------------------
1. blanket

You have 1/4 items in your inventory.
---------------------------------------------------
You can go in the following directions:
You can go south.
Enter your next action>quit

Bad Data Case 5(not an action word)
----------------------------------- WELCOME TO THE ALICE IN WONDERLAND GAME-----------------------------------
Would you like to play? (Y/N): y
Welcome to the Alice in Wonderland Game! You are playing the character Alice. The goal of this game is to escape Wonderland. This means that you must survive
until the very end and make the right choices. You are going to be exploring a large map, with many different rooms, objects, and characters. Interact with these
 elements carefully, as their can be consequences. Pay close attention to your health levels, as consuming certain items and going to certain locations can lower them. However, don't threat!
You can pick up and use objects to raise your health. You can only hold 4 items at a time. You can either drop or use the items to lose them from inventory. You may also display your health and inventory at any time. There is a safe room further in the game that you can use to store these items if needed.
 Listen closely to characters and their helpful advice. Good luck playing!
-------------------------------------------------GAME START-------------------------------------------------

You find yourself standing in a verdant open meadow. You shiver as the cool breeze sways the tall grass, and the leaves on the trees.
You see a White Rabbit wearing a waistcoat, carrying a pocket watch, and seemingly in a great hurry. He is running off to the south, about to jump into a rabbit hole.
Rabbit: "I am going to be late!"
You can go in the following directions:
You can go north.
You can go east.
You can go west.
You can go south.
Enter your next action> go sdfdf
Invalid action word.
You can go in the following directions:
You can go north.
You can go east.
You can go west.
You can go south.
Enter your next action>quit

Bad input 6(Using an object not in inventory)
----------------------------------- WELCOME TO THE ALICE IN WONDERLAND GAME-----------------------------------
Would you like to play? (Y/N): y
Welcome to the Alice in Wonderland Game! You are playing the character Alice. The goal of this game is to escape Wonderland. This means that you must survive
until the very end and make the right choices. You are going to be exploring a large map, with many different rooms, objects, and characters. Interact with these
 elements carefully, as their can be consequences. Pay close attention to your health levels, as consuming certain items and going to certain locations can lower them. However, don't threat!
You can pick up and use objects to raise your health. You can only hold 4 items at a time. You can either drop or use the items to lose them from inventory. You may also display your health and inventory at any time. There is a safe room further in the game that you can use to store these items if needed.
 Listen closely to characters and their helpful advice. Good luck playing!
-------------------------------------------------GAME START-------------------------------------------------

You find yourself standing in a verdant open meadow. You shiver as the cool breeze sways the tall grass, and the leaves on the trees.
You see a White Rabbit wearing a waistcoat, carrying a pocket watch, and seemingly in a great hurry. He is running off to the south, about to jump into a rabbit hole.
Rabbit: "I am going to be late!"
You can go in the following directions:
You can go north.
You can go east.
You can go west.
You can go south.
Enter your next action> use shovel
You do not have this item.
You can go in the following directions:
You can go north.
You can go east.
You can go west.
You can go south.
Enter your next action> quit

Bad input 7(Dropping an object that is not in inventory)
----------------------------------- WELCOME TO THE ALICE IN WONDERLAND GAME-----------------------------------
Would you like to play? (Y/N): y
Welcome to the Alice in Wonderland Game! You are playing the character Alice. The goal of this game is to escape Wonderland. This means that you must survive
until the very end and make the right choices. You are going to be exploring a large map, with many different rooms, objects, and characters. Interact with these
 elements carefully, as their can be consequences. Pay close attention to your health levels, as consuming certain items and going to certain locations can lower them. However, don't threat!
You can pick up and use objects to raise your health. You can only hold 4 items at a time. You can either drop or use the items to lose them from inventory. You may also display your health and inventory at any time. There is a safe room further in the game that you can use to store these items if needed.
 Listen closely to characters and their helpful advice. Good luck playing!
-------------------------------------------------GAME START-------------------------------------------------

You find yourself standing in a verdant open meadow. You shiver as the cool breeze sways the tall grass, and the leaves on the trees.
You see a White Rabbit wearing a waistcoat, carrying a pocket watch, and seemingly in a great hurry. He is running off to the south, about to jump into a rabbit hole.
Rabbit: "I am going to be late!"
You can go in the following directions:
You can go north.
You can go east.
You can go west.
You can go south.
Enter your next action> drop shovel
This item could not be found in your inventory.

---------------------Inventory---------------------

You have 0/4 items in your inventory.
---------------------------------------------------
You can go in the following directions:
You can go north.
You can go east.
You can go west.
You can go south.
Enter your next action>quit

Bad input 8(empty space for action)
----------------------------------- WELCOME TO THE ALICE IN WONDERLAND GAME-----------------------------------
Would you like to play? (Y/N): y
Welcome to the Alice in Wonderland Game! You are playing the character Alice. The goal of this game is to escape Wonderland. This means that you must survive
until the very end and make the right choices. You are going to be exploring a large map, with many different rooms, objects, and characters. Interact with these
 elements carefully, as their can be consequences. Pay close attention to your health levels, as consuming certain items and going to certain locations can lower them. However, don't threat!
You can pick up and use objects to raise your health. You can only hold 4 items at a time. You can either drop or use the items to lose them from inventory. You may also display your health and inventory at any time. There is a safe room further in the game that you can use to store these items if needed.
 Listen closely to characters and their helpful advice. Good luck playing!
-------------------------------------------------GAME START-------------------------------------------------

You find yourself standing in a verdant open meadow. You shiver as the cool breeze sways the tall grass, and the leaves on the trees.
You see a White Rabbit wearing a waistcoat, carrying a pocket watch, and seemingly in a great hurry. He is running off to the south, about to jump into a rabbit hole.
Rabbit: "I am going to be late!"
You can go in the following directions:
You can go north.
You can go east.
You can go west.
You can go south.
Enter your next action> go n
You find a large house, sitting on the edge of a valley.


You have found a Blanket.
You can go in the following directions:
You can go south.
Enter your next action>
Invalid action word.
You can go in the following directions:
You can go south.
Enter your next action>quit

Bad input 9(dropping something in safe room that is not in inventory, picking up something from safe room that is not in safe room inventory)
----------------------------------- WELCOME TO THE ALICE IN WONDERLAND GAME-----------------------------------
Would you like to play? (Y/N): y
Welcome to the Alice in Wonderland Game! You are playing the character Alice. The goal of this game is to escape Wonderland. This means that you must survive
until the very end and make the right choices. You are going to be exploring a large map, with many different rooms, objects, and characters. Interact with these
 elements carefully, as their can be consequences. Pay close attention to your health levels, as consuming certain items and going to certain locations can lower them. However, don't threat!
You can pick up and use objects to raise your health. You can only hold 4 items at a time. You can either drop or use the items to lose them from inventory. You may also display your health and inventory at any time. There is a safe room further in the game that you can use to store these items if needed.
 Listen closely to characters and their helpful advice. Good luck playing!
-------------------------------------------------GAME START-------------------------------------------------

You find yourself standing in a verdant open meadow. You shiver as the cool breeze sways the tall grass, and the leaves on the trees.
You see a White Rabbit wearing a waistcoat, carrying a pocket watch, and seemingly in a great hurry. He is running off to the south, about to jump into a rabbit hole.
Rabbit: "I am going to be late!"
You can go in the following directions:
You can go north.
You can go east.
You can go west.
You can go south.
Enter your next action> go s
As you took a hit while falling down the rabbit hole, you lose health.
------------------Health------------------
Alice's current health is 6/8
------------------------------------------

You are now in the rabbit hole. You cannot return back to the field. You notice the decorations and the furniture of this long hallway in the hole. You see many mini doors, fit for a rabbit, but not you.You can go in the following directions:
You can go north.
You can go east.
Enter your next action> n
You find a table, with a few items on it. You move towards it to get a closer look.


You have found a Potion with a label DRINK ME. You also find miniature Cake with a label EAT ME. However, you are not the right size to eat this cake as your current form! These can only be consumed in this location.
You can go in the following directions:
You can go south.
Enter your next action> pick up potion
potion added to inventory.

---------------------Inventory---------------------
1. potion

You have 1/4 items in your inventory.
---------------------------------------------------
You can go in the following directions:
You can go south.
Enter your next action> use potion
You drink the liquid and become very tiny. You cannot stay like this to survive!
------------------Health------------------
Alice's current health is 7/8
------------------------------------------

potion removed from inventory.
You can go in the following directions:
You can go south.
Enter your next action> pick up cake
cake added to inventory.

---------------------Inventory---------------------
1. cake

You have 1/4 items in your inventory.
---------------------------------------------------
You can go in the following directions:
You can go south.
Enter your next action> use cake
You eat the cake and grow VERY LARGE! How will you ever leave the hole?
cake removed from inventory.
You notice a loud noise coming from the east part of the hole.
You can go in the following directions:
You can go south.
Enter your next action> s
------------------------------
Welcome back to this location!
------------------------------
Here is the description again in case you forgot:
You are now in the rabbit hole. You cannot return back to the field. You notice the decorations and the furniture of this long hallway in the hole. You see many mini doors, fit for a rabbit, but not you.You can go in the following directions:
You can go north.
You can go east.
Enter your next action> e
Rabbit: "Oh, but what a large creature you are!". He drops a fan and scurries away, leaving the miniature south door unlocked on the way out.You have found a Fan. Maybe this can help you leave the rabbit hole...You can go in the following directions:
You can go west.
Enter your next action> pick up fan
fan added to inventory.

---------------------Inventory---------------------
1. fan

You have 1/4 items in your inventory.
---------------------------------------------------
You can go in the following directions:
You can go west.
Enter your next action> use fan
fan removed from inventory.
You use the fan, and notice that it shrinks you back down to a very small figure. You throw away the fan once you are done.
You can go in the following directions:
You can go west.
Enter your next action> w
------------------------------
Welcome back to this location!
------------------------------
Here is the description again in case you forgot:
You are now in the rabbit hole. You cannot return back to the field. You notice the decorations and the furniture of this long hallway in the hole. You see many mini doors, fit for a rabbit, but not you.You can go in the following directions:
You can go north.
You can go east.
You can go south.
Enter your next action> s
You enter Wonderland. You look around, amazed by the bright colors, the tall trees, and the surrounding nature. You feel the warm weather on your skin, and take in the sunlight. What a marvelous place!



You can go in the following directions:
You can go north.
You can go east.
You can go west.
Enter your next action> go w
You have entered the forest. The forest has many trees and plants. You hear birds chirping in the distance.



You can go in the following directions:
You can go north.
You can go east.
You can go south.
Enter your next action> s
You walk into a field of mushrooms! As you are still a tiny size, these mushrooms seem to be like large trees.You find a colourful Caterpillar, sitting on a mushroom. He is smoking a hookah lazily.Caterpillar: You are very tiny for a human! Look around, these are all magic mushrooms. Take and use them to grow larger. You must grow larger to go any further.Caterpillar: And before I forget...don't you dare take more than one magic mushroom, or bad things will happen, dear.You have found Magic Mushrooms.You can go in the following directions:
You can go north.
Enter your next action> pick up mushroom
mushroom added to inventory.

---------------------Inventory---------------------
1. mushroom

You have 1/4 items in your inventory.
---------------------------------------------------
You can go in the following directions:
You can go north.
Enter your next action> use mushroom
You eat the mushroom, and immediately grow back to your normal size! You eat the whole piece.
mushroom removed from inventory.
The magic mushroom does have health side effects..
------------------Health------------------
Alice's current health is 5/8
------------------------------------------

You can go in the following directions:
You can go north.
You can go south.
Enter your next action> s
You walk into a house, made of bricks, that has a large balcony. It is a rather dull house.



You can go in the following directions:
You can go north.
You can go east.
You can go west.
Enter your next action> go w
You enter the Safe Room. To store an object here, you must type drop "item" and it will be stored.



You can go in the following directions:
You can go east.
Enter your next action> drop shovel
You do not have this item in your inventory
You can go in the following directions:
You can go east.
Enter your next action> pick up shovel
This item could not be found in your safe room inventory.
You can go in the following directions:
You can go east.
Enter your next action> quit

Bad input 10(not saying pick up, but something else)
----------------------------------- WELCOME TO THE ALICE IN WONDERLAND GAME-----------------------------------
Would you like to play? (Y/N): y
Welcome to the Alice in Wonderland Game! You are playing the character Alice. The goal of this game is to escape Wonderland. This means that you must survive
until the very end and make the right choices. You are going to be exploring a large map, with many different rooms, objects, and characters. Interact with these
 elements carefully, as their can be consequences. Pay close attention to your health levels, as consuming certain items and going to certain locations can lower them. However, don't threat!
You can pick up and use objects to raise your health. You can only hold 4 items at a time. You can either drop or use the items to lose them from inventory. You may also display your health and inventory at any time. There is a safe room further in the game that you can use to store these items if needed.
 Listen closely to characters and their helpful advice. Good luck playing!
-------------------------------------------------GAME START-------------------------------------------------

You find yourself standing in a verdant open meadow. You shiver as the cool breeze sways the tall grass, and the leaves on the trees.
You see a White Rabbit wearing a waistcoat, carrying a pocket watch, and seemingly in a great hurry. He is running off to the south, about to jump into a rabbit hole.
Rabbit: "I am going to be late!"
You can go in the following directions:
You can go north.
You can go east.
You can go west.
You can go south.
Enter your next action> pick this up
Invalid action. Please enter a valid action.
You can go in the following directions:
You can go north.
You can go east.
You can go west.
You can go south.
Enter your next action> quit

Bad input 11(display something that does not exist)
	----------------------------------- WELCOME TO THE ALICE IN WONDERLAND GAME-----------------------------------
Would you like to play? (Y/N): y
Welcome to the Alice in Wonderland Game! You are playing the character Alice. The goal of this game is to escape Wonderland. This means that you must survive
until the very end and make the right choices. You are going to be exploring a large map, with many different rooms, objects, and characters. Interact with these
 elements carefully, as their can be consequences. Pay close attention to your health levels, as consuming certain items and going to certain locations can lower them. However, don't threat!
You can pick up and use objects to raise your health. You can only hold 4 items at a time. You can either drop or use the items to lose them from inventory. You may also display your health and inventory at any time. There is a safe room further in the game that you can use to store these items if needed.
 Listen closely to characters and their helpful advice. Good luck playing!
-------------------------------------------------GAME START-------------------------------------------------

You find yourself standing in a verdant open meadow. You shiver as the cool breeze sways the tall grass, and the leaves on the trees.
You see a White Rabbit wearing a waistcoat, carrying a pocket watch, and seemingly in a great hurry. He is running off to the south, about to jump into a rabbit hole.
Rabbit: "I am going to be late!"
You can go in the following directions:
You can go north.
You can go east.
You can go west.
You can go south.
Enter your next action> display home
You cannot display this.
You can go in the following directions:
You can go north.
You can go east.
You can go west.
You can go south.
Enter your next action>quit

 Bad input 12(exceeding inventory)
 Enter your next action> pick up mushroom
Your inventory is full. This could not be added.

---------------------Inventory---------------------
1. blanket
2. shovel
3. plush
4. water

You have 4/4 items in your inventory.
---------------------------------------------------
You can go in the following directions:
You can go north.
Enter your next action>quit

Bad input 13(Files not opening)
----------------------------------- WELCOME TO THE ALICE IN WONDERLAND GAME-----------------------------------
Would you like to play? (Y/N): y
Welcome to the Alice in Wonderland Game! You are playing the character Alice. The goal of this game is to escape Wonderland. This means that you must survive 
until the very end and make the right choices. You are going to be exploring a large map, with many different rooms, objects, and characters. Interact with these
 elements carefully, as their can be consequences. Pay close attention to your health levels, as consuming certain items and going to certain locations can lower them. However, don't threat!
You can pick up and use objects to raise your health. You can only hold 4 items at a time. You can either drop or use the items to lose them from inventory. You may also display your health and inventory at any time. There is a safe room further in the game that you can use to store these items if needed.
 Listen closely to characters and their helpful advice. Good luck playing! 
You can quit the game at any time by typing quit.
-------------------------------------------------GAME START-------------------------------------------------

Unable to open Items.txt

You see a White Rabbit wearing a waistcoat, carrying a pocket watch, and seemingly in a great hurry. He is running off to the south, about to jump into a rabbit hole.
Rabbit: "I am going to be late!"
You can go in the following directions:
You can go north.
You can go east.
You can go west.
You can go south.
Enter your next action> quit

Discussion:
	The program accepts action words displayed in action.txt.
	An object must be there to be picked up, and must be stored in inventory to be used.
	Going to a location that is null is not permitted.
	Objects that are picked up from the safe room need to be there already. Objects dropped into safe room need to already be in inventory.
	If any rule is not followed, an error message displays, and the user is prompted again.

*/

#include "AliceinWonderland.h"

int main()
{
	return AliceinWonderland::main();
}
