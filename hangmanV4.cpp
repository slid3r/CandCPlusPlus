// Program: Hangman (Linux/Unix platform)
// Author:  Slid3r
//          slid3r@linuxmail.org
// Date:  18 May 2004
//
// Description:  It's Hangman man!!!
//				
// Compile Instructions: save this code as hangmanV4.cpp
//						 then, using the gnu compiler type:
//						 g++ hangmanV4.cpp -o hangman
//			                         chmod 755 ./hangman
//						 then you may copy it to /usr/local/bin if you wish
//
// 		  Author's Note: This program is yours to do with as you wish, I ask only
//                as many before me have asked, that you leave this comment
//		  block as it is.  Enjoy.   
//			  -slid3r
//
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <termios.h>
#include <fstream>
#include <vector>

using namespace std;

static struct termios stored_settings;

void drawGallows (int guess);
string getWord ();
void guesser ();
bool charCheck (char),alreadyGuessed = 0;
void playAgain ();
int strLength (string);

int charCount;
char guessedLetters[26];


void set_keypress(void)
{
     struct termios new_settings;
     
     tcgetattr(0,&stored_settings);
     new_settings = stored_settings;
     new_settings.c_lflag &= (~ICANON);
     new_settings.c_cc[VTIME] = 0;
     new_settings.c_cc[VMIN] = 1;
     tcsetattr(0,TCSANOW,&new_settings);
}
     
void reset_keypress(void)
{
     tcsetattr(0,TCSANOW,&stored_settings);
     return;
}

int main ()
{
	guesser();
}

void drawGallows (int guess)
{
	string a = " _________\n";
	string b = " |/      |\n";
	string c = " |       \n";
	string c2 = " |       0\n";
	string d = " |      \n";
	string d2 = " |       |\n";
	string d3 = " |      \\|\n";
	string d4 = " |      \\|/\n";
	string e = " |       \n";
	string e2 = " |       |\n";
	string f = " |      \n";
	string f2 = " |      / \n";
	string f3 = " |      / \\\n";
	string g = " |\n";
	string h = "{-}-----{-}	\n";
	string i = " |       |\n";
	if (guess >= 1)
	{
		c = c2;
	}
	if (guess >= 2)
	{
		d = d2;
	}
	if (guess >= 3)
	{
		d = d3;
	}
	if (guess >= 4)
	{
		d = d4;
	}
	if (guess >= 5)
	{
		e = e2;
	}
	if (guess >= 6)
	{
		f = f2;
	}
	if (guess >= 7)
	{
		f = f3;
	}

	system ("clear");
	cout << "Hangman Game for the *nix Console"
		<< endl;
	cout << "by: Slid3r" << endl;
	cout << "\n" << endl;
	cout << a;
	cout << b;
	cout << c;
	cout << d;
	cout << e;
	cout << f;
	cout << g;
	cout << h;
	cout << i << endl;
}

string getWord()
{
        srand(time(NULL));

        std::vector<std::string> list;
        std::string word;
	std::string returnWord;
        int index = 0;

        std::ifstream fin("/usr/share/dict/words");
        while(fin >> word)
                list.push_back(word);

        index = rand() % list.size() - 1;
	returnWord = list[index];
	while(std::isupper(returnWord[0])){
		index = rand() % list.size() - 1;
		returnWord = list[index];
	}
	return list[index];
}

void guesser()
{
	charCount = 0;
	string word = getWord(), drawWord, tempChar, letterList;
	int dashes = strLength(word), wGuessCount = 0, aLetter = 0;
	bool guessedWrong;
	char letterGuessed;
	drawGallows(0);
	for (int i = 0;i < dashes; i++)
	{
		drawWord.insert(i,"-");
	}
	bool done;
	do {
		done = 1;
		cout << "\nWord:  ";
		cout << drawWord << endl;
		if (aLetter > 0)
		{
			for (int i = 0; guessedLetters[i] != '\0'; i++)
			{
				if (i == 0)
				{
					letterList = guessedLetters[i];
					aLetter++;
				}
				else 
				{
					letterList = letterList + "," + guessedLetters[i];
					aLetter++;
				}
			}
			cout << "(Letters guessed: " +
				letterList + ")" << endl;
		}
		if (alreadyGuessed)
		{
			cout << "\nYou already guessed '" << letterGuessed << "'" << endl;
			alreadyGuessed = false;
		}
		cout << "\nGuess a letter: ";
		set_keypress();
		letterGuessed = getchar();
		reset_keypress();
		guessedWrong = true;
		if (charCheck(letterGuessed))
		{
			for (int i = 0; i < dashes; i++)
			{
				if (letterGuessed == word[i])
				{
					tempChar = word[i];
					drawWord.replace(i,1,tempChar);
					guessedWrong = false;
				}
			}
			aLetter++;
			if (guessedWrong)
			{
				wGuessCount ++;
			}
			for (int i = 0; i <= dashes; i++)
			{
				if (drawWord[i] == '-')
				{
					done = 0;
				}
			}
			if (done)
			{
				drawGallows(wGuessCount);
				cout << "\nWord:  ";
				cout << word << endl;
				cout << "You guessed the word!!" << endl;
			}
			if (wGuessCount == 7)
			{
				drawGallows(wGuessCount);
				cout << "\nWord:  ";
				cout << drawWord << endl;
				cout << "\nSorry you are hung." << endl;
				cout << "\nYour word was " << word << endl;
				done = 1;
			}
			if (!done)
			{
				drawGallows(wGuessCount);
			}
		}
		else 
		{
			drawGallows(wGuessCount);
			done = 0;
		}
	}while (!done);

	playAgain();
}

bool charCheck (char a)
{
	bool wasGuessed = 0;
	if (a == ' ' || !isalpha(a))
		return false;
	if (charCount == 0)
	{
		for (int i = 0; i < 26; i++)
		{
			guessedLetters[i] = '\0';
		}
		guessedLetters[0] = a;
		charCount++;
		return true;
	}
	for (int i = 0; guessedLetters[i] != '\0'; i++)
	{
		if (guessedLetters[i] == a)
		{
			alreadyGuessed = true;
			wasGuessed = 1;
			charCount++;
			break;
		}
	}
	if (!wasGuessed)
	{
		guessedLetters[strLength(guessedLetters)] = a;
		charCount ++;
		return true;
	}
	else
	{
		return false;
	}
}



void playAgain ()
{
	bool done = 0;
	cout << "\nWould you like to play again? (y/n): ";
	do {
		set_keypress();
		char yesNo = getchar();
		reset_keypress();
		yesNo = tolower(yesNo);
		switch (yesNo)  {
		case 'y' :
			drawGallows(0);
			guesser();
			done = 1;
			break;
		case 'n' :
			cout << "\n\nThanks for playing!\n\n" << endl;
			done = 1;
			break;
		default :
			break;
		}
	}while (!done);
}


int strLength (string s)
{
	int j = 0;
	while( s[j] != '\0')
		j++;
	return j;
}
