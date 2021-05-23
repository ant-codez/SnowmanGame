// ============================================================================
// File: CSnowmanGame.cpp
// ============================================================================
// This is an implementation file for the CSnowmanGame class.
// ============================================================================


#include <cstring>
#include <unordered_map>
#include <unistd.h>         	// sleep function
// #include "IntToCStringLib.h"	// uncomment if you are going to use the included 
								// functions
#include "CSnowmanGame.h"
#include <iostream>
#include <iomanip>
using namespace std;



// ==== CSnowmanGame::CSnowmanGame ============================================
//
// This is the CSnowmanGame default constructor. It sets up the environment by
// initializing the private data members by calling the Reset function.
//
// Input:
//      None
//
// ============================================================================

CSnowmanGame::CSnowmanGame(){
    Reset();
}


// ==== CSnowmanGame::Start ===================================================
//
// This function starts the game.  It clears the terminal screen to show only
// the game by calling the function system("clear").  It further calls member
// functions to display the title of the game, draw the snowman figure, draw
// available letters, draw the number of tries, and the word to guess in dashed
// lines.  The Start function will loop continously until the user guesses
// correctly or has no more tries.  This function will display a message to the
// user if they have guessed the word(s) correctly or ran out of tries.
//
// Input:
//      None
//
// Output:
//      None
//
// ============================================================================

void CSnowmanGame::Start(){

    while (true){
        system("clear");
        DispSnowmanTitle();
        DrawSnowman(m_numTries);
        DrawAvailLetters();
        //draw number of tries
        DispWordDash();

        if (m_numTries == 0 || CheckWin()){
            if (CheckWin())
                printf("You WON!! ");
            else
                printf("Sorry, out of tries! It was %s. ", m_wordToGuess);
            break;
        }

        GetUserGuess();
    }

}

// ==== CSnowmanGame::CheckWin ===================================================
//
// This function will check if the play has correctly guessed all the letters in 
// m_wordToGuess. If the player has correctly guessed the word then this fucntion will
// return True, else it will return false.
//
// Input:
//      None
//
// Output:
//      bool   -- true if the user guessed each word corrctly, else false
//
// ============================================================================

bool CSnowmanGame::CheckWin(){
    int found = 0;

    for (int i = 0; i < NUM_ALPHA_CHARS; i++){
        if (m_lettersInWord[i] == true && m_letterGuessed[i] == true)
            found++;
    }

    if (found == m_numUniqueLetters)
        return true;
    else
        return false;
}

// ==== CSnowmanGame::Reset ===================================================
//
// This function initializes all the private data members.  It will use CWords'
// object to randomly obtain a word and update m_wordToGuess.
//
// Input:
//      None
//
// Output:
//      None
//
// ============================================================================


void CSnowmanGame::Reset(){
    m_numTries = NUM_TRIES;
    strcpy(m_wordToGuess, m_words.GetRandomWord());

    for (int i = 0; i < NUM_ALPHA_CHARS; i++){
        m_letterGuessed[i] = false;
        m_lettersInWord[i] = false;
    }
    
    m_wordLen = strlen(m_wordToGuess);
    m_guessedWord = false;
    m_numUniqueLetters = GetNumUniqueLetters();
}


// ==== CSnowmanGame::DrawAvailLetters ========================================
//
// This function displays the letters over two rows that the user has not
// guessed yet.  At the start of the game, the function will display all the
// letters in the alphabet.  As the user takes their guesses, the letters will
// be replaced with a space.  This will keep the structure/spacing of all the
// letters the same.
//
// Input:
//      None
//
// Output:
//      None
//
// ============================================================================

void CSnowmanGame::DrawAvailLetters() const {

    cout << "================================================================================\n\n";
    cout << setw(47) << "Available Letters\n\n";
    cout << "================================================================================\n\n";
    cout << setw(25);

    for (char i = 'A'; i <= 'Z'; i++){

        if (m_letterGuessed[i - 'A'] == true)
            cout << "  ";
        else
            cout << i << " ";

        if (i == 'M')
        {
            cout << endl;
            cout << setw(25);
        }
            
    }
    cout << endl << endl;
    cout << "================================================================================\n\n";
    cout << setw(45) << "Guess The Word (You have " << m_numTries <<  " tries)\n\n";
}


// ==== CSnowmanGame::DispWordDash ============================================
//
// This function displays the word to guess with underscores.  As the user
// guesses each correct letter, the function appropriately updates the dash to
// the letter guessed. As a note, only alphabetical characters are expressed
// with underscores.  If the word contains anything else, like a space, period,
// or a number, make sure that is not hidden and displayed.
//
// Input:
//      None
//
// Output:
//      None
//
// ============================================================================

void CSnowmanGame::DispWordDash() const{
    cout << "================================================================================\n\n";
    cout << "\t\t\t\t";
    for (int i = 0; i < m_wordLen; i++){
        
        if (m_letterGuessed[toupper(m_wordToGuess[i]) - 'A'] == true)
            printf("%c", m_wordToGuess[i]);
        else if (isalpha(m_wordToGuess[i]))
            printf("_");
        else
            printf("%c", m_wordToGuess[i]);
    }

    cout << "\n\n================================================================================\n\n";    

}


// ==== CSnowmanGame::GetUserGuess ============================================
//
// This function prompts the user to enter a guess.  It then validates the guess
// by calling the IsValidGuess.  If the guess is not valid, it will repeatedly
// ask the user to enter a valid guess.
//
// Input:
//      None
//
// Output:
//      None
//
// ============================================================================

void CSnowmanGame::GetUserGuess(){
    char guess;

    while (true){
        printf("Enter your guess one char at a time (not case-sensitive): ");
        cin >> guess;
        if (IsValidGuess(guess))
            break;
    }
}


// ==== CSnowmanGame::IsValidGuess ============================================
//
// This function checks if the guess the user entered is valid.  The function
// will return false if the user enters a non-alphabetical character or if the
// user entered the same letter before.  None of these two cases should count
// against the user's tries.  The function returns true if the guess has not
// been entered before, whether the guess is correct or not.  For each case,
// the function will display an appropriate message and sleep for
// SLEEP_NUM_SNOWMAN seconds, to let the user read the message before moving on
// with the program.
//
// Input:
//      guess   [IN]    -- a char to represent the guess of the user.
//
// Output:
//      bool            -- true if the guess is valid, false otherwise.
//
// ============================================================================

bool CSnowmanGame::IsValidGuess(char guess){

    bool found = false;

    if (!isalpha(guess)){
        printf("The guess you entered is not an alphabetical character. Try again...\n");
        sleep(SLEEP_NUM_SNOWMAN);
        return false;
    }
    else if (m_letterGuessed[toupper(guess) - 'A'] == true){
        printf("You already tried that letter, silly. Try again...\n");
        sleep(SLEEP_NUM_SNOWMAN);
        return false;
    }
    else if (m_letterGuessed[toupper(guess) - 'A'] == false){
        //printf("GUESS = [%c], NUM = [%i]\n",guess, toupper(guess) - 'A');


        for (int i = 0; i < m_wordLen; i++){
            if (toupper(guess) == toupper(m_wordToGuess[i])){
                found = true;
                break;
            }
        }

        if (found){
            printf("You got one!!\n");
        }
        else{
            printf("Almost!! But it's gon' cost you!!\n");
            m_numTries--;
        }


        sleep(SLEEP_NUM_SNOWMAN);
        m_letterGuessed[toupper(guess) - 'A'] = true;
        return true;
    }
}


// ==== CSnowmanGame::GetNumUniqueLetters =====================================
//
// This function calculates the number of unique letters for the word to guess.
// It also changes the location of each letter position in m_lettersInWord as
// true.
//
// Input:
//      None
//
// Output:
//      int     -- Number of unique letters in m_wordToGuess.
//
// ============================================================================

int CSnowmanGame::GetNumUniqueLetters(){

    int value = 0;

    for (int i = 0; i < m_wordLen; i++){
            if (isalpha(m_wordToGuess[i]) && m_lettersInWord[toupper(m_wordToGuess[i]) - 'A'] != true)
                m_lettersInWord[toupper(m_wordToGuess[i]) - 'A'] = true;
    }

    for (int i = 0; i < NUM_ALPHA_CHARS; i++){
        if (m_lettersInWord[i] == true)
            value++;
    }

    return value;
}

// ==== CSnowmanGame::DrawSnowman =============================================
//
// This function draws the appropriate stage/part of the snowman based on the
// number of tries the user has.
//
// Input:
//      numTries    [IN]    -- The number of tries the user has so far.
//
// Output:
//      None
//
// ============================================================================

