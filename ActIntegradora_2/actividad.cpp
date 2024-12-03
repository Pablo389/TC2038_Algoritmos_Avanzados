#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <climits>
#include <algorithm>

#define INF 1000000

using namespace std;

//Algoritmo de Prim para calcular el minimun spanning tree (MST) la ruta que recorre todo el grafo de la manera más corta
void calcularMSTPrim(int N, const vector<vector<int > >& matrizDistancias, vector<int>& padre) {
    vector<bool> enMST(N, false);

    vector<int> llave(N, INT_MAX);

    llave[0] = 0;
    padre[0] = -1;

    for (int count = 0; count < N - 1; ++count) {
        int min = INT_MAX, u;

        for (int v = 0; v < N; ++v) {
            if (!enMST[v] && llave[v] < min) {
                min = llave[v];
                u = v;
            }
        }

        enMST[u] = true;

        for (int v = 0; v < N; ++v) {
            if (matrizDistancias[u][v] && !enMST[v] && matrizDistancias[u][v] < llave[v]) {
                padre[v] = u;
                llave[v] = matrizDistancias[u][v];
            }
        }
    }
}

void mostrarMST(int N, const vector<int>& padre) {
    cout << "1. Forma de cablear las colonias con fibra óptica:\n";
    for (int i = 1; i < N; ++i) {
        char origen = 'A' + padre[i];
        char destino = 'A' + i;
        cout << "(" << origen << "," << destino << ")\n";
    }
}

//Backtracking para hacer por brut force el recorrido de la ruta más corta
void tspBacktracking(int N, const vector<vector<int > >& matrizDistancias) {
    vector<int> ciudades(N - 1);
    for (int i = 1; i < N; ++i) {
        ciudades[i - 1] = i;
    }
    int costoMinimo = INT_MAX;
    vector<int> mejorRuta;

    do {
        int costoActual = 0;
        int k = 0;
        for (int i = 0; i < ciudades.size(); ++i) {
            int ciudadActual = ciudades[i];
            if (matrizDistancias[k][ciudadActual] == 0) {
                costoActual = INT_MAX;
                break;
            }
            costoActual += matrizDistancias[k][ciudadActual];
            k = ciudadActual;
        } if (matrizDistancias[k][0] == 0) {
            costoActual = INT_MAX;
        } else {
            costoActual += matrizDistancias[k][0];
        } if (costoActual < costoMinimo) {
            costoMinimo = costoActual;
            mejorRuta = ciudades;
        }
    } while (next_permutation(ciudades.begin(), ciudades.end()));

    cout << "\n2. Ruta a seguir por el personal que reparte correspondencia:\n";
    cout << "A";
    for (int ciudad : mejorRuta) {
        char c = 'A' + ciudad;
        cout << " >> " << c;
    }
    cout << " >> A\n";
    cout << "Costo total de la ruta: " << costoMinimo << "\n";
}

//BFS como auxiliar para el algoritmo de Edmonds-Karp
int bfs(int N, const vector<vector<int > >& grafoResidual, int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int> > q;
    q.push({s, INF});

    while (!q.empty()) {
        int u = q.front().first;
        int flujo = q.front().second;
        q.pop();

        for (int v = 0; v < N; ++v) {
            if (parent[v] == -1 && grafoResidual[u][v] > 0) {
                parent[v] = u;
                int nuevoFlujo = min(flujo, grafoResidual[u][v]);
                if (v == t)
                    return nuevoFlujo;
                q.push({v, nuevoFlujo});
            }
        }
    }
    return 0;
}

//Algoritmo de Edmons-Karp que hace lo contrario al de Prim, busca el camino más costoso que recorra todo el grafo
int edmondsKarp(int N, const vector<vector<int > >& capacidad, int s, int t) {
    int flujoMaximo = 0;
    vector<vector<int > > grafoResidual = capacidad;
    vector<int> parent(N);

    int nuevoFlujo;
    while ((nuevoFlujo = bfs(N, grafoResidual, s, t, parent)) != 0) {
        flujoMaximo += nuevoFlujo;
        int v = t;
        while (v != s) {
            int u = parent[v];
            grafoResidual[u][v] -= nuevoFlujo;
            grafoResidual[v][u] += nuevoFlujo;
            v = u;
        }
    }
    return flujoMaximo;
}

void imprimirMatriz(const vector<vector<int > >& matriz) {
    for (int i = 0; i < matriz.size(); ++i) {
        for (int j = 0; j < matriz[i].size(); ++j) {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
}

void leerArchivoEntrada(const string& nombreArchivo, int& N, vector<vector<int > >& matrizDistancias, vector<vector<int > >& matrizCapacidades) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo: " << nombreArchivo << endl;
        return;
    }

    archivo >> N;

    matrizDistancias.resize(N, vector<int>(N, 0));
    matrizCapacidades.resize(N, vector<int>(N, 0));

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            archivo >> matrizDistancias[i][j];
        }
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            archivo >> matrizCapacidades[i][j];
        }
    }

    archivo.close();
}

int main() {
    int N;
    vector<vector<int > > matrizDistancias;
    vector<vector<int > > matrizCapacidades;

    leerArchivoEntrada("ejemplo.txt", N, matrizDistancias, matrizCapacidades);
    imprimirMatriz(matrizDistancias);
    cout << endl;
    imprimirMatriz(matrizCapacidades);
    cout << endl;

    // Punto 1
    vector<int> padre(N);
    calcularMSTPrim(N, matrizDistancias, padre);
    mostrarMST(N, padre);

    // Punto 2
    tspBacktracking(N, matrizDistancias);

    // Punto 3
    int nodoInicial = 0;
    int nodoFinal = N - 1;
    int flujoMaximo = edmondsKarp(N, matrizCapacidades, nodoInicial, nodoFinal);
    cout << "\n3. Valor de flujo máximo de información del nodo inicial al nodo final:\n";
    cout << flujoMaximo << "\n";

    return 0;
}
