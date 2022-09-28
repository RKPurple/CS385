/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Rohan Kallur
 * Date        : 9/27/2022
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System
 ******************************************************************************/
#include <iostream>
#include <cctype>
#include <iostream>
#include <cstring>

using namespace std;

bool is_all_lowercase(const string &s)
{
    for (char x : s) // Iterate through all individual characters in the string s
    {
        if (!islower(x)) // Check casing at first occurence of an uppercase letter return false
        {
            return false;
        }
    }
    return true; // will return if all chars are lowercase
}

bool all_unique_letters(const string &s)
{
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.

    // You MUST use only a single int for storage and work with bitwise
    // and bitshifting operators.  Using any other kind of solution will
    // automatically result in a grade of ZERO for the whole assignment.
    unsigned int checker = 0; // The binary 32 bit int that holds which chars have been seen
    unsigned int temp;        // Hold the current what has been already iterated through when performing next operation
    unsigned int setter;
    for (char x : s) // Iterate through each character in le string
    {
        setter = 1 << (x - 'a'); // shift the bit to the letter in the alphabet's number
        temp = checker;          // store checker array
        checker = temp & setter; // and them
        if (checker == setter)   // if they are equivalent then that means the char has been seen before
        {
            return false;
        }
        else
        {
            checker = temp | setter; // change it so that the character is logged
        }
    }
    return true; // YAY
}

int main(int argc, char *const argv[])
{
    if (argc != 2) // Must only be 1 paramter when calling main
    {
        cerr << "Usage: " << argv[0] << " <string>" << endl;
        return -1;
    }
    if (!is_all_lowercase(argv[1])) // All letters must be cased in the lower variety
    {
        cerr << "Error: String must contain only lowercase letters." << endl;
        return -1;
    }
    if (all_unique_letters(argv[1])) // The letters are unique
    {
        cout << "All letters are unique." << endl;
        return 1;
    }
    else // Letters aren't unique
    {
        cout << "Duplicate letters found." << endl;
        return 0;
    }
    // Calls other functions to produce correct output.
}
