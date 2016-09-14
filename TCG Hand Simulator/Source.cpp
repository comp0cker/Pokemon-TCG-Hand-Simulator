#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <algorithm>
#include <vector>
#include <windows.h>
#include "cards.h"
#include "gotoxy.h"
using namespace std;

#define DECK_SIZE 60
#define HAND_SIZE 8
#define PRIZES 6
#define SELECTION_MAX 1		// Number of items in the menu of the selection screen

int readDeck(vector<string>&, vector<string>&);
int resetDeck(vector<string>&);

int start(vector<string>&, vector<string>&, vector<string>&);
int constructHand(vector<string>&, vector<string>&);
int layPrizes(vector<string>&);
int checkMulligan(vector<string>&, string);

int checkHand(vector<string>&, string);
int Sort(vector<string>&, vector<int>&);

int checkStartingHand(vector<string>&, vector<string>&, vector<string>&);
int vileSetup(vector<string>&, vector<string>&, vector<string>&);
int vileStartSequence(vector<string>&, vector<string>&, vector<string>&, vector<string>&, vector<string>&, vector<string>&, bool&, int&, int&);

int main()
{
	vector<string> deck(DECK_SIZE, "");
	vector<string> hand(HAND_SIZE, "");
	vector<string> basics;

	cout << "Welcome to the TCG Hand Simulator!\n"
		<< "==================================\n\n"
		<< ""
		<< "Please choose a function to load.\n\n"
		<< ""
		<< "Basic Checker\n"
		<< "Vileplume Start Checker";

	int c = 0;											// Counter for the position of the arrow

	gotoxy(35, c + 5);
	cout << "<==";

	while (!(GetAsyncKeyState(VK_RETURN) & SHRT_MAX))		// Keep checking for keypress as long as the Enter key hasn't been clicked
	{
		if (GetAsyncKeyState(VK_UP) & SHRT_MAX)
		{
			if (c != 0)
			{
				gotoxy(35, c + 5);
				cout << "           ";
				c--;
				gotoxy(35, c + 5);
				cout << "<==";
			}
		}

		else if (GetAsyncKeyState(VK_DOWN) & SHRT_MAX)
		{
			if (c != SELECTION_MAX)
			{
				gotoxy(35, c + 5);
				cout << "           ";
				c++;
				gotoxy(35, c + 5);
				cout << "<==";
			}
		}
	}

	readDeck(deck, basics);

	if (c == 0)
		checkStartingHand(deck, hand, basics);
	else if (c == 1)
		vileSetup(deck, hand, basics);

	system("pause");
}

int readDeck(vector<string> &deck, vector<string> &basics)
{
	ifstream inFile;
	int dup, i, c = 0;

	inFile.open("deck.txt");

	if (inFile.fail())
	{
		cout << "\n\n\ndeck.txt not found!!\n";
		system("pause");
		exit(1);
	}

	basics.clear();
	resetDeck(deck);

	for (i = 0; i < DECK_SIZE; 1)
	{
		inFile >> dup;

		inFile >> deck[i];

		if (deck[i].find("*") == 0)
		{
			c += dup;
			deck[i].erase(0, 1);

			vector<string>::iterator it;
			it = basics.begin();
			it = basics.insert(it, deck[i]);
			basics.insert(it, 0, "");
		}

		if (dup != 1)
		{
			for (int j = 0; j < dup; i++, j++)
				if (j != 0)
					deck[i] = deck[i - 1];
		}
		else
			i++;
	}

	return c;
}

int resetDeck(vector<string>& deck)		// I don't believe this is ever used, but whatever man :P
{
	deck.clear();

	for (int i = 0; i < DECK_SIZE; i++)
		deck.push_back("");
	return 0;
}

int start(vector<string>& deck, vector<string> &hand, vector<string>& basics) // a combination of readDeck, constructHand, checkMulligan, and layPrizes
{
	int c = 0;

	do
	{
		readDeck(deck, basics);
		constructHand(deck, hand);

		/*
		for (int i = 0; i < HAND_SIZE; i++)		// Outputs hands
		cout << hand[i] << "\t";				// Probably not in the right place :P

		cout << "\n";
		*/

		c = 0;

		for (int i = 0; i < basics.size(); i++)
		{
			if (checkMulligan(hand, basics[i]))
				c++;
			if (c)
				break;
		}
	} while (c == 0);

	layPrizes(deck);

	return 0;
}

int constructHand(vector<string>& deck, vector<string> &hand)
{
	random_device rd;
	srand(rd());

	for (int i = 0; i < hand.size(); i++)
	{
		int temp = rand() % deck.size();

		hand[i] = deck[temp];

		deck.erase(deck.begin() + temp);
	}

	return 0;
}

int layPrizes(vector<string>& deck) // not yet implemented
{
	random_device rd;
	srand(rd());

	for (int i = 0; i < PRIZES; i++)
	{
		int temp = rand() % deck.size();

		deck.erase(deck.begin() + temp);
	}

	return 0;
}

int checkMulligan(vector<string> &hand_cards, string basic)
{
	for (int i = 0; i < hand_cards.size(); i++)
		if (hand_cards[i] == basic)
			return 1;

	return 0;
}

int checkHand(vector<string> &hand_cards, string subject)
{
	for (int i = 1; i < hand_cards.size() + 1; i++)
		if (hand_cards[i - 1] == subject)
			return i;

	return 0;
}

int Sort(vector<string> &str, vector<int> &in)
{
	for (int i = 0; i < in.size(); i++)
	{
		for (int j = 1; j < in.size(); j++)
		{
			if (in[j] > in[j - 1])
			{
				string temps;
				int tempi;

				temps = str[j - 1];
				str[j - 1] = str[j];
				str[j] = temps;

				tempi = in[j - 1];
				in[j - 1] = in[j];
				in[j] = tempi;
			}
		}
	}

	return 0;
}

int checkStartingHand(vector<string> &deck, vector<string> &hand, vector<string> &basics)
{
	int trials, count = 0;
	bool valid = false;
	string subject_card;

	vector<int> basicCount(basics.size(), 0);
	vector<string> uniqueBasicCombs(1, "");
	vector<int> uniqueBasicCombsCount;

	vector<string>::iterator it;
	vector<int>::iterator itt;

	system("cls");

	cout << "Number of trials to run: ";
	cin >> trials;

	for (int ii = 0; ii < trials; ii++)
	{
		cout << "\rComputing trial " << ii + 1 << " out of " << trials << "...";
		start(deck, hand, basics);

		string temp = "";


		for (int j = 0; j < basics.size(); j++)
		{
			temp += to_string(checkHand(hand, basics[j]));
			basicCount[j] += checkHand(hand, basics[j]);
		}

		int cc = 0;

		for (int k = 0; k < uniqueBasicCombs.size(); k++)
		{
			if (uniqueBasicCombs[k] == temp)
			{
				uniqueBasicCombsCount[k]++;
				cc++;
			}
		}

		if (cc == 0)
		{
			vector<string>::iterator it;
			it = uniqueBasicCombs.begin();
			it = uniqueBasicCombs.insert(it, temp);
			uniqueBasicCombs.insert(it, 0, "");

			vector<int>::iterator itt;
			itt = uniqueBasicCombsCount.begin();
			itt = uniqueBasicCombsCount.insert(itt, 1);
			uniqueBasicCombsCount.insert(itt, 0, 0);
		}
	}

	cout << "\rDone!                                             \n";

	vector<string> basicsCopy(basics);

	Sort(basicsCopy, basicCount);

	for (int i = 0; i < basics.size(); i++)
	{
		if (basicCount[i] == 1)
			cout << basicCount[i] << " starting hand included " << basicsCopy[i] << " (" << float(basicCount[i]) * 100 / trials << "%)\n";

		else
			cout << basicCount[i] << " starting hands included " << basicsCopy[i] << " (" << float(basicCount[i]) * 100 / trials << "%)\n";
	}
	cout << "\n";

	Sort(uniqueBasicCombs, uniqueBasicCombsCount);


	for (int k = 0; k < uniqueBasicCombsCount.size(); k++)
	{
		if (uniqueBasicCombsCount[k] == 1)
			cout << uniqueBasicCombsCount[k] << " starting hand included ";
		else
			cout << uniqueBasicCombsCount[k] << " starting hands included ";

		int z = 0;
		for (int i = 0; i < basics.size(); i++)
			if (uniqueBasicCombs[k].at(i) == '1')
				z++;

		if (z == 1)
			cout << "only ";

		string str = "";

		for (int i = 0; i < basics.size(); i++)
			if (uniqueBasicCombs[k].at(i))
				str += basics[i] + ", ";

		str.pop_back();
		str.pop_back();

		cout << str;

		cout << " (" << float(uniqueBasicCombsCount[k]) * 100 / float(trials) << "%)\n";
	}

	cout << "\n";

	return 0;
}

