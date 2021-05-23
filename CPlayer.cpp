// ============================================================================
// File: CPlayer.cpp
// ============================================================================
// This is an implementation file for the CPlayer class.
// ============================================================================

#include <iostream>
#include <cstring>
#include <unistd.h>   // sleep function
#include "CPlayer.h"
using namespace std;



// ==== CPlayer::CPlayer ======================================================
//
// This is the CPlayer default constructor. It allocates space from the HEAP and
// initializes the private data member m_name to "Guest Player". Futhermore, it
// sets m_gameResetted to false.
//
// Input:
//      None
//
// ============================================================================

CPlayer::CPlayer(){
    m_name = new char [strlen("Guest Player") + 1];
    strcpy(m_name, "Guest Player");
    m_gameResetted = false;
}



// ==== CPlayer::CPlayer ======================================================
//
// This is the CPlayer type constructor. It uses the parameter to allocate space
// from the HEAP and initialize the private data member m_name.  Futhermore, it
// sets m_gameResetted to false.
//
// Input:
//      name    [IN]    -- a char pointer to a given name
//
// ============================================================================


CPlayer::CPlayer(char const* name){
    m_name = new char [strlen(name) + 1];
    strcpy(m_name, name);
    m_gameResetted = false;
}



// ==== CPlayer::~CPlayer =====================================================
//
// This is the CPlayer destructor. It appropriately releases memory from the
// HEAP.
//
// Input:
//      None
//
// ============================================================================

CPlayer::~CPlayer(){
    delete m_name;
}



// ==== CPlayer::SetName ======================================================
//
// The SetName function uses the parameter to update the private data member
// m_name. Be sure you have exactly the space needed to store the new name.
//
// Input:
//      name    [IN]    -- a char pointer to a given name
//
// Output:
//      None
//
// ============================================================================

void CPlayer::SetName(char const* name){
    m_name = new char [strlen(name) + 1];
    strcpy(m_name, name);
}



// ==== CPlayer::GetName ======================================================
//
// The GetName function returns m_name as a const char pointer.
//
// Input:
//      None
//
// Output:
//      A const char*
//
// ============================================================================

const char* CPlayer::GetName() const{
    return m_name;
}



// ==== CPlayer::Start ========================================================
//
// The Start function uses the CSnowmanGame object to begin the game by calling
// its public member function Start. Before calling the Start function and if
// the game has not been resetted, the program will display a welcoming message
// and a game loading message. Afterwards the program will sleep for
// SLEEP_NUM_PLAYER seconds.
//
// Input:
//      None
//
// Output:
//      None
//
// ============================================================================


void CPlayer::Start(){
    
    if (!m_gameResetted){
        cout << "\t\tYou're about to play the game Snowman\n\n";
        cout << "\t\tPlease wait while the game loads...\n\n";
        sleep(SLEEP_NUM_PLAYER);
    }

    m_game.Start();
}


// ==== CPlayer::Reset ========================================================
//
// The Reset function uses the CSnowmanGame object to restart the game by
// calling its public member function Reset. Before calling the Reset function
// the program will display a restarting and reloading message. Afterwards the
// program will sleep for SLEEP_NUM_PLAYER seconds.
//
// Input:
//      None
//
// Output:
//      None
//
// ============================================================================


void CPlayer::Reset(){

    cout << "You're about to play the Game Snowman again...\n\n";
    cout << "Please wait while the game resets...\n\n";

    m_gameResetted = true;

    sleep (SLEEP_NUM_PLAYER);

    m_game.Reset();
}