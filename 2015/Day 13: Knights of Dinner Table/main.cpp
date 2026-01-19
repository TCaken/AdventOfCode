#include <bits/stdc++.h>
using namespace std;

int main() {
	// your code goes here
    string s, user1, user2, happiness, action;
    int n = 9, tmp = 0, tmp2 = 0, from, to, val; // PART 2 CHANGE N TO 9
    vector<vector<int>> grid(n, vector<int>(n, 0));
    
    while(getline(cin, s)){
        // Find the user1 and user 2;
        tmp = s.find(' ');
        user1 = s.substr(0, tmp);
        
        action = s.substr(tmp+7, 4);
        tmp2 = s.find(' ', tmp+12);
        happiness = s.substr(tmp+12, tmp2-tmp-12);
        // cout << tmp << " " << tmp2 << "\n";
        
        tmp = s.rfind(' ');
        user2 = s.substr(tmp+1);
        
        if(user1[0] == 'A') from = 0;
        else if(user1[0] == 'B') from = 1;
        else if(user1[0] == 'C') from = 2;
        else if(user1[0] == 'D') from = 3;
        else if(user1[0] == 'E') from = 4;
        else if(user1[0] == 'F') from = 5;
        else if(user1[0] == 'G') from = 6;
        else if(user1[0] == 'M') from = 7;
        
        if(user2[0] == 'A') to = 0;
        else if(user2[0] == 'B') to = 1;
        else if(user2[0] == 'C') to = 2;
        else if(user2[0] == 'D') to = 3;
        else if(user2[0] == 'E') to = 4;
        else if(user2[0] == 'F') to = 5;
        else if(user2[0] == 'G') to = 6;
        else if(user2[0] == 'M') to = 7;
        
        if(action == "gain"){
            val = stoi(happiness);
        }else if(action == "lose"){
            val = 0 - stoi(happiness);
        }
        
        grid[from][to] += val;
        grid[to][from] += val;
        
        // cout << user1 << " " << action << " " << happiness << " "<< user2 << "\n";
        
    }
    
    queue<pair<int, unordered_map<int,int>>> q;
    unordered_map<int, int> visited;
    visited[0] = 0;
    for(int i = 1; i < n; i++){
        unordered_map<int, int> vis = visited;
        vis[1] = i;
        q.push(make_pair(1 | (1 << i), vis));
    }
    
    int ans = 0;
    while(!q.empty()){
        auto el = q.front();
        unordered_map<int,int> mp = el.second;
        int bit = el.first, size = mp.size();
        int from = mp[size-1];
        q.pop();

        // bitset<8> binaryRep(bit);
        // cout << bitset<8>(binaryRep) << " " << size << "\n";
        
        if(size == n){
            int sum = 0;
            for(int i = 0; i < size - 1; i++){
                sum += grid[mp[i]][mp[i+1]];
            }
            sum += grid[mp[size-1]][0];
            
            if(sum > ans){
                cout << "NEW ";
                for(int i = 0; i < size; i++){
                    cout << mp[i] << " ";
                }
                cout << " : " << sum << "\n";
                ans = sum;
            }
        
            // ans = max(sum, ans);
            continue;
        }
        
        for(int i = 1; i < n; i++){
            if(bit & (1 << i)){
                
            }
            else{
                mp[size] = i;
                q.push(make_pair(bit | (1 << i), mp));
            }
        }
    }
    
    
    // for(int i = 0; i < n; i++){
    //     for(int j = 0; j < n; j++){
    //         cout << grid[i][j] << " ";
    //     }
    //     cout << '\n';
    // }
    
    cout << "Part 1 Answer: " << ans << "\n";
    
    return 0;
    
}