int vileSetup(vector<string> &deck, vector<string> &hand, vector<string> &basics)
{
	int trials;

	system("cls");

	cout << "Number of trials to run: ";
	cin >> trials;

	for (int ii = 0; ii < trials; ii++)
	{
		vector<string> priorities{ "Vileplume_AOR", "Trainers_Mail", "Gloom_AOR", "Acro_Bike", "Ultra Ball", "Level_Ball", "Shaymin_ROS", "Oddish_AOR", "Forest_Of_Giant_Plants" };
		vector<string> pokemon{ "Vileplume_AOR", "Gloom_AOR", "Oddish_AOR" };
		vector<string> trainers{ "Trainers_Mail", "Acro_Bike", "Ultra_Ball", "Level_Ball", "Forest_Of_Giant_Plants" };

		cout << "\rComputing trial " << ii + 1 << " out of " << trials << "...";
		start(deck, hand, basics);

		vector<int> pos;

		//cout << "\nHAND BEFORE\n===========\n";

		bool oddishFound = false;							// A boolean that stops the program from deleting the Oddish priority more than once
		bool ifForest = false;
		int pokemonCount = 0, shayminCount = 0, unownCount = 0;
		string activePokemon = "null";

		for (int j = 0; j < hand.size(); j++)				// Cycles through the hand
		{
			//cout << hand[j] << "\n";						// Debugs hand before basics removed
			if (hand[j] == "Oddish_AOR" && !oddishFound)
			{
				pokemon.erase(pokemon.begin() + 2);			// Erases Oddish from pokemon priorities vector
				priorities.erase(priorities.begin() + 5);	// Erases Oddish from main priorities vector
															//cout << "\nODDISH FOUND!\n";
				oddishFound = true;							// Keeps loop from searching for Oddish if Oddish is already in hand
			}

			for (int i = 0; i < basics.size(); i++)
				if (hand[j] == basics[i])						// Note: The first Pokemon found is your A
				{
					pokemonCount++;
					hand.erase(hand.begin() + j);
					j--;

					if (basics[i] == "Unown_AOR")
						unownCount++;
					else if (basics[i] == "Shaymin-EX_ROS")
						shayminCount++;
					else
						activePokemon = basics[i];

					break;
				}
		}

		if (activePokemon == "null")						// If only Shaymin and Unown are available, make Unown be your Active
		{
			if (unownCount && shayminCount)
				activePokemon = "Unown_AOR";
			else if (unownCount > 0)
				activePokemon = "Unown_AOR";
			else if (shayminCount > 0)
				activePokemon = "Shaymin-EX_ROS";
		}

		if (activePokemon == "Unown_AOR")					// If Unown is your active Pokemon, don't use it
			unownCount--;

		int DEBUG = unownCount;

		//cout << "\n\nACTIVE: " << activePokemon << "\nUnown Count: " << DEBUG << "\nShaymin Count: " << shayminCount << "\n\n";


		//cout << "\n\n";

		vileStartSequence(deck, hand, basics, priorities, pokemon, trainers, ifForest, unownCount, shayminCount);
		vileStartSequence(deck, hand, basics, priorities, pokemon, trainers, ifForest, unownCount, shayminCount);

		/*
		cout << "\n";
		for (int i = 0; i < priorities.size(); i++)			// DEBUG: Outputs the priority vector
		cout << priorities[i] << "  ";
		cout << "\n";
		*/
		/*
		cout << "\n";
		for (int i = 0; i < pokemon.size(); i++)			// DEBUG: Outputs the pokemon vector (priorities for Pokemon only)
		cout << pokemon[i] << "  ";
		cout << "\n";
		*/
		/*
		cout << "HAND AFTER\n==========\n";
		for (int i = 0; i < hand.size(); i++)				// DEBUG: Outputs your hand
		cout << "\n" << hand[i] << "   ";

		for (int i = hand.size(); i < HAND_SIZE; i++)
		hand.push_back("");
		*/
		//cout << "\n";	// Debug
	}

	cout << "\rDone!                                             \n";

	return 0;
}

