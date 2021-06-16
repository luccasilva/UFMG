#include <iostream>
#include <string>
#include <fstream>

#include <time.h>

#include "Planet.h"
#include "Stack.h"

void readFile(Planet *dataPlanet, std::ifstream &dataFile, int SIZE){
    std::string intermediate;
    std::string nameStr;
    int distanceInt;

    for (int aux = 0; aux < SIZE; aux++) {
        std::getline(dataFile, nameStr, ' ');
        std::getline(dataFile, intermediate);
        distanceInt = stoi(intermediate);
        dataPlanet[aux].name = nameStr;
        dataPlanet[aux].distance = distanceInt;
    }
    dataFile.close();
}

void printPlanets(Planet *dataPlanet){
    for (int i = 0; i < 7; i++){
        std::cout << dataPlanet[i].name << " " << dataPlanet[i].distance << std::endl;
    }
}

void deletePlanets(Planet *dataPlanet){
    delete dataPlanet;
}

/* ------- INSERTION SORT ------- */
void insertionSort(Planet *A, int n) {
    Planet aux;
    int j;
    for(int i=1; i<n; i++){
        aux = A[i];
        j = i-1;
        while(j>=0 && A[j].distance < aux.distance){
            A[j+1] = A[j];
            j--;
        }
        A[j+1] = aux;
    }
}

/* ------- MERGE SORT ------- */
void merge(Planet *A, int Esq, int Meio, int Dir){
    int n1 = Meio - Esq + 1;
    int n2 = Dir - Meio;
    
    Planet *E;
    E = new Planet[n1];

    Planet *D;
    D = new Planet[n2];
 
    for (int i = 0; i < n1; i++)
        E[i] = A[Esq + i];
    for (int j = 0; j < n2; j++)
        D[j] = A[Meio + 1 + j];
 
    int i = 0;
    int j = 0;
    int k = Esq;
 
    while (i < n1 && j < n2) {
        if (E[i].distance >= D[j].distance) {
            A[k] = E[i];
            i++;
        }
        else {
            A[k] = D[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        A[k] = E[i];
        i++;
        k++;
    }
    while (j < n2) {
        A[k] = D[j];
        j++;
        k++;
    }
}
 
void mergeSortMethod(Planet *A,int Esq,int Dir) {
    if(Esq>=Dir){
        return;
    }
    int Meio = Esq+(Dir-Esq)/2;
    mergeSortMethod(A,Esq,Meio);
    mergeSortMethod(A,Meio+1,Dir);
    merge(A,Esq,Meio,Dir);
}

void mergeSort(Planet *A, int n) {
    mergeSortMethod(A, 0, n-1);
}

/* ------- QUICK SORT ------- */
void Partition(int Esq, int Dir, int *i, int *j, Planet *A) {
    Planet x, w;
    *i = Esq; *j = Dir;
    x = A[(*i + *j)/2]; /* obtem o pivo x */
    do
    {
        while (x.distance < A[*i].distance) (*i)++;
        while (x.distance > A[*j].distance) (*j)--;
        if (*i <= *j)
        {
            w = A[*i]; A[*i] = A[*j]; A[*j] = w;
            (*i)++; (*j)--;
        }
    } while (*i <= *j);
}

void Order(int Esq, int Dir, Planet *A) { 
    int i;
    int j;
    Partition(Esq, Dir, &i, &j, A);
    if (Esq < j) Order(Esq, j, A);
    if (i < Dir) Order(i, Dir, A);
}

void quickSort(Planet *A, int n) {
    Order(0, n-1, A);
}

/* ------- QUICK SORT MODIFICADO ------- */
void notRecQuickSort(Planet *A, int n) {
    Stack pilha;
    Item item; //esq e dir
    int esq, dir, i, j;
    esq = 0;
    dir = n-1;
    item.dir = dir;
    item.esq = esq;
    pilha.pushStack(item);
    do
        if (dir > esq) {
            Partition(esq,dir,&i, &j,A);
            if ((j-esq)>(dir-i)) {
                item.dir = j;
                item.esq = esq;
                pilha.pushStack(item);
                esq = i;
        }
        else {
            item.esq = i;
            item.dir = dir;
            pilha.pushStack(item);
            dir = j;
            }
        }
        else {
            item = pilha.popStack();
            dir = item.dir;
            esq = item.esq;
    } while (pilha.getSize());
}

/* ------- SHELL SORT ------- */
void shellSort(Planet *A, int n) {
    int i, j, h;
    Planet aux;
    for(h = 1; h < n; h = 3*h+1);
    while(h > 0) {
        h = (h-1)/3;
        for(i = h; i < n; i++) {
            aux = A[i];
            j = i;
            while(A[j - h].distance < aux.distance) {
                A[j] = A[j - h];
                j -= h;
                if(j < h) break;
            }
            A[j] = aux;
        }
    }
}

int main(int argc, char const *argv[]) {
    std::ifstream dataFile(argv[1]);
    std::string size = argv[2];
    int SIZE = stoi(size);
    
    Planet *dataPlanet;
    dataPlanet = new Planet[SIZE];

    readFile(dataPlanet,dataFile,SIZE);

    //insertionSort(dataPlanet,SIZE);
    //mergeSort(dataPlanet,SIZE);
    quickSort(dataPlanet,SIZE);
    //notRecQuickSort(dataPlanet,SIZE);
    //shellSort(dataPlanet,SIZE);
    
    printPlanets(dataPlanet);
    deletePlanets(dataPlanet);

    /*
    --------------------------------
    ESTRUTURA UTILIZADA PARA MEDIÇÂO
    --------------------------------

    std::string m = argv[3];
    clock_t t;
    t = clock();
    switch (stoi(m)){
    case 1:
        std::cout << "insertionSort" << std::endl;
        insertionSort(dataPlanet,SIZE);
        break;
    case 2:
        std::cout << "mergeSort" << std::endl;
        mergeSort(dataPlanet,SIZE);
        break;
    case 3:
        std::cout << "quickSort" << std::endl;
        quickSort(dataPlanet,SIZE);
        break;
    case 4:
        std::cout << "notRecQuickSort" << std::endl;
        notRecQuickSort(dataPlanet,SIZE);
        break;
    case 5:
        std::cout << "shellSort" << std::endl;
        shellSort(dataPlanet,SIZE);
        break;
    }
    t = (clock() - t)/(CLOCKS_PER_SEC/1000);
    std::cout << "o Tempo e de: " << t << " milisegundos"<< std::endl;
    */
    return 0;
}