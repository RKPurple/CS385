/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Rohan Kallur
 * Date        : 10/13/2022
 * Description : Water Jug Puzzle
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <iomanip>
#include <queue>
#include <vector>
#include <numeric>
#include <sstream>
#include <array>
using namespace std;

struct State
{
    int a, b, c;
    string directions;
    State *parent;

    State(int _a, int _b, int _c, string _directions) : a{_a}, b{_b}, c{_c}, directions{_directions}, parent{nullptr} {}

    // String representation of state in tuple form.
    string to_String()
    {
        ostringstream oss;
        oss << directions << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
};

string make_direction(int diff, string from, string to)
{
    string result;
    string difference;
    if (diff == 1)
    {
        result = "Pour 1 gallon from " + from + " to " + to + ". ";
        return result;
    }
    else
    {
        stringstream ss;
        ss << diff;
        ss >> difference;
        result = "Pour " + difference + " gallons from " + from + " to " + to + ". ";
        return result;
    }
}

vector<State *> backpath;
void backtrack(State *x)
{
    // cout << "hi" << endl;
    if (x->parent != nullptr)
    {
        backpath.insert(backpath.begin(), x);
        // cout << x->to_String() << endl;
        backtrack(x->parent);
    }
    else
    {
        // cout << x->to_String() << endl;
        backpath.insert(backpath.begin(), x);
    }
}

void print_backtrack()
{
    for (unsigned int i = 0; i < backpath.size(); i++)
    {
        cout << backpath.at(i)->to_String() << endl;
    }
}

void bfs(int goal_a, int goal_b, int goal_c, int cap_a, int cap_b, int cap_c)
{
    int a;
    int b;
    int c;
    queue<State *> q;
    queue<State *> q2;
    bool found = false;
    bool **inqueue = new bool *[cap_a + 1];
    for (int i = 0; i < cap_a + 1; ++i)
    {
        inqueue[i] = new bool[cap_b + 1];
        fill(inqueue[i], inqueue[i] + cap_b + 1, false);
    }
    State *initial = new State(0, 0, (goal_a + goal_b + goal_c), "Initial state. ");
    initial->parent = nullptr;
    q.push(initial);
    while (!(q.empty()))
    {
        State cur = *(q.front());
        // Check if you've reached your goal states
        // cout << "Cur: " << cur.to_String() << endl;
        // print_q(q);
        if (cur.a == goal_a && cur.b == goal_b)
        {
            backtrack(q.front());
            found = true;
            break;
        }
        // Mark state as inqueue
        inqueue[cur.a][cur.b] = true;

        // Pour C -> A
        if (cur.c != 0 && cur.a != cap_a)
        {
            a = cur.a + cur.c;
            b = cur.b;
            c = cur.c - (cap_a - cur.a);
            if (a > cap_a)
            {
                a = cap_a;
            }
            if (c < 0)
            {
                c = 0;
            }
            State *x = new State(a, b, c, make_direction(cur.c - c, "C", "A"));
            x->parent = q.front();
            if (!(inqueue[a][b]))
            {
                q.push(x);
            }
            else
            {
                delete x;
            }
        }

        // Pour B -> A
        if (cur.b != 0 && cur.a != cap_a)
        {
            a = cur.a + cur.b;
            b = cur.b - (cap_a - cur.a);
            c = cur.c;
            if (a > cap_a)
            {
                a = cap_a;
            }
            if (b < 0)
            {
                b = 0;
            }
            State *x = new State(a, b, c, make_direction(cur.b - b, "B", "A"));
            x->parent = q.front();
            if (!(inqueue[a][b]))
            {
                q.push(x);
            }
            else
            {
                delete x;
            }
        }

        // Pour C -> B
        if (cur.c != 0 && cur.b != cap_b)
        {
            a = cur.a;
            b = cur.b + cur.c;
            c = cur.c - (cap_b - cur.b);
            if (b > cap_b)
            {
                b = cap_b;
            }
            if (c < 0)
            {
                c = 0;
            }
            State *x = new State(a, b, c, make_direction(cur.c - c, "C", "B"));
            x->parent = q.front();
            if (!(inqueue[a][b]))
            {
                q.push(x);
            }
            else
            {
                delete x;
            }
        }

        // Pour A -> B
        if (cur.a != 0 && cur.b != cap_b)
        {
            a = cur.a - (cap_b - cur.b);
            b = cur.b + cur.a;
            c = cur.c;
            if (b > cap_b)
            {
                b = cap_b;
            }
            if (a < 0)
            {
                a = 0;
            }
            State *x = new State(a, b, c, make_direction(cur.a - a, "A", "B"));
            x->parent = q.front();
            if (!(inqueue[a][b]))
            {
                q.push(x);
            }
            else
            {
                delete x;
            }
        }

        // Pour B -> C
        if (cur.b != 0 && cur.c != cap_c)
        {
            a = cur.a;
            b = cur.b - (cap_c - cur.c);
            c = cur.c + cur.b;
            if (c > cap_c)
            {
                c = cap_c;
            }
            if (b < 0)
            {
                b = 0;
            }
            State *x = new State(a, b, c, make_direction(cur.b - b, "B", "C"));
            x->parent = q.front();
            if (!(inqueue[a][b]))
            {
                q.push(x);
            }
            else
            {
                delete x;
            }
        }

        // Pour A -> C
        if (cur.a != 0 && cur.c != cap_c)
        {
            a = cur.a - (cap_c - cur.c);
            b = cur.b;
            c = cur.c + cur.a;
            if (c > cap_c)
            {
                c = cap_c;
            }
            if (a < 0)
            {
                a = 0;
            }
            State *x = new State(a, b, c, make_direction(cur.a - a, "A", "C"));
            x->parent = q.front();
            if (!(inqueue[a][b]))
            {
                q.push(x);
            }
            else
            {
                delete x;
            }
        }
        q2.push(q.front());
        q.pop();
    }

    // Delete 2D array
    for (int i = 0; i < cap_a + 1; i++)
    {
        delete[] inqueue[i];
    }
    delete[] inqueue;

    if (!found)
    {
        while (!q2.empty())
        {
            delete q2.front();
            q2.pop();
        }
        while (!q.empty())
        {
            delete q.front();
            q.pop();
        }
        cout << "No solution." << endl;
        return;
    }
    // print_paths();
    print_backtrack();
    while (!q2.empty())
    {
        delete q2.front();
        q2.pop();
    }
    while (!q.empty())
    {
        delete q.front();
        q.pop();
    }
}

string checkInputs(int len, string inputs[])
{
    istringstream iss;
    int input;
    int compare;
    string result;
    string jugs[] = {"A", "B", "C", "A", "B", "C"};
    int total = 0;
    for (int i = 0; i < len; i++)
    {
        iss.clear();
        iss.str(inputs[i]);
        if (!(iss >> input) || input < 0 || (input == 0 && i < 3))
        {
            if (i < 3)
            {
                result = "Error: Invalid capacity '" + inputs[i];
                result = result + "' for jug " + jugs[i] + ".";
                return result;
            }
            else
            {
                result = "Error: Invalid goal '" + inputs[i];
                result = result + "' for jug " + jugs[i] + ".";
                return result;
            }
        }
    }
    for (int i = 3; i < len; i++)
    {
        iss.clear();
        iss.str(inputs[i]);
        iss >> input;
        iss.clear();
        iss.str(inputs[i - 3]);
        iss >> compare;
        if (input > compare)
        {
            result = "Error: Goal cannot exceed capacity of jug " + jugs[i] + ".";
            return result;
        }
        total += input;
    }
    iss.clear();
    iss.str(inputs[2]);
    iss >> input;
    if (total != input)
    {
        return "Error: Total gallons in goal state must be equal to the capacity of jug C.";
    }
    return "Valid";
}

int main(int argc, char *const argv[])
{
    if (argc != 7)
    {
        cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
        return -1;
    }
    string inputs[] = {argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]};
    if (checkInputs(argc - 1, inputs) != "Valid")
    {
        cerr << checkInputs(argc - 1, inputs) << endl;
        return -1;
    }
    istringstream iss;
    int convert;
    int newputs[6];
    for (int i = 0; i < 6; i++)
    {
        iss.clear();
        iss.str(inputs[i]);
        iss >> convert;
        newputs[i] = convert;
    }
    bfs(newputs[3], newputs[4], newputs[5], newputs[0], newputs[1], newputs[2]);
    return 0;
}