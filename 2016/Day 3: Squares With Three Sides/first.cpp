#include <iostream>

using namespace std;

int main() {
    // Variables to hold the three numbers on each line
    int a, b, c;
    int validCount = 0;

    // "cin >> a" skips whitespace (spaces, tabs, newlines) automatically.
    // The loop runs as long as there are 3 numbers available to read.
    while (cin >> a >> b >> c) {
        
        // This input is for the "Valid Triangle" puzzle.
        // Logic: Sum of any two sides must be > the third side.
        if (a + b > c && a + c > b && b + c > a) {
            validCount++;
        }
    }

    cout << "Valid triangles found: " << validCount << endl;

    return 0;
}