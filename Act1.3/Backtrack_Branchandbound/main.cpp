#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Función para imprimir la solución
void printSolution(const vector<vector<int>>& solution) {
    for (const auto& row : solution) {
        for (int cell : row) {
            cout << cell << " ";
        }
        cout << endl;
    }
}

// Función para verificar si la posición (x, y) es válida y no es una pared
bool isSafe(int x, int y, const vector<vector<int>>& maze, const vector<vector<int>>& solution, int M, int N) {
    return (x >= 0 && x < M && y >= 0 && y < N && maze[x][y] == 1 && solution[x][y] == 0);
}

// Backtracking para resolver el laberinto
bool solveMazeBacktracking(int x, int y, const vector<vector<int>>& maze, vector<vector<int>>& solution, int M, int N) {
    if (x == M - 1 && y == N - 1 && maze[x][y] == 1) {
        solution[x][y] = 1;
        return true;
    }
    
    if (isSafe(x, y, maze, solution, M, N)) {
        solution[x][y] = 1;

        // Mover hacia abajo
        if (solveMazeBacktracking(x + 1, y, maze, solution, M, N)) return true;

        // Mover hacia la derecha
        if (solveMazeBacktracking(x, y + 1, maze, solution, M, N)) return true;

        // Si ninguna opción es válida, retrocede
        solution[x][y] = 0;
    }
    
    return false;
}

// Ramificación y poda para resolver el laberinto
bool solveMazeBranchAndBound(const vector<vector<int>>& maze, vector<vector<int>>& solution, int M, int N) {
    queue<pair<int, int>> q;
    q.push({0, 0});
    solution[0][0] = 1;
    
    int dx[] = {1, 0}; // Posibles movimientos: abajo, derecha
    int dy[] = {0, 1};
    
    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        
        if (x == M - 1 && y == N - 1) {
            return true;
        }
        
        // Expandir los nodos (ramificar)
        for (int i = 0; i < 2; ++i) {
            int newX = x + dx[i];
            int newY = y + dy[i];
            
            if (isSafe(newX, newY, maze, solution, M, N)) {
                solution[newX][newY] = 1;
                q.push({newX, newY});
            }
        }
    }
    
    return false;
}

int main() {
    int M, N;
    cin >> M >> N;

    vector<vector<int>> maze(M, vector<int>(N));
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> maze[i][j];
        }
    }

    vector<vector<int>> solutionBacktracking(M, vector<int>(N, 0));
    vector<vector<int>> solutionBranchAndBound(M, vector<int>(N, 0));

    // Resolver con Backtracking
    cout << "Solución con Backtracking:" << endl;
    if (solveMazeBacktracking(0, 0, maze, solutionBacktracking, M, N)) {
        printSolution(solutionBacktracking);
    } else {
        cout << "No hay solución usando Backtracking." << endl;
    }

    // Resolver con Ramificación y Poda
    cout << "Solución con Ramificación y Poda:" << endl;
    if (solveMazeBranchAndBound(maze, solutionBranchAndBound, M, N)) {
        printSolution(solutionBranchAndBound);
    } else {
        cout << "No hay solución usando Ramificación y Poda." << endl;
    }

    return 0;
}
