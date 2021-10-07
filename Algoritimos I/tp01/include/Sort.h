#ifndef MERGE_H
#define MERGE_H

#include <string>
#include <iostream>
#include "HealthCenter.h"
#include "Person.h"

//Ordena por MergeSort os postos pelo ID
void merge(healthCenter *A, int Esq, int Meio, int Dir);
void mergeSortMethod(healthCenter *A,int Esq,int Dir);
void mergeSort(healthCenter *A, int n);

//Ordena por MergeSort as pessoas por idade
void merge2(person *A, int Esq, int Meio, int Dir);
void mergeSortMethod2(person *A,int Esq,int Dir);
void mergeSort2(person *A, int n);

//Ordena por QuickSort preferencia das pessoas por distancia dos postos
void Partition(int Esq, int Dir, int *i, int *j, healthCenter *A, person &P);
void Order(int Esq, int Dir, healthCenter *A, person &P);
void quickSort(healthCenter *A, int n, person &P);


#endif