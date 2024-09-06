#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <algorithm>
#include <functional>
#include <memory>
#include <string>
#include <chrono> // Include chrono library for timing

using namespace std;

// Define a point structure to represent coordinates on the puzzle
struct Point {
    int x, y;
    Point(int _x, int _y) : x(_x), y(_y) {}
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

// Define a state structure to represent the puzzle's current configuration
struct State {
    vector<vector<int>> board;
    Point empty; // Position of the empty tile (0)
    int g = 0;   // Cost from the start state
    int h = 0;   // Heuristic value
    string moves; // Sequence of moves made ('U', 'D', 'L', 'R')
    shared_ptr<State> parent = nullptr; // Pointer to the parent state using shared_ptr

    // Calculate an enhanced heuristic for the puzzle
    int calculateHeuristic(const vector<vector<int>>& goal) {
        int distance = 0;
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[i].size(); j++) {
                if (board[i][j] == 0) continue;
                // Find the goal position of the current tile
                for (int x = 0; x < goal.size(); x++) {
                    for (int y = 0; y < goal[x].size(); y++) {
                        if (goal[x][y] == board[i][j]) {
                            distance += abs(i - x) + abs(j - y);
                        }
                    }
                }
            }
        }
        return distance;
    }

    bool operator<(const State& other) const {
        return (g + h) > (other.g + other.h); // Min-heap based on f = g + h
    }
};

// Utility function to print the puzzle
void printBoard(const vector<vector<int>>& board) {
    for (const auto& row : board) {
        for (int tile : row) {
            cout << tile << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Function to convert the board to a string representation
string boardToString(const vector<vector<int>>& board) {
    string result;
    for (const auto& row : board) {
        for (int num : row) {
            result += to_string(num) + " ";
        }
    }
    return result;
}

// Function to get valid moves from the current empty position
vector<pair<Point, char>> getValidMoves(const Point& empty, int n) {
    vector<pair<Point, char>> moves;
    if (empty.x > 0) moves.push_back({Point(empty.x - 1, empty.y), 'D'}); // Up
    if (empty.x < n - 1) moves.push_back({Point(empty.x + 1, empty.y), 'U'}); // Down
    if (empty.y > 0) moves.push_back({Point(empty.x, empty.y - 1), 'R'}); // Left
    if (empty.y < n - 1) moves.push_back({Point(empty.x, empty.y + 1), 'L'}); // Right
    return moves;
}

// Function to reconstruct the path and print each step
void reconstructPath(shared_ptr<State> state) {
    vector<shared_ptr<State>> path;
    while (state) {
        path.push_back(state);
        state = state->parent;
    }
    reverse(path.begin(), path.end());
    for (auto step : path) {
        if (!step->moves.empty()) {
            cout << "Move: " << step->moves.back() << endl;
        }
        printBoard(step->board);
    }
}

// Function to perform A* search
pair<string, int> solveAStar(const vector<vector<int>>& start, const vector<vector<int>>& goal, const Point& empty) {
    priority_queue<State> open;
    unordered_map<string, shared_ptr<State>> closed;

    auto initial = make_shared<State>(State{start, empty, 0, 0, ""});
    initial->h = initial->calculateHeuristic(goal);
    open.push(*initial);
    closed[boardToString(initial->board)] = initial;

    // Start timing
    auto start_time = chrono::steady_clock::now();

    while (!open.empty()) {
        // Check elapsed time
        auto current_time = chrono::steady_clock::now();
        auto elapsed_seconds = chrono::duration_cast<chrono::seconds>(current_time - start_time).count();
        if (elapsed_seconds % 60 == 0 && elapsed_seconds != 0) {
            cout << "Loading... " << elapsed_seconds / 60 << " minute(s) passed." << endl;
            start_time = chrono::steady_clock::now(); // Reset the time to avoid repeated prints within the same minute
        }

        State current = open.top();
        open.pop();

        // Check if the current state matches the goal state
        if (current.board == goal) {
            reconstructPath(closed[boardToString(current.board)]);
            return {current.moves, current.g};
        }

        // Explore all valid moves
        for (const auto& [nextPos, move] : getValidMoves(current.empty, start.size())) {
            auto nextState = make_shared<State>(current);
            nextState->parent = closed[boardToString(current.board)]; // Link to parent
            swap(nextState->board[current.empty.x][current.empty.y], nextState->board[nextPos.x][nextPos.y]);
            nextState->empty = nextPos;
            nextState->g++;
            nextState->h = nextState->calculateHeuristic(goal);
            nextState->moves += move;

            string boardKey = boardToString(nextState->board);
            if (closed.find(boardKey) == closed.end() || closed[boardKey]->g > nextState->g) {
                closed[boardKey] = nextState;
                open.push(*nextState);
            }
        }
    }

    return {"", -1}; // No solution
}

int main() {
    int n;
    cout << "Enter puzzle size (n for an n x n puzzle): ";
    cin >> n;

    vector<vector<int>> start(n, vector<int>(n));
    vector<vector<int>> goal(n, vector<int>(n));

    cout << "Enter the initial stage of the puzzle - separating each number with a space - (0 represents the empty slot):\n";
    Point startEmpty(0, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> start[i][j];
            if (start[i][j] == 0) startEmpty = Point(i, j);
        }
    }

    cout << "Enter goal stage of the puzzle - separating each number with a space - :\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> goal[i][j];
        }
    }

    cout << "Using A* algorithm...\n";

    pair<string, int> result = solveAStar(start, goal, startEmpty);

    if (result.second != -1) {
        cout << "Steps to solve the puzzle: " << result.first << endl;
        cout << "Number of steps taken: " << result.second << endl;
    } else {
        cout << "No solution found.\n";
    }

    return 0;
}
