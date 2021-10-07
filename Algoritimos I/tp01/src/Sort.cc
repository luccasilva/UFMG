#include "Sort.h"

/* ---------------------------- */
/* ------- MERGE SORT 1 ------- */
/* ---------------------------- */

void merge(healthCenter *A, int Esq, int Meio, int Dir){
    int n1 = Meio - Esq + 1;
    int n2 = Dir - Meio;
    
    healthCenter *E;
    E = new healthCenter[n1];

    healthCenter *D;
    D = new healthCenter[n2];
 
    for (int i = 0; i < n1; i++)
        E[i] = A[Esq + i];
    for (int j = 0; j < n2; j++)
        D[j] = A[Meio + 1 + j];
 
    int i = 0;
    int j = 0;
    int k = Esq;
 
    while (i < n1 && j < n2) {
        if (E[i].getNumber() <= D[j].getNumber()) {
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
 
void mergeSortMethod(healthCenter *A,int Esq,int Dir) {
    if(Esq>=Dir){
        return;
    }
    int Meio = Esq+(Dir-Esq)/2;
    mergeSortMethod(A,Esq,Meio);
    mergeSortMethod(A,Meio+1,Dir);
    merge(A,Esq,Meio,Dir);
}

void mergeSort(healthCenter *A, int n) {
    mergeSortMethod(A, 0, n-1);
}

/* ---------------------------- */
/* ------- MERGE SORT 2 ------- */
/* ---------------------------- */

void merge2(person *A, int Esq, int Meio, int Dir){
    int n1 = Meio - Esq + 1;
    int n2 = Dir - Meio;
    
    person *E;
    E = new person[n1];

    person *D;
    D = new person[n2];
 
    for (int i = 0; i < n1; i++)
        E[i] = A[Esq + i];
    for (int j = 0; j < n2; j++)
        D[j] = A[Meio + 1 + j];
 
    int i = 0;
    int j = 0;
    int k = Esq;
 
    while (i < n1 && j < n2) {
        if (E[i].getAge() >= D[j].getAge()) {
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
 
void mergeSortMethod2(person *A,int Esq,int Dir) {
    if(Esq>=Dir){
        return;
    }
    int Meio = Esq+(Dir-Esq)/2;
    mergeSortMethod2(A,Esq,Meio);
    mergeSortMethod2(A,Meio+1,Dir);
    merge2(A,Esq,Meio,Dir);
}

void mergeSort2(person *A, int n) {
    mergeSortMethod2(A, 0, n-1);
}

/* ---------------------------- */
/* ------- QUICK SORT --------- */
/* ---------------------------- */

void Partition(int Esq, int Dir, int *i, int *j, healthCenter *A, person &P) {
    healthCenter x, w;
    *i = Esq; *j = Dir;
    x = A[(*i + *j)/2]; /* obtem o pivo x */
    do
    {
        while (x.getDistance(P) > A[*i].getDistance(P) || (x.getDistance(P) == A[*i].getDistance(P) && x.getNumber() > A[*i].getNumber())) (*i)++;
        while (x.getDistance(P) < A[*j].getDistance(P) || (x.getDistance(P) == A[*j].getDistance(P) && x.getNumber() < A[*j].getNumber())) (*j)--;
        if (*i <= *j)
        {
            w = A[*i]; A[*i] = A[*j]; A[*j] = w;
            (*i)++; (*j)--;
        }
    } while (*i <= *j);
}

void Order(int Esq, int Dir, healthCenter *A, person &P) { 
    int i;
    int j;
    Partition(Esq, Dir, &i, &j, A, P);
    if (Esq < j) Order(Esq, j, A, P);
    if (i < Dir) Order(i, Dir, A, P);
}

void quickSort(healthCenter *A, int n, person &P) {
    Order(0, n-1, A, P);
}