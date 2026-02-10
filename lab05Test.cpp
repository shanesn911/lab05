// IMPORTANT NOTE TO USER: 
// The only parts of the program that you should change are:
// 1. The function definitions that are currently on lines 30-32.
// 2. The addition of more test cases in the main() function.
// PLEASE LEAVE ALL OTHER CODE (especially the ASSERT_EQUAL() functions) AS-IS!
//
#include <iostream>
#include <cstdlib> 
#include <cmath>
#include <string>
#include <vector>
// YOU ARE NOT ALLOWED TO INCLUDE ANY OTHER LIBRARY!!! (zero grade penalty)

using namespace std;

// FYI, templates are a way to make a variable type "flexible".
// We'll cover these at some point, but for now just leave these alone.
template <typename T>
void ASSERT_EQUAL(T, T);

template <typename T>
void ASSERT_EQUAL(const vector<T>&, const vector<T>&);

// FUNCTION DECLARATIONS: YOU MUST DEFINE AND USE THESE IN THE TESTS (do not remove):
vector<string> split(string target, string delimiter);
int bin2d(string binstring);
string dec2bh(string sdec, char bh);

// FUNCTION DEFINITIONS:
vector<string> split(string target, string delimiter) {
    vector<string> result;
    
    // If delimiter is empty, return the target as the only element
    if (delimiter.length() == 0) {
        if (target.length() > 0) {
            result.push_back(target);
        }
        return result;
    }
    
    int start = 0;
    int end = target.find(delimiter);
    
    // Loop through the string and find all occurrences of delimiter
    while (end != string::npos) {
        string substring = target.substr(start, end - start);
        
        // Only add non-empty substrings
        if (substring.length() > 0) {
            result.push_back(substring);
        }
        
        // Move start position past the delimiter
        start = end + delimiter.length();
        end = target.find(delimiter, start);
    }
    
    // Add the last substring (after the last delimiter)
    string lastSubstring = target.substr(start);
    if (lastSubstring.length() > 0) {
        result.push_back(lastSubstring);
    }
    
    return result;
}

int bin2d(string binstring) {
    int decimal = 0;
    int length = binstring.length();
    
    // Process each digit from left to right
    for (int i = 0; i < length; i++) {
        char digit = binstring[i];
        
        // Check if the digit is valid (only '0' or '1')
        if (digit != '0' && digit != '1') {
            return -1;
        }
        
        // Convert character to integer value
        int digitValue = digit - '0';
        
        // Calculate position from the right (for power calculation)
        int position = length - 1 - i;
        
        // Add the contribution of this digit to the decimal value
        decimal = decimal + digitValue * pow(2, position);
    }
    
    return decimal;
}

string dec2bh(string sdec, char bh) {
    // Convert string to integer
    int decimal = 0;
    for (int i = 0; i < sdec.length(); i++) {
        decimal = decimal * 10 + (sdec[i] - '0');
    }
    
    // Handle special case of 0
    if (decimal == 0) {
        return "0";
    }
    
    string result = "";
    
    if (bh == 'b') {
        // Convert to binary
        while (decimal > 0) {
            int remainder = decimal % 2;
            char digitChar = '0' + remainder;
            result = digitChar + result;
            decimal = decimal / 2;
        }
    } 
    else if (bh == 'h') {
        // Convert to hexadecimal
        while (decimal > 0) {
            int remainder = decimal % 16;
            char digitChar;
            if (remainder < 10) {
                digitChar = '0' + remainder;
            } else {
                digitChar = 'A' + (remainder - 10);
            }
            result = digitChar + result;
            decimal = decimal / 16;
        }
    }
    
    return result;
}


int main() {
    cout << "Testing split..." << endl;    
    vector<string> answer;

    // Testing split function
    answer = {"Apples", "Bananas", "Cherries", "Dragon Fruits", "Elderberries"};
    ASSERT_EQUAL(answer, split("Apples,Bananas,Cherries,Dragon Fruits,Elderberries", ","));

    answer = {"The", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog"};
    ASSERT_EQUAL(answer, split("The quick brown fox jumps over the lazy dog", " "));

    answer = {"It w", "s r", "re, I w", "s there."};
    ASSERT_EQUAL(answer, split("It was rare, I was there.", "a"));

    answer = {"Can you hear me?", " - The Machine"};
    ASSERT_EQUAL(answer, split("\"Can you hear me?\" - The Machine", "\""));


    // Feel free to add additional test cases and edge cases
    // answer = {}
    // ASSERT_EQUAL(answer, split("", ""));


    cout << endl << "Testing bin2d..." << endl;
    // Testing binary to decimal
    ASSERT_EQUAL(0, bin2d("0"));
    ASSERT_EQUAL(2, bin2d("10"));
    ASSERT_EQUAL(9,bin2d("1001"));
    ASSERT_EQUAL(45,bin2d("101101"));
    ASSERT_EQUAL(246, bin2d("11110110"));

    cout << "Testing dec2hb..." << endl;
    // Testing decimal to binary
    ASSERT_EQUAL(string("1010"), dec2bh("10", 'b'));
    ASSERT_EQUAL(string("1111"), dec2bh("15", 'b'));
    ASSERT_EQUAL(string("1100100"), dec2bh("100", 'b'));

    // Testing decimal to hex conversion
    ASSERT_EQUAL(string("A"), dec2bh("10", 'h'));
    ASSERT_EQUAL(string("64"), dec2bh("100", 'h')); 

    // Feel free to add additional test cases and edge cases
    // ASSERT_EQUAL(string("64"), dec2bh("100", 'h')); 


    return 0;
}


// Template function to compare expected and actual values.
// If the values match, it prints a "PASSED" message; otherwise, a "FAILED" message.
template <typename T>
void ASSERT_EQUAL(T expected, T actual) {
    if (expected == actual) {
        cout << "PASSED: Expected and actual values are equal: " << expected << endl;
    } else {
        cout << "FAILED: Expected " << expected << " but got " << actual << endl;
    }
}

template <typename T>
void ASSERT_EQUAL(const vector<T>& expectation, const vector<T>& actuality) {
    T expect;
    T actual;
    if (expectation.size() != actuality.size()) {
	    cout << "FAILED: Expected vector of size " << expectation.size() << " but got " << actuality.size() << endl;
	    return;
    }
    for (int i = 0; i < min(expectation.size(), actuality.size()); i++) {
	    expect = expectation[i];
	    actual = actuality[i];
    	if (expect == actual) continue;
        cout << "FAILED: With index=" << i << ", Expected " << endl << "\t\"" << expect << "\"\n" << "\tbut got " << endl << "\t\"" << actual << "\"\n";
	    return;
    }

    cout << "PASSED: Expected and actual values are equal:";
    for (const T& expect: expectation) cout << endl << "\t" << expect;
    cout << endl << endl;    
}