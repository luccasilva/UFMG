#include <iostream>
#include <iomanip>
#include <string>
#include "Estudante.hpp"

int main(void){
    
    std::cout << std::fixed;

    Estudante vetor[10];//Lista de estudantes
    for (int i = 0; i < 10; i++) {
        std::cin>>vetor[i].matricula;
        std::cin>>vetor[i].nome;

        for (size_t ii = 0; ii < 5; ii++)
        {
            std::cin >> vetor[i].notas[ii];
        }

    }

    float rsgs[10];
    for (size_t i = 0; i < 10; i++)
    {
        rsgs[i] = vetor[i].calcularRSG();
    }

        //Primeiro
        float maior = rsgs[0];
        int m = 0;
        Estudante aux;
        float auxx;

        for (size_t i = 0; i < 10; i++)
        {
            if (maior<rsgs[i])
            {
                maior=rsgs[i];
                m = i;
            }
        }
        for (size_t i = 0; i < 10; i++)
        {
            if ((maior==rsgs[i])&&(m!=i))
            {
                if (vetor[i].matricula<vetor[m].matricula)
                {
                    m = i;
                }
            }
        }
        
        if(m!=0){
            aux = vetor[0];
            vetor[0] = vetor[m];
            vetor[m] = aux;
            auxx = rsgs[0];
            rsgs[0] = rsgs[m];
            rsgs[m] = auxx;
        }

        //Segundo
        maior = rsgs[1];
        m = 1;

        for (size_t i = 1; i < 10; i++)
        {
            if (maior<rsgs[i])
            {
                maior=rsgs[i];
                m = i;
            }
        }
        for (size_t i = 1; i < 10; i++)
        {
            if ((maior==rsgs[i])&&(m!=i))
            {
                if (vetor[i].matricula<vetor[m].matricula)
                {
                    m = i;
                }
            }
        }
        
        if(m!=1){
            aux = vetor[1];
            vetor[1] = vetor[m];
            vetor[m] = aux;
            auxx = rsgs[1];
            rsgs[1] = rsgs[m];
            rsgs[m] = auxx;
        }

        //Terceiro
        maior = rsgs[2];
        m = 2;

        for (size_t i = 2; i < 10; i++)
        {
            if (maior<rsgs[i])
            {
                maior=rsgs[i];
                m = i;
            }
        }
        for (size_t i = 2; i < 10; i++)
        {
            if ((maior==rsgs[i])&&(m!=i))
            {
                if (vetor[i].matricula<vetor[m].matricula)
                {
                    m = i;
                }
            }
        }
        
        if(m!=2){
            aux = vetor[2];
            vetor[2] = vetor[m];
            vetor[m] = aux;
            auxx = rsgs[2];
            rsgs[2] = rsgs[m];
            rsgs[m] = auxx;
        }
        
    
        std::cout << vetor[0].matricula << " " << vetor[0].nome << " " << std::setprecision(2) << vetor[0].calcularRSG() << '\n';
        std::cout << vetor[1].matricula << " " << vetor[1].nome << " " << std::setprecision(2) << vetor[1].calcularRSG() << '\n';
        std::cout << vetor[2].matricula << " " << vetor[2].nome << " " << std::setprecision(2) << vetor[2].calcularRSG() << '\n';
     }
