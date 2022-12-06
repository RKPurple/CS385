/*******************************************************************************
 * Name        : shortestpaths.cpp
 * Author      : Rohan Kallur & Makena Williamson
 * Date        : 12/5/2022
 * Description : Floyd's Algorithm
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System
 ******************************************************************************/
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <vector>
#include <string>
#include <cstring>
#include <iomanip>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

long INF = __LONG_MAX__;
vector<vector<long>> dist_matrix;
vector<vector<long>> path_matrix;
vector<vector<string>> inter_matrix;
vector<string> path_backtrack;

int digits(long n)
{
    int digits = 0;
    while (n > 0)
    {
        n /= 10;
        digits++;
    }
    return digits;
}

void display_table(vector<vector<long>> matrix, const string &label, int num_vertices,
                   const bool use_letters = false)
{
    cout << label << endl;
    long max_val = 0;
    for (int i = 0; i < num_vertices; i++)
    {
        for (int j = 0; j < num_vertices; j++)
        {
            long cell = matrix.at(i).at(j);
            if (cell < INF && cell > max_val)
            {
                max_val = matrix.at(i).at(j);
            }
        }
    }
    int max_cell_width = digits(max_val);
    if (num_vertices == 1)
        cout << ' ';
    cout << ' ';
    for (int j = 0; j < num_vertices; j++)
    {
        cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');
    }
    cout << endl;
    for (int i = 0; i < num_vertices; i++)
    {
        cout << static_cast<char>(i + 'A');
        for (int j = 0; j < num_vertices; j++)
        {
            cout << " " << setw(max_cell_width);
            if (matrix.at(i).at(j) == INF)
            {
                cout << "-";
            }
            else if (use_letters)
            {
                cout << static_cast<char>(matrix.at(i).at(j) + 'A');
            }
            else
            {
                cout << matrix.at(i).at(j);
            }
        }
        cout << endl;
    }
    cout << endl;
}

void display_inter(int num_vertices, string letters)
{
    cout << "Intermediate vertices:" << endl;
    cout << ' ';
    for (int j = 0; j < num_vertices; j++)
    {
        cout << setw(2) << static_cast<char>(j + 'A');
    }
    cout << endl;
    for (int i = 0; i < num_vertices; i++)
    {
        cout << static_cast<char>(i + 'A');
        for (int j = 0; j < num_vertices; j++)
        {
            cout << " " << setw(1);
            cout << inter_matrix.at(i).at(j);
        }
        cout << endl;
    }
    cout << endl;
}

string vector_stringization(vector<string> v)
{
    string ret = "";
    for (auto x : v)
    {
        ret.append(x);
        ret.append(" ");
    }
    ret.pop_back();
    return ret;
}

// Create distance matrix
void make_distance_matrix(int n)
{
    vector<long> row;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                row.push_back(0);
            }
            else
            {
                row.push_back(INF);
            }
        }
        dist_matrix.push_back(row);
        row.clear();
    }
}

// Create path matrix
void make_path_matrix(int n)
{
    vector<long> row;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                row.push_back(0);
            }
            else
            {
                row.push_back(INF);
            }
        }
        path_matrix.push_back(row);
        row.clear();
    }
}

// Create intermediate matrix
void make_intermediate_matrix(int n)
{
    vector<string> row;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            row.push_back("-");
        }
        inter_matrix.push_back(row);
        row.clear();
    }
}

void floyd(int n, string letters)
{
    path_matrix = dist_matrix;
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (path_matrix.at(i).at(j) > (path_matrix.at(i).at(k) + path_matrix.at(k).at(j)) && (path_matrix.at(k).at(j) != INF) && (path_matrix.at(i).at(k) != INF))
                {
                    path_matrix.at(i).at(j) = path_matrix.at(i).at(k) + path_matrix.at(k).at(j);
                    inter_matrix.at(i).at(j) = letters.at(k);
                }
            }
        }
    }
}

string backtrack(int from, int to, string letters)
{
    string s;
    if (from == to)
    {
        return s;
    }
    else if (inter_matrix.at(from).at(to) == "-")
    {
        string sx(1, letters.at(to));
        return sx;
    }
    else
    {
        s.append(backtrack(from, letters.find(inter_matrix.at(from).at(to)), letters));
        s.append(backtrack(letters.find(inter_matrix.at(from).at(to)), to, letters));
        return s;
    }
}

int main(int argc, const char *argv[])
{
    // No command line argument or too many arguments
    if (argc != 2)
    {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    // Create an ifstream object
    ifstream input_file(argv[1]);
    // Input file not found in the same folder as the executable
    if (!input_file)
    {
        cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
        return 1;
    }

    // Add read errors to the list of exceptions the ifstream will handle.
    input_file.exceptions(ifstream::badbit);
    string line;
    try
    {
        // Initialize variables
        unsigned int line_number = 1;
        istringstream iss;
        int num_vertices;
        int weight;
        string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

        while (getline(input_file, line))
        {
            // The number of vertices is not an integer between 1 and 26
            if (line_number == 1)
            {
                iss.str(line);
                if (!(iss >> num_vertices) || num_vertices < 1 || num_vertices > 26)
                {
                    cerr << "Error: Invalid number of vertices '" << line << "' on line 1." << endl;
                    return 1;
                }
                iss.clear();

                // Make arrays of size num_vertices x num_vertices
                make_distance_matrix(num_vertices);
                make_path_matrix(num_vertices);
                make_intermediate_matrix(num_vertices);

                // Move onto next line
                line_number++;
                continue;
            }
            // The number of line components != 3
            vector<string> params;
            char *token = strtok(const_cast<char *>(line.c_str()), " ");
            while (token != nullptr)
            {
                params.push_back(string(token));
                token = strtok(nullptr, " ");
            }

            if (params.size() != 3)
            {
                cerr << "Error: Invalid edge data '" << vector_stringization(params) << "' on line " << line_number << "." << endl;
                return 1;
            }
            string letters = alphabet.substr(0, num_vertices);
            size_t err = -1;
            for (unsigned int i = 0; i < params.size() - 1; i++)
            {
                if (letters.find(params.at(i)) == err)
                {
                    if (i == 0)
                    {
                        cerr << "Error: Starting vertex '" << params.at(i) << "' on line " << line_number << " is not among valid values " << letters.at(0) << "-" << letters.at(letters.size() - 1) << "." << endl;
                        return 1;
                    }
                    else if (i == 1)
                    {
                        cerr << "Error: Ending vertex '" << params.at(i) << "' on line " << line_number << " is not among valid values " << letters.at(0) << "-" << letters.at(letters.size() - 1) << "." << endl;
                        return 1;
                    }
                }
            }
            iss.str(params.at(2));
            if (!(iss >> weight) || weight <= 0)
            {
                cerr << "Error: Invalid edge weight '" << params.at(2) << "' on line " << line_number << "." << endl;
                return 1;
            }
            iss.clear();
            dist_matrix.at(letters.find(params.at(0))).at(letters.find(params.at(1))) = weight;
            ++line_number;
        }
        string letters = alphabet.substr(0, num_vertices);
        // Don't forget to close the file.
        input_file.close();
        display_table(dist_matrix, "Distance matrix:", num_vertices);
        floyd(num_vertices, letters);
        display_table(path_matrix, "Path lengths:", num_vertices);
        display_inter(num_vertices, letters);
        for (int i = 0; i < num_vertices; i++)
        {
            for (int j = 0; j < num_vertices; j++)
            {
                if (path_matrix.at(i).at(j) == INF)
                {
                    cout << letters.at(i) << " -> " << letters.at(j) << ", distance: infinity, path: none" << endl;
                }
                else
                {
                    cout << letters.at(i) << " -> " << letters.at(j) << ", distance: " << path_matrix.at(i).at(j) << ", path: ";
                    cout << letters.at(i);
                    if (i == j)
                    {
                        cout << endl;
                    }
                    else
                    {
                        cout << " -> ";
                        string s = backtrack(i, j, letters);
                        for (long unsigned int i = 0; i < s.length() - 1; i++)
                        {
                            cout << s.at(i) << " -> ";
                        }
                        cout << s.at(s.length() - 1) << endl;
                    }
                }
            }
        }
    }
    catch (const ifstream::failure &f)
    {
        cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
        return 1;
    }

    return 0;
}
