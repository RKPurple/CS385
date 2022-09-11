/******************************************************************************* 
 * Filename: helloworld.cpp 
 * Author  :  Rohan Kallur
 * Version : 1.0 
 * Date    :  9/1/22
 * Description: Basic Hello World program. 
 * Pledge  :  I pledge my honor that I have abided by the Stevens honor system.
 ******************************************************************************/
#include <iostream>
using namespace std; //do this so dont have to write std:: before all input outputs
int main() {
    string s;
    cout << "Hello World!" << endl;
    cout << "Enter a string: ";
    cin >> s;
    cout << "s is: " << s << endl;
    //<< std::endl - moves to next line
    return 0;
}