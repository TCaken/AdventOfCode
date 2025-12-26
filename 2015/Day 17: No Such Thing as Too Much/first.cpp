#include <bits/stdc++.h>

using namespace std;

// Configuration
const int TARGET_LITERS = 150;

// Recursive function to find combinations
// index: current container we are considering
// currentSum: amount of eggnog currently stored
// containers: the list of available container sizes
void findCombinations(int index, int currentSum, const std::vector<int>& containers, int& validCombinations) {
    
    // Base Case 1: We hit the target exactly
    if (currentSum == TARGET_LITERS) {
        validCombinations++;
        return;
    }
    
    // Base Case 2: We exceeded the target OR we ran out of containers
    if (currentSum > TARGET_LITERS || index >= containers.size()) {
        return;
    }

    // --- Recursive Step ---
    
    // Option A: Include the current container
    findCombinations(index + 1, currentSum + containers[index], containers, validCombinations);
    
    // Option B: Exclude the current container (skip it)
    findCombinations(index + 1, currentSum, containers, validCombinations);
}

int main() {
    std::vector<int> containers;
    string size;


    while(getline(cin, size)) {
        containers.push_back(stoi(size));
    }

    // 2. Solve
    int totalValidCombinations = 0;
    
    // Start recursion: index 0, current sum 0
    findCombinations(0, 0, containers, totalValidCombinations);

    // 3. Output
    std::cout << "--- Results ---" << std::endl;
    std::cout << "Target Volume: " << TARGET_LITERS << " liters" << std::endl;
    std::cout << "Total Containers: " << containers.size() << std::endl;
    std::cout << "Valid Combinations: " << totalValidCombinations << std::endl;

    return 0;
}