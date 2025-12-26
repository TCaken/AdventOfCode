#include <bits/stdc++.h>

using namespace std;

int main() {
    vector<vector<bool>> grid;
    string s;

    while (getline(cin, s)) {
        vector<bool> tmp;
        for(auto ch : s){
            if(ch == '.'){
                tmp.push_back(false);
            }
            else{
                tmp.push_back(true);
            }
        }
        grid.push_back(tmp);
    }
    
    int n = grid.size();
    
    
    for(int i = 0; i < 100; i++){
        vector<vector<bool>> tmp(n, vector<bool>(n, false));
        for(int x = 0; x < n; x++){
            for(int y = 0; y < n; y++){
                int sum = 0;
                if(x > 0){
                    if(y > 0) sum += grid[x-1][y-1];
                    sum += grid[x-1][y];
                    if(y < n-1) sum += grid[x-1][y+1];
                }
                
                if(y > 0) sum += grid[x][y-1];
                if(y < n-1) sum += grid[x][y+1];
                
                if(x < n-1){
                    if(y > 0) sum += grid[x+1][y-1];
                    sum += grid[x+1][y];
                    if(y < n-1) sum += grid[x+1][y+1];
                }
                
                if(grid[x][y]){
                    if(sum == 2 || sum == 3){
                        tmp[x][y] = true;
                    }
                    else{
                        tmp[x][y] = false;
                    }
                }
                else{
                    if(sum == 3){
                        tmp[x][y] = true;
                    }
                    else{
                        tmp[x][y] = false;
                    }
                }
            }
        }
        
        tmp[0][0] = true;
        tmp[0][n-1] = true;
        tmp[n-1][0] = true;
        tmp[n-1][n-1] = true;
        
        int ans = 0;
        grid = tmp;
        for(int x = 0; x < n; x++){
            for(int y = 0; y < n; y++){
                ans += tmp[x][y];
                // if(tmp[x][y]){
                //     cout << "#";
                // }
                // else{
                //     cout << ".";
                // }
            }
            // cout << "\n";
        }
        cout << i << ": " << ans << "\n";
    
    }
    return 0;
}