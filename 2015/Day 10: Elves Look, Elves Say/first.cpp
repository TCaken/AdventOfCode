#include <bits/stdc++.h>
using namespace std;

string lookandsay(string s){
    vector<int> tmp;
    string ans = "";
    char cur = ' ';
    int count = 0;
    
    for(auto ch : s){
        if(cur == ' '){
            cur = ch;
            count = 1;
        }
        else{
            if(cur == ch){
                count += 1;
            }
            else{
                tmp.push_back(count);
                tmp.push_back(cur - '0');
                
                cur = ch;
                count = 1;
            }
        }
    }
    
    tmp.push_back(count);
    tmp.push_back(cur - '0');
    
    // for(auto it : tmp){
    //     cout << it << " ";
    // }
    // cout << "\n";
    
    for(int i = 0; i < tmp.size(); i+= 2){
        ans += tmp[i] + '0';
        ans += tmp[i+1] + '0';
    }
    // cout << "Ans: " << ans << "\n";
    
    return ans;
}

int main() {
    string s, ans = "";
    getline(cin, s);
    cout << "0: " << s << "\n";
    
    int n = 40;
    ans = s;
    for(int i = 1; i <= n; i++){
        ans = lookandsay(ans);
        // cout << i << ": " << ans << "\n";
    }
    
    cout << "Length of the string: " << ans.size() << "\n";
    
    return 0;
}
