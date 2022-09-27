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
    for (char x : s)
    {
        if (!islower(x))
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
    unsigned int checker = 0;
    unsigned int temp = 0;
    unsigned int setter;
    for (char x : s)
    {
        setter = 1 << (x - 'a');
        temp = checker;
        checker = temp & setter;
        if (checker == setter)
        {
            return false;
        }
        else
        {
            checker = temp | setter;
        }
    }
    return true;
}

int main(int argc, char *const argv[])
{
    if (argc != 2)
    {
        cerr << "Usage: " << argv[0] << " <string>" << endl;
        return -1;
    }
    if (!is_all_lowercase(argv[1]))
    {
        cerr << "Error: String must contain only lowercase letters." << endl;
        return -1;
    }
    if (all_unique_letters(argv[1]))
    {
        cout << "All letters are unique." << endl;
    }
    else
    {
        cout << "Duplicate letters found." << endl;
    }
    // Calls other functions to produce correct output.
}
