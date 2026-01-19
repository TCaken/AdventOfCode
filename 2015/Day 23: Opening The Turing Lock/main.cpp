#include <bits/stdc++.h>
using namespace std;

int main() {
	// your code goes here
	unordered_map<char, int> mp;
	string s, input, command, value;
	vector<string> commands;
	int offset = 0, n, i;
	char reg;
	
	while(getline(cin, input)){
	    commands.push_back(input);
	}
	
	//Part 2
	mp['a'] = 1;
	
	n = commands.size();
	while(i >= 0 && i < n){
	    s = commands[i];
        command = s.substr(0, 3);
	    reg = s[4];
	    
	    if(mp.find(reg) == mp.end()){
            mp[reg] = 0;
        }
	    
	    if(command == "hlf"){
	        mp[reg] = mp[reg] >> 1;
	        i++;
	    }else if(command == "tpl"){
	        mp[reg] = mp[reg]*3;
	        i++;
	    }
	    else if(command == "inc"){
	        mp[reg]++;
	        i++;
	    }
	    else if(command == "jmp"){
	        value = s.substr(4);
	        offset = stoi(value);
	        i+= offset;
	    }
	    else if(command == "jie"){
	        if(mp[reg] % 2 == 0){
	            value = s.substr(7);
    	        offset = stoi(value);
    	        i+= offset;
	        }
	        else{
	            i++;
	        }
	    }
	    else if(command == "jio"){
	        if(mp[reg] == 1){
	            value = s.substr(7);
    	        offset = stoi(value);
    	        i+= offset;
	        }
	        else{
	            i++;
	        }
	    }
	    
	   // cout << s << " " << mp[reg] << "\n";
	}
	
	
	for(auto &[ch, value] : mp){
	    cout << ch << ": " << value << "\n";
	}

}
