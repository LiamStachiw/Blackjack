/*
Original Authors:	Keith Mathur & Liam Stachiw
Modified By	:		Liam Stachiw, Max O'Connor, Miguel Macciocchi
Date: 				Jan 10, 2018
File Name:	 		StandardDeck.h
Description: 		This file will create a class called StandardDeck, containing objects of the StandardPlayingCard class. 
*/

#ifndef _STD_DECK
#define _STD_DECK

#include <iostream>
#include <algorithm>
#include <ctime>
#include "StandardPlayingCard.h"

using namespace std;

class StandardDeck
{
	public:
		//default constructor
		StandardDeck(int playingCards = 0);
		
		//destructor
		~StandardDeck();
		
		//copy constructor
		StandardDeck(const StandardDeck&);
		
		//overloaded assignment operator
		StandardDeck& operator=(const StandardDeck&);
		
		
		/*******
		ACCESSORS
		********/
		//CardsRemaining Method
		void CardsRemaining();
		
		
		/*******
		MUTATORS
		********/
		
		//initialize method
		void Initialize(int playingCardsArrayStartingSize);
		
		//DrawNextCard Method
		StandardPlayingCard DrawNextCard();
		
		//DrawRandomCard Method
		string DrawRandomCard();
		
		//Shuffle method
		void Shuffle();
		
		
	private:
		StandardPlayingCard *playingCards; //member of StandardPlayingCard class initially set to 0
		
		int playingCardsArrayStartingSize = 52; //move to initialize
};

//constructor
StandardDeck::StandardDeck(int deckArraySize)
{
	//call the initialize method
	Initialize(deckArraySize);
}

//Destructor
StandardDeck::~StandardDeck()
{
	//delete the deck
	delete [] playingCards;	
}

//copy constructor
StandardDeck::StandardDeck(const StandardDeck& oldDeck) 
{
	playingCardsArrayStartingSize = oldDeck.playingCardsArrayStartingSize; //the deck size is equal to the deck size of the object being copied
	
	//Copy the value from each array element in the deck object being copied
	for(int copyArray = 0; copyArray < playingCardsArrayStartingSize; copyArray++)
	{
		playingCards[copyArray] = oldDeck.playingCards[copyArray];
	}
}

//assignment operator (acts similar to the copy constructor)
StandardDeck& StandardDeck::operator=(const StandardDeck& oldDeck)
{
	playingCardsArrayStartingSize = oldDeck.playingCardsArrayStartingSize; //the deck size is equal to the deck size of the object being copied
	
	//Copy the value from each array element in the deck object being copied
	for(int copyArray = 0; copyArray < playingCardsArrayStartingSize; copyArray++)
	{
		playingCards[copyArray] = oldDeck.playingCards[copyArray];
	}
} 

//cards remaining 
void StandardDeck::CardsRemaining() 
{
	//output the number of cards remaining in the deck
	cout << endl << playingCardsArrayStartingSize << " cards remain in the deck.\n";
}

//initialize
void StandardDeck::Initialize(int deckArraySize)
{
	//fill the deck
	playingCards = new StandardPlayingCard [deckArraySize];
	
	//Get the suits and ranks for each card in the deck
	for(int cardCounter = 0; cardCounter < playingCardsArrayStartingSize; cardCounter++)
	{		
		playingCards[cardCounter].setSuit(cardCounter / (StandardPlayingCard::MAX_RANK));
		playingCards[cardCounter].setRank(1 + cardCounter % (StandardPlayingCard::MAX_RANK));
	}
}

//draw next card
StandardPlayingCard StandardDeck::DrawNextCard()
{
	StandardPlayingCard nextCardDrawn = playingCards[0]; //The next card drawn is the top element in the array
	
	playingCardsArrayStartingSize--; //decrease the size of the deck by one card
	
	//move the position of each card (element) in the deck (array) up by one. Prepares for the next potential draw.
	for(int positionCount = 0; positionCount < playingCardsArrayStartingSize; positionCount++)
	{
		playingCards[positionCount] = playingCards[positionCount + 1];
	}
	
	int *playingCards;
	playingCards = new int[playingCardsArrayStartingSize]; // dynamically allocate memory using new
	
	
	return nextCardDrawn; //returns the string value of the card drawn
}

//draw random card
string StandardDeck::DrawRandomCard() 
{
	playingCardsArrayStartingSize--; //decrease the size of the deck by one card
	
	//set teh value of the random card drawn to a random card between 0 and the size of the array
	int randomCard = rand() % playingCardsArrayStartingSize;
	string randomCardDrawn = playingCards[randomCard];	
	
	int *playingCards;
	playingCards = new int[playingCardsArrayStartingSize]; // dynamically allocate memory using new
	
	//move the position of each card (element) in the deck (array) up by one. Prepares for the next potential draw.
	for(int positionCount = randomCard; positionCount < playingCardsArrayStartingSize; positionCount++)
	{
		playingCards[positionCount] = playingCards[positionCount + 1];
	}
	
	return randomCardDrawn; //return the string value of the random card drawn
}

//shuffle method
void StandardDeck::Shuffle() 
{
	//random_shuffle(playingCards) //reference vectors9.algorithm.cpp from OOP content	
	for (int cardToSwap = 0; cardToSwap < playingCardsArrayStartingSize; cardToSwap++) {
            int secondCard = rand() % playingCardsArrayStartingSize;  // generate a random position
            StandardPlayingCard temp = playingCards[cardToSwap]; 
			playingCards[cardToSwap] = playingCards[secondCard]; 
			playingCards[secondCard] = temp;
        }
}

#endif
