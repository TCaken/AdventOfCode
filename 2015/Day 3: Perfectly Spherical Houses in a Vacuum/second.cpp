#include <bits/stdc++.h>
using namespace std;

struct pair_hash {
    size_t operator()(const pair<int,int>& p) const noexcept {
        return std::hash<int>()(p.first) ^ (std::hash<int>()(p.second) << 1);
    }
};


int main() {
    string commands;
    cin >> commands;
    unordered_map<pair<int,int>, int, pair_hash> vis;
    pair<int, int> pos = {0,0};
    pair<int, int> pos2 = {0,0};
    bool first = true;
    vis[pos] = 1;
    int ans = 1;
    
    
    for(auto command : commands){
        if(first){
            if(command == '^'){
                pos.second += 1;
            }else if(command == 'v'){
                pos.second -= 1;
            }else if(command == '>'){
                pos.first += 1;
            }else{
                pos.first -= 1;
            }
            
            if(vis.find(pos) == vis.end()){
                vis[pos] = 1;
                ans++;
            }
            // cout << pos.first << "," << pos.second << " " << ans << "\n";
        }
        else{
            if(command == '^'){
                pos2.second += 1;
            }else if(command == 'v'){
                pos2.second -= 1;
            }else if(command == '>'){
                pos2.first += 1;
            }else{
                pos2.first -= 1;
            } 
            
            if(vis.find(pos2) == vis.end()){
                vis[pos2] = 1;
                ans++;
            }
            // cout << pos2.first << "," << pos2.second << " " << ans << "\n";
        }
        
        first = !first;
    }
    
    cout << ans;
    
}
