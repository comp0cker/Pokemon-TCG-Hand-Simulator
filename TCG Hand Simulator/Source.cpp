#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <algorithm>
#include <vector>
#include "cards.h"
using namespace std;

#ifdef _WIN32	// Required junk for the cursor

#include <windows.h>

void gotoxy(int x, int y)
{
	COORD p = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), p);
}

#else

#include <unistd.h>
#include <term.h>

void gotoxy(int x, int y)
{
	int err;
	if (!cur_term)
		if (setupterm(NULL, STDOUT_FILENO, &err) == ERR)
			return;
	putp(tparm(tigetstr("cup"), y, x, 0, 0, 0, 0, 0, 0, 0));
}

#endif			// end of junk

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
int vileSetup(vector<string>&, vector<string>&);

bool sortt(int i, int j) 
{ 
	return (i>j);
}

int main()
{
	vector<string> deck (DECK_SIZE, "");
	vector<string> hand (HAND_SIZE, "");
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
		cout << "\nOOPS! NOT PROGRAMMED YET!\n";
	
	system("pause");
}

int readDeck(vector<string> &deck, vector<string> &basics)
{
	ifstream inFile;
	int dup, i;

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

	return 0;
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

	for (int i = 0; i < HAND_SIZE; i++)
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
	for (int i = 0; i < HAND_SIZE; i++)
		if (hand_cards[i] == basic)
			return 1;

	return 0;
}

int checkHand(vector<string> &hand_cards, string subject)
{
	for (int i = 0; i < HAND_SIZE; i++)
		if (hand_cards[i] == subject)
			return 1;

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

// random_shuffle (deck.begin(), deck.end()) is the shuffling algorithm

int checkStartingHand(vector<string> &deck, vector<string> &hand, vector<string> &basics)
{
	int trials, count = 0;
	bool valid = false;
	string subject_card;

	vector<int> basicCount (basics.size(), 0);
	vector<string> uniqueBasicCombs (1, "");
	vector<int> uniqueBasicCombsCount;

	vector<string>::iterator it;
	vector<int>::iterator itt;

	system("cls");

	cout << "Number of trials to run: ";
	cin >> trials;

	for (int ii = 0; ii < trials; ii++)
	{	
		cout << "\rComputing trial " << ii << " out of " << trials << "...";
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
			if (uniqueBasicCombs[k].at(i) == '1')
				str += basics[i] + ", ";

		str.pop_back();
		str.pop_back();

		cout << str;

		cout << " (" << float(uniqueBasicCombsCount[k]) * 100 / float(trials) << "%)\n";
	}

	cout << "\n";

	return 0;
}

int vileSetup(vector<string> &deck, vector<string> &hand)
{


	return 0;
}