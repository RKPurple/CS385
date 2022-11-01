/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Rohan Kallur
 * Version     : 1.0
 * Date        : 10/31/22
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in Theta(n^2) time.
 */
long count_inversions_slow(int array[], int length)
{
    // TODO
    int num_inversions = 0;
    // loop over all the elements except for the last
    for (int i = 0; i < length - 1; ++i)
    {
        // check the current element against all after it
        for (int j = i + 1; j < length; ++j)
        {
            // check if the current element is greater than elements after it and add to inversion counter
            if (array[i] > array[j])
                ++num_inversions;
        }
    }
    return num_inversions;
}

/**
 * Counts the number of inversions in an array in Theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length)
{
    // TODO
    // Hint: Use mergesort!
    int *scratch = new int[length];
    long num_inversions = mergesort(array, scratch, 0, length - 1);
    delete[] scratch;
    return num_inversions;
}

long merge(int array[], int scratch[], int low, int mid, int high)
{
    int i1 = low;
    int i2 = mid + 1;
    int i = low;
    long num_inversions = 0;
    while (i1 <= mid && i2 <= high)
    {
        if (array[i1] <= array[i2])
        {
            scratch[i++] = array[i1++];
        }
        else
        {
            scratch[i++] = array[i2++];
            num_inversions += (mid - i1 + 1);
        }
    }
    while (i1 <= mid)
    {
        scratch[i++] = array[i1++];
    }
    while (i2 <= high)
    {
        scratch[i++] = array[i2++];
    }
    for (i = low; i <= high; i++)
    {
        array[i] = scratch[i];
    }
    return num_inversions;
}

static long mergesort(int array[], int scratch[], int low, int high)
{
    // TODO
    long num_inversions = 0;
    if (low < high)
    {
        int mid = low + ((high - low) / 2);
        num_inversions += mergesort(array, scratch, low, mid);
        num_inversions += mergesort(array, scratch, mid + 1, high);
        num_inversions += merge(array, scratch, low, mid, high);
    }
    return num_inversions;
}

int main(int argc, char *argv[])
{
    // TODO: parse command-line argument
    if (argc > 2)
    {
        cerr << "Usage: " << argv[0] << " [slow]" << endl;
        return -1;
    }
    string s;
    if (argc == 2)
    {
        s = argv[1];
        if (s != "slow")
        {
            cerr << "Error: Unrecognized option '" << argv[1] << "'." << endl;
            return -1;
        }
    }
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
    int num_values = values.size();
    if (num_values == 0)
    {
        cerr << "Error: Sequence of integers not received." << endl;
        return -1;
    }
    // TODO: produce output
    if (s == "slow")
    {
        cout << "Number of inversions: " << count_inversions_slow(&values[0], num_values) << endl;
        return 1;
    }
    else
    {
        cout << "Number of inversions: " << count_inversions_fast(&values[0], num_values) << endl;
        return 1;
    }
}
