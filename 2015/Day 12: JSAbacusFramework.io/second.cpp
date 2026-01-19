#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

// Global string and position tracker
string jsonStr;
int pos = 0;

// Forward declarations so functions can call each other
long long parseValue();
string parseString();
long long parseNumber();
long long parseArray();
long long parseObject();

// 1. Parse a String (returns the string content)
string parseString() {
    pos++; // consume opening quote '"'
    string res = "";
    while (jsonStr[pos] != '"') {
        res += jsonStr[pos];
        pos++;
    }
    pos++; // consume closing quote '"'
    return res;
}

// 2. Parse a Number (returns the int value)
long long parseNumber() {
    size_t len = 0;
    // stoll parses the number and tells us how many chars it used in 'len'
    long long num = stoll(jsonStr.substr(pos), &len);
    pos += len;
    return num;
}

// 3. Parse an Array [...] (returns sum of elements)
long long parseArray() {
    pos++; // consume '['
    long long sum = 0;
    
    while (jsonStr[pos] != ']') {
        sum += parseValue();
        if (jsonStr[pos] == ',') pos++; // skip comma
    }
    
    pos++; // consume ']'
    return sum;
}

// 4. Parse an Object {...} (returns sum, OR 0 if "red" is found)
long long parseObject() {
    pos++; // consume '{'
    long long currentSum = 0;
    bool isRed = false;
    
    while (jsonStr[pos] != '}') {
        // Parse Key (we ignore keys, but must consume them)
        parseString(); 
        
        pos++; // consume ':'
        
        // Check Value type to see if it is the string "red"
        if (jsonStr[pos] == '"') {
            string val = parseString();
            if (val == "red") {
                isRed = true;
            }
        } else {
            // It's a number, array, or object -> add to sum
            currentSum += parseValue();
        }
        
        if (jsonStr[pos] == ',') pos++; // skip comma
    }
    
    pos++; // consume '}'
    
    // If we found "red" anywhere as a direct value, the whole object is 0
    if (isRed) return 0;
    return currentSum;
}

// 5. Main Dispatcher
long long parseValue() {
    char c = jsonStr[pos];
    
    if (c == '{') return parseObject();
    if (c == '[') return parseArray();
    if (c == '"') {
        parseString(); // Consume string, contributes 0 to sum
        return 0;
    }
    if (isdigit(c) || c == '-') return parseNumber();
    
    return 0; // Should not happen in valid input
}

int main() {
    // Optimization to make cin faster
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string line;
    // Read line by line until End of File (EOF)
    while (getline(cin, line)) {
        jsonStr += line;
    }
    
    // Start parsing
    long long totalSum = parseValue();
    
    cout << "Total Sum (ignoring red objects): " << totalSum << endl;
    
    return 0;
}