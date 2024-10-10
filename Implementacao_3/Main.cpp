#include <iostream>
#include <limits>
#include <vector>
#include <queue>
#include <utility>  
#include <stack>
#include "LinkedList.hpp"

using namespace std;

//template para linha de separação
template<typename _String, typename _Traits>
inline std::basic_ostream<_String, _Traits>&
line(std::basic_ostream<_String, _Traits>& __os)
{
    const char* separator = "\n------------------------------------------------------------------------------------------------\n";
    while (*separator) {
        __os.put(__os.widen(*separator++));
    }
    return flush(__os);
}

//template para linha de separação
template<typename _String, typename _Traits>
inline std::basic_ostream<_String, _Traits>&
finalLine(std::basic_ostream<_String, _Traits>& __os)
{
    const char* separator = "\n-----------------------------------------------//-----------------------------------------------\n";
    while (*separator) {
        __os.put(__os.widen(*separator++));
    }
    return flush(__os);
}

// Comparadores para ordenar pelo segundo elemento do par
struct CompareSecond {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second;  // Ordena em ordem crescente pelo segundo elemento
    }
};
struct CompareSecondInverted {
    bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
        return a.second < b.second;  // Ordena em ordem decrescente pelo segundo elemento
    }
};

// Classe Grafo
class Graph {
private:
    int vertices;
    vector<LinkedList<pair<int, int>>> adjList;  // Lista de adjacência: (vértice destino, peso)

public:
    Graph(int V) : vertices(V), adjList(V) {}

    // Adiciona aresta de u para v com peso w
    void addEdge(int u, int v, int w) {
        adjList[u].push_back({v, w});
    }

    // Exibe o grafo
    void display() {
        cout << line << " Lista de adjacencia " << line;

        for (int i = 0; i < vertices; i++) {
            cout << "| Vertice " << i << ": ";
            Node<pair<int, int>>* node = adjList[i].getBegin();
            while (node != nullptr) {
                cout << "| (v: " << node->value->first << ", w: " << node->value->second << ") ";
                node = node->next;
            }
            cout << "|" << line;
        }
    }

    // Função para exibir o caminho a partir de um vetor de antecessores
    void showPath(int src, int dest, const vector<int>& parent) {
        if (parent[dest] == -1) {
            cout << "Nao ha caminho do vertice " << src << " para o vertice " << dest << ".\n";
            return;
        }

        stack<int> caminho;
        int atual = dest;

        // Reconstrói o caminho do destino até a origem
        while (atual != src) {
            caminho.push(atual);
            atual = parent[atual];
        }
        caminho.push(src);

        // Exibe o caminho reconstruído
        cout << "Caminho do vertice " << src << " ate o vertice " << dest << ": ";
        while (!caminho.empty()) {
            cout << caminho.top();
            caminho.pop();
            if (!caminho.empty()) cout << " -> ";
        }
        cout << endl;
    }

    // Função que executa o dijkstra a partir de um vértice inicial (src)
    void dijkstra(int src) {
        vector<int> distance(vertices, numeric_limits<int>::max());
        vector<int> parent(vertices, -1);
        distance[src] = 0;
        parent[src] = src;

        priority_queue<pair<int, int>, vector<pair<int, int>>, CompareSecond> queue;
        queue.push({src, 0});

        while (!queue.empty()) {
            pair<int, int> actual = queue.top();
            queue.pop();

            int u = actual.first;
            Node<pair<int, int>>* node = adjList[u].getBegin();
            while (node != nullptr) {
                int v = node->value->first;
                int weight = node->value->second;

                if (distance[u] + weight < distance[v]) {
                    distance[v] = distance[u] + weight;
                    parent[v] = u;
                    queue.push({v, distance[v]});
                }
                node = node->next;
            }
            cout << "Vertice analisado: " << u << ". Distancia atual: " << distance[u] << endl;
        }

        cout << endl << "Distancias a partir do vertice " << src << ":\n";
        for (int i = 0; i < vertices; i++) {
            cout << "Vertice " << i << ": " << distance[i] << endl;
            showPath(src, i, parent);
        }
        cout << finalLine;
    }

    // Algoritmo de Minmax para todos os vértices
    void minMax(int src) {
        vector<int> maxV(vertices, numeric_limits<int>::max());
        vector<int> parent(vertices, -1);
        maxV[src] = 0;
        parent[src] = src;

        priority_queue<pair<int, int>, vector<pair<int, int>>, CompareSecond> queue;
        queue.push({src, 0});

        while (!queue.empty()) {
            pair<int, int> actual = queue.top();
            queue.pop();

            int u = actual.first;
            Node<pair<int, int>>* node = adjList[u].getBegin();
            while (node != nullptr) {
                int v = node->value->first;
                int weight = node->value->second;

                int new_value = min(max(maxV[u], weight), maxV[v]);
                if (new_value < maxV[v]) {
                    maxV[v] = new_value;
                    parent[v] = u;
                    queue.push({v, maxV[v]});
                }
                node = node->next;
            }
            cout << "Vertice analisado: " << u << ". Valor atual de Minmax: " << maxV[u] << endl;
        }

        cout << endl << "Valores Minmax a partir do vertice " << src << ":\n";
        for (int i = 0; i < vertices; i++) {
            cout << "Vertice " << i << ": " << maxV[i] << endl;
            showPath(src, i, parent);
        }
        cout << finalLine;
    }

    // Algoritmo de Maxmin para todos os vértices
    void maxMin(int src) {
        vector<int> minV(vertices, numeric_limits<int>::min());
        vector<int> parent(vertices, -1);
        minV[src] = numeric_limits<int>::max();
        parent[src] = src;

        priority_queue<pair<int, int>, vector<pair<int, int>>, CompareSecondInverted> queue;
        queue.push({src, minV[src]});

        while (!queue.empty()) {
            pair<int, int> actual = queue.top();
            queue.pop();

            int u = actual.first;
            Node<pair<int, int>>* node = adjList[u].getBegin();
            while (node != nullptr) {
                int v = node->value->first;
                int weight = node->value->second;

                int new_value = max(min(minV[u], weight), minV[v]);
                if (new_value > minV[v]) {
                    minV[v] = new_value;
                    parent[v] = u;
                    queue.push({v, minV[v]});
                }
                node = node->next;
            }
            cout << "Vertice analisado: " << u << ". Valor atual de Maxmin: " << minV[u] << endl;
        }

        cout << endl << "Valores Maxmin a partir do vertice " << src << ":\n";
        for (int i = 0; i < vertices; i++) {
            cout << "Vertice " << i << ": " << minV[i] << endl;
            showPath(src, i, parent);
        }
        cout << finalLine;
    }


};

// Função principal (main)
int main() {
    Graph g(5);

    // Adiciona arestas (u, v, peso)
    g.addEdge(0, 1, 10);
    g.addEdge(0, 4, 5);
    g.addEdge(0, 3, 4);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 4, 2);
    g.addEdge(2, 3, 4);
    g.addEdge(3, 4, 3);
    g.addEdge(4, 2, 2);

    // Exibe o grafo
    g.display();

    // Executa o algoritmo de Dijkstra a partir do vértice 0
    cout << "\nExecutando Dijkstra a partir do vertice 0:\n";
    g.dijkstra(0);

    cout << "\nExecutando Minmax a partir do vertice 0 ate o vertice 4:\n";
    g.minMax(0);

    cout << "\nExecutando Maxmin a partir do vertice 0 ate o vertice 4:\n";
    g.maxMin(0);

    return 0;
}