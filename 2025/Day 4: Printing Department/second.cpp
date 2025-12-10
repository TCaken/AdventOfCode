#include <bits/stdc++.h>
using namespace std;

// Function to convert string row to vector<bool>
vector<bool> decipher(const string& s){
    vector<bool> ans;
    for(char ch : s){
        if(ch == '@') ans.push_back(true);
        else ans.push_back(false);
    }
    return ans;
}

// Helper function to count neighbors for a given (r, c)
int count_neighbors(const vector<vector<bool>>& grid, int m, int n, int r, int c) {
    int count = 0;
    
    // Arrays for 8 directions: {dr, dc}
    int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    for (int k = 0; k < 8; k++) {
        int nr = r + dr[k];
        int nc = c + dc[k];

        // Check bounds and if the neighbor is a roll
        if (nr >= 0 && nr < m && nc >= 0 && nc < n) {
            if (grid[nr][nc]) {
                count++;
            }
        }
    }
    return count;
}


int solve(vector<vector<bool>>& grid, int m, int n) {
    if (m == 0 || n == 0) return 0;

    int total_accessible_rolls = 0;
    queue<pair<int, int>> q;
    
    // To prevent adding the same roll multiple times to the queue
    vector<vector<bool>> in_queue(m, vector<bool>(n, false)); 

    // --- PASS 1: Find all initially accessible rolls ---
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            if(grid[i][j]){
                if(count_neighbors(grid, m, n, i, j) < 4){
                    q.push({i, j});
                    in_queue[i][j] = true;
                }
            }
        }
    }
    
    // --- PASS 2: Iteratively remove rolls and check neighbors ---
    int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};

    while(!q.empty()){
        pair<int, int> current = q.front();
        q.pop();
        int r = current.first;
        int c = current.second;

        // The roll must still exist to be removed.
        // It's possible a neighbor check put it in the queue, 
        // but it was already processed, so we double-check.
        if (!grid[r][c]) continue; 

        // 1. Remove the accessible roll
        grid[r][c] = false; // The roll is removed
        total_accessible_rolls++;

        // 2. Check all 8 neighbors of the removed roll
        for (int k = 0; k < 8; k++) {
            int nr = r + dr[k];
            int nc = c + dc[k];

            // Check bounds
            if (nr >= 0 && nr < m && nc >= 0 && nc < n) {
                // If the neighbor is a roll AND hasn't been added to the queue yet
                if (grid[nr][nc] && !in_queue[nr][nc]) {
                    
                    // Re-evaluate its accessibility based on the new, modified grid
                    if (count_neighbors(grid, m, n, nr, nc) < 4) {
                        q.push({nr, nc});
                        in_queue[nr][nc] = true;
                    }
                }
            }
        }
    }
    
    return total_accessible_rolls;
}

int main() {
    // Fast I/O (optional, but good practice in competitive programming)
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<vector<bool>> grid;
    string s;
    
    // Read the grid from standard input
    while(getline(cin, s)){
        if (!s.empty()) {
            grid.push_back(decipher(s));
        }
    }
    
    int m = grid.size();
    int n = (m > 0) ? grid[0].size() : 0;
    
    // Calculate and print the final answer
    cout << solve(grid, m, n) << "\n";
    
    return 0;
}