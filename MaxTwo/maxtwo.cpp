/******************************************************************************* 
 * Filename: maxtwo.cpp 
 * Author  :  Rohan Kallur
 * Version : 1.0 
 * Date    :  9/7/22
 * Description: Computes the GCD of two command line arguments
 * Pledge  :  I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;

//argc is the amount of arguments in the command line
int main(int argc, char* argv[]) {
    int m;
    int n;
    istringstream iss;
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <integer m> <integer n>" << endl;
        return -1;
    }
    iss.str(argv[1]); //Built in command to store the string stored in argv into iss object
    //Variable M will contain the value of iss : if iss cannot become a valid int will return 0
    if (!(iss >> m)) {
        cerr << "First argument must be an integer" << endl;
        return -1;
    }
    iss.clear(); //Must clear the iss object before processing second string
    iss.str(argv[2]);
    if (!(iss >> n)) {
        cerr << "Second argument must be an integer" << endl;
        return -1;
    }
    cout << "m: " << m << endl;
    cout << "n: " << n << endl;
    cout << "max(" << m << ", " << n << ") is " << max(m, n) << endl; //Built in max func with <algorithm>
    return 0;
}