#include <bits/stdc++.h>
using namespace std;

enum Orientation { N, E, S, W };

class Position {
private: 
    int x;
    int y;
    Orientation dir;
    set<pair<int,int>> visited;

public:
    Position(int startX, int startY, Orientation startDir) {
        x = startX;
        y = startY;
        dir = startDir;
        visited.insert({x, y});
    }

    void printInfo() {
        cout << "First location visited twice: (" << x << ", " << y << ")" << endl;
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
    
    // MODIFIED: Returns TRUE if we hit a visited spot, FALSE otherwise
    bool moveOneStep() {
        // 1. Update coordinates
        if (dir == N) y++;
        else if (dir == E) x++;
        else if (dir == S) y--;
        else if (dir == W) x--;
        
        // 2. CHECK FIRST (Before inserting!)
        if (visited.count({x, y})) {
            return true; // Collision found!
        }

        // 3. INSERT SECOND
        visited.insert({x,y});
        return false;
    }
};

int main() {
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
        
        if(dir == 'R'){
            santa.turnRight();
        }
        else{
            santa.turnLeft();
        }
        
        // --- LOOP FIX ---
        for(int i = 0; i < steps; i++){
            // We call the function that moves AND checks
            if (santa.moveOneStep()) {
                santa.printInfo();
                santa.printManhattanDistance();
                return 0; // CRITICAL: Stop the whole program immediately!
            }
        }
    
        if(temp == -1){
            start = start + 2;
        }
        else{
            start = temp + 2;
        }
    }
    
    cout << "No location visited twice found." << endl;
    return 0;
}