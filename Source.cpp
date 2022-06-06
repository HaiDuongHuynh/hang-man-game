// Hangman
// The classic game of hangman, now with methods

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cctype>
#include <stdlib.h>

using namespace std;

string THE_WORD;            // word to guess
int wrong;
string soFar;
string used;
int Player1Point = 0;
int Player2Point = 0;
int PointCounter = 0; //for single player
bool Player1Turn = false;
bool Player2Turn = false;
int playernumber;
bool match(char letter, string word);
char askGuess(string usedLettersStr); //tells the compiler of method askGuess
bool playAgain();

int main()
{
    srand(time(0));

    vector<string> words;  // collection of possible words to guess
    words.push_back("WORRY");
    words.push_back("SUPPER");
    words.push_back("INTELLIGENCE");
    words.push_back("PHENOMENON");
    words.push_back("COMPLICATED");
    words.push_back("BYZANTINE");
    words.push_back("DEMONSTRATE");
    words.push_back("CONDUCT");
    words.push_back("LEVIATHAN");
    words.push_back("PSYCHIATRIST");
    words.push_back("PILGRIMAGE");
    words.push_back("AESTHETIC");

    cout << "Welcome to Hangman.  Good luck!\n";
    
    cout << "\n\nHow many player do you want to play with? <0/1>: ";
    cin >> playernumber;
    if (playernumber == 1) {
        Player1Turn = true;
    }

    // loop starts here
    bool done = false;
    do
    {
        const int MAX_WRONG = 6;  // maximum number of incorrect guesses allowed

        random_shuffle(words.begin(), words.end());
        THE_WORD = words[0];            // word to guess

        soFar = string(THE_WORD.size(), '-');          // word guessed so far
        used = "";                            // letters already guessed

        // loop for current word
        while ((wrong < MAX_WRONG) && (soFar != THE_WORD))
        {
            cout << "\n\nYou have " << (MAX_WRONG - wrong) << " incorrect guesses left.\n";
            if (wrong == 1) {
                cout << "|----" << endl;
                cout << "|   O" << endl;
                cout << "|" << endl;
                cout << "|" << endl;
                cout << "|" << endl;
                cout << "-" << endl;
            }
            if (wrong == 2) {
                cout << "|----" << endl;
                cout << "|   O" << endl;
                cout << "|   |" << endl;
                cout << "|" << endl;
                cout << "|" << endl;
                cout << "-" << endl;
            }
            if (wrong == 3) {
                cout << "|----" << endl;
                cout << "|   O" << endl;
                cout << "|  /|" << endl;
                cout << "|" << endl;
                cout << "|" << endl;
                cout << "-" << endl;
            }
            if (wrong == 4) {
                cout << "|----" << endl;
                cout << "|   O" << endl;
                cout << "|  /|/ " << endl;
                cout << "|" << endl;
                cout << "|" << endl;
                cout << "-" << endl;
            }
            if (wrong == 5) {
                cout << "|----" << endl;
                cout << "|   O" << endl;
                cout << "|  /|/ " << endl;
                cout << "|  /" << endl;
                cout << "|" << endl;
                cout << "-" << endl;
            }

            cout << "\nYou've used the following letters:\n" << used << endl;
            cout << "\nSo far, the word is:\n" << soFar << endl;
            if (playernumber == 1) {
                if (Player1Turn == true) {
                    cout << "\nIt's player1's turn" << endl;
                }
                else {
                    cout << "\nIt's player2's turn" << endl;
                }
            }
            used += askGuess(used);


            system("CLS");
        } // end of while ((wrong < MAX_WRONG) && (soFar != THE_WORD))

        // shut down
        if (wrong == MAX_WRONG)
        {
            cout << "|----" << endl;
            cout << "|   O" << endl;
            cout << "|  /|/ " << endl;
            cout << "|  // " << endl;
            cout << "|" << endl;
            cout << "-" << endl;
            cout << "\nYou've been hanged!";
            cout << "\nThe word was " << THE_WORD << endl;
        }
        else {
            cout << "CONGRATULATION!" << endl;
            cout << "\nThe word was " << THE_WORD << endl;
            if (playernumber == 1) {
                if (Player1Turn == false) {
                    Player1Point++;
                }
                if (Player2Turn == false) {
                    Player2Point++;
                }
                cout << "\nPlayer1's Point is: " << Player1Point << endl;
                cout << "\nPlayer2's Point is: " << Player2Point << endl;
            }
            else {
                PointCounter++;
                cout << "\nPlayer's Point is: " << PointCounter << endl;
            }
        }
    } while (playAgain());

    return 0;
}

inline bool match(char letter, string word)
{
    return (word.find(letter) != string::npos);
}

char askGuess(string usedLettersStr)
{
    char guess;
    cout << "\n\nEnter your guess: ";
    cin >> guess;
    guess = toupper(guess); //make uppercase since secret word in uppercase
//        while (used.find(guess) != string::npos)
    while (match(guess, used))
    {
        cout << "\nYou've already guessed " << guess << endl;
        cout << "Enter your guess: ";
        cin >> guess;
        guess = toupper(guess);
    }


    //        if (THE_WORD.find(guess) != string::npos)
    if (match(guess, THE_WORD))
    {
        cout << "That's right! " << guess << " is in the word.\n";

        // update soFar to include newly guessed letter
        for (int i = 0; i < THE_WORD.length(); ++i)
            if (THE_WORD[i] == guess)
                soFar[i] = guess;
        
    }
    else
    {
        cout << "Sorry, " << guess << " isn't in the word.\n";
        ++wrong;
        
    }
    if (Player1Turn == true) {
        
        Player2Turn = true;
        Player1Turn = false;
    }
    else {
        Player1Turn = true;
        Player2Turn = false;
    }

    return guess;
}

bool playAgain() // function to play again while clearing system
{
    char again;
    cout << "\n\nWould you like to play again? <y/n>: ";
    cin >> again;

    cin.clear(); //clear and ignore cin
    cin.ignore();

    again = toupper(again);

    system("cls");
    if (again == 'Y' ) wrong = 0;
    if (again == 'N') {
        if (playernumber == 1) {
            if (Player1Point > Player2Point) {
                cout << "Player 1 win!!!" << endl;
            }
            if (Player1Point < Player2Point) {
                cout << "Player 2 win!!!" << endl;
            }
            else cout << "DRAW!!!" << endl;
        }
        exit(1);
    }
    return (again == 'Y');
}