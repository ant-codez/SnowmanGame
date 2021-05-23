// =============================================================================
// File: main.cpp
// =============================================================================
// Programmer: Anthony Chavez
// Date: 5/22/2021
// Class: CSCI 123 ("Intro to Programming Using C++")
// Instructor: Dr. Rodriguez
// Project: Snowman
//
// Description:
//      This is a simulation of the game "snomwman", which is the politically
//      correct version of "hangman".  This is the file where the main function
//      is located.  Main uses the class CPlayer to Start and Reset the game.
//      At the end of the game, we retrieve the player's name and thank them for
//      playing.
//
// =============================================================================

#include <iostream>
#include "CPlayer.h"
using namespace std;

int main ()
{
    // Create a CPlayer object
    CPlayer    player1("Darth Vader");
    
    // Or Create a basic (guest) player
    //CPlayer  player1;
    
    char       userResp;
    
    // Create a do-while loop to have the user player as much as they like.
    do {
        // Start the game
        player1.Start();
        
        // Game ended, ask if the user wants to play again
        cout << "Do you want to play again? (Y/N): ";
        cin >> userResp;
        
        cout << endl << endl << endl;
        
        userResp = toupper(userResp);
        
        if (userResp == 'Y')
        {
            player1.Reset();
        }
        
    } while (userResp == 'Y');
    
    cout << "\n\nThanks for playing " << player1.GetName() << "!\n";
    cout << "Good Bye!\n\n";
    
    return 0;
}
