#include <bits/stdc++.h>
using namespace std;

vector<string> grid;

long long calculatePath(vector<vector<long long>> &paths, int x, int y, int m, int n){
    if(paths[x][y] != -1) return paths[x][y];
    else if(x == m-1){
        paths[x][y] = 1;
    }
    else{
        if(grid[x][y] == '^'){
            long long tmp = 0;
            if(y-1 >= 0){
                tmp += calculatePath(paths, x, y-1, m, n);  
            }
            if(y+1 < n){
                tmp += calculatePath(paths, x, y+1, m, n); 
            }
            paths[x][y] = tmp;
        }
        else{
            grid[x][y] = '|';
            if(x+1 < m){
                paths[x][y] = calculatePath(paths, x+1, y, m, n);
            }
        }
    }
    // cout << x << " " << y << " " <<  paths[x][y] << "\n";
    return paths[x][y];
}

int main() {
	// your code goes here
	string str;
	
    while(getline(cin, str)){
        grid.push_back(str);
    }   
    
    //Start point
    int x = 0, y = 0, m = grid.size(), n = grid[0].size();
    long long ans = 0;
    vector<vector<long long>> paths (m, vector<long long>(n, -1));
    
    cout << m << " x " << n << "\n";
    
    for(int i = 0; i < n; i++){
        if(grid[0][i] == 'S'){
            ans = calculatePath(paths, 0, i, m, n);
        }
    }

    
    // while(!s.empty()){
    //     auto pos = s.top();
    //     s.pop();
    //     x = pos.first, y = pos.second;
        
    //     if(grid[x][y] == '.'){
    //         grid[x][y] = '|';
    //         if(x+1 < m){
    //             s.push(make_pair(x+1, y));  
    //         }
    //     }
    //     else if(grid[x][y] == '^'){
    //         if(y-1 >= 0){
    //             s.push(make_pair(x, y-1));  
    //         }
    //         if(y+1 < n){
    //             s.push(make_pair(x, y+1));  
    //         }
    //     }
    //     else{
    //         if(x+1 < m){
    //             s.push(make_pair(x+1, y));  
    //         }
    //     }
        
    //     if(x == m-1) {
    //         ans++;
    //         // cout << x << " " << y << " :" << ans << "\n";
    //     }
    //     // cout << x << " " << y << " :" << ans << "\n";
    // }
    
    cout << "Final Result: " << ans << "\n";
    
    return 0;
    
    
    
}
