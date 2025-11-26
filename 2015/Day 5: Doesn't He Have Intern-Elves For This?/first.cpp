#include <bits/stdc++.h>
using namespace std;

bool isNice(string s){
    bool req1 = false; //Contain three vowels
    bool req2 = false; //Contain double letters
    bool req3 = true; //Does not contain ab,cd,pq,xy
    
    int vowel_counts = 0, n = s.size();
    
    if(s[0] == 'a' || s[0] == 'e' || s[0] == 'i' || s[0] == 'u' || s[0] == 'o'){
        vowel_counts += 1;
    }
    
    for(int i = 1; i < n; i++){
       if(s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'u' || s[i] == 'o'){
            vowel_counts += 1;
        };
        
        if(req2 || (s[i-1] == s[i])) req2 = true;
        if(req3){
            if(s[i-1] == 'a' && s[i] == 'b') req3 = false;
            if(s[i-1] == 'c' && s[i] == 'd') req3 = false;
            if(s[i-1] == 'p' && s[i] == 'q') req3 = false;
            if(s[i-1] == 'x' && s[i] == 'y') req3 = false;
        }
    }
    
    if(vowel_counts >= 3) req1 = true;
    
    // cout << req1 << " " << req2 << " " << req3 << "\n";
    return req1 && req2 && req3;
}


int main() {
    string s;
    int ans = 0;
    
    while(getline(cin, s)){
        if(isNice(s)) ans++;
    }
    
    cout << ans << "\n";
    
}