void CSnowmanGame::DrawSnowman(int numTries) const {

    if (numTries == 8)
        DrawSnowmanPart0();
    else if (numTries == 7)
        DrawSnowmanPart1();
    else if (numTries == 6)
        DrawSnowmanPart2();
    else if (numTries == 5)
        DrawSnowmanPart3();
    else if (numTries == 4)
        DrawSnowmanPart4();
    else if (numTries == 3)
        DrawSnowmanPart5();
    else if (numTries == 2)
        DrawSnowmanPart6();
    else if (numTries == 1)
        DrawSnowmanPart7();
    else if (numTries == 0)
        DrawSnowmanPart8();
}


// ==== CSnowmanGame::DispTitle ===============================================
//
// This function displays any character array as a title, where a title is
// defined as centered to the const value SCREEN_DIM with a header and footer.
//
// Ex:
//                      ====================
//
//                              Title
//
//                      ====================
//
// Input:
//      title       [IN]    -- a const char pointer that contains the string
//                             you'll want to display
//      header      [IN]    -- a bool (default true) if you want to display a
//                             top row of "equal signs."
//      footer      [IN]    -- a bool (default true) if you want to display a
//                             bottom row of "equal signs."
//      headerSpace [IN]    -- a bool (default true) if you want a space between
//                             the header and the string title.
//      footerSpace [IN]    -- a bool (default true) if you want a space between
//                             the footer and the string title.
//
// Output:
//      None
//
// ============================================================================

void    CSnowmanGame::DispTitle(char const* title, bool header,
                                bool footer, bool headerSpace,
                                bool footerSpace) const
{
    int i;
    int lenStr = static_cast<int>(strlen(title));
    int pos = (SCREEN_DIM - lenStr) / 2;
    
    // Display top row if header == true
    if (header == true)
    {
        for (i = 0; i < SCREEN_DIM; i++)
        {
            cout << '=';
        }
    
        cout << endl;
        
        if (headerSpace == true)
        {
            cout << endl;
        }
    }
    else
    {
        if (headerSpace == true)
        {
            cout << endl;
        }
    }
    
    // Display title at the center of SCREEN_DIM
    for (i = 0; i < pos; i++)
    {
        cout << ' ';
    }
    
    cout << title << endl;
    
    if (footerSpace == true)
    {
        cout << endl;
    }
    
    // Display bottom row if footer == true
    if (footer == true)
    {
        for (i = 0; i < SCREEN_DIM; i++)
        {
            cout << "=";
        }
        
        if (footerSpace == true)
        {
            cout << endl;
        }
    }
    
} // end of CSnowmanGame::DispTitle



// ==== CSnowmanGame::DispSnowmanTitle ========================================
//
// This function displays the title "SNOWMAN."
//
// Input:
//      None
//
// Output:
//      None
//
// ============================================================================

void CSnowmanGame::DispSnowmanTitle()
{
    const int   ROWS = 4;
    const char* snowmanTitle[ROWS] =
        {"___ _ __   _____      ___ __ ___   __ _ _ __",
         "/ __| '_ \\ / _ \\ \\ /\\ / / '_ ` _ \\ / _` | '_ \\",
         " \\__ \\ | | | (_) \\ V  V /| | | | | | (_| | | | |",
         " |___/_| |_|\\___/ \\_/\\_/ |_| |_| |_|\\__,_|_| |_|"};
    
    // Call DispTitle for each row of "SNOWMAN"
    DispTitle(snowmanTitle[0], true, false, true, false);
    DispTitle(snowmanTitle[1], false, false, false, false);
    DispTitle(snowmanTitle[2], false, false, false, false);
    DispTitle(snowmanTitle[3], false, true, false, true);
    
} // end of CSnowmanGame::DispSnowmanTitle




// ==== CSnowmanGame::DrawSnowmanPart8 ========================================
//
// This function draws the final stage of the snowman.
//
// Input:
//      None
//
// Output:
//      None
//
// ============================================================================

void    CSnowmanGame::DrawSnowmanPart8() const
{
    DispTitle(",===.", false, false, true, false);
    DispTitle("_|___|_", false, false, false, false);
    DispTitle("__/     /. .\\      /__", false, false, false, false);
    DispTitle("/`.    \\___/    ,'\\", false, false, false, false);
    DispTitle("`. .'=*=`. .'", false, false, false, false);
    DispTitle("Y   *   Y", false, false, false, false);
    DispTitle("\\  *  /", false, false, false, false);
    DispTitle(".`---'.", false, false, false, false);
    DispTitle(".`   *   '.", false, false, false, false);
    DispTitle("|    *    |", false, false, false, false);
    DispTitle("\\    *    /", false, false, false, false);
    DispTitle("__.-`._____.'-.__", false, false, false, false);
    DispTitle(".'`                 `'..", false, false, false, true);
    
} // end of CSnowmanGame::DrawSnowmanPart8



// ==== CSnowmanGame::DrawSnowmanPart7 ========================================
//
// This function draws the 7th stage of the snowman
//
// Input:
//      None
//
// Output:
//      None
//
// ============================================================================

void    CSnowmanGame::DrawSnowmanPart7() const
{
    DispTitle("", false, false, true, false);
    DispTitle("___", false, false, false, false);
    DispTitle("__/     /. .\\      /__", false, false, false, false);
    DispTitle("/`.    \\___/    ,'\\", false, false, false, false);
    DispTitle("`. .'=*=`. .'", false, false, false, false);
    DispTitle("Y   *   Y", false, false, false, false);
    DispTitle("\\  *  /", false, false, false, false);
    DispTitle(".`---'.", false, false, false, false);
    DispTitle(".`   *   '.", false, false, false, false);
    DispTitle("|    *    |", false, false, false, false);
    DispTitle("\\    *    /", false, false, false, false);
    DispTitle("__.-`._____.'-.__", false, false, false, false);
    DispTitle(".'`                 `'..", false, false, false, true);
    
} // end of CSnowmanGame::DrawSnowmanPart7



// ==== CSnowmanGame::DrawSnowmanPart6 ========================================
//
// This function draws the 6th stage of the snowman
//
// Input:
//      None
//
// Output:
//      None
//
// ============================================================================

void    CSnowmanGame::DrawSnowmanPart6() const
{
    DispTitle("", false, false, true, false);
    DispTitle("___", false, false, false, false);
    DispTitle("__/     /. .\\      /__", false, false, false, false);
    DispTitle("/`.    \\___/    ,'\\", false, false, false, false);
    DispTitle("`. .'=*=`. .'", false, false, false, false);
    DispTitle("Y   *   Y", false, false, false, false);
    DispTitle("\\  *  /", false, false, false, false);
    DispTitle(".`---'.", false, false, false, false);
    DispTitle(".`   *   '.", false, false, false, false);
    DispTitle("|    *    |", false, false, false, false);
    DispTitle("\\    *    /", false, false, false, false);
    DispTitle("__.-`._____.'    ", false, false, false, false);
    DispTitle(".'`                     ", false, false, false, true);
    
} // end of CSnowmanGame::DrawSnowmanPart6



// ==== CSnowmanGame::DrawSnowmanPart5 ========================================
//
// This function draws the 5th stage of the snowman
//
// Input:
//      None
//
// Output:
//      None
//
// ============================================================================

void    CSnowmanGame::DrawSnowmanPart5() const
{
    DispTitle("", false, false, true, false);
    DispTitle("___", false, false, false, false);
    DispTitle("__/     /. .\\      /__", false, false, false, false);
    DispTitle("/`.    \\___/    ,'\\", false, false, false, false);
    DispTitle("`. .'=*=`. .'", false, false, false, false);
    DispTitle("Y   *   Y", false, false, false, false);
    DispTitle("\\  *  /", false, false, false, false);
    DispTitle(".`---'.", false, false, false, false);
    DispTitle(".`   *   '.", false, false, false, false);
    DispTitle("|    *    |", false, false, false, false);
    DispTitle("\\    *    /", false, false, false, false);
    DispTitle("`._____.'", false, false, false, false);
    DispTitle("", false, false, false, true);
    
} // end of CSnowmanGame::DrawSnowmanPart5



// ==== CSnowmanGame::DrawSnowmanPart4 ========================================
//
// This function draws the 4th stage of the snowman
//
// Input:
//      None
//
// Output:
//      None
//
// ============================================================================

void    CSnowmanGame::DrawSnowmanPart4() const
{
    DispTitle("", false, false, true, false);
    DispTitle("___", false, false, false, false);
    DispTitle("__/     /. .\\         ", false, false, false, false);
    DispTitle("/`.    \\___/       ", false, false, false, false);
    DispTitle("`. .'=*=`.   ", false, false, false, false);
    DispTitle("Y   *  | ", false, false, false, false);
    DispTitle("\\  *  /", false, false, false, false);
    DispTitle(".`---'.", false, false, false, false);
    DispTitle(".`   *   '.", false, false, false, false);
    DispTitle("|    *    |", false, false, false, false);
    DispTitle("\\    *    /", false, false, false, false);
    DispTitle("`._____.'", false, false, false, false);
    DispTitle("", false, false, false, true);
    
} // end of CSnowmanGame::DrawSnowmanPart4



// ==== CSnowmanGame::DrawSnowmanPart3 ========================================
//
// This function draws the 3rd stage of the snowman
//
// Input:
//      None
//
// Output:
//      None
//
// ============================================================================

void    CSnowmanGame::DrawSnowmanPart3() const
{
    DispTitle("", false, false, true, false);
    DispTitle("___", false, false, false, false);
    DispTitle("        /. .\\         ", false, false, false, false);
    DispTitle("\\___/", false, false, false, false);
    DispTitle(".'=*=`.", false, false, false, false);
    DispTitle("|  *  |", false, false, false, false);
    DispTitle("\\  *  /", false, false, false, false);
    DispTitle(".`---'.", false, false, false, false);
    DispTitle(".`   *   '.", false, false, false, false);
    DispTitle("|    *    |", false, false, false, false);
    DispTitle("\\    *    /", false, false, false, false);
    DispTitle("`._____.'", false, false, false, false);
    DispTitle("", false, false, false, true);
    
} // end of CSnowmanGame::DrawSnowmanPart3



// ==== CSnowmanGame::DrawSnowmanPart2 ========================================
//
// This function draws the 2nd stage of the snowman
//
// Input:
//      None
//
// Output:
//      None
//
// ============================================================================

void    CSnowmanGame::DrawSnowmanPart2() const
{
    DispTitle("", false, false, true, false);
    DispTitle("", false, false, false, false);
    DispTitle("", false, false, false, false);
    DispTitle("___", false, false, false, false);
    DispTitle(".'=*=`.", false, false, false, false);
    DispTitle("|  *  |", false, false, false, false);
    DispTitle("\\  *  /", false, false, false, false);
    DispTitle(".`---'.", false, false, false, false);
    DispTitle(".`   *   '.", false, false, false, false);
    DispTitle("|    *    |", false, false, false, false);
    DispTitle("\\    *    /", false, false, false, false);
    DispTitle("`._____.'", false, false, false, false);
    DispTitle("", false, false, false, true);
    
} // end of CSnowmanGame::DrawSnowmanPart2



// ==== CSnowmanGame::DrawSnowmanPart1 ========================================
//
// This function draws the 1st stage of the snowman
//
// Input:
//      None
//
// Output:
//      None
//
// ============================================================================

void    CSnowmanGame::DrawSnowmanPart1() const
{
    DispTitle("", false, false, true, false);
    DispTitle("", false, false, false, false);
    DispTitle("", false, false, false, false);
    DispTitle("", false, false, false, false);
    DispTitle("", false, false, false, false);
    DispTitle("", false, false, false, false);
    DispTitle("", false, false, false, false);
    DispTitle(". --- .", false, false, false, false);
    DispTitle(".`   *   '.", false, false, false, false);
    DispTitle("|    *    |", false, false, false, false);
    DispTitle("\\    *    /", false, false, false, false);
    DispTitle("`._____.'", false, false, false, false);
    DispTitle("", false, false, false, true);
    
} // end of CSnowmanGame::DrawSnowmanPart1



// ==== CSnowmanGame::DrawSnowmanPart0 ========================================
//
// This function draws a blank snowman.  This is the first thing that is drawn
// to show an empty canvas.
//
// Input:
//      None
//
// Output:
//      None
//
// ============================================================================

void    CSnowmanGame::DrawSnowmanPart0() const
{
    DispTitle("", false, false, true, false);
    DispTitle("", false, false, false, false);
    DispTitle("", false, false, false, false);
    DispTitle("", false, false, false, false);
    DispTitle("", false, false, false, false);
    DispTitle("", false, false, false, false);
    DispTitle("", false, false, false, false);
    DispTitle("", false, false, false, false);
    DispTitle("", false, false, false, false);
    DispTitle("", false, false, false, false);
    DispTitle("", false, false, false, false);
    DispTitle("", false, false, false, false);
    DispTitle("", false, false, false, true);
    
} // end of CSnowmanGame::DrawSnowmanPart0
