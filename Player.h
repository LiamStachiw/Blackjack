/*
Authors:			Liam Stachiw, Max O'Connor, Miguel Macciocchi
Date: 				Jan 10, 2018
File Name:	 		Player.h
Description: 		This file will create a class called Player, containing information related to the blackjack player. 
*/

#ifndef _PLAYER
#define _PLAYER

#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include "MyInputValidation.h"
#include "StandardDeck.h"

using namespace std;

class Player
{
	public:
		//Default Constructor
		Player(string name = "Player", int chips = 1000);
		
		//Accessors
		string GetName() const { return myName; }
		int GetChips() const { return myChips; }
		int GetHandValue();
		void ShowHand();
		
		//Mutators
		bool SetName(string nameValue);			
		bool SetChips(int chipsValue);		
		void AddCard(StandardPlayingCard drawnCard);
		void ResetHand();	
		void UpdateChips(int changeAmount, bool bet);
		void ChangeAceValue();
		
		vector<StandardPlayingCard> myHand;
		
	private:
		string myName;
		int myBet;
		int myChips;
		//vector<StandardPlayingCard> myHand;
};

//Constructor
Player::Player(string name, int chips)
{
	SetName(name);
	SetChips(chips);
}

//Sets the player's name
bool Player::SetName(string nameValue) 
{ 
	if (nameValue.empty())
	{
		return false;
	}
	else
	{
		myName = nameValue;		
		return true;
	}			 
}

//Set the player's chip count
bool Player::SetChips(int chipsValue)
{
	const int MAX_CHIPS = 100000;
	
	if (cin.fail() || chipsValue <= 0 || chipsValue > MAX_CHIPS)
	{
		return false;
	}
	else
	{
		myChips = chipsValue;
		return true;
	}
}

//Adds a card to the player's hand
void Player::AddCard(StandardPlayingCard drawnCard)
{
	myHand.push_back(drawnCard);
}

//Shows all cards in the player's hand
void Player::ShowHand()
{
	int vectorSize = myHand.size();
	
	string fileName = "blackjack_log.txt";
	ofstream outputFile;
	outputFile.open(fileName, std::ios_base::app);
	
	for(int i = 0; i < vectorSize; i++)
	{
		if(myHand.at(i).isFaceUp == true)
		{
			string currentCard = myHand.at(i);
			
			cout << "\n" << currentCard;
			outputFile << "\n" << currentCard;
		}
	}
	
	cout << endl;
}

//Empties all elements of the player's hand
void Player::ResetHand()
{
	myHand.clear();
}

//Update the player's chip count
void Player::UpdateChips(int changeAmount, bool bet)
{
	if(bet == false)
	{
		myChips += changeAmount;
	}
	else if(bet == true)
	{
		myChips -= changeAmount;
	}
}

//Get the value of the player's hand
int Player::GetHandValue()
{
	int vectorSize = myHand.size();
	int handValue = 0;
	
	for(int i = 0; i < vectorSize; i++)
	{
		if(myHand.at(i).isFaceUp == true)
		{
			handValue += myHand.at(i).getValue();
		}
	}
	
	return handValue;
}

#endif
