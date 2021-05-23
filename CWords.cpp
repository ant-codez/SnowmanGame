// ============================================================================
// File: CWords.cpp
// ============================================================================
// This is an implementation file for the CWord class.
// ============================================================================

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <cstdlib>  // srand function
#include <ctime>    // time function
#include "CWords.h"
using namespace std;



// ==== CWords::CWords ========================================================
//
// This is the CWords default constructor. It initializes the private data
// members.  It sets m_numWords to zero, allocates space for m_words, and calls
// the ReadFile function.
//
// Input:
//      None
//
// ============================================================================

CWords::CWords(){

    //std::cout << "CWORDS CONSTRUCTOR\n";

    m_numWords = 0;
    for (int i = 0; i < NUM_WORDS; i++){
        m_words[i] = new char [CHAR_SIZE];
    }
    ReadFile();
}



// ==== CWords::~CWords =======================================================
//
// This is the CWords destructor. It releases the dynamic memory.
//
// Input:
//      None
//
// ============================================================================

CWords::~CWords(){
    //printf("CWORDS DESTRUCTOR\n");
    for (int i = 0; i < m_numWords; ++i){
        delete []m_words[i];
    }
}



// ==== CWords::GetRandomWord =================================================
//
// This function randomly selects a word from m_words and returns it as a const
// char pointer.  It must first seed the random function (srand) to the current
// time to start the randomness.  Then use the random function (rand) to
// randomly select a word.
//
// Input:
//      None
//
// Output:
//      A const char pointer that contains the string of the random word/phrase.
//
// ============================================================================

const char *CWords::GetRandomWord() const{
    const char* word;
    int r;

    srand(time(NULL));

    r = (rand() % m_numWords) + 1;
    word = m_words[r];
    
    return word; 
}



// ==== CWords::ReadFile ======================================================
//
// This function reads the contents of the file that have a word separated by a
// new line.  As a note, the word can be a combination of two words (as a name
// in this case).  You will read the contents of the file until there are no
// more words to read or NUM_WORDS has been exhausted. As you read each word, be
// sure to update m_numWords (number of words read).
//
// Input:
//      None
//
// ============================================================================

void CWords::ReadFile(){
    string text;
    std::ifstream ReadFile("ListOfMarvelCharacters.txt");

    //read file line by line
    while (getline(ReadFile, text)){
        strcpy(m_words[m_numWords], text.c_str());
        m_numWords++;
    }
}
