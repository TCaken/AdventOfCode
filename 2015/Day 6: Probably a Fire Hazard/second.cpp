#include <bits/stdc++.h>
using namespace std;

void followCommand(vector<vector<int>>& lights, vector<string> command){
    int x1 = stoi(command[1]);
    int y1 = stoi(command[2]);
    int x2 = stoi(command[3]);
    int y2 = stoi(command[4]);
    
    if(command[0] == "turn off"){
        for(int i = x1; i <= x2; i++){
            for(int j = y1; j <= y2; j++){
                if(lights[i][j] > 0) lights[i][j] -= 1;
            }
        }
    }else if(command[0] == "turn on"){
        for(int i = x1; i <= x2; i++){
            for(int j = y1; j <= y2; j++){
                lights[i][j] += 1;
            }
        }
    }else{
        for(int i = x1; i <= x2; i++){
            for(int j = y1; j <= y2; j++){
                lights[i][j] += 2;
            }
        }
    }
    
}

vector<string> splitInput(string s){
    vector<string> ans;
    int pos, pos2, split, n = s.size(), m = 0;;
    string temp;
    
    if(s[6] == 'f'){ //Turn off
        ans.push_back("turn off");
        pos = 8;
    }else if(s[6] == 'n'){ // Turn on 
        ans.push_back("turn on");
        pos = 7;
    }else{ //Toggle
        ans.push_back("toggle");
        pos = 6;
    }
    
    //Split the coordination
    pos2 = s.find(' ', pos+1);
    temp = s.substr(pos+1, pos2-pos);
    
    // Split to (x,y)
    split = temp.find(',');
    m = temp.size();
    ans.push_back(temp.substr(0, split));
    ans.push_back(temp.substr(split+1, m-split-1));
    
    //Split the coordination
    temp = s.substr(pos2+9, n-pos2-8);
    
    // Split to (x,y)
    split = temp.find(',');
    m = temp.size();
    ans.push_back(temp.substr(0, split));
    ans.push_back(temp.substr(split+1, m-split-1));
    
    // for(auto ch : ans){
    //     cout << ch << "\n";
    // }
    
    return ans;
}

int getLights(vector<vector<int>>& lights){
    int ans = 0;
    for(auto row : lights){
        ans += accumulate(row.begin(), row.end(), 0);
    }
    
    return ans;
}

int main() {
    string s;
    int ans = 0;
    vector<vector<int>> lights (1000, vector<int>(1000, 0));
    vector<string> command;
    
    while(getline(cin, s)){
        command = splitInput(s);
        followCommand(lights, command);
    }
    
    cout << getLights(lights) << "\n";
    
}
