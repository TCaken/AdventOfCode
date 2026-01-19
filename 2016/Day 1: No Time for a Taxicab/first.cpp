#include <bits/stdc++.h>
using namespace std;

enum Orientation { N, E, S, W };

class Position {
private: 
    // Data is usually private in a class (hidden from outside)
    int x;
    int y;
    Orientation dir;
    set<pair<int,int>> visited;

public:
    // 1. CONSTRUCTOR: This runs automatically when you create the object
    Position(int startX, int startY, Orientation startDir) {
        x = startX;
        y = startY;
        dir = startDir;
        visited.insert({x, y});
    }

    // 2. METHOD: A function inside the class to display info
    void printInfo() {
        cout << "At (" << x << ", " << y << ") facing " << dir << endl;
    }
    
    void printManhattanDistance(){
        cout << "Manhattan Distance: "<< abs(x) + abs(y) << endl;
    }
    
    void turnLeft(){
        dir = static_cast<Orientation>((dir + 3) % 4);
    }
    
    void turnRight(){
        dir = static_cast<Orientation>((dir + 1) % 4);
    }
    
    void moveForward(int steps) {
        if (dir == N) y += steps;
        else if (dir == E) x += steps;
        else if (dir == S) y -= steps;
        else if (dir == W) x -= steps;
        
        visited.insert({x,y});
    }
    
    bool isVisited(){
        return visited.count({x,y});
    }
};

int main() {
	// your code goes here
    Position santa(0,0,N);
    string s;
    char dir;
    int start = 0, temp, steps, n;
    
    getline(cin, s);
    n = s.size();
    
    while(start < n){
        dir = s[start];
        temp = s.find(",", start);
        
        if(temp == -1){
            steps = stoi(s.substr(start+1));
        }else{
            steps = stoi(s.substr(start+1, temp-start));  
        }
        
        // cout << dir << " " << steps << endl;
        
        // cout << start << " " << temp << " " << steps << "\n";
        
        if(dir == 'R'){
            santa.turnRight();
        }
        else{
            santa.turnLeft();
        }
        
        for(int i = 0; i < steps; i++){
            santa.moveForward(1);
        }
    
        if(temp == -1){
            start = start + 2;
        }
        else{
            start = temp + 2;
        }
    }
    
    santa.printInfo();
    santa.printManhattanDistance();
    
    return 0;
}
