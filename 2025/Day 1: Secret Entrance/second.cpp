#include <bits/stdc++.h>
using namespace std;

int readCommand(string s){
    int n = s.size();
    
    if(s[0] == 'L'){
        return -stoi(s.substr(1, n-1));
    }else if(s[0] == 'R'){
        return stoi(s.substr(1, n-1));
    }
}
int main() {
	// your code goes here
    int pos = 50, mod = 100, ans = 0, val = 0, remainder = 0;
    string command;
    
    while(getline(cin, command)){
        // cout << pos << " --> ";
        
        remainder = readCommand(command);
        val = abs(remainder) / mod;
        remainder += val*mod;
        
        ans += val;
        
        if(pos == 0){
            pos = (pos + remainder + mod) % mod;
        }
        else if (pos != 0){
            pos += remainder;
            if(pos <= 0 || pos >= mod){
                ans++;
                if(pos < 0) pos += mod;
                else if(pos >= mod) pos -= mod;
            }
        }
        
        // cout << pos << " = " << ans << "\n";
    }
    
    cout << "ANSWER: " << ans << "\n";
}
