# Pokemon TCG Hand Simulator
A program that simulates hands and such for the Pokemon TCG!

## Formatting your Deck

Please adhere to the following guidelines to make sure the program doesn't crash and burn :p

* The target deck should be the same directory as the excecutable, and named deck.txt
* Indicate basic Pokemon by putting an asterisk directly before the Pokemon name (example shown below)
* Start with the quantity of the card, followed by the name. 
* You can name your cards whatever you want, except for a select group of cards for the Vileplume Start Function(see below).

If you are using the Vileplume Start function, please format the following cards as follows:


Shaymin-EX:     `Shaymin-EX_ROS`
Unown AOR:      `Unown_AOR`
Trainer's Mail: `Trainers_Mail`
Acro Bike:      `Acro_Bike`

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
