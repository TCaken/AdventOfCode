#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;
};

// --- Coordinate Compression Helpers ---
void compress_coords(vector<int> &coords) {
    sort(coords.begin(), coords.end());
    coords.erase(unique(coords.begin(), coords.end()), coords.end());
}

int get_id(const vector<int> &coords, int val) {
    return lower_bound(coords.begin(), coords.end(), val) - coords.begin();
}

pair<int, int> readCommand(string s) {
    int pos = s.find(',');
    if (pos == string::npos) return {0,0};
    return {stoi(s.substr(0, pos)), stoi(s.substr(pos+1))};
}

int main() {
    // Optimization for faster I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    vector<Point> raw_points;
    vector<int> Xs, Ys;

    // 1. Read Input
    while(getline(cin, s)) {
        if(s.empty()) continue;
        pair<int,int> p = readCommand(s);
        raw_points.push_back({p.first, p.second});
        
        // Critical Trick: We add x and x+1. 
        // This ensures we have a grid column for the wall (x) 
        // AND a grid column for the space immediately after it (x+1).
        Xs.push_back(p.first);
        Xs.push_back(p.first + 1);
        Ys.push_back(p.second);
        Ys.push_back(p.second + 1);
    }
    
    // --- FIX 1: Add Padding ---
    // This adds empty space around the entire coordinate system
    // so the flood fill can travel around the shape.
    if (!Xs.empty()) {
        Xs.push_back(*min_element(Xs.begin(), Xs.end()) - 1);
        Xs.push_back(*max_element(Xs.begin(), Xs.end()) + 1);
        Ys.push_back(*min_element(Ys.begin(), Ys.end()) - 1);
        Ys.push_back(*max_element(Ys.begin(), Ys.end()) + 1);
    }

    // 2. Compress Coordinates
    compress_coords(Xs);
    compress_coords(Ys);

    int W = Xs.size(); // Note: Grid width is actually W-1 intervals
    int H = Ys.size(); 
    
    // grid[y][x] stores:
    //  -1 if Outside
    //   0 if Inside/Wall (initially)
    vector<vector<int>> grid(H, vector<int>(W, 0));

    // 3. Paint the Polygon Boundaries
    int n = raw_points.size();
    for(int i = 0; i < n; i++) {
        Point p1 = raw_points[i];
        Point p2 = raw_points[(i+1) % n]; // Wrap around

        int x1 = get_id(Xs, p1.x), x2 = get_id(Xs, p2.x);
        int y1 = get_id(Ys, p1.y), y2 = get_id(Ys, p2.y);

        if (y1 == y2) { // Horizontal
            for(int k = min(x1, x2); k < max(x1, x2); k++) grid[y1][k] = 1; 
        } else { // Vertical
             for(int k = min(y1, y2); k < max(y1, y2); k++) grid[k][x1] = 1;
        }
    }

    // 4. Flood Fill to mark "Outside" as -1
    // Safe to start at 0,0 because of padding
    queue<pair<int,int>> q;
    q.push({0,0});
    grid[0][0] = -1; 
    
    int dx[] = {0,0,1,-1};
    int dy[] = {1,-1,0,0};
    
    while(!q.empty()){
        auto [cx, cy] = q.front(); q.pop();
        for(int i=0; i<4; i++){
            int nx = cx + dx[i];
            int ny = cy + dy[i];
            // Check bounds (W-1, H-1 because cells are intervals between coords)
            if(nx >= 0 && nx < W-1 && ny >= 0 && ny < H-1 && grid[ny][nx] == 0) {
                grid[ny][nx] = -1; 
                q.push({nx, ny});
            }
        }
    }

    // 5. Build Weighted Prefix Sum
    // pref[y][x] stores the sum of VALID AREA up to that point
    vector<vector<long long>> pref(H, vector<long long>(W, 0));
    
    for(int y = 0; y < H-1; y++) {
        for(int x = 0; x < W-1; x++) {
            long long cell_area = 0;
            if (grid[y][x] != -1) { // If it's NOT outside
                // Calculate physical area of this compressed cell
                long long w = Xs[x+1] - Xs[x];
                long long h = Ys[y+1] - Ys[y];
                cell_area = w * h;
            }
            pref[y+1][x+1] = pref[y][x+1] + pref[y+1][x] - pref[y][x] + cell_area;
        }
    }

    // Helper to get sum of rectangle in O(1)
    auto get_sum = [&](int x1, int y1, int x2, int y2) {
        return pref[y2+1][x2+1] - pref[y1][x2+1] - pref[y2+1][x1] + pref[y1][x1];
    };

    // 6. Check all pairs of Red Tiles
    long long ans = 0;
    
    for(int i = 0; i < n; i++) {
        for(int j = i + 1; j < n; j++) {
            // Get compressed indices for the chosen points
            int r1_idx = get_id(Ys, raw_points[i].y);
            int c1_idx = get_id(Xs, raw_points[i].x);
            int r2_idx = get_id(Ys, raw_points[j].y);
            int c2_idx = get_id(Xs, raw_points[j].x);

            int r_min = min(r1_idx, r2_idx);
            int r_max = max(r1_idx, r2_idx);
            int c_min = min(c1_idx, c2_idx);
            int c_max = max(c1_idx, c2_idx);

            // Calculate the PHYSICAL Area we expect this rectangle to have
            long long real_width = abs(raw_points[i].x - raw_points[j].x) + 1;
            long long real_height = abs(raw_points[i].y - raw_points[j].y) + 1;
            long long required_area = real_width * real_height;

            // Get the Actual Valid Area from our grid
            // We query the prefix sum from (c_min, r_min) to (c_max, r_max)
            // Note: because grid coordinates are inclusive for points, we query up to the indices.
            long long valid_area = get_sum(c_min, r_min, c_max, r_max);

            if(valid_area == required_area) {
                ans = max(ans, required_area);
            }
        }
    }

    cout << "Final Result: " << ans << "\n";
    return 0;
}