#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

// 1. Define a struct/class for the priority queue items
struct LetterStat {
    char letter;
    int count;

    // Define operator< to teach the priority_queue how to sort these.
    // The priority_queue keeps the "largest" element at the top.
    // We want: High Count first, then Alphabetical (A < Z).
    bool operator<(const LetterStat& other) const {
        if (count != other.count) {
            // If my count is lower, I am "smaller" (so I go to the bottom)
            return count < other.count;
        }
        // If counts are equal, we want 'a' to be "bigger" than 'z' so 'a' pops first.
        // In ASCII, 'a' (97) < 'z' (122).
        // So if my char value is HIGHER, I am "smaller" in priority.
        return letter > other.letter;
    }
};

class RoomValidator {
public:
    // Helper function to solve a single line
    // Returns the sectorID if real, 0 if decoy
    int processRoom(string rawLine) {
        // --- PARSING ---
        // Format: aaaaa-bbb-z-y-x-123[abxyz]
        
        // Find the bracket '['
        size_t bracketPos = rawLine.find('[');
        string checksum = rawLine.substr(bracketPos + 1, 5); // take 5 chars inside []
        
        // The part before '[' looks like: aaaaa-bbb-z-y-x-123
        string temp = rawLine.substr(0, bracketPos);
        
        // Find the last dash to split Name and Sector ID
        size_t lastDash = temp.rfind('-');
        string encryptedName = temp.substr(0, lastDash);
        int sectorID = stoi(temp.substr(lastDash + 1));

        // --- COUNTING ---
        map<char, int> counts;
        for (char c : encryptedName) {
            if (c != '-') {
                counts[c]++;
            }
        }

        // --- PRIORITY QUEUE LOGIC ---
        priority_queue<LetterStat> pq;
        for (auto const& [key, val] : counts) {
            pq.push({key, val});
        }

        // --- VERIFICATION ---
        // Pop the top 5 valid letters from the queue
        string calculatedChecksum = "";
        for (int i = 0; i < 5; i++) {
            if (pq.empty()) break;
            calculatedChecksum += pq.top().letter;
            pq.pop();
        }

        if (calculatedChecksum == checksum) {
            return sectorID;
        } else {
            return 0;
        }
    }
};

int main() {
    RoomValidator validator;
    string line;
    long totalSectorIDs = 0;

    // Read input line by line (Ctrl+Z or Ctrl+D to stop)
    while (cin >> line) {
        totalSectorIDs += validator.processRoom(line);
    }

    cout << "Sum of Sector IDs for real rooms: " << totalSectorIDs << endl;

    return 0;
}