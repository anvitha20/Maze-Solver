#include <iostream>
#include <vector>

// Define the directions for moving in the maze (right, down, left, up)
const std::vector<std::pair<int, int>> directions = {
    {0, 1},  // Right
    {1, 0},  // Down
    {0, -1}, // Left
    {-1, 0}  // Up
};

// Function to print the maze
void printMaze(const std::vector<std::vector<int>>& maze) {
    for (const auto& row : maze) {
        for (int cell : row) {
            if (cell == -1) {
                std::cout << "* "; // Path
            } else {
                std::cout << cell << " ";
            }
        }
        std::cout << std::endl;
    }
}

// Function to check if a position is within the maze and not a wall
bool isValid(const std::vector<std::vector<int>>& maze, int x, int y) {
    return x >= 0 && x < maze.size() && y >= 0 && y < maze[0].size() && (maze[x][y] == 0 || maze[x][y] == 2);
}

// Depth-First Search to solve the maze
bool solveMaze(std::vector<std::vector<int>>& maze, int x, int y) {
    if (!isValid(maze, x, y)) return false;
    if (maze[x][y] == 2) {
        return true; // Reached the goal
    }

    // Mark the current cell as part of the path
    maze[x][y] = -1;

    for (const auto& dir : directions) {
        int newX = x + dir.first;
        int newY = y + dir.second;

        if (solveMaze(maze, newX, newY)) {
            return true;
        }
    }

    // Backtrack: unmark the cell if no solution was found
    maze[x][y] = 0;
    return false;
}

int main() {
    int rows, cols;
    std::cout << "Enter the number of rows and columns in the maze: ";
    std::cin >> rows >> cols;

    std::vector<std::vector<int>> maze(rows, std::vector<int>(cols));

    std::cout << "Enter the maze (0 for path, 1 for wall, 2 for goal):" << std::endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cin >> maze[i][j];
        }
    }

    int startX, startY;
    std::cout << "Enter the starting position (row and column): ";
    std::cin >> startX >> startY;

    // Validate starting position
    if (!isValid(maze, startX, startY) || maze[startX][startY] == 1) {
        std::cout << "Invalid starting position. No path to the goal exists.\n";
        return 0;
    }

    std::cout << "Maze before solving:\n";
    printMaze(maze);

    if (solveMaze(maze, startX, startY)) {
        std::cout << "Path to the goal found:\n";
    } else {
        std::cout << "No path to the goal exists.\n";
    }

    printMaze(maze);

    return 0;
}
