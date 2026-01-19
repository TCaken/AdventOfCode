#include <bits/stdc++.h>
using namespace std;

int main() {
	// your code goes here
    string command, req1, req2;
    vector<vector<string>> commands;
    int step, n, i;
    unordered_map<char, int> mp;
    
    
    mp['a'] = 0; mp['b'] = 0; mp['c'] = 1; mp['d'] = 0;
    // mp['a'] = 317811; mp['b'] = 196418; mp['c'] = 196418; mp['d'] = 0;
    while(cin >> command){
        vector<string> tmp;
        tmp.push_back(command);
        

        if(command == "cpy"){
            cin >> req1 >> req2;
            tmp.push_back(req1);
            tmp.push_back(req2);
        }
        else if(command == "inc"){
            cin >> req1;
            tmp.push_back(req1);
        }
        else if(command == "dec"){
            cin >> req1;
            tmp.push_back(req1);
        }
        else if(command == "jnz"){
            cin >> req1 >> req2;
            tmp.push_back(req1);
            tmp.push_back(req2);
        }
        
        commands.push_back(tmp);
    }
    
    i = 0; n = commands.size();
    while(i < n){
        // for(auto com : commands[i]){
        //     cout << com << " ";
        // }
        // cout << "\n";
        
        if(commands[i][0] == "cpy"){
            if(mp.find(commands[i][1][0]) == mp.end()){
                step = stoi(commands[i][1]);
                mp[commands[i][2][0]] = step;
            }
            else{
                mp[commands[i][2][0]] = mp[commands[i][1][0]];
            }
            i++;
        }
        else if(commands[i][0] == "inc"){
            mp[commands[i][1][0]]++;
            i++;
        }
        else if(commands[i][0] == "dec"){
            mp[commands[i][1][0]]--;
            i++;
        }
        else if(commands[i][0] == "jnz"){
            if(mp.find(commands[i][1][0]) == mp.end()){
                step = stoi(commands[i][1]);
                 if(step != 0){
                    step = stoi(commands[i][2]);
                    i+= step;
                }
                else{
                    i++;
                }
            }
            else{
                if(mp[commands[i][1][0]] != 0){
                    step = stoi(commands[i][2]);
                    i+= step;
                }
                else{
                    i++;
                }
            }
        }
        
        // for(auto &[key, val]: mp){
        //     cout << key << " " << val << "\n";
        // }

    }
    
    for(auto &[key, val]: mp){
        cout << key << " " << val << "\n";
    }
    
    return mp['a'];
}