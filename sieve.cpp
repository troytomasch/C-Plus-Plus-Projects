/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Troy Tomasch
 * Date        :
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

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
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
}

void PrimesSieve::display_primes() const {
    // TODO: write code to display the primes in the format specified in the
    // requirements document.
	const int max_prime_width = num_digits(max_prime_);
	int primes_per_row = 80 / (max_prime_width + 1);
	int row_ints = 0;
	cout << "\n";
	cout << "Number of primes found: " << count_num_primes() << endl;
	cout << "Primes up to " << limit_ << ":" << endl;
	for (int i = 2; i <= limit_; i++) {
		if (limit_ < 103) {
			if (is_prime_[i] == true) {
				cout << i;
				if (!(i == max_prime_)) {
					cout << " ";
				}
			}
		}
		else {
		if (is_prime_[i] == true) {
				if (row_ints >= primes_per_row) {
					cout << "\n";
					row_ints = 0;
				}
				cout << setw(max_prime_width) << i;
				row_ints++;
				if (!(i == max_prime_) and !(row_ints >= primes_per_row)) {
					cout << " ";
				}
			}
		}
	}
}

int PrimesSieve::count_num_primes() const {
    // TODO: write code to count the number of primes found
	int primes = 0;
	for (int i = 2; i <= limit_; i++) {
    	if (is_prime_[i] == 1) {
    		primes++;
    	}
    }
	return primes;
}

void PrimesSieve::sieve() {
    // TODO: write sieve algorithm
	for (int i=2; i <= limit_; i++) {
		is_prime_[i] = 1;
	}

	for (int i=2; i <= sqrt(limit_); i++) {
		if (is_prime_[i] == 1) {
			for (int j=i*i; j <= limit_; j+= i) {
				is_prime_[j] = 0;
			}
		}
	}

	for (int i=2; i <= limit_; i++) {
		if (is_prime_[i] == 1) {
			max_prime_ = i;
		}
	}
}

int PrimesSieve::num_digits(int num) {
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.
	int digits_ = 1;
	while (num > 10) {
		num = num / 10;
		digits_++;
	}
    return digits_;
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

    // TODO: write code that uses your class to produce the desired output.
    PrimesSieve(limit).display_primes();

    return 0;
}
