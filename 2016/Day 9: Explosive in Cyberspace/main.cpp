#include <bits/stdc++.h>

using namespace std;

int main() {
    string s, result = "", tmp = "", pattern = "";
    getline(cin, s);
    
    int n = s.size(), start = 0, end = 0, pos = 0, ans = 0;
    stack<string> stk;
    
    while(start < n){
        if(s[start] == '('){
            end = s.find(")", start);
            if(end == -1){
                // cout << s.substr(start) << "\n";
                stk.push(s.substr(start));
                start += n;
            }
            else{
                // cout << s.substr(start+1, end-start-1) << "\n";
                stk.push(s.substr(start+1, end-start-1));
                start = end+1;
            }
        }
        else{
            end = s.find("(", start) - 1;
            if(end == -2){
                // cout << s.substr(start) << "\n";
                stk.push(s.substr(start));
                start += n;
            }
            else{
                // cout << s.substr(start, end-start+1) << "\n";
                stk.push(s.substr(start, end-start+1));
                start = end+1;
            }
        }
    }
    
    start = 0, end = 0;
    while(!stk.empty()){
        tmp = stk.top();
        stk.pop();
        
        // cout << tmp << "\n";
        
        if(tmp[0] >= '0' && tmp[0] <= '9'){
            pos = tmp.find('x');
            
            pattern = tmp.substr(0, pos);
            start = stoi(pattern);
            pattern = tmp.substr(pos+1);
            end = stoi(pattern);
            
            ans += (start-1)*end;
        }
        else{
            ans += tmp.size();
        }
    }
    
    cout << ans << "\n";
    
    
    
    return 0;
}

