#include <bits/stdc++.h>
using namespace std;


int main() {
	// your code goes here
    vector<int> speed = {27, 22, 11, 28, 4, 14, 3, 18, 18};
    vector<int> raceDuration = {5, 2, 5, 5, 16, 3, 21, 6, 5};
    vector<int> restDuration = {132, 41, 48, 134, 55, 38, 40, 103, 84};
    int target = 2503;
    vector<int> distance;
    queue<vector<int>> race;
    vector<int> ans(9, 0);
    
    for(int i = 0; i < 9; i++){
        vector<int> temp (5, 0);
        temp[0] = speed[i];
        temp[1] = raceDuration[i];
        temp[2] = raceDuration[i] + restDuration[i];
        race.push(temp);
    }
    
    for(int i = 1; i <= target; i++){
        int n = race.size();
        int maxD = 0;
        vector<int> maxI;
        for(int j = 0; j < n; j++){
            vector<int> reindeer = race.front();
            race.pop();
            
            if(reindeer[3] < reindeer[1]){
                reindeer[4] += reindeer[0];
                reindeer[3]++;
            }else if(reindeer[3] < reindeer[2]){
                reindeer[3]++;
            }
            
            if(reindeer[4] > maxD){
                maxI.clear();
                maxI.push_back(j);
                maxD = reindeer[4];
            }else if(reindeer[4] == maxD){
                maxI.push_back(j);
            }
            
            if(reindeer[3] == reindeer[2]) reindeer[3] = 0;
            // cout << i << " " << reindeer[4] << "\n";
            race.push(reindeer);
        }
        
        for(auto reindeer : maxI){
            ans[reindeer]++;
        }
    }
    
    while(!race.empty()){
        vector<int> reindeer = race.front();
        race.pop();
        
        cout << "Speed " << reindeer[0] << " at his " << reindeer[3] << " reached distance of " << reindeer[4] << "\n"; 
    };
    
    for(int i = 0; i < 9; i++){
        cout << "Reindeer " << i << " : " << ans[i] << "\n";
    }
    
    return 0;
}
