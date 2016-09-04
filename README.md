# Pokemon TCG Hand Simulator
A program that simulates hands and such for the Pokemon TCG!

## Formatting your Deck

Please adhere to the following guidelines to make sure the program doesn't crash and burn :p

* The target deck should be the same directory as the excecutable, and named deck.txt
* Indicate basic Pokemon by putting an asterisk directly before the Pokemon name (example shown below)
* Start with the quantity of the card, followed by the name. 
* Please capitalize the start of all new words in a card title
* Please no 's or any other characters in card names
* Please no empty lines or extra spaces in the front, middle, or end of the deck.txt file
* Card names should be formatted as follows:

```
*Card_Name-EX_Set_SetNumber
```

The set number is only required when there are multiple cards with the same name and set in your deck.

Here are some examples:

```
Shaymin-EX_ROS
M_Rayquaza-EX_ROS
M_Mewtwo_EX_BRT_64
Professor_Sycamore
Forest_Of_Giant_Plants
Fire_Energy
```

* Indicate basic Pokemon by putting an asterisk directly before the Pokemon name (example shown below)

### Example deck.txt

```
3 M_Audino-EX_FCO
4 *Audino_EX_FCO
2 *Shaymin-EX_ROS
1 *Hoopa-EX_ROS
1 *Magearna-EX_STM
1 *Cobalion_STM
1 *Absol_ROS
4 Professor_Sycamore
2 N
2 AZ
2 Lysandre
1 Hex_Maniac
1 Xerosic
1 Pokemon_Center_Lady
4 VS_Seeker
4 Ultra_Ball
4 Trainers_Mail
4 Audino_Spirit_Link
2 Float_Stone
2 Parallel_City
1 Mega_Turbo
1 Escape_Rope
1 Super_Rod
1 Startling_Megaphone
6 Metal_Energy
4 Double_Colorless_Energy
```

## Current Functions

* Calculates the probability of starting with each Basic Pokemon in your deck
* Calculates the probability of starting with any given combination of Basic Pokemon in your deck
