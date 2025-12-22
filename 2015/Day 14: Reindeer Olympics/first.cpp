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
    
    
    for(int i = 0; i < 9; i++){
        int n = 0, dist = 0;
        while(n < target){
            for(int t = 0; t < raceDuration[i] && n < target; t++, n++){
                // cout << n << " " << dist << "\n";
                dist += speed[i];
            }
            // cout << n << " " << dist << "\n";
            n += restDuration[i];
        };
        distance.push_back(dist);
    }
    
    for(auto it : distance){
        cout << it << " " << "\n";
    }
    
    return 0;
}
