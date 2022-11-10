#include <iostream>
#include <vector>
#include <windows.h>
#include "card.h"
#include <time.h>

enum faces { ace = 1, jack = 11, queen = 12, king = 13 };


//creates a randomized deck
std::vector<card> randomizeDeck(std::vector<card> deckToRandomize) {
	std::vector<card> randomizedDeck;
	for (int i = 52; i > 0; i--)
	{
		int cardToAddIndex = rand() % i;
		randomizedDeck.push_back(deckToRandomize[cardToAddIndex]);
		deckToRandomize.erase(deckToRandomize.begin()+ cardToAddIndex);
	};
	return randomizedDeck;
}

std::vector<card> createOrderedDeck() {
	std::string cardFaces[4] = { "Hearts","Clubs","Diamonds","Spades" };
	std::vector <card> orderedDeck;

	//create a ordered deck
	int deckPointer = 0;
	for (int i = 0; i < 2; i++) {
		for (int j = 1; j <= 13; j++)
		{
			orderedDeck.push_back({ cardFaces[i], j });
			deckPointer++;
		};
	};
	for (int i = 2; i < 4; i++) {
		for (int j = 13; j > 0; j--)
		{
			orderedDeck.push_back({ cardFaces[i], j });
			deckPointer++;
		};
	}
	return orderedDeck;
}

int main() {
	srand(time(NULL));

	std::vector<card> orderedDeck = createOrderedDeck();
	std::vector<card> randomizedDeck = randomizeDeck(orderedDeck);
	std::vector<card> playerCards;
	std::vector<card> dealerCards;
	int playerTotal;
	int dealerTotal;
	int playerAceFix = 0;
	int dealerAceFix = 0;
	bool playerLost = false;

	for (int i = 0; i < 2; i++)
	{
		playerCards.push_back(randomizedDeck.back());
		randomizedDeck.pop_back();
	};
	
	while (true) {
		int playerCardsCumVal = 0;
		std::cout << "Your cards are: \n";

		for (card tempCard : playerCards) {
			int tempCardVal = tempCard.returnVal();
			switch (tempCardVal) {
				case 1:
					std::cout << "Ace ";
					playerCardsCumVal += 11;
					playerCardsCumVal -= playerAceFix * 10;
					break;
				case 11:
					std::cout << "Jack ";
					playerCardsCumVal += 10;
					break;
				case 12:
					std::cout << "Queen ";
					playerCardsCumVal += 10;
					break;
				case 13:
					std::cout << "King ";
					playerCardsCumVal += 10;
					break;
				default:
					std::cout << tempCardVal << " ";
					playerCardsCumVal += tempCardVal;
					break;
			};

			std::cout << "of " << tempCard.returnFace() << std::endl;
			
		};

		if (playerCardsCumVal > 21) {
			if (playerAceFix != playerCards.size() - 1) {
				for (int i = 0; i < playerCards.size() -1; i++)
				{
					if (playerCards[i].returnVal() == 1) {
						playerAceFix += 1;
						playerCardsCumVal -= 10;
						break;
					}
				}
				
			}
		}

		if (playerCardsCumVal > 21) {
			std::cout << "You've gone bust!\n";
			playerLost = true;
			break;
		}


		std::cout << "Would you like to Hit(H), or Stick(S): ";
		std::string input;
		std::cin >> input;

		if (input == "H"){
			playerCards.push_back(randomizedDeck.back());
			randomizedDeck.pop_back();
			playerCardsCumVal += playerCards.back().returnVal();
		}
		else 
		{
			playerTotal = playerCardsCumVal;	
			break;
		};

	};


	for (int i = 0; i < 2; i++)
	{
		dealerCards.push_back(randomizedDeck.back());
		randomizedDeck.pop_back();
	};

	while (true) {
		int dealerCardsCumVal = 0;
		std::cout << "Dealer's cards are: \n";

		for (card tempCard : dealerCards) {
			int tempCardVal = tempCard.returnVal();
			switch (tempCardVal) {
			case 1:
				std::cout << "Ace ";
				dealerCardsCumVal += 11;
				dealerCardsCumVal -= dealerAceFix * 10;
				break;
			case 11:
				std::cout << "Jack ";
				dealerCardsCumVal += 10;
				break;
			case 12:
				std::cout << "Queen ";
				dealerCardsCumVal += 10;
				break;
			case 13:
				std::cout << "King ";
				dealerCardsCumVal += 10;
				break;
			default:
				std::cout << tempCardVal << " ";
				dealerCardsCumVal += tempCardVal;
				break;
	
			};
			std::cout << "of " << tempCard.returnFace() << std::endl;
		}
		if (playerLost) {
			break;
		}
		if (dealerCardsCumVal > 21) {
			if (dealerAceFix != dealerCards.size() - 1) {
				for (int i = 0; i < dealerCards.size() - 1; i++)
				{
					if (dealerCards[i].returnVal() == 1) {
						dealerAceFix += 1;
						dealerCardsCumVal -= 10;
						break;
					}
				}
			}
		}
		if (dealerCardsCumVal > 21) {
			std::cout << "Dealer's gone bust!\n";
			break;
		}
		if (dealerCardsCumVal >= 17) {
			if (dealerCardsCumVal >= playerTotal) {
				std::cout << "Dealer is better than player!\n";
				playerLost = true;
				break;
			}
		}
		if (dealerCardsCumVal < 17) {
			Sleep(2000);
			std::cout << "Dealer hits!\n";

			dealerCards.push_back(randomizedDeck.back());
			randomizedDeck.pop_back();
			dealerCardsCumVal += dealerCards.back().returnVal();
		}
	}
	if (playerLost) {
		std::cout << "Dealer wins!";
	}
	else {
		std::cout << "You win!";
	}
	std::cin;

}