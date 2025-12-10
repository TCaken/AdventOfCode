#include <bits/stdc++.h>
using namespace std;

pair<int, int> readCommand(string s){
    int n = s.size();
    int pos = s.find(',');
    
    int x = stoi(s.substr(0, pos));
    int y = stoi(s.substr(pos+1, n-pos-1));
    
    return make_pair(x,y);
}

int main() {
    string s;
    long long ans = 0, x = 0, y = 0;
    vector<pair<int,int>> points;
    unordered_map<pair<int, int>, int> mp;
    while(getline(cin, s)){
        points.push_back(readCommand(s));  
    }
    
    int n = points.size();
    
    for(int i = 0; i < n-1; i++){
        for(int j = i+1; j < n; j++){
            ans = max(ans, (long long)(abs(points[i].first - points[j].first) + 1) * (abs(points[i].second - points[j].second) + 1));
        }
    }
    
    // for(auto point : points){
    //      cout << point.first << " " << point.second << "\n";
    // }
    
    cout << "Final Result: " << ans << "\n";
    return 0;
}
