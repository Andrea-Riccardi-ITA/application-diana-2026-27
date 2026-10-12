#include <algorithm>
#include <climits>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#define MAP_FILE_NAME "map.txt"

void generateMap(int rows, int cols);
int findShortestPath(int rows, int cols);

int main() {
    int minDistance;
    int rows, cols;

    std::cout << "Test case 1" << std::endl;
    rows = 10;
    cols = 10;
    generateMap(rows, cols);
    minDistance = findShortestPath(rows, cols);
    std::cout << "Minimum traversal time: " << minDistance << std::endl << std::endl;

    std::cout << "Test case 2" << std::endl;
    rows = 20;
    cols = 5;
    generateMap(rows, cols);
    minDistance = findShortestPath(rows, cols);
    std::cout << "Minimum traversal time: " << minDistance << std::endl << std::endl;

    std::cout << "Test case 3" << std::endl;
    rows = 5;
    cols = 20;
    generateMap(rows, cols);
    minDistance = findShortestPath(rows, cols);
    std::cout << "Minimum traversal time: " << minDistance << std::endl << std::endl;

    std::cout << "Test case 4" << std::endl;
    rows = 20;
    cols = 1;
    generateMap(rows, cols);
    minDistance = findShortestPath(rows, cols);
    std::cout << "Minimum traversal time: " << minDistance << std::endl << std::endl;

    std::cout << "Test case 5" << std::endl;
    rows = 1;
    cols = 20;
    generateMap(rows, cols);
    minDistance = findShortestPath(rows, cols);
    std::cout << "Minimum traversal time: " << minDistance << std::endl << std::endl;

    std::cout << "Test case 6" << std::endl;
    rows = 100;
    cols = 100;
    generateMap(rows, cols);
    minDistance = findShortestPath(rows, cols);
    std::cout << "Minimum traversal time: " << minDistance << std::endl << std::endl;
}

int findShortestPath(int rows, int cols) {
    std::ifstream mapFile(MAP_FILE_NAME);
    if (!mapFile.is_open()) {
        std::cout << "Error reading map.txt file, check read privileges" << std::endl;
        return -1;
    }

    std::vector<std::vector<int>> grid(rows, std::vector<int>(cols));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (!(mapFile >> grid[i][j])) {
                std::cout << "Error reading map contents from map.txt" << std::endl;
                return -1;
            }
        }
    }

    std::vector<std::vector<int>> dp(rows, std::vector<int>(cols, INT_MAX));
    dp[0][0] = grid[0][0];

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (i == 0 && j == 0) {
                continue;
            }

            int bestFromAbove = (i > 0) ? dp[i - 1][j] : INT_MAX;
            int bestFromLeft = (j > 0) ? dp[i][j - 1] : INT_MAX;

            if (bestFromAbove == INT_MAX && bestFromLeft == INT_MAX) {
                continue;
            }

            int bestPrevious = std::min(bestFromAbove, bestFromLeft);
            dp[i][j] = bestPrevious + grid[i][j];
        }
    }

    std::vector<std::string> moves;
    int row = rows - 1;
    int col = cols - 1;

    while (row > 0 || col > 0) {
        if (row > 0 && dp[row][col] == dp[row - 1][col] + grid[row][col]) {
            moves.push_back("d");
            --row;
        }
        else {
            moves.push_back("r");
            --col;
        }
    }

    std::reverse(moves.begin(), moves.end());

    std::cout << "Move sequence: ";
    for (size_t i = 0; i < moves.size(); ++i) {
        if (i > 0) {
            std::cout << " ";
        }
        std::cout << moves[i];
    }
    std::cout << std::endl;

    return dp[rows - 1][cols - 1];
}

//generate random map
void generateMap(int rows, int cols) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 9);

    std::ofstream mapFile(MAP_FILE_NAME);

    if(!mapFile.is_open()) {
        std::cout << "Error writing map.txt file, check write privileges " << std::endl;
        std::exit(1);
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (i == 0 && j == 0) {
                mapFile << 0;
                continue;
            }

            if (j != 0) {
                mapFile << " ";
            }

            if (i != rows - 1 || j != cols - 1) {
                mapFile << dist(gen);
            }
            else {
                mapFile << 0;
            }
        }

        mapFile << std::endl;
    }
}