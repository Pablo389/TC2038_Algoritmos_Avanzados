#include <iostream>
#include <list>
#include <stack>
#include <queue>


using namespace std;

class Graph{
    private:
        int V; //Number of vertices
        list<int> *adj; //Adj list
    
    public:
        Graph(int V);
        void addEdge(int v, int w);
        void DFS(int S); //Search key
        void BFS(int S);
};

Graph::Graph(int V){
    this -> V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w){
    adj[v].push_back(w);
}

void Graph::DFS(int s){
    bool *visited = new bool[V];

    for (int i = 0; i < V; i++){
        visited[i] = false;
    }

    //Create stack
    stack<int> stack;
    stack.push(s);

    while (!stack.empty()){
        s = stack.top();
        stack.pop();

        if (!visited[s]){
            cout << s << " ";
            visited[s] = true;
        }

        for(list <int>::iterator i = adj[s].begin(); i != adj[s].end(); i++){
            if (!visited[*i]){
                stack.push(*i);
            }
        }
    }
}

void Graph::BFS(int s){         //Breath First Search complejidad O(V + E)
    queue <int> queue;
    bool *visited = new bool[V];

    for (int i = 0; i < V; i++){        //Poner todos los vertices en visited false
        visited[i] = false;
    }

    queue.push(s);          //Agregar el nodo inicial de búsqueda
    while (!queue.empty()){
        s = queue.front();
        queue.pop();

        if (!visited[s]){           //Se marca como visitado el nodo que estamos visitando
            cout << s << " ";
            visited[s] = true;
            for (list <int>::iterator i = adj[s].begin(); i != adj[s].end(); i++){          //Se agregan todas las conexiones del nodo mientras no esten visitados
                if (!visited[*i]){
                    queue.push(*i);
                }
            }
        }
    }
}

int main(){
    Graph g(11);
    g.addEdge(0,1);
    g.addEdge(0,2);
    g.addEdge(0,3);
    g.addEdge(1,5);
    g.addEdge(2,4);
    g.addEdge(4,5);
    g.addEdge(3,7);
    g.addEdge(7,8);
    g.addEdge(8,9);
    g.addEdge(8,10);

    g.DFS(0);
    cout << endl;
    g.BFS(0);

    return 0;
}