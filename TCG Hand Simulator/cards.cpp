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
	int c1_priority = 0, c2_priority = 0;			// Created a priority level for the two cards on the top of the deck, the lower one gets discarded

	for (int i = 0; i < priorities.size(); i++)		// Go through all of the priorities, and see if it matches each card
	{
		if (deck[0] == priorities[i])				// If the top card is the priority, increase the count of card one
			c1_priority = i;
		if (deck[1] == priorities[i])				// If the second top card is the priority, increase the count of card two
			c2_priority = i;
		if (deck[0] == deck[1])						// If the cards are identical, quit the whole thing and just choose card one
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

int trainersMail(vector<string> &deck, vector<string> &hand, vector<string> &trainers)
{
	vector<int> cardPriorities(4, 0);
	vector<int> numbers;

	for (int i = 0; i < 4; i++)						// Defining numbers
		numbers.push_back(i);

	for (int i = 0; i < trainers.size(); i++)		// Go through all of the priorities, and see if it matches each card
		for (int j = 0; j < 4; j++)					// Assigns priority to all 4 top cards
			if (deck[j] == trainers[i])
				cardPriorities[j] = i;

	Sort(cardPriorities, numbers);					// Sorts the card priorities, and sends the position of each with it

	hand.push_back(deck[numbers[3]]);				// Add highest priority card from the top 4 cards to hand
	deck.erase(deck.begin(), deck.begin() + 3);		// Erase card one through 4 from deck

	random_shuffle(deck.begin(), deck.end());		// Shuffles the deck afterwards :]

	return 0;
}

int ultraBall(vector<string> &deck, vector<string> &hand, vector<string> &priorities, vector<string> &pokemon)
{
	vector<int> cardPriorities(hand.size(), 0);
	vector<int> numbers;

	for (int i = 0; i < hand.size(); i++)				// Defining numbers
		numbers.push_back(i);

	if (hand.size() < 3)								// If there's not 3 cards in your hand to discard, you cant play Ultra Ball
		return 0;

	for (int i = 0; i < priorities.size(); i++)			// Go through all of the priorities, and see if it matches each card
		for (int j = 0; j < hand.size(); j++)			// Assigns priority to all cards in hand
			if (deck[j] == priorities[i])
				cardPriorities[j] = i;

	Sort(cardPriorities, numbers);						// Sorts the card priorities, and sends the position of each with it

	hand.erase(numbers[0] + hand.begin());				// Erase the card from hand with the lowest priority
	hand.erase(numbers[1] + hand.begin());				// Erase the card from hand with the second lowest priority

	for (int i = 0; i < deck.size(); i++)				// Searches deck for the Pokemon with the highest priority (Oddish -> Gloom -> Vileplume) (vileplume, gloom, oddish)
	{
		if (deck[i] == pokemon[pokemon.size() - 1])		// If the deck has the highest prioritized Pokemon, take it
		{
			hand.push_back(deck[i]);					// Put card in hand
			deck.erase(deck.begin() + i);				// Take card out from deck
			random_shuffle(deck.begin(), deck.end());	// Shuffles the deck afterwards :]
			break;										// Stops looping to save time
		}
	}

	return 0;
}

int levelBall(vector<string> &deck, vector<string> &hand, vector<string> &priorities, vector<string> &pokemon)
{
	vector<int> cardPriorities(hand.size(), 0);
	vector<int> numbers;

	for (int i = 0; i < hand.size(); i++)				// Defining numbers
		numbers.push_back(i);

	/*
	This function doesn't need to discard cards from hand, because that's what Level Ball does!
	*/

	if (pokemon.size() == 1)							// If only Vileplume is left, don't even grab a card
		return 0;

	for (int i = 0; i < deck.size(); i++)				// Searches deck for the Pokemon with the highest priority (Oddish -> Gloom) (gloom, oddish)
	{
		if (deck[i] == pokemon[pokemon.size() - 1])		// If the deck has the highest prioritized Pokemon, take it
		{
			hand.push_back(deck[i]);					// Put card in hand
			deck.erase(deck.begin() + i);				// Take card out from deck
			random_shuffle(deck.begin(), deck.end());	// Shuffles the deck afterwards :]
			break;										// Stops looping to save time
		}
	}

	return 0;
}