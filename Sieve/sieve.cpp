/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Rohan Kallur
 * Date        : 9/21/22
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System
 ******************************************************************************/
#include <cmath>
#include <iomanip>  
#include <iostream>
#include <sstream>
#include <cstring>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_, max_prime_width_, primes_per_row;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) :
    is_prime_{new bool[limit + 1]}, limit_{limit} {
    memset(is_prime_, 1, limit + 1); //Initialize the elements of is_prime_ to True except for the final value
    sieve();
    num_primes_ = count_num_primes();
    int i = limit_;
    while (!is_prime_[i]) { // Iterate through is_prime_ backward to find largest prime
        i--;
    }
    max_prime_ = i;
    max_prime_width_ = num_digits(max_prime_);
    primes_per_row = 80 / (max_prime_width_ + 1);
}

void PrimesSieve::display_primes() const {
    // TODO: write code to display the primes in the format specified in the
    // requirements document.
    int count = 0;
    bool first = 1;
    if (primes_per_row > num_primes_) {
        for (int i = 2; i <= limit_; i++) {
        if (is_prime_[i]) {
            if (first) {
                cout << i;
                first = 0;
            }
            else {
                cout << setw(num_digits(i) + 1) << i;
            }
        }
        }
    }
    else {
        for (int i = 2; i <= limit_; i++) {
            if (is_prime_[i]) {
                if (first) {
                    cout << setw(max_prime_width_) << i;
                    first = 0;
                    count++;
                }
                else {
                    cout << setw(max_prime_width_ + 1) << i;
                    count++;
                        if (count == primes_per_row) {
                            cout << endl;
                            count = 0;
                            first = 1;
                        }
                }
            }
        }
    }
}

int PrimesSieve::count_num_primes() const {
    // TODO: write code to count the number of primes found
    int num_primes = 0;
    for (int i = 2; i <= limit_; i++) {
        if (is_prime_[i]) {
            num_primes++;
        }
    }
    return num_primes;
}

void PrimesSieve::sieve() {
    for (int i = 2; i <= sqrt(limit_); i++) {
        if (is_prime_[i]) {
            for (int j = pow(i, 2); j <= limit_; j+= i) {
                is_prime_[j] = 0;
            }
        }
    }
}

int PrimesSieve::num_digits(int num) {
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.
    int digits = 0;
    while (num > 9) {
        num /= 10;
        digits++;
    }
    digits++;
    return digits;
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    PrimesSieve x(limit);
    cout << endl << "Number of primes found: " << x.num_primes() << endl;
    cout << "Primes up to " << limit << ":" << endl;
    x.display_primes();
    // TODO: write code that uses your class to produce the desired output.
    return 0;
}
