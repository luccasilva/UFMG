#include "Graph.h"

int main() {
    std::string dataInfo;

    std::cin >> dataInfo;
    int verticesQuantity = std::stoi(dataInfo);

    std::cin >> dataInfo;
    int edgesQuantity = std::stoi(dataInfo);
  
    Graph Graph(verticesQuantity);

    // Adiciona as arestas do arquivo no grafo
    for (int i = 0; i < edgesQuantity; i++){

        std::cin >> dataInfo;
        int x = std::stoi(dataInfo);

        std::cin >> dataInfo;
        int y = std::stoi(dataInfo);

        Graph.Edge(x-1, y-1);
    }

    vector<int> StronglyConnectedComponents;

    Graph.Kosaraju(StronglyConnectedComponents);
    Graph.DAG(StronglyConnectedComponents);
    
    return 0;
}