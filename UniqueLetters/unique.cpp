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
    for (int i = 0; i < s.length(); i++)
    {
        if (!islower(s.at(i)))
        {
            return false;
        }
    }
    return true;
}

bool all_unique_letters(const string &s)
{
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.

    // You MUST use only a single int for storage and work with bitwise
    // and bitshifting operators.  Using any other kind of solution will
    // automatically result in a grade of ZERO for the whole assignment.
    return true;
}

int main(int argc, char *const argv[])
{
    if (argc != 1)
    {
        cerr << "Usage: " << argv[0] << "<string>" << endl;
        return -1;
    }
    if (!is_all_lowercase(argv[1]))
    {
        cerr << "Error: String must contain only lowercase letters." << endl;
        return -1;
    }
    // Calls other functions to produce correct output.
}
