/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Rohan Kallur
 * Date        : 9/28/22
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <cstring>
using namespace std;

vector<vector<int>> get_ways(int num_stairs)
{
    vector<int> finalreturn;                          // Blank vector
    vector<vector<int>> ways = vector<vector<int>>(); // Return vector
    if (num_stairs <= 0)                              // Break case
    {
        ways.push_back(finalreturn); // return a blank vector to the end of the ways vector and end the recusion
    }
    else
    {
        for (int i = 1; i < 4; i++) // 1 2 and 3 steps at a time
        {
            if (num_stairs >= i) // Check if you can step i times
            {
                vector<vector<int>> result = get_ways(num_stairs - i); // checek the next iterations of it
                for (unsigned int j = 0; j < result.size(); j++)
                {
                    result.at(j).insert(result.at(j).begin(), i); // add i steps to the front of the current series
                }
                ways.insert(ways.end(), result.begin(), result.end()); // add the series to the vector of ways that you can climb
            }
        }
    }
    return ways;
}

void display_ways(const vector<vector<int>> &ways)
{
    stringstream ss;
    ss << ways.size();
    string width;
    ss >> width; // Figure out how many digits are in the amount of ways to right align
    for (unsigned int i = 0; i < ways.size(); i++)
    {
        cout << setw(width.length()) << i + 1; // which number version it is
        cout << ". [";
        for (unsigned int j = 0; j < ways.at(i).size() - 1; j++)
        {
            cout << ways.at(i).at(j) << ", "; // print all except last steps
        }
        cout << ways.at(i).at(ways.at(i).size() - 1) << "]" << endl; // print last step, clsoe bracket and end line
    }
}

int main(int argc, char *const argv[])
{
    int input;
    if (argc != 2) // Check if the the correct amount of inputs were given
    {
        cerr << "Usage: " << argv[0] << " <number of stairs>" << endl;
        return -1;
    }
    istringstream iss;
    iss.str(argv[1]);
    if (!(iss >> input) || input <= 0) // Check if the given input is an integer and if it is greater than 0 (Positive)
    {
        cerr << "Error: Number of stairs must be a positive integer." << endl;
        return -1;
    }
    vector<vector<int>> ways = get_ways(input);
    if (input == 1) // Different display if there is 1 step
    {
        cout << ways.size() << " way to climb " << input << " stair." << endl;
    }
    else // display how many ways for steps
    {
        cout << ways.size() << " ways to climb " << input << " stairs." << endl;
    }
    display_ways(ways);
    return 0;
}
