#include <iostream> // for cin, cout, endl
#include <cstdlib>  // for exit()
#include <cmath>    // for pow() function ONLY
// YOU ARE NOT ALLOWED TO INCLUDE ANY OTHER LIBRARY!!! (zero grade penalty)
using namespace std;

// FUNCTION DECLARATIONS: YOU MUST DEFINE AND USE THESE (do not remove):
//      You can declare/define other functions if you like as well,
//      but you must use the 2 functions below.
int bin2d(string binstring);
string dec2bh(string sdec, char bh);

int main ( int argc, char *argv[] ) {

    // Check if there are correct number of arguments
    if (argc != 3) {
        cout << "Usage: converter <options: d2b, d2h, b2d> <value>" << endl;
        return 1;
    }
    
    // Convert argv to strings
    string option = argv[1];
    string value = argv[2];
    
    // Check which option was selected and perform conversion
    if (option == "d2b") {
        // Decimal to binary conversion
        string result = dec2bh(value, 'b');
        cout << "The value in binary is: " << result << endl;
    } 
    else if (option == "d2h") {
        // Decimal to hexadecimal conversion
        string result = dec2bh(value, 'h');
        cout << "The value in hexadecimal is: " << result << endl;
    } 
    else if (option == "b2d") {
        // Binary to decimal conversion
        int result = bin2d(value);
        if (result == -1) {
            cout << "Binary value contains non-binary digits." << endl;
            return 1;
        }
        cout << "The value in decimal is: " << result << endl;
    } 
    else {
        // Invalid option
        cout << "Usage: converter <options: d2b, d2h, b2d> <value>" << endl;
        return 1;
    }

    return 0;
}


int bin2d(string binstring) {
    int decimal = 0;
    int length = binstring.length();
    
    // Process each digit from left to right
    for (int i = 0; i < length; i++) {
        char digit = binstring[i];
        
        // Check if the digit is valid 
        if (digit != '0' && digit != '1') {
            return -1;
        }
        
        // Convert character to integer 
        int digitValue = digit - '0';
        
        // Calculate position
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