/*
Authors:			Liam Stachiw, Max O'Connor, Miguel Macciocchi
Date: 				Jan 10, 2018
File Name:	 		Blackjack.cpp
Description: 		This file will allow the user to play Blackjack using many functions, classes etc.
*/

#include <iostream>
#include <algorithm>
#include <ctime>
#include <string>
#include <fstream>
#include "MyInputValidation.h"
#include "StandardPlayingCard.h"
#include "StandardDeck.h"
#include "Player.h"

using namespace std;

Player gameOfBlackjack(Player userPlayer);	//function prototype

int main()
{
	const int STARTING_CHIPS = 1000;	//amount of chips the player will start with
	
	//variable declarations
	char choice;
	string playerName;
	int chipCount;
	int bet;
	bool isPlaying = true;
	
	time_t t = time(0);
	struct tm * now = localtime( & t );
	
	string fileName = "blackjack_log.txt";
	ofstream outputFile;
	outputFile.open(fileName, std::ios_base::app);
	
	srand (time(NULL)); //random seed for drawing a random card
	
	//Header
	cout << "**********************************" << endl;
	cout << "************BLACKJACK*************" << endl;
	cout << "**********************************" << endl;
	
	outputFile << "\n\n**********************************" << endl;
	outputFile << "APPLICATION START -- " 
			   << (now->tm_year + 1900) << '-'
			   << (now->tm_mon + 1) << '-'
			   << now->tm_mday << " - "
			   << (1 + now->tm_hour) << ':'
			   << (1 + now->tm_min) << ':'
			   << (1 + now->tm_sec) << endl;
	outputFile << "**********************************" << endl;
	
	//Get the player's name
	cout << "Please enter your name: ";
	cin >> playerName;
	
	Player userPlayer(playerName, STARTING_CHIPS);	//create a player object
	
	do
	{		
		//Clear the screen and display a new header
		system("cls");
		cout << "**********************************" << endl;
		cout << "************MAIN MENU*************" << endl;
		cout << "**********************************" << endl;
		
		//if the player has 0 or less chips
		if(userPlayer.GetChips() <= 0)
		{
			cout << "You have run out of chips. Better luck next time!" << endl;
			outputFile << endl << userPlayer.GetName() << " has run out of chips." << endl;
			isPlaying = false;
		}
		else
		{				
			//Show the prompts
			cout << "N - Play a new game." << endl;
			cout << "E - Exit the program." << endl << endl;
			
			cout << "Enter your choice: ";
			cin >> choice;
			
			switch(choice)
			{
				case 'n': 
				case 'N':
					userPlayer = gameOfBlackjack(userPlayer);	//start a new game
					break;
				case 'e':
				case 'E':					
					isPlaying = false;	//exit the loop
					break;
				default:
					cout << "Not a valid choice. Please choose again." << endl;	//prompt for another choice
					break;
			}
		}
	}while (isPlaying);//while the user is playing
	
	
	outputFile << "\n\n**********************************" << endl;
	outputFile << "APPLICATION END -- " 
			   << (now->tm_year + 1900) << '-'
			   << (now->tm_mon + 1) << '-'
			   << now->tm_mday << " - "
			   << (1 + now->tm_hour) << ':'
			   << (1 + now->tm_min) << ':'
			   << (1 + now->tm_sec) << endl;
	outputFile << "**********************************" << endl;
	outputFile.close();
	
	return 0;
}

//Function to run a game of blackjack
Player gameOfBlackjack(Player userPlayer)
{
	//variable declarations
	int deckArraySize = 52; //initial size of the deck array
	int betAmount;
	int surrenderCount = 0;
	bool isValidBet = false;
	bool gameOn = true;
	bool surrender = false;
	bool firstFlip = false;
	bool isStaying = false;
	bool dealerGo = true;
	char choice;
	
	time_t t = time(0);
	struct tm * now = localtime( & t );
	
	string fileName = "blackjack_log.txt";
	ofstream outputFile;
	outputFile.open(fileName, std::ios_base::app);
	
	userPlayer.ResetHand();	//reset the player's had to not have any cards in it
	
	//Create a new deck object and dealer object
	StandardDeck deck(deckArraySize);
	Player dealer("Dealer", 0);
	
	//Clear the screen and display a new header
	system("cls");		
	cout << "*********************************" << endl;
	cout << "************NEW GAME*************" << endl;
	cout << "*********************************" << endl;
	
	outputFile << "\n\nNew Game Started -- "
			   << (now->tm_year + 1900) << '-'
			   << (now->tm_mon + 1) << '-'
			   << now->tm_mday << " - "
			   << (1 + now->tm_hour) << ':'
			   << (1 + now->tm_min) << ':'
			   << (1 + now->tm_sec) << endl;
	
	//While the user entered a valid bet
	while(isValidBet == false)
	{	
		//prompt the user
		cout << "Your chip count is " << userPlayer.GetChips() << "." << endl << endl;
		cout << "Please enter the amount you would like to bet: ";
		betAmount = myValidation::GetValidInteger();
		
		//If the user has enough chips for the bet placed
		if(betAmount <= userPlayer.GetChips())
		{
			//Remove the bet from the user's chips
			isValidBet = true;
			userPlayer.UpdateChips(betAmount, true);
			//outputFile << userPlayer.GetName() << " bets " << betAmount << endl;
		}
		else
		{
			cout << "ERROR! Bet placed was greater than your amount of chips. Your bet must be " << userPlayer.GetChips() << "or less." << endl;
		}
	}
	
	deck.Shuffle();	//shuffle the deck
	
	//Give the player and dealer thier 2 inital cards
	userPlayer.AddCard(deck.DrawNextCard());
	dealer.AddCard(deck.DrawNextCard());
	userPlayer.AddCard(deck.DrawNextCard());
	dealer.AddCard(deck.DrawNextCard());
	dealer.myHand.at(1).flipCard();
	
	//Display the user's cards
	cout << "\nYour cards are: ";
	outputFile << "\n\n" << userPlayer.GetName() << "'s hand:"; 
	userPlayer.ShowHand();
	cout << "Your hand is worth: " << userPlayer.GetHandValue() << endl << endl;
	
	//Display the dealer's cards
	cout << "The dealer's cards are: ";
	outputFile << "\n\nDealer's hand:";
	dealer.ShowHand();
	cout << "The Dealer's hand is worth: " << dealer.GetHandValue() << endl << endl;
	
	//While the game still needs to be played
	while(gameOn)
	{			
		if(isStaying == false)
		{
			//Display the user's options
			cout << "\n\nH - Hit." << endl;
			cout << "S - Stay." << endl;
			cout << "D - Double Down." << endl;
			cout << "R - Surrender." << endl << endl;
			//Prompt the user
			cout << "Enter your choice: ";
			cin >> choice;
		
			switch(choice)
			{
				case 'h': 
				case 'H': 
					outputFile << "\n\n" << userPlayer.GetName() << ": Hit!" << endl;
					//Add another card to the user's hand
					userPlayer.AddCard(deck.DrawNextCard());
					outputFile << "\n\n" << userPlayer.GetName() << "'s cards are now:" << endl;
					cout << "Your cards are now: ";
					userPlayer.ShowHand();
					cout << "Your hand is now worth: " << userPlayer.GetHandValue() << endl << endl;
					dealerGo = true;
					//If the user busts
					if(userPlayer.GetHandValue() >= 21)
					{
						gameOn = false;//player busted, end the game
						dealerGo = false;
					}
					break;
				case 's':
				case 'S':
					//end the game
					outputFile << "\n\n" << userPlayer.GetName() << ": Stay!" << endl;
					isStaying = true;
					break;
				case 'd':
				case 'D':
					//If the user has enough chips to double down
					if(betAmount*2 <= userPlayer.GetChips())
					{
						//Add a card to the user's hand
						userPlayer.AddCard(deck.DrawNextCard());
						userPlayer.UpdateChips(betAmount, true);
						//Double the bet amount
						betAmount += betAmount;
						cout << "\nDOUBLE DOWN!" << endl;
						outputFile << "\n\n" << userPlayer.GetName() << ": DOUBLE DOWN!" << endl;
						cout << "\nYour bet is now: " << betAmount << endl;
						outputFile << "\n\n" << userPlayer.GetName() << "'s cards are now:";
						cout << "\nYour cards are now: ";
						userPlayer.ShowHand();
						cout << "\nYour hand is now worth: " << userPlayer.GetHandValue() << endl << endl;
						gameOn = false;
						dealerGo = true;
					}
					else
					{
						cout << "\nYou do not have enough chips to double down. Please select another action." << endl;
						dealerGo = false;
					}
					break;
				case 'r':
				case 'R':
					//if it is the inital draw
					if (surrenderCount == 0)
					{
						//Give the user half their bet back and end the game
						outputFile << "\n\n" << userPlayer.GetName() << ": Surrender!" << endl;
						betAmount = betAmount / 2;
						userPlayer.UpdateChips(betAmount, false);
						gameOn = false;
						surrender = true;
					}
					else
					{
						cout << "Surrendering is only allowed on the inital draw. Please select another action.";
						dealerGo = false;
					}
					break;
				default:
					cout << "Not a valid choice. Please choose again." << endl;
					dealerGo = false;
					break;
			}
		}
		
		surrenderCount += 1;	//Increment the surrender counter
		
		//If the dealer hasn't flipped his hard yet
		if(firstFlip == false && surrender == false && dealerGo == true)
		{
			dealer.myHand.at(1).flipCard();
			firstFlip = true;
			//Hit and add another card
			cout << "\nDealer flips his second card." << endl << endl;
			outputFile << "\n\nDealer's cards are now:";
			cout << "The dealer's cards are now: ";
			dealer.ShowHand();
			cout << "The Dealer's hand is now worth: " << dealer.GetHandValue() << endl << endl;			
		}
		
		//If the user hasn't busted yet
		if(userPlayer.GetHandValue() < 21 && surrender == false && dealerGo == true)
		{
			//While the dealer's cards are worth less than 17
			if(dealer.GetHandValue() < 17)
			{
				//Hit and add another card
				cout << "Dealer HITS." << endl << endl;
				outputFile << "\n\nDealer: Hit!" << endl;
				dealer.AddCard(deck.DrawNextCard());
				outputFile << "\n\nDealer's hand:";
				cout << "The dealer's cards are now: ";
				dealer.ShowHand();
				cout << "The Dealer's hand is now worth: " << dealer.GetHandValue() << endl << endl;
			}	
			//If the dealer's cards are less than 21
			else if(dealer.GetHandValue() >= 17 && dealer.GetHandValue() < 21)
			{
				cout << "\nDealer STAYS." << endl << endl;
				outputFile << "\n\nDealer: Stays!" << endl;
				dealerGo = false;
				
				if (isStaying == true)
				{
					gameOn = false;
				}
			}
			//If the dealer busts
			if(dealer.GetHandValue() >= 21 || userPlayer.GetHandValue() == 21)
			{
				gameOn = false;
			}	
		}
	}
	
	//If the user surrendered
	if(surrender == true)
	{
		cout << "You have surrendered. You have gotten " << betAmount << " chips back. Your chip count is now " << userPlayer.GetChips() << endl;
		outputFile << "\n\nFINAL - " << userPlayer.GetName() << " has surrendered. Chip count: " << userPlayer.GetChips() << endl; 
	}
	//If the user busted
	else if(userPlayer.GetHandValue() > 21)
	{
		cout << "BUST!" << endl << endl;
		cout << "Sorry, you lost! Your chip count is now " << userPlayer.GetChips() << endl;
		outputFile << "\n\nFINAL - " << userPlayer.GetName() << ": " << userPlayer.GetHandValue() << "\tDealer: " << dealer.GetHandValue() << endl
				   << "DEALER HAS WON!\n" << endl;
	}
	//if the dealer busted
	else if(dealer.GetHandValue() > 21)
	{
		cout << "Dealer BUSTS!" << endl << endl;
		userPlayer.UpdateChips(betAmount*2, false);
		cout << "Congratulations, you won! Your chip count is now " << userPlayer.GetChips() << endl;
		outputFile << "\n\nFINAL - " << userPlayer.GetName() << ": " << userPlayer.GetHandValue() << "\tDealer: " << dealer.GetHandValue() << endl
				   << userPlayer.GetName() << " HAS WON!\n" << endl;
	}
	//if the dealer has a better hand than the user
	else if(dealer.GetHandValue() >= userPlayer.GetHandValue())
	{
		cout << "Sorry, you lost! Your chip count is now " << userPlayer.GetChips() << endl;
		outputFile << "\n\nFINAL - " << userPlayer.GetName() << ": " << userPlayer.GetHandValue() << "\tDealer: " << dealer.GetHandValue() << endl
				   << "DEALER HAS WON!\n" << endl;
	}
	//if the user has a better hand than the dealer
	else if(userPlayer.GetHandValue() > dealer.GetHandValue())
	{
		userPlayer.UpdateChips(betAmount*2, false);
		cout << "Congratulations, you won! Your chip count is now " << userPlayer.GetChips() << endl;
		outputFile << "\n\nFINAL - " << userPlayer.GetName() << ": " << userPlayer.GetHandValue() << "\tDealer: " << dealer.GetHandValue() << endl
				   << userPlayer.GetName() << " HAS WON!\n" << endl;
	}
	
	outputFile << userPlayer.GetName() <<  " now has " << userPlayer.GetChips() << " chips." << endl;
	
	system("pause");	//pause the system
	return userPlayer;	//return the userPlayer object
	
}
