#pragma once

#include "FBullCowGame.h"
#include <map>
#define TMap std::map

FBullCowGame::FBullCowGame()
{
	Reset();
}

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap<int32, int32> WordLengthToMaxTries{
		{3, 4}, {4, 7}, {5, 10}, {6, 15}, {7, 20}
	};

	return WordLengthToMaxTries[GetHiddenWordLength()];
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "planet"; // This MUST be an isogram

	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;

	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) {
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowerCase(Guess)) {
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) {
		return EGuessStatus::Wrong_Length;
	}
	else {
		return EGuessStatus::OK;
	}
}

// receives valid guess, increments try count and return bulls/cows counts
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount result;

	// loop through all letters in guess
	int32 HiddenWordLength = GetHiddenWordLength();
	int32 GuessWordLength = Guess.length();
	for (int32 i = 0; i < GuessWordLength; i++) {
		char currentChar = Guess[i];
		for (int32 j = 0; j < HiddenWordLength; j++) {
			if (currentChar == MyHiddenWord[j]) {
				if (i == j) {
					result.Bulls++;
				} else {
					result.Cows++;
				}
			}
		}
	}

	if (result.Bulls == HiddenWordLength) {
		bGameIsWon = true;
	}

	return result;
}

bool FBullCowGame::IsIsogram(FString Guess) const
{
	if (Guess.length() < 2) { return true; }

	TMap<char, bool> LetterSeen;

	// auto: let the compiler figure out the type
	for (auto Letter : Guess) {
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) {
			return false;
		} else {
			LetterSeen[Letter] = true;
		}
	}

	return true;
}

bool FBullCowGame::IsLowerCase(FString Guess) const
{
	if (Guess.length() < 2) { return true; }
	for (auto Letter : Guess) { if (!islower(Letter)) return false; }
	return true;
}
