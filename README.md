# Pokemon TCG Hand Simulator
A program that simulates hands and such for the Pokemon TCG!

## Formatting your Deck

Please adhere to the following guidelines to make sure the program doesn't crash and burn :p

* The target deck should be the same directory as the excecutable, and named deck.txt
* Indicate basic Pokemon by putting an asterisk directly before the Pokemon name (example shown below)
* Start with the quantity of the card, followed by the name. 
* You can name your cards whatever you want, except for a select group of cards for the Vileplume Start Function(see below).

If you are using the Vileplume Start function, please format the following cards as follows:

| Card                   | Syntax                   |
| -----------------------|:------------------------:|
| Oddish                 | `Oddish_AOR`             |
| Gloom                  | `Gloom_AOR`              | 
| Vileplume              | `Vileplume_AOR`          |
| Shaymin-EX             | `Shaymin-EX_ROS`         |
| Unown                  | `Unown_AOR`              |
| Professor Sycamore     | `Professor_Sycamore`     |
| N                      | `N`                      |
| Trainer's Mail         | `Trainers_Mail`          |
| Ultra Ball             | `Ultra_Ball`             |
| Level Ball             | `Level_Ball`             |
| Acro Bike              | `Acro_Bike`              |
| Forest of Giant Plants | `Forest_Of_Giant_Plants` |

*If all of the above cards are not named as written, the program may crash and/or burn.*

## Example deck.txt

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
* Calculates the probability of hitting a turn one item lock with Vileplume (**IN PROGRESS**)

That's all there is as of now! Below are some of the algorithms used for developers/players of the TCG.

## Pseudocode for Vileplume Algorithm

The program repeats a loop (function vileStartSequence) which does the following in order. The loop stops when there's no cards to play in hand:

* Plays all Unowns
* Plays all Trainer's Mails
* Plays Forest of Giant Plants (if one is not already in play)
* If there's no Oddish on the field, Level Ball for an Oddish
* If Forest of Giant Plants and Oddish are out, Level Ball for Gloom
* If Oddish and Gloom are already on the field, use a Level Ball in hand for an Unown
* If Gloom is in hand and Oddish is on the field, play Gloom
* If Vileplume is in hand and Gloom is on the field, play Vileplume

Below are elements to the algorithm that have yet to be added:

* Play all Acro Bikes (will probably go before Play all Trainer's Mails in algorithm)
* If there's an Ultra Ball in your hand and no draw Supporter/Ultra Ball, grab a Shaymin-EX
* If there's an Ultra Ball in your hand and a draw Supporter/Ultra Ball, grab the next Pokemon in the priorities vector
* Keep repeating the above loop until there's nothing left to do
* (Outside of the loop) If there's a Supporter, play it and re-enter the loop
