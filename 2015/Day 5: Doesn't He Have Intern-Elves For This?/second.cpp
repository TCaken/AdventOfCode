#include <bits/stdc++.h>
using namespace std;

bool isNice2(string s){
    bool req1 = false; //Contain pairs of letters that appears twice
    bool req2 = false; //Contain same letters that has another letter in between
    
    unordered_map<string, int> mp;
    int n = s.size();
    string temp;
    
    for(int i = 0; i < n - 1; i++){
        if(!req1){
            temp = s.substr(i, 2);
            mp[temp] += 1;
            if(mp[temp] >= 2) req1 = true;
        }
        
        if(i < n - 2){
            if(s[i] == s[i+2]){
                if(s[i] == s[i+1]) i++;
                req2 = true;
            }  
        }
    }
    
    // cout << req1 << " " << req2 << "\n";
    return req1 && req2;
}


int main() {
    string s;
    int ans = 0;
    
    while(getline(cin, s)){
        if(isNice2(s)) ans++;
    }
    
    cout << ans << "\n";
    
}
