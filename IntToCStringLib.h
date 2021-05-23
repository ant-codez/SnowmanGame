// ============================================================================
// File: IntToCStringLib.h
// ============================================================================
// This is the header file that contains two function prototypes to convert an
// int to a CString.
//
// Note: Include this header file if you plan on using the functions below.
//
// How to compile:
//
// Make sure you compile only all your .cpp files
//  g++ -Wall -g -c <file1>.cpp <file2>.cpp
//
// Link all your files included IntToCStringLib.o
// g++ <file1>.o <file2>.o IntToCStringLib.o
//
// Then you should be able to run your executable file: ./a.out
// ============================================================================



// ==== Reverse ===============================================================
//
// This function reverses the order a character array.
//
// Input:
//      str     [IN/OUT]    -- a char array to reverse
//      length  [IN]        -- an int that represents the size of str
//
// Output:
//      None
//
// ============================================================================

void	Reverse(char str[], int length);



// ==== IntToCString ==========================================================
//
// This function converts an int to a string (cstring).
//
// Input:
//      num     [IN]    -- an int to convert to a string (cstring)
//      str     [OUT]   -- a char pointer where the converted int to cstring
//                         will be stored.
//      base    [IN]    -- the base to convert the int (default to 10)
//
// Output:
//      char pointer    -- the output of the converted int to a cstring.
//
// ============================================================================
char*	IntToCString(int num, char* str, int base);
