#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <vector>
using namespace std;

#define DECK_SIZE 60
#define HAND_SIZE 7
#define PRIZES 6

int readDeck(string[], vector<string>&);
int constructHand(string[], string[]);
int checkMulligan(string[], string);
int checkHand(string[], string);

int checkStartingHand(string[], string[], vector<string>&);

int main()
{
	string deck[DECK_SIZE], hand[HAND_SIZE];

	vector<string> basics;

	readDeck(deck, basics);
	/*
	constructHand(deck, hand);
	
	while (!checkMulligan(hand, "beedrill") && !checkMulligan(hand, "talonflame"))
		constructHand(deck, hand);
	*/
	checkStartingHand(deck, hand, basics);
	
	system("pause");
}

int readDeck(string deck[], vector<string> &basics)
{
	ifstream inFile;
	int dup, i;

	inFile.open("deck.txt");

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

int constructHand(string deck[], string hand[])
{
	int used[DECK_SIZE] = { 0 };
	random_device rd;
	srand(rd());

	for (int i = 0; i < HAND_SIZE; i++)
	{
		int temp = rand() % DECK_SIZE;

		while (used[temp] != 0)
			temp = rand() % DECK_SIZE;

		used[temp]++;

		hand[i] = deck[temp];
	}

	return 0;
}

int checkMulligan(string hand_cards[], string basic)
{
	for (int i = 0; i < HAND_SIZE; i++)
		if (hand_cards[i] == basic)
			return 1;

	return 0;
}

int checkHand(string hand_cards[], string subject)
{
	for (int i = 0; i < HAND_SIZE; i++)
		if (hand_cards[i] == subject)
			return 1;

	return 0;
}

int checkStartingHand(string deck[], string hand[], vector<string> &basics)
{
	int trials, count = 0;
	bool valid = false;
	string subject_card;

	cout << "Desired card: ";
	cin >> subject_card;

	for (int i = 0; i < DECK_SIZE; i++)
		if (deck[i] == subject_card)
			valid = true;

	while (!valid)
	{
		system("cls");
		cout << "The card " << subject_card << " is not in your deck.\n" << "Desired card: ";
		cin >> subject_card;

		for (int i = 0; i < DECK_SIZE; i++)
			if (deck[i] == subject_card)
				valid = true;
	}

	cout << "Number of trials to run: ";
	cin >> trials;

	for (int i = 0; i < trials; i++)
	{
		constructHand(deck, hand);
		
		int c = 0;

		do
		{
			constructHand(deck, hand);

			c = 0;

			for (int i = 0; i < basics.size(); i++)
				if (checkMulligan(hand, basics[i]))
					c++;
		} while (c == 0);
		/*
		for (int i = 0; i < HAND_SIZE; i++)		// Outputs hands 
			cout << hand[i] << "\t";

		cout << "\n";
		*/
		checkHand(hand, subject_card);

		count += checkHand(hand, subject_card);
	}

	cout << "Out of " << trials << " starting hands, " << count << " included " << subject_card << " (" << 100 * float(count) / float(trials) << "%).\n";

	return 0;
}