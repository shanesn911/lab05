#include <iostream> // for cin, cout
#include <vector>   // for vector
#include <string>   // for getline()
// YOU ARE NOT ALLOWED TO INCLUDE ANY OTHER LIBRARY!!! (zero grade penalty)
using namespace std;

// FUNCTION DECLARATION: YOU MUST DEFINE AND USE THIS (do not remove):
//      You can declare/define other functions if you like as well,
//      but you must use function split() below.
vector<string> split(string target, string delimiter);

int main() {
    string target, delimiter;
    
    // Get target string from user (use getline to handle whitespaces)
    cout << "Enter string to split:" << endl;
    getline(cin, target);
    
    // Get delimiter string from user
    cout << "Enter delimiter string:" << endl;
    getline(cin, delimiter);
    
    // Call function split()
    vector<string> result = split(target, delimiter);
    
    // Check if there are any valid substrings
    if(result.size() == 0){
        cout << "No substrings." << endl;
    }else{
        // Print the results
        cout << "The substrings are: ";
        for(int i = 0; i < result.size(); i++){
            cout << "\"" << result[i] << "\"";
            if(i < result.size() - 1){
                cout << ", ";
            }
        }
        cout << endl;
    }
    return 0;
}

// FUNCTION DEFINITIONS
// Pre-Condition: target is a string to be split, delimiter is a string to split by
// Post-Condition: returns a vector of substrings from target separated by delimiter
//                 (empty substrings are excluded)
vector<string> split(string target, string delimiter) {
    vector<string> result;
    
    // If delimiter is empty, return the target as the only element
    if(delimiter.length() == 0){
        if(target.length() > 0){
            result.push_back(target);
        }
        return result;
    }
    
    int start = 0;
    int end = target.find(delimiter);
    
    // Loop through the string and find all occurrences of delimiter
    while(end != string::npos){
        string substring = target.substr(start, end - start);
        
        // Only add non-empty substrings
        if(substring.length() > 0){
            result.push_back(substring);
        }
        
        // Move start position past the delimiter
        start = end + delimiter.length();
        end = target.find(delimiter, start);
    }
    
    // Add the last substring (after the last delimiter)
    string lastSubstring = target.substr(start);
    if(lastSubstring.length() > 0){
        result.push_back(lastSubstring);
    }
    
    return result;
}