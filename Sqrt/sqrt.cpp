/******************************************************************************* 
 * Filename: sqrt.cpp 
 * Author  :  Rohan Kallur
 * Version : 1.0 
 * Date    :  9/7/22
 * Description: Computes the square root of a command line given value
 * Pledge  :  I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <iomanip> 
#include <limits>
using namespace std;
// cout << fixed; Fixes double division notation
// cout << setprecision(20); Sets how many decimal places to use in fixed notation

double sqrt(double a, double b) {
    cout << fixed;
    cout << setprecision(8);
    double nextGuess;
    double lastGuess = a;
    double n = a;
    double difference;
    if (a < 0) {
        return numeric_limits<double>::quiet_NaN();
    }
    if (a == 0) {
        return 0.0;
    }
    else if (a == 1) {
        return 1.0;
    }
    else {
        nextGuess = ((lastGuess + (n / lastGuess)) / 2);
        difference = abs(lastGuess - nextGuess);
        while (difference > b) {
            lastGuess = nextGuess;
            nextGuess = ((lastGuess + (n / lastGuess)) / 2);
            difference = abs(lastGuess - nextGuess);
        }
        return nextGuess;
    }
    return 0.0;
}

int main(int argc, char* argv[]) {
    double value;
    double epsilon = 1e-7;
    istringstream iss;
    if (argc != 2 && argc != 3) { //Check to see if correct amount of inputs
        cerr << "Usage: " << argv[0] << " <value> [epsilon]" << endl;
        return -1;
    }
    iss.str(argv[1]);
    if (!(iss >> value)) { //Check if the given value is valid
        cerr << "Error: Value argument must be a double." << endl;
        return -1;
    }
    iss.clear();
    if(argc == 3) {
        iss.str(argv[2]);
        if (!(iss >> epsilon) || epsilon <= 0) { //Check to see if inputted epsilon is positive and a valid double
            cerr << "Error: Epsilon argument must be a positive double." << endl;
            return -1;
        }
        iss.clear();    
    }
    cout << sqrt(value, epsilon) << endl;
    return 0;
}