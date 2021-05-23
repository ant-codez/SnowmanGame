// ============================================================================
// File: CSnowmanGame.h
// ============================================================================
// This header file contains the declaration for the CSnowmanGame class. The
// class is used in main.cpp to start the game of Snowman.
// ============================================================================

#include "CWords.h"

#ifndef CSnowmanGame_h
#define CSnowmanGame_h

const int NUM_TRIES = 8;
const int NUM_ALPHA_CHARS = 26;
const int SCREEN_DIM = 80;
const int SLEEP_NUM_SNOWMAN = 1;

class CSnowmanGame
{
public:
    // Constructor(s)
    CSnowmanGame();
    
    // Public Member Function(s)
    void    Start();
    void    Reset();
    
private:
    // private data members
    int         m_numTries;
    char        m_wordToGuess[256];
    bool        m_letterGuessed[NUM_ALPHA_CHARS];
    bool        m_lettersInWord[NUM_ALPHA_CHARS];
    int         m_wordLen;
    bool        m_guessedWord;
    int         m_numUniqueLetters;
    CWords      m_words;

    // private member functions
    void    DispTitle(char const* title, bool header = true,
                      bool footer = true, bool headerSpace = true,
                      bool footerSpace = true) const;
    void    DispWordDash() const;
    void    DrawSnowman(int numTries) const;
    void    DrawAvailLetters() const;
    void    DrawSnowmanPart0() const;
    void    DrawSnowmanPart1() const;
    void    DrawSnowmanPart2() const;
    void    DrawSnowmanPart3() const;
    void    DrawSnowmanPart4() const;
    void    DrawSnowmanPart5() const;
    void    DrawSnowmanPart6() const;
    void    DrawSnowmanPart7() const;
    void    DrawSnowmanPart8() const;
    void    GetUserGuess();
    bool    IsValidGuess(char guess);
    int     GetNumUniqueLetters();
    void    DispSnowmanTitle();
    bool    CheckWin();
};


#endif /* CSnowmanGame_h */
