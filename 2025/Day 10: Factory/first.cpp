#include <bits/stdc++.h>
using namespace std;

pair<int, int> readCommand(string s){
    int len = 0, val = 0;
    for(auto ch : s){
        if(ch == '.'){
            val = val << 1;
            len++;
        }
        else if(ch == '#'){
            val = (val << 1) + 1;
            len++;
        }
    }
    
    return make_pair(len, val);
}

vector<int> readCommand2(string s, int sz){
    vector<int> ans, lights;
    int n = s.size(), val = 0, len = 0;
    string tmp = "";
    
    for(int i = 0; i < n; i++){
        if(s[i] >= '0' && s[i] <= '9'){
            tmp += s[i];
        }
        else if(s[i] == ','){
            lights.push_back(stoi(tmp));
            tmp = "";
        }else if(s[i] == ')'){
            lights.push_back(stoi(tmp));
            tmp = "";
            
            // for(auto light : lights){
            //     cout << light << " ";
            // }
            
            len = lights.size();
            for(int i = 0; i < len; i++){
              val += (1 << (sz-lights[i]-1));
            }
            ans.push_back(val);
            
            lights.clear();
            val = 0;
            len = 0;
        }
    }
    // cout << s << "\n";
    return ans;
}

int main() {
	// your code goes here
	string s;
	int target = 0, pos1=0, pos2=0, n=0, m=0,  ans=0;
	vector<int> buttons;
	vector<int> joltages;
	
	while(getline(cin, s)){
	    pos1 = s.find(' ');
	    auto p = readCommand(s.substr(0, pos1));
	    n = p.first;
	    target = p.second;
	    
	    pos2 = s.find('{');
	    buttons= readCommand2(s.substr(pos1+1, pos2-pos1-2), n);
	    m = buttons.size();
	    
	    queue<pair<int,int>> q;
	    q.push(make_pair(0,0));
	    
	   // cout << "Buttons: ";
	   // for(auto button : buttons){
	   //     cout << button << " ";
	   // }
	   // cout << "\n";
	    
	    for(int i = 0; i < m; i++){
	        int sz = q.size();
	        for(int j = 0; j < sz; j++){
	            auto p = q.front();
	            q.pop();
	            
	            //Choice 1 - Did not pick
	            q.push(p);
	            
	            //Choice 2 - Pick the
	            int val = p.first ^ buttons[i];
	            int len = p.second + (1 << (i));
	            q.push(make_pair(val, len));
	        }
	    }
	    
	    int smallest = INT_MAX;
	    while(!q.empty()){
	        auto p = q.front();
	        q.pop();
	        
	       // cout << p.first << " " << bitset<10>(p.second) << "\n";
	        if(p.first == target){
	           // cout << p.first << " " << bitset<10>(p.second) << " " << __builtin_popcount(p.second) << "\n";
	            smallest = min(smallest, __builtin_popcount(p.second));
	        }
	    }
        ans += smallest;
	    
	    //Comment
	   // cout << n << " " << target << "\n";
	   // for(auto button : buttons){
	   //     cout << button << " ";
	   // }
	   // cout << "\n";
	}
	cout << "Final Result " << ans << "\n";

}
