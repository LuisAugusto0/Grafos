#include <iostream>
#include <limits>
#include <vector>
#include <queue>
#include <utility>  
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


    // Algoritmo de Dijkstra
    void dijkstra(int src) {
        vector<int> distance(vertices, numeric_limits<int>::max());
        distance[src] = 0;

        //Fila de prioridade organizada do menor para o maior, garantindo que sempre o menor peso é utilizado no pop
        priority_queue<pair<int, int>, vector<pair<int, int>>, CompareSecond> queue;
        queue.push({src, 0});

        //Enquanto a fila de execução for vazia
        while (!queue.empty()) {
            pair<int, int> actual = queue.top();
            queue.pop();
            
            Node<pair<int, int>>* node = adjList[actual.first].getBegin();
            while (node != nullptr) {
                int v = node->value->first;
                int weight = node->value->second;
                //Comparação para determinar o minimo e caso o caminho atual seja o menor, atualizar a distância 
                // e adicionar o vertice na fila de prioridade (o que remove a necessidade de um vetor de visitados)
                if(distance[actual.first] + weight < distance[v]){
                    distance[v] = distance[actual.first] + weight;
                    queue.push({v, distance[v]});
                }
                node = node->next;
            }
            cout << "Analized vertex " << actual.first << ". Current total weight - " << distance[actual.first] << endl;
        }

        // Exibe as distâncias mínimas
        cout << endl << "Distancias do vertice " << src << ":\n";
        for (int i = 0; i < vertices; i++) {
            cout << "Vertice " << i << ": " << distance[i] << endl;
        }
        cout << finalLine;
    }

    // Algoritmo de Min(max()) mas sem a modificação na fila de prioridade pois não há necessidade
    void minMax(int src, int target) {
        vector<int> maxV(vertices, numeric_limits<int>::max());
        maxV[src] = 0;
        pair<int, int> actual = {-1, -1};

        //Fila de prioridade organizada do menor para o maior
        priority_queue<pair<int, int>, vector<pair<int, int>>, CompareSecond> queue;
        queue.push({src, 0});

        //Enquanto o target não tiver sido atingido
        while (actual.first != target) {
            actual = queue.top();
            queue.pop();

            Node<pair<int, int>>* node = adjList[actual.first].getBegin();
            while (node != nullptr) {
                int v = node->value->first;
                int weight = node->value->second;
                //condição para saber se vértice já foi visitado, caso já foi, teoricamente não deveria ser necessário fazer a verificação de distãncia da aresta novamente (devido a fila de prioridade)
                maxV[v] = min(max(maxV[actual.first], weight), maxV[v]);
                queue.push({v, weight});
                node = node->next;
            }
            cout << endl << "Analized vertex " << actual.first << ". Current value - " << maxV[actual.first];
        }

        cout << endl << "Minmax do conjunto (src, target) (" << src << " - "<< target << ") = " << maxV[target] << finalLine;
    }

    // Algoritmo de Min(max()) mas sem a modificação na fila de prioridade pois não há necessidade
    void maxMin(int src, int target) {
        vector<int> minV(vertices, numeric_limits<int>::min());
        minV[src] = numeric_limits<int>::max();
        pair<int, int> actual = {-1, -1};

        //Fila de prioridade organizada do maior para o menor (para garantir o máximo sempre)
        priority_queue<pair<int, int>, vector<pair<int, int>>, CompareSecondInverted> queue;
        queue.push({0, src});

        //Enquanto o target não tiver sido atingido
        while (actual.first != target) {
            actual = queue.top();
            queue.pop();

            Node<pair<int, int>>* node = adjList[actual.first].getBegin();
            while (node != nullptr) {
                int v = node->value->first;
                int weight = node->value->second;
                //condição para saber se vértice já foi visitado, caso já foi, teoricamente não deveria ser necessário fazer a verificação de distãncia da aresta novamente (devido a fila de prioridade)
                minV[v] = max(min(minV[actual.first], weight), minV[v]);
                queue.push({v, minV[v]});
                node = node->next;
            }

            cout << endl << "Analized vertex " << actual.first << ". Current value - " << minV[actual.first];
        }
        minV[src] = 0;

        cout << endl << "Maxmin do conjunto (src, target) (" << src << " - "<< target << ") : " << minV[target] << finalLine;
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
    g.minMax(0, 4);

    cout << "\nExecutando Maxmin a partir do vertice 0 ate o vertice 4:\n";
    g.maxMin(0, 4);

    return 0;
}