#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

// Configuration
const int TARGET_LITERS = 150;

// We store the number of containers used for EVERY valid combination found
std::vector<int> validSolutionLengths;

// index: current container index
// currentSum: current liters
// currentCount: number of containers used so far
// containers: the input data
void findCombinations(int index, int currentSum, int currentCount, const std::vector<int>& containers) {
    
    // Base Case 1: Exact match
    if (currentSum == TARGET_LITERS) {
        // Record how many containers it took to get here
        validSolutionLengths.push_back(currentCount);
        return;
    }
    
    // Base Case 2: Overshot or no containers left
    if (currentSum > TARGET_LITERS || index >= containers.size()) {
        return;
    }

    // --- Recursive Step ---

    // Option A: Include current container
    // (Notice we increment currentCount)
    findCombinations(index + 1, currentSum + containers[index], currentCount + 1, containers);
    
    // Option B: Exclude current container
    // (currentCount stays the same)
    findCombinations(index + 1, currentSum, currentCount, containers);
}

int main() {
    std::vector<int> containers;
    int size;

    // Reading input (Standard Input)
    // Paste your input into the console and press Ctrl+D (Linux/Mac) or Ctrl+Z (Windows) to end
    while (std::cin >> size) {
        containers.push_back(size);
    }

    // 1. Find all valid combinations
    findCombinations(0, 0, 0, containers);

    if (validSolutionLengths.empty()) {
        std::cout << "No valid combinations found (Check your input!)." << std::endl;
        return 0;
    }

    // 2. Find the minimum number of containers used
    int minContainers = *std::min_element(validSolutionLengths.begin(), validSolutionLengths.end());

    // 3. Count how many ways use that minimum number
    int waysWithMinContainers = 0;
    for (int len : validSolutionLengths) {
        if (len == minContainers) {
            waysWithMinContainers++;
        }
    }

    // Output
    std::cout << "--- Results ---" << std::endl;
    std::cout << "Total Valid Combinations (Part 1 Answer): " << validSolutionLengths.size() << std::endl;
    std::cout << "Minimum Containers Needed: " << minContainers << std::endl;
    std::cout << "Ways to fill with min containers (Part 2 Answer): " << waysWithMinContainers << std::endl;

    return 0;
}