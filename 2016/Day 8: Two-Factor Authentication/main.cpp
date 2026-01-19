#include <iostream>
#include <vector>
#include <string>
#include <sstream>

const int WIDTH = 50;
const int HEIGHT = 6;

// Helper to print the screen
void printScreen(const std::vector<std::vector<bool>>& screen) {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            std::cout << (screen[y][x] ? '#' : '.');
        }
        std::cout << '\n';
    }
}

int main() {
    std::vector<std::vector<bool>> screen(HEIGHT, std::vector<bool>(WIDTH, false));
    std::string line;

    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string command;
        ss >> command; // Reads "rect" or "rotate"

        if (command == "rect") {
            std::string dimensions;
            ss >> dimensions; // Reads "3x2"
            
            size_t x_pos = dimensions.find('x');
            int A = std::stoi(dimensions.substr(0, x_pos));
            int B = std::stoi(dimensions.substr(x_pos + 1));

            for (int y = 0; y < B; ++y) {
                for (int x = 0; x < A; ++x) {
                    screen[y][x] = true;
                }
            }
        } 
        else if (command == "rotate") {
            std::string type, coord_str, by_keyword;
            int amount;

            // Input: "rotate column x=1 by 1"
            // Token 1: type       -> "column"
            // Token 2: coord_str  -> "x=1"
            // Token 3: by_keyword -> "by"
            // Token 4: amount     -> 1
            ss >> type >> coord_str >> by_keyword >> amount;
            
            // Parse "x=1" or "y=0" to get the number after '='
            size_t eq_pos = coord_str.find('=');
            int index = std::stoi(coord_str.substr(eq_pos + 1));

            if (type == "row") {
                std::vector<bool> new_row(WIDTH);
                for (int x = 0; x < WIDTH; ++x) {
                    new_row[(x + amount) % WIDTH] = screen[index][x];
                }
                screen[index] = new_row;
            } 
            else if (type == "column") {
                std::vector<bool> new_col(HEIGHT);
                for (int y = 0; y < HEIGHT; ++y) {
                    new_col[(y + amount) % HEIGHT] = screen[y][index];
                }
                for (int y = 0; y < HEIGHT; ++y) {
                    screen[y][index] = new_col[y];
                }
            }
        }
    }

    int lit_pixels = 0;
    for (const auto& row : screen) {
        for (bool pixel : row) {
            if (pixel) lit_pixels++;
        }
    }

    std::cout << "--- Final Screen ---" << std::endl;
    printScreen(screen);
    std::cout << "Answer: " << lit_pixels << std::endl;

    return 0;
}