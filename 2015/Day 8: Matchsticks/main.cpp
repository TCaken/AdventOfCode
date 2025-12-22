#include <bits/stdc++.h>
using namespace std;

int countLength(string s){
    int n = s.size();
    int len = 0;
    
    for(int i = 1; i < n-1; i++){
        if(s[i] == '\\'){
            if(s[i+1] == 'x'){
                i+=3;
            }
            else{
                i+=1;
            }
        }
        len++;
    }
    return n-len;
}

int encode(string s){
    int n = s.size();
    int len = n+2;
    
    for(auto ch : s){
        if(ch == '\\' || ch == '"' ){
            len += 1;
        }
    }
    return len-n;
}

int main() {
	// your code goes here
    string s;
    int ans1 = 0, ans2 = 0;
    while(getline(cin, s)){
        // cout << s << " " << countLength(s) << "\n";
        ans1 += countLength(s);
        ans2 += encode(s);
    }
    
    cout << "Answer1: " << ans1 << "\n";
    cout << "Answer2: " << ans2 << "\n";

}
