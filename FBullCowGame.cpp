#pragma once
#include "FBullCowGame.h"
#include <map>
//make syntax more Unreal friendly
#define TMap std::map
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); } //default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); } //so main code doesn't
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }						// call the public variables

int32 FBullCowGame::GetMaxTries() const {
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,15}, {7,20} }; //maps the number of tries
	return  WordLengthToMaxTries[MyHiddenWord.length()];							 // to the length of the word
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "plane"; //This MUST be an isogram
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;	
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) //if the guess is not isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess)) //if the guess isn't all lowercase
	{
		return EGuessStatus::Not_Lowercase; //TODO write a function
	}
	else if (Guess.length() != GetHiddenWordLength()) //if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

//receives a valid guess, increments turn and return count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); //assuming same length as guess

	//loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		//compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) 
		{
			//if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				if (MHWChar == GChar) {	//if they're in the same place
					BullCowCount.Bulls++; //increment bulls
				}
				else {
					BullCowCount.Cows++; //must be a cow
				}

			}
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;		//game win condition
	}
	else {
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	//treat 0 and 1 letter strings, as isograms
	if (Word.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen; 	//setup map

	for (auto Letter : Word)	//for all letters of the word
	{
		Letter = tolower(Letter); //handle mixed case
		//if the letter is in the map
		if (LetterSeen[Letter]) { 
			return false;	//we do NOT have an isogram
		} else {
			LetterSeen[Letter] = true; //we DO have an isogram
		}
	}
			
	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter)) 
		{ 
			return false; //if not a lowercase letter, return false.
		}
	}
	return true;
}
