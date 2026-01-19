#include <bits/stdc++.h>
using namespace std;

int main() {
    int sz = 8;
    vector<unordered_map<char, int>> signals(sz, unordered_map<char,int>());
    string s;
    
    while(getline(cin, s)){
        for(int i = 0; i < sz; i++){
            if(signals[i].find(s[i]) == signals[i].end()){
                signals[i][s[i]] = 0;
            }
            signals[i][s[i]]++;
            // cout << s[i] << " " << signals[i][s[i]] << "\n";
        }
    }
    
    for(int i = 0; i < sz; i++){
        // Part 1
        // int cnt = 0;
        
        // Part 2;
        int cnt = INT_MAX;
        
        char ch;
        for(auto &[key, val] : signals[i]){
            // cout << key << " " << val << "\n";
            if(val < cnt){
                cnt = val;
                ch = key;
            }
        }
        
        cout << "Pos-" << i << ": " << ch << " " << cnt << endl;
    }
    
	return 0;
}
