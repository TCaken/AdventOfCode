 // 1. Define the Keypad
    // Note: We use a 2D array. grid[row][col]
    char keypad[5][5] = {
        {'#', '#', '1', '#', '#'},
        {'#', '2', '3', '4', '#'},
        {'5', '6', '7', '8', '9'},
        {'#', 'A', 'B', 'C', '#'},
        {'#', '#', 'D', '#', '#'}
    };

    // 2. Starting Position (Button '5' is at row 1, col 1)
    int row = 1, newRow = 1;
    int col = 1, newCol;

    string s;
    cout << "Paste your puzzle input below (Press Ctrl+D or Ctrl+Z to end):" << endl;

    // 3. Process Input Line by Line
    while (getline(cin, s)) {
        if (s.empty()) continue;

        // Process each character in the current line
        for (char direction : s) {
            newRow = row;
            newCol = col;
            switch (direction) {
                case 'U':
                    newRow = max(0, row - 1); // Move Up, but clamp at
                    break;
                case 'D':
                    newRow = min(4, row + 1); // Move Down, but clamp at 2
                    break;
                case 'L':
                    newCol = max(0, col - 1); // Move Left, but clamp at 0
                    break;
                case 'R':
                    newCol = min(4, col + 1); // Move Right, but clamp at 2
                    break;
            }
            
            if(keypad[newRow][newCol] != '#'){
                row = newRow;
                col = newCol;
            }
        }
        
        // 4. Output the digit found at the end of the line
        cout << keypad[row][col];
    }
    
    cout << endl;
    return 0;