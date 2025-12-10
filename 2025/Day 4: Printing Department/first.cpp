#include <bits/stdc++.h>
using namespace std;

vector<bool> decipher(string s){
    vector<bool> ans;
    for(auto ch : s){
        if(ch == '@') ans.push_back(true);
        else ans.push_back(false);
    }
    return ans;
}

int main() {
    vector<vector<bool>> grid;
    string s;
    
    // 1. Read the grid from standard input
    while(getline(cin, s)){
        // Skip empty lines that might be at the end of input
        if (s.empty()) continue; 
        grid.push_back(decipher(s));
    }
    
    if (grid.empty()) {
        // Handle case where input is empty or invalid
        cout << 0 << "\n";
        return 0;
    }
    
    int ans = 0, m = grid.size(), n = grid[0].size(), temp = 0;
    
    // REMOVE DEBUG/EXTRA OUTPUT:
    // cout << m << " " << n << "\n"; 
    
    // 2. Iterate and count accessible rolls (correct logic)
    for(int i = 0 ; i < m; i++){
        for(int j = 0; j < n; j++){
            if(grid[i][j]){
                temp = 0;
                
                // Count all 8 neighbors...
                // (The boundary checks and logic here is correct)
                
                if(i > 0){
                    if(j > 0 && grid[i-1][j-1]) temp++;
                    temp += grid[i-1][j]? 1 : 0;
                    if(j < n-1 && grid[i-1][j+1]) temp++;
                }
                
                if(j > 0 && grid[i][j-1]) temp++;
                if(j < n-1 && grid[i][j+1]) temp++;
                
                if (i < m - 1){
                    if(j > 0 && grid[i+1][j-1]) temp++;
                    temp += grid[i+1][j]? 1 : 0;
                    if(j < n-1 && grid[i+1][j+1]) temp++;
                }
                
                if(temp < 4){
                    // REMOVE DEBUG/EXTRA OUTPUT:
                    // cout << i << " " << j << "\n"; 
                    ans++;
                }
            }
        }
    }
    
    // 3. Print ONLY the final answer
    cout << ans << "\n"; // This should be the only line of output.
    
    return 0; // Return 0 instead of 'return ans' inside main.
}