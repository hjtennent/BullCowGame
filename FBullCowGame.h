/*The game logic (no view code or direct user interaction)
The game is a simple guess the word game based on Mastermind.
*/

#pragma once
#include <string>

using FString = std::string; //makes syntax Unreal friendly
using int32 = int;

//makes the FBullCowCount data type
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus //for checking status when validating guess
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};
/* Provides the key methods for the game
   to run, used throughout the game. Includes
    the constructor.*/
class FBullCowGame {
public:
	FBullCowGame(); //constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;

	void Reset();
	FBullCowCount SubmitValidGuess(FString);

private:
	int32 MyCurrentTry; //see constructor for intitialisation
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};