int vileStartSequence(vector<string> &deck, vector<string> &hand, vector<string> &basics, vector<string> &priorities, vector<string> &pokemon, vector<string> &trainers, bool &ifForest, int &unownCount, int& shayminCount)
{
	for (int i = 0; i < unownCount; unownCount--)					// Play all benched Unowns to start off
		draw(deck, hand);

	if (checkHand(hand, "Acro_Bike"))
		acroBike(deck, hand, priorities);

	if (checkHand(hand, "Trainers_Mail"))
		trainersMail(deck, hand, trainers);

	if (play("Forest_Of_Giant_Plants", hand) && !ifForest)			// Play down Forest if one is not already played
	{
		hand.erase(hand.begin() + play("Forest_Of_Giant_Plants", hand));
		priorities.erase(remove(priorities.begin(), priorities.end(), "Forest_Of_Giant_Plants"), priorities.end());
		ifForest = true;
	}

	/*Play
	if (ifForest)													// DEBUG: If IFFOREST = TRUE
	cout << "IF FOREST IS TRUE";
	else
	cout << "IF FOREST IS FALSE";
	*/

	if (ifForest)
	{
		if (checkHand(hand, "Level_Ball") && pokemon.size() == 2)
		{
			levelBall(deck, hand, pokemon);
			hand.erase(hand.begin() + checkHand(hand, "Level_Ball") - 1);
		}

		else if (checkHand(hand, "Level_Ball") && pokemon.size() == 1)
			for (int i = 0; i < deck.size(); i++)
				if (deck[i] == "Unown_AOR")								// If an Unown is in the deck and Oddish and Gloom are on the field, skip the crap and draw a card
				{
					deck.erase(deck.begin() + i);
					hand.erase(hand.begin() + checkHand(hand, "Level_Ball") - 1);
					random_shuffle(deck.begin(), deck.end());		// Shuffles the deck afterwards :]
					draw(deck, hand);
					break;
				}
		//cout << "FOREST IS ACTIVE AHHHHHHH";						// DEBUG: Rage I guess
		if (checkHand(hand, "Gloom_AOR") && pokemon.size() == 2)	// Evolve Oddish into Gloom if you have Gloom and there is an Oddish on the field
		{
			//system("pause");										// DEBUG: Pauses when Gloom set up is in starting hand
			pokemon.pop_back();
			priorities.erase(remove(priorities.begin(), priorities.end(), "Gloom_AOR"), priorities.end());
		}

		if (checkHand(hand, "Vileplume_AOR") && pokemon.size() == 1)// Evolve Gloom into Vileplume if you have 
		{
			//system("pause");										// DEBUG: Pauses when Vileplume set up is in starting hand
			return 1;
		}
	}

	if (checkHand(hand, "Ultra_Ball") && !checkHand(hand, "Professor_Sycamore") && !checkHand(hand, "N") && !checkHand(hand, "Ultra_Ball"))
		ultraBall(deck, hand, priorities, "Shaymin-EX_ROS");

	if (checkHand(hand, "Ultra_Ball") && (checkHand(hand, "Professor_Sycamore") || checkHand(hand, "N") || checkHand(hand, "Ultra_Ball")))
		ultraBall(deck, hand, priorities, pokemon[pokemon.size - 1]);

	return 0;
}