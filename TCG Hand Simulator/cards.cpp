#include <vector>
#include <algorithm>
using namespace std;

#define PRIZES 6

int Sort(vector<int> &str, vector<int> &in)
{
	for (int i = 0; i < in.size(); i++)
	{
		for (int j = 1; j < in.size(); j++)
		{
			if (in[j] > in[j - 1])
			{
				int temps;
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

int sycamore(vector<string> &deck, vector<string> &hand)
{
	hand.clear();								// Discards your hand

	for (int i = 0; i < 7; i++)					// For each of the 7 cards you draw
	{
		hand.push_back(deck[0]);				// Draws the first card of the deck
		deck.erase(deck.begin());				// Deletes this card from your deck
	}

	return 0;
}

int n(vector<string> &deck, vector<string> &hand)
{
	for (int i = 0; i < hand.size(); i++)		// For each of the cards in your hand
	{
		deck.push_back(hand[0]);				// Add the first card in your hand to the deck
		hand.erase(hand.begin());				// Erase the card that was copied over to the deck
	}

	random_shuffle(deck.begin(), deck.end());	// Shuffles the deck

	for (int i = 0; i < PRIZES; i++)			// For each of your prizes (it's going to be 6, this is the start of the game)
	{
		hand.push_back(deck[0]);				// Draws the first card of the deck
		deck.erase(deck.begin());				// Deletes this card from your deck
	}

	return 0;
}

int acroBike(vector<string> &deck, vector<string> &hand, vector<string> &priorities) // priorities HAS to be stored reverse (i.e. higher priorities at the end)
{
	int c1_priority = 0, c2_priority = 0;		// Created a priority level for the two cards on the top of the deck, the lower one gets discarded

	for (int i = 0; i < priorities.size(); i++)	// Go through all of the priorities, and see if it matches each card
	{
		if (deck[0] == priorities[i])			// If the top card is the priority, increase the count of card one
			c1_priority = i;
		if (deck[1] == priorities[i])			// If the second top card is the priority, increase the count of card two
			c2_priority = i;
		if (deck[0] == deck[1])					// If the cards are identical, quit the whole thing and just choose card one
		{
			c1_priority = 69;
			c2_priority = 0;
			break;
		}
	}

	if (c1_priority > c2_priority)					// If card one holds a greater priority than card two
	{
		hand.push_back(deck[0]);					// Add card one to hand
		deck.erase(deck.begin(), deck.begin() + 1);	// Erase card one and card two from your deck
	}

	else if (c2_priority > c1_priority)				// If card two holds a greater priority than card one
	{
		hand.push_back(deck[1]);					// Add card two to hand
		deck.erase(deck.begin(), deck.begin() + 1);	// Erase card one and card two from your deck
	}

	else											//  If both cards aren't priority, add card one because Wynaut
	{
		hand.push_back(deck[0]);					// Add card one to hand
		deck.erase(deck.begin(), deck.begin() + 1);	// Erase card one and card two from your deck
	}

	random_shuffle(deck.begin(), deck.end());		// Shuffles the deck afterwards :]

	return 0;
}

int trainersMail(vector<string> &deck, vector<string> &hand, vector<string> &priorities)
{
	vector<int> cardPriorities(4, 0);
	vector<int> numbers;

	for (int i = 0; i < 4; i++)						// Defining numbers
		numbers.push_back(i);

	for (int i = 0; i < priorities.size(); i++)		// Go through all of the priorities, and see if it matches each card
		for (int j = 0; j < 4; j++)					// Assigns priority to all 4 top cards
			if (deck[j] == priorities[i])
				cardPriorities[j] = i;

	Sort(cardPriorities, numbers);

	hand.push_back(deck[numbers[3]]);				// Add highest priority card from the top 4 cards to hand
	deck.erase(deck.begin(), deck.begin() + 3);		// Erase card one through 4 from deck

	random_shuffle(deck.begin(), deck.end());		// Shuffles the deck afterwards :]

	return 0;
}