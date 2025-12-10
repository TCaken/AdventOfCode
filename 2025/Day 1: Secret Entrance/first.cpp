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
    int pos = 50, mod = 100, ans = 0;
    string command;
    
    while(getline(cin, command)){
        pos = (pos + readCommand(command)) % 100;
        if(pos == 0) ans++;
        // cout << pos << "\n";
    }
    
    cout << "ANSWER: " << ans << "\n";
}
