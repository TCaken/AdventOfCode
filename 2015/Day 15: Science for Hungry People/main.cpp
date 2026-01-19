#include <iostream>
#include <algorithm> // Required for std::max

int main() {
    long long maxScore = 0, maxScore2 = 0; // Use long long to prevent overflow

    // Loop 1: Frosting (i) ranges from 0 to 100
    for (int i = 0; i <= 100; ++i) {
    
        // Loop 2: Candy (j) ranges from 0 to whatever is left
        for (int j = 0; j <= 100 - i; ++j) {
            
            // Loop 3: Butterscotch (k) ranges from 0 to whatever is left
            for (int k = 0; k <= 100 - i - j; ++k) {
                
                // Sugar (l) takes up the remaining space
                int l = 100 - i - j - k;

                // --- Calculate Properties based on your input ---
                
                // Input: Frosting(4, -2, 0, 0), Candy(0, 5, -1, 0), Butterscotch(-1, 0, 5, 0), Sugar(0, 0, -2, 2)

                long long capacity = (4 * i) + (0 * j) + (-1 * k) + (0 * l);
                long long durability = (-2 * i) + (5 * j) + (0 * k) + (0 * l);
                long long flavor = (0 * i) + (-1 * j) + (5 * k) + (-2 * l);
                long long texture = (0 * i) + (0 * j) + (0 * k) + (2 * l);
                long long calories = (5 * i) + (8 * j) + (6 * k) + (1 * l);

                // --- Apply Rules ---

                // Rule 1: If any property is negative, it becomes 0
                if (capacity < 0) capacity = 0;
                if (durability < 0) durability = 0;
                if (flavor < 0) flavor = 0;
                if (texture < 0) texture = 0;

                // Rule 2: Calculate total score (ignore calories for Part 1)
                long long currentScore = capacity * durability * flavor * texture;

                // Check if this is the best score so far
                if (currentScore > maxScore) {
                    maxScore = currentScore;
                    // Optional: Uncomment to see the winning recipe
                    // std::cout << "New Best: " << maxScore 
                    //           << " [F:" << i << " C:" << j << " B:" << k << " S:" << l << "]" << std::endl;
                }
                if(calories == 500 & currentScore > maxScore2){
                    maxScore2 = currentScore;
                }
            }
        }
    }

    std::cout << "Final Highest Score: " << maxScore << std::endl;
    std::cout << "Final Highest Score Part 2: " << maxScore2 << std::endl;
    return 0;
}