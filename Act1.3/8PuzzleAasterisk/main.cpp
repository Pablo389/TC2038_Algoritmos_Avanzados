#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <cmath>
#include <algorithm>
#include <limits>

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
    Point empty;  // Position of the empty tile (0)
    int g = 0;    // Cost from the start state
    int h = 0;    // Heuristic value
    string moves; // Sequence of moves made ('U', 'D', 'L', 'R')
    State* parent = nullptr; // Pointer to the parent state

    // Calculate the Manhattan distance heuristic
    int calculateHeuristic(const vector<vector<int>>& goal) {
        int distance = 0;
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[i].size(); j++) {
                if (board[i][j] == 0) continue;
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
void reconstructPath(State* state) {
    stack<State*> path;
    while (state) {
        path.push(state);
        state = state->parent;
    }
    
    while (!path.empty()) {
        State* current = path.top();
        path.pop();
        if (!current->moves.empty()) {
            cout << "Move: " << current->moves.back() << endl;
        }
        printBoard(current->board);
    }
}

// Function to perform A* search
pair<string, int> solveAStar(const vector<vector<int>>& start, const vector<vector<int>>& goal, const Point& empty) {
    priority_queue<State> open;
    map<vector<vector<int>>, State*> closed;
    State* initial = new State{start, empty, 0, 0, ""};
    initial->h = initial->calculateHeuristic(goal);
    open.push(*initial);
    closed[start] = initial;

    while (!open.empty()) {
        State current = open.top();
        open.pop();

        if (current.board == goal) {
            reconstructPath(&current);
            return {current.moves, current.g};
        }

        for (const auto& [nextPos, move] : getValidMoves(current.empty, start.size())) {
            State* nextState = new State{current};
            nextState->parent = closed[current.board]; // Link to parent
            swap(nextState->board[current.empty.x][current.empty.y], nextState->board[nextPos.x][nextPos.y]);
            nextState->empty = nextPos;
            nextState->g++;
            nextState->h = nextState->calculateHeuristic(goal);
            nextState->moves += move;

            if (!closed.count(nextState->board)) {
                closed[nextState->board] = nextState;
                open.push(*nextState);
            }
        }
    }

    return {"", -1}; // No solution
}

int main() {
    int n;
    n = 3; // Size of the puzzle

    vector<vector<int>> start(n, vector<int>(n));
    vector<vector<int>> goal(n, vector<int>(n));

    cout << "Enter starting stage of the puzzle - separating each number with a space - (0 represents the empty slot):\n";
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

    cout << "Choose algorithm:\n1. A*\n2. Breadth-First Search (BFS)\n3. Dijkstra\n";
    int choice;
    cin >> choice;

    pair<string, int> result;
    switch (choice) {
        case 1:
            result = solveAStar(start, goal, startEmpty);
            break;
        default:
            cout << "Invalid choice. Only A* implemented for step printing.\n";
            return 0;
    }

    if (result.second != -1) {
        cout << "Steps to solve the puzzle: " << result.first << endl;
        cout << "Number of steps taken: " << result.second << endl;
    } else {
        cout << "No solution found.\n";
    }

    return 0;
}
