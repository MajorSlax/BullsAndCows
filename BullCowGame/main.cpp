/*
	This is the console executable that makes use of the BullCow class.
	This acts as the view in a MVC pattern and is responsible for all user interactions for game logic.
	For game logic, see FBullCowGame class.
*/

#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// To make sybtax Unreal-friendly
using FText = std::string;
using int32 = int;

// Function prototypes, becaue we're outside a class
void PrintIntro();
void PlayGame();
bool AskToPlayAgain();
FText GetValidGuess();
void PrintGameResult();

FBullCowGame BCGame;

int main()
{
	PrintIntro();

	do {
		PlayGame();
	} while (AskToPlayAgain());

	return 0;
}

void PrintIntro() 
{
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n\n";
	return;
}

// play the game
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop while game is NOT won and there are tries remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();

		FBullCowCount result = BCGame.SubmitValidGuess(Guess);
		std::cout << "Bulls=" << result.Bulls << ", Cows=" << result.Cows << "\n\n";
	}

	PrintGameResult();
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word (y/n)? ";
	FText Response = "";
	getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

// get a guess from the player
FText GetValidGuess() 
{
	while (true) {
		FText Guess = "";
		std::cout << "Try " << BCGame.GetCurrentTry() << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
		getline(std::cin, Guess);

		EGuessStatus GuessStatus = BCGame.CheckGuessValidity(Guess);
		switch (GuessStatus) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter an isogram.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter only lowercase letters.\n\n";
			break;
		default:
			return Guess;
		}
	}
}

void PrintGameResult()
{
	if (BCGame.IsGameWon()) {
		std::cout << "You won! Congratulations!\n";
	}
	else {
		std::cout << "You lost. Better luck next time.\n";
	}
	std::cout << std::endl;
}
