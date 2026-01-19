#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

int main() {
    string content;
    getline(cin, content);

    // 3. Define regex pattern
    // "-?" matches optional minus, "\\d+" matches digits
    regex pattern("-?\\d+");
    
    // 4. Create an iterator to find matches
    sregex_iterator begin(content.begin(), content.end(), pattern);
    sregex_iterator end;

    long long totalSum = 0;

    // 5. Iterate and sum
    for (sregex_iterator i = begin; i != end; ++i) {
        smatch match = *i;
        totalSum += stoi(match.str());
    }

    cout << "Total Sum: " << totalSum << endl;

    return 0;
}