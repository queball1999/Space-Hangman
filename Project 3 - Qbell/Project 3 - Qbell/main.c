/*	ENG175IN	Summer 2020
 *
 *	NOT personally written by Quynn. Code was provided from outside source and modified.
 *
 *	Author:	Quynn Bell
 *
 *	Date Modified:	24th of June 2020
 *
 *	Copyright @Qbell.	All Rights Reserved.
 *
 *	Program Function:	Hangman Game
 */

#define _CRT_SECURE_NO_WARNINGS

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define MAXLEN 20            // maximum word length
#define MAXGUESS 12            // maximum number of guesses allowed
#define NUMWORDS 26            // number of words in hangman's dictionary

int getword(int[]);            /* chooses a word from the dictionary for the user to guess -- uses a random number
									   generator to determine which word to choose; a counter array is used to prevent
									   the same word being used twice until all words have been exhausted */

void initguess(char[]);        // initializes array that holds user's correct guesses to '_' character

char getguess();        // reads in the letter guessed by the user

int processguess(char[], char[], int, char);    /* compares guessed letter with word to be guessed
												--if guess is correct, letter is placed in user's word array;
												otherwise, wrong guesses are counted */

int checkwin(char[], char[], int);    // checks to see if user has won by matching the two arrays

void showLogo();

void printInstructions();

void drawfig(const int, char storeGuess[40], int i);    // draws hangman figure based on the number of wrong guesses by the user

void easterEGG(char storeGuess[40], int i);

//****************************************** INT  MAIN  VOID  ***********************************************
int main(void) {

	//hangman dictionary:  List of Flowers a to z
	char* secrets[NUMWORDS] = { "asteroid", "booster", "comet", "darkmatter", "earth", "fuselage", "gemini",
		"hubble", "interstellar", "jupiter", "kepler", "lightyear", "meteorite", "neptune",
		"orion", "pluto", "quasar", "rocketship", "saturn", "telescope", "uranus", "venus",
		"wavelength", "xray", "ymir", "zenith" };

	char gword[MAXLEN];            // array that holds user's correct guesses

	char guess;                    // letter guessed

	char* challenge;            // current word to be guessed

	int    used[NUMWORDS] = { 0 };    // frequency count of words used so far
	int    wrongs = 0;            // count of wrong guesses
	int wordLen;            // length of current hangman word
	int loop;                // loop counter
	int again = 1;            // flags 1 to play again 0 to quit game
	int won = 0;            // flags 1 if win and 0 if loss
	int j;

	srand(time(NULL));            //sends a "seed" for random number generation

	
	while (again) {

		int i = 0;
		char storeGuess[40];
		storeGuess[0] = ' ';

		initguess(gword);
		challenge = secrets[getword(used)];
		wordLen = strlen(challenge);

		while (wrongs < MAXGUESS && !won) {

			drawfig(wrongs, storeGuess, i);

			for (loop = 0; loop < wordLen; loop++)
				printf("%c ", gword[loop]);

			printf("\n");

			alreadyGuessed:
			guess = tolower(getguess());
			
			if (guess == '*') { easterEGG(storeGuess, i); wrongs = MAXGUESS; }

			if (!processguess(challenge, gword, wordLen, guess)) {
				storeGuess[i] = guess;
				for (int j = 0; j < i; j++) {
					while (storeGuess[j] == guess) {
						printf("\nAlready Guessed, Please Try Again!\n\n");
						goto alreadyGuessed;
					}
				}
				wrongs++;
				i += 1;
			}

			if (!won)
				won = checkwin(challenge, gword, wordLen);

			if (won) {
				for (loop = 0; loop < wordLen; loop++)
					printf("%c ", gword[loop]);
					printf("\n");
					printf("You win!\n");
					wrongs = 0;
					won = 0;
					break;
			}

			if (wrongs >= MAXGUESS) {
				drawfig(wrongs, storeGuess, i);
				printf("You lost! The word was %s\n", challenge);
				wrongs = 0;
				break;
			}

			

		}  /* end of inner while loop */

		printf("Do you want to play again? (Y / N): ");
		guess = tolower(getchar());
		getchar();


		// checking and validating user's response is either Y or N
		while ((guess != 'n') && (guess != 'y')) {
			printf("Invalid Entry. Please enter Yes or No (Y / N) ");
			guess = tolower(getchar());
			getchar();
		}


		// if user wants to exit, break from loop an exit. else continue the loop.
		if ((guess == 'n')) {
			printf("\nGoodbye.\n\n");
			again = 0;
			break;
		}
		else {
			continue;
		}
	}



	printf("\n------------------------------------------------------------------------------------------------------------------------\n");
	return 0;
}

int getword(int uct[]) {
	int index, i, sum = 0;

	/* reinitialize used word count to 0 if all words
	have been used -- start recycling */

	for (i = 0; i < NUMWORDS; i++)
		if (uct[i] != 0)
			sum++;
	if (sum == NUMWORDS)
		for (i = 0; i < NUMWORDS; i++)
			uct[i] = 0;

	index = rand() % NUMWORDS;    /* generate a candidate for the challenge */

	while (uct[index])
		index = rand() % NUMWORDS;    /* if this one has been used, get another */

	uct[index]++;        /* mark this index as used */
	return index;
}

void initguess(char g[]) {
	int i;
	for (i = 0; i < MAXLEN; ++i)
		g[i] = '_';
	return;
}

char getguess() {
	char g;
	printf("Your guess: ");
	g = getchar();
	getchar();
	return g;
}


int processguess(char c[], char g[], int l, char gl) {
	int i, hits = 0;
	for (i = 0; i <= l; i++)
	{
		if (c[i] == gl)
		{
			g[i] = gl;
			hits++;
		}
	}
	return hits;
}

int checkwin(char c[], char g[], int l) {
	int i, matches = 0;
	for (i = 0; i < l; i++)
		if (c[i] == g[i])
			matches++;
	if (matches == l)
		return 1;
	else
		return 0;
}

void showLogo() {

	/*
   _____                        _    _
  / ____|                      | |  | |
 | (___  _ __   __ _  ___ ___  | |__| | __ _ _ __   __ _ _ __ ___   __ _ _ __
  \___ \| '_ \ / _` |/ __/ _ \ |  __  |/ _` | '_ \ / _` | '_ ` _ \ / _` | '_ \
  ____) | |_) | (_| | (_|  __/ | |  | | (_| | | | | (_| | | | | | | (_| | | | |
 |_____/| .__/ \__,_|\___\___| |_|  |_|\__,_|_| |_|\__, |_| |_| |_|\__,_|_| |_|
		| |                                         __/ |
		|_|                                        |___/

						   *     .--.
								/ /  `
			   +               | |
					  '         \ \__,
				  *          +   '--'  *
					  +   /\
		 +              .'  '.   *
				*      /======\      +
					  ;:.  _   ;
					  |:. (_)  |
					  |:.  _   |
			+         |:. (_)  |          *
					  ;:.      ;
					.' \:.    / `.
				   / .-'':._.'`-. \
				   |/    /||\    \|
			     _..--"""````"""--.._
		   _.-'``                    ``'-._
		 -'                                '-

	*/
	printf("\033[1;31m");
	printf("   _____                        _    _\n");
	printf("  / ____|                      | |  | |\n");
	printf(" | (___  _ __   __ _  ___ ___  | |__| | __ _ _ __   __ _ _ __ ___   __ _ _ __\n");
	printf("  \\___ \\| '_ \\ / _` |/ __/ _ \\ |  __  |/ _` | '_ \\ / _` | '_ ` _ \\ / _` | '_ \\ \n");
	printf("  ____) | |_) | (_| | (_|  __/ | |  | | (_| | | | | (_| | | | | | | (_| | | | | \n");
	printf(" |_____/| .__/ \\__,_|\\___\\___| |_|  |_|\\__,_|_| |_|\\__, |_| |_| |_|\\__,_|_| |_|\n");
	printf("	| |                                         __/ |\n");
	printf("	|_|                                        |___/\n\n");
	
	printf("\033[1;34m");
	printf("\t				    *      .--.\n");
	printf("\t					  / /  `\n");
	printf("\t		   +                     | |\n");
	printf("\t				*         \\ \\__,\n");
	printf("\t			*              +   '--'  *\n");
	printf("\t			    +   /\\\n");
	printf("\t	       +              .'  '.   *\n");
	printf("\t		      *      /======\\      +\n");
	printf("\t			    ;:.  _   ;\n");
	printf("\t			    |:. (_)  |	*\n");
	printf("\t			    |:.  _   |\n");
	printf("\t		+           |:. (_)  |          *\n");
	printf("\t			    ;:.      ;	  +\n");
	printf("\t			   .'\\:.     / `.\n");
	printf("\t			  / .-'':._.'`-. \\\n");
	printf("\t			  |/    /||\\    \\|\n");
	printf("\t		        _..--\"\"\"\*\*\*\*\"\"\"- - .._\n");
	printf("\t		   _.-'``                    ``'-._\n");
	printf("\t		 -'                                '-\n\n");
	printf("\033[0m");
}

void printInstructions() {
	puts("\t\tWelcome to Space Hangman!");
	puts("\t\tTry to guess my secret word one letter at a time.");
	puts("\t\tYou can enter both uppercase and lowercase letters.");
	puts("\t\tYou have a total of 12 guesses ... here we go!!\n\n");
}

void drawfig(const int j, char storeGuess[40], int i) {
	
	/* clrscr(); */
	system("CLS"); /* clears screen using windows command */

	showLogo();

	printInstructions();

	switch (j)
		/* Each case draws a different part of the hangman stick figure.
		Larger cases intentionally fall through to smaller ones, so
		the drawing is built from the bottom up. */
	{
	case 0:
		printf("Amount of wrong letters: %d\tLetters Used: ", j);
		for (int k = 0; k < i; k++) {
			if (k == 6) {
				printf("\n\t\t\t\t\t      %c ", storeGuess[k]);
			}
			else {
				printf("%c ", storeGuess[k]);
			}
		}
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\t============\n\n");
		break;
	case 1:
		printf("Amount of wrong letters: %d\tLetters Used: ", j);
		for (int k = 0; k < i; k++) {
			if (k == 6) {
				printf("\n\t\t\t\t\t      %c ", storeGuess[k]);
			}
			else {
				printf("%c ", storeGuess[k]);
			}
		}
		printf("\n");
		printf("\n");
		printf("\n");
		printf("  \n");
		printf("  \n");
		printf("  \n");
		printf("\t  ||\n");
		printf("\t  ||\n");
		printf("\t=============\n\n");
		break;

	case 2:
		printf("Amount of wrong letters: %d\tLetters Used: ", j);
		for (int k = 0; k < i; k++) {
			if (k == 6) {
				printf("\n\t\t\t\t\t      %c ", storeGuess[k]);
			}
			else {
				printf("%c ", storeGuess[k]);
			}
		}
		printf("\n");
		printf("\n");
		printf("\n");
		printf("\t  ||\n");
		printf("\t  ||\n");
		printf("\t  ||\n");
		printf("\t  ||\n");
		printf("\t  ||\n");
		printf("\t=============\n\n");
		break;
	case 3:
		printf("Amount of wrong letters: %d\tLetters Used: ", j);
		for (int k = 0; k < i; k++) {
			if (k == 6) {
				printf("\n\t\t\t\t\t      %c ", storeGuess[k]);
			}
			else {
				printf("%c ", storeGuess[k]);
			}
		}
		printf("\n");
		printf("\n");
		printf("\t  ===========\n");
		printf("\t  ||\n");
		printf("\t  ||\n");
		printf("\t  ||\n");
		printf("\t  ||\n");
		printf("\t  ||\n");
		printf("\t=============\n\n");
		break;
	case 4:
		printf("Amount of wrong letters: %d\tLetters Used: ", j);
		for (int k = 0; k < i; k++) {
			if (k == 6) {
				printf("\n\t\t\t\t\t      %c ", storeGuess[k]);
			}
			else {
				printf("%c ", storeGuess[k]);
			}
		}
		printf("\n");
		printf("\n");
		printf("\t  ===========\n");
		printf("\t  || /\n");
		printf("\t  ||/\n");
		printf("\t  ||\n");
		printf("\t  ||\n");
		printf("\t  ||\n");
		printf("\t=============\n\n");
		break;
	case 5:
		printf("Amount of wrong letters: %d\tLetters Used: ", j);
		for (int k = 0; k < i; k++) {
			if (k == 6) {
				printf("\n\t\t\t\t\t      %c ", storeGuess[k]);
			}
			else {
				printf("%c ", storeGuess[k]);
			}
		}
		printf("\n");
		printf("\n");
		printf("\t  ===========\n");
		printf("\t  || /  |\n");
		printf("\t  ||/   O\n");
		printf("\t  ||\n");
		printf("\t  ||\n");
		printf("\t  ||\n");
		printf("\t=============\n\n");
		break;
	case 6:
		printf("Amount of wrong letters: %d\tLetters Used: ", j);
		for (int k = 0; k < i; k++) {
			if (k == 6) {
				printf("\n\t\t\t\t\t      %c ", storeGuess[k]);
			}
			else {
				printf("%c ", storeGuess[k]);
			}
		}
		printf("\n");
		printf("\n");
		printf("\t  ===========\n");
		printf("\t  || /  |\n");
		printf("\t  ||/   O\n");
		printf("\t  ||    |\n");
		printf("\t  ||\n");
		printf("\t  ||\n");
		printf("\t=============\n\n");
		break;
	case 7:
		printf("Amount of wrong letters: %d\tLetters Used: ", j);
		for (int k = 0; k < i; k++) {
			if (k == 6) {
				printf("\n\t\t\t\t\t      %c ", storeGuess[k]);
			}
			else {
				printf("%c ", storeGuess[k]);
			}
		}
		printf("\n");
		printf("\t  ===========\n");
		printf("\t  || /  |\n");
		printf("\t  ||/   O\n");
		printf("\t  ||    |\n");
		printf("\t  ||    |\n");
		printf("\t  ||\n");
		printf("\t=============\n\n");
		break;
	case 8:
		printf("Amount of wrong letters: %d\tLetters Used: ", j);
		for (int k = 0; k < i; k++) {
			if (k == 6) {
				printf("\n\t\t\t\t\t      %c ", storeGuess[k]);
			}
			else {
				printf("%c ", storeGuess[k]);
			}
		}
		printf("\n");
		printf("\t  ===========\n");
		printf("\t  || /  |\n");
		printf("\t  ||/   O\n");
		printf("\t  ||   \\|\n");
		printf("\t  ||    |\n");
		printf("\t  ||\n");
		printf("\t=============\n\n");
		break;
	case 9:
		printf("Amount of wrong letters: %d\tLetters Used: ", j);
		for (int k = 0; k < i; k++) {
			if (k == 6) {
				printf("\n\t\t\t\t\t      %c ", storeGuess[k]);
			}
			else {
				printf("%c ", storeGuess[k]);
			}
		}
		printf("\n");
		printf("\t  ===========\n");
		printf("\t  || /  |\n");
		printf("\t  ||/   O\n");
		printf("\t  ||   \\|/\n");
		printf("\t  ||    |\n");
		printf("\t  ||\n");
		printf("\t=============\n\n");
		break;
	case 10:
		printf("Amount of wrong letters: %d\tLetters Used: ", j);
		for (int k = 0; k < i; k++) {
			if (k == 6) {
				printf("\n\t\t\t\t\t      %c ", storeGuess[k]);
			}
			else {
				printf("%c ", storeGuess[k]);
			}
		}
		printf("\n");
		printf("\t  ===========\n");
		printf("\t  || /  |\n");
		printf("\t  ||/   O\n");
		printf("\t  ||   \\|/\n");
		printf("\t  ||    |\n");
		printf("\t  ||     \\\n");
		printf("\t=============\n\n");
		break;
	case 11:
		printf("Amount of wrong letters: %d\tLetters Used: ", j);
		for (int k = 0; k < i; k++) {
			if (k == 6) {
				printf("\n\t\t\t\t\t      %c ", storeGuess[k]);
			}
			else {
				printf("%c ", storeGuess[k]);
			}
		}
		printf("\n");
		printf("\t  ===========\n");
		printf("\t  || /  |\n");
		printf("\t  ||/   O\n");
		printf("\t  ||   \\|/\n");
		printf("\t  ||    |\n");
		printf("\t  ||   / \\\n");
		printf("\t=============\n\n");
		break;
	case 12:
		printf("Amount of wrong letters: %d\tLetters Used: ", j);
		for (int k = 0; k < i; k++) {
			if (k == 6) {
				printf("\n\t\t\t\t\t      %c ", storeGuess[k]);
			}
			else {
				printf("%c ", storeGuess[k]);
			}
		}
		printf("\n");
		printf("\t  ===========\n");
		printf("\t  || /  |\n");
		printf("\t  ||/   X\n");
		printf("\t  ||   \\|/\n");
		printf("\t  ||    |\n");
		printf("\t  ||   / \\\n");
		printf("\t======\\   ==\n\n");
		break;
	case 13:
		printf("You've discovered my secret easter egg!\n\n");
		printf("\t  ,'\"`.\n");
		printf("\t /     \\\n");
		printf("\t:       :\n");
		printf("\t:       :\n");
		printf("\t `.___,' \n");
		printf("\t   Q B\n");
		break;

	}
	printf("\n");
	return;
}

void easterEGG(char storeGuess[40], int i) {
	drawfig(13, storeGuess, i);
	return;
}


