#include "Graph.h"

int main(int argc, char** argv){
    string task;
    string dataInfo;

    task = argv[1];

    ifstream file;
    file.open(argv[2]);

    file >> dataInfo;
    int verticesQuantity = stoi(dataInfo);

    file >> dataInfo;
    int edgesQuantity = stoi(dataInfo);
  
    Graph Graph(verticesQuantity+1,edgesQuantity);

    //Adiciona as arestas do arquivo no grafo
    for (int i = 0; i < edgesQuantity; i++){

        file >> dataInfo;
        int x = stoi(dataInfo);

        file >> dataInfo;
        int y = stoi(dataInfo);

        Graph.AddEdge(x+1, y+1);
    }

    if (task == "tarefa1"){
        Graph.minimalVertexCover();
        return 0;
    }

    if (task == "tarefa2"){
        Graph.aproxMinimalVertexCover();
        return 0;
    }

    cout << "Digite os parametros corretamente!" << endl;
    cout << "tarefa1 ou tarefa2 + caminho do arquivo txt" << endl;

    return 0;
}