#include <iostream>
#include <fstream>
#include <string>
#include <random>
using namespace std;

#define DECK_SIZE 60
#define HAND_SIZE 7
#define PRIZES 6

int readDeck(string[]);
int constructHand(string[], string[]);
int checkMulligan(string[], string);
int checkHand(string[], string);

int checkStartingHand(string[], string[]);

int main()
{
	string deck[DECK_SIZE], hand[HAND_SIZE];

	readDeck(deck);
	constructHand(deck, hand);

	while (!checkMulligan(hand, "beedrill") && !checkMulligan(hand, "talonflame"))
		constructHand(deck, hand);

	checkStartingHand(deck, hand);

	system("pause");
}

int readDeck(string deck[])
{
	ifstream inFile;
	int dup, i;

	inFile.open("deck.txt");

	for (i = 0; i < DECK_SIZE; 1)
	{
		inFile >> dup;

		inFile >> deck[i];

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

int checkStartingHand(string deck[], string hand[])
{
	int trials, count = 0;
	string subject_card;

	cout << "Desired card: ";
	cin >> subject_card;

	cout << "Number of trials to run: ";
	cin >> trials;

	for (int i = 0; i < trials; i++)
	{
		constructHand(deck, hand);

		while (!checkMulligan(hand, "beedrill") && !checkMulligan(hand, "talonflame"))
			constructHand(deck, hand);

		count += checkHand(hand, subject_card);
	}

	cout << "Out of " << trials << " hands, " << count << " included " << subject_card << " (" << 100 * float(count) / float(trials) << "%).\n";

	return 0;
}