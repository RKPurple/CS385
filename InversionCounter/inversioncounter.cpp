/*******************************************************************************
 * Name          : quickselect.cpp
 * Author        : Rohan Kallur
 * Pledge        : I pledge my honor that I have abided by the Stevens Honor System.
 * Date          : 10/28/22
 * Description   : Implements the quickselect algorithm.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>
using namespace std;

int main(int argc, char *argv[])
{
    // TODO: parse command-line argument
    cout << "Enter sequence of integers, each followed by a space: " << flush;
    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true)
    {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln)
        {
            if (str.length() > 0)
            {
                iss.str(str);
                if (iss >> value)
                {
                    values.push_back(value);
                }
                else
                {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln)
            {
                break;
            }
            str.clear();
        }
        else
        {
            str += c;
        }
    }
    // TODO: produce output
    return 0;
}