#include <stdlib.h>
#include <stdio.h>

void main()
{
    // Abre um arquivo TEXTO para LEITURA
    FILE *arq;
    arq = fopen("conjunto.txt", "rt");

    int *numeros;
    int nos;

    // Le o primeiro inteiro que se refere ao numero de nos
    fscanf(arq, "%d", &nos);

    // cria um vetor com o tamanho do numero de nos para armazenar os valores de cada nó
    numeros = malloc(sizeof(int) * nos);

    // armazena todos os valores dos nós no vetor
    int contador;
    for (contador = 0; contador < nos; contador++)
    {
        fscanf(arq, "%d", &numeros[contador]);
    }

    //aloca uma matriz quadrada cujo numero de linha é o numero de nós do conjunto
    int NUMERO_DE_LINHAS = nos;
    int NUMERO_DE_COLUNAS = nos;
    int **matriz;
    int i = 0;

    matriz = (int **)malloc(sizeof(int *) * NUMERO_DE_LINHAS);
    for (i = 0; i < NUMERO_DE_LINHAS; i++)
    {
        matriz[i] = (int *)malloc(sizeof(int) * NUMERO_DE_COLUNAS);
    }
    int l, j = 0;

    // zera a matriz
    for (l = 0; l < NUMERO_DE_LINHAS; l++)
    {
        for (j = 0; j < NUMERO_DE_COLUNAS; j++)
        {
            matriz[l][j] = 0;
        }
    }

    // trata cada par ordenado na matriz, indicando a relação direta com o valor 1, sendo a linha o valor de saída e a coluna o valor de origem
    int numero1, numero2;
    while (!feof(arq))
    {
        fscanf(arq, "%d", &numero1);
        fscanf(arq, "%d", &numero2);
        l = 0;
        j = 0;
        for (contador = 0; contador < nos; contador++)
        {
            if (numero1 == numeros[contador])
            {
                l = contador;
            }
        }
        for (contador = 0; contador < nos; contador++)
        {
            if (numero2 == numeros[contador])
            {
                j = contador;
            }
        }
        matriz[l][j] = 1;
    }
    fclose(arq);
    arq = fopen("resultado.txt", "w");

    //checa a propriedade reflexivo
    int reflexivo = 0;
    contador = 0;
    for (l = 0; l < NUMERO_DE_LINHAS; l++)
    {
        if (matriz[l][l] == 1)
        {
            contador++;
        }
    }
    if (contador == NUMERO_DE_LINHAS)
    {
        reflexivo = 1;
        fprintf(arq,"1. Reflexiva: V\n");
        contador = 0;
        for (l = 0; l < NUMERO_DE_LINHAS; l++)
        {
            if (matriz[l][l] == 1)
            {
                fprintf(arq,"(%d,%d); ", numeros[l], numeros[l]);
                contador++;
            }
        }
        fprintf(arq,"\n");
    }
    else
    {
        fprintf(arq,"1. Reflexiva: F\n");
        contador = 0;
        for (l = 0; l < NUMERO_DE_LINHAS; l++)
        {
            if (matriz[l][l] == 0)
            {
                fprintf(arq,"(%d,%d); ", numeros[l], numeros[l]);
                contador++;
            }
        }
        fprintf(arq,"\n");
    }

        //checa a propriedade irreflexivo
    int irreflexivo = 0;
    contador = 0;
    for (l = 0; l < NUMERO_DE_LINHAS; l++)
    {
        if (matriz[l][l] == 1)
        {
            contador++;
        }
    }
    if (contador == 0)
    {
        irreflexivo = 1;
        fprintf(arq,"2. Irreflexiva: V\n");
    }
    else
    {
        fprintf(arq,"1. Irreflexiva: F\n");
        contador = 0;
        for (l = 0; l < NUMERO_DE_LINHAS; l++)
        {
            if (matriz[l][l] == 1)
            {
                fprintf(arq,"(%d,%d); ", numeros[l], numeros[l]);
                contador++;
            }
        }
        fprintf(arq,"\n");
    }
    contador = 0;

    // checa a propriedade de simetria
    int simetria = 1;
    for (l = 0; l < NUMERO_DE_LINHAS; l++)
    {
        for (j = 0; j < NUMERO_DE_COLUNAS; j++)
        {
            if (matriz[l][j] == 1)
            {
                if (matriz[l][j] != matriz[j][l])
                {
                    simetria = 0;
                }
            }
        }
    }
    // checa a propriedade de antissimetria
    int antisimetria = 1;
    for (l = 0; l < NUMERO_DE_LINHAS; l++)
    {
        for (j = 0; j < NUMERO_DE_COLUNAS; j++)
        {
            if ((matriz[l][j] == 1) && (l != j))
            {
                if (matriz[l][j] == matriz[j][l])
                {
                    antisimetria = 0;
                }
            }
        }
    }

    // checa a propriedade de assimetria
    int assimetria = 1;
    for (l = 0; l < NUMERO_DE_LINHAS; l++)
    {
        for (j = 0; j < NUMERO_DE_COLUNAS; j++)
        {
            if (matriz[l][j] == 1)
            {
                if (matriz[l][j] == matriz[j][l])
                {
                    assimetria = 0;
                }
            }
        }
    }

    //caso simetrica
    fprintf(arq,"\n");
    if (simetria == 1)
    {
        fprintf(arq,"3. Simétrica: V\n");
    }
    else
    {
        fprintf(arq,"3. Simétrica: F\n");
        for (l = 0; l < NUMERO_DE_LINHAS; l++)
        {
            for (j = 0; j < NUMERO_DE_COLUNAS; j++)
            {
                if (matriz[l][j] == 1)
                {
                    if (matriz[l][j] != matriz[j][l])
                    {
                        fprintf(arq,"(%d,%d); ", numeros[j], numeros[l]);
                    }
                }
            }
        }
        fprintf(arq,"\n");
    }

    //caso antisimetrico

    if (antisimetria == 1)
    {
        fprintf(arq,"4. Anti-simétrica: V\n");
    }
    else
    {
        fprintf(arq,"4. Anti-simétrica: F\n");
        for (l = 0; l < NUMERO_DE_LINHAS; l++)
        {
            for (j = 0; j < NUMERO_DE_COLUNAS; j++)
            {
                if ((matriz[l][j] == 1) && (l > j))
                {
                    if (matriz[l][j] == matriz[j][l])
                    {
                        fprintf(arq,"(%d,%d) e (%d,%d); ", numeros[l], numeros[j], numeros[j], numeros[l]);
                    }
                }
            }
        }
    }

    fprintf(arq,"\n");
    if (assimetria == 1)
    {
        fprintf(arq,"5. Assimétrica: V\n");
    }
    else
    {
        fprintf(arq,"5. Assimétrica: F\n");
    }

    // checa a propriedade de transição
    int transitiva = 1;
    int relacoes = 0;
    int z;
    for (l = 0; l < NUMERO_DE_LINHAS; l++)
    {
        for (j = 0; j < NUMERO_DE_COLUNAS; j++)
        {
            for (z = 0; z < NUMERO_DE_COLUNAS; z++)
            {
                if (matriz[l][j] == 1 && matriz[j][z] == 1)
                {
                    if (matriz[l][z] != 1)
                    {
                        transitiva = 0;
                    }
                }
            }
        }
    }

    if (transitiva == 1)
    {
        fprintf(arq,"6. Transitiva: V\n");
    }

    else
    {
        fprintf(arq,"6. Transitiva: F\n");
        for (l = 0; l < NUMERO_DE_LINHAS; l++)
        {
            for (j = 0; j < NUMERO_DE_COLUNAS; j++)
            {
                for (z = 0; z < NUMERO_DE_COLUNAS; z++)
                {
                    if (matriz[l][j] == 1 && matriz[j][z] == 1)
                    {
                        if (matriz[l][z] != 1)
                        {
                            fprintf(arq,"(%d,%d); ", numeros[l], numeros[z]);
                        }
                    }
                }
            }
        }
    }

    // checa se é uma relação de equivalencia
    if (reflexivo == 1 && simetria == 1 && transitiva == 1)
    {
        fprintf(arq,"\nRelação de equivalência: V\n");
    }
    else
    {
        fprintf(arq,"\nRelação de equivalência: F\n");
    }

    // checa se é uma relação de ordem parcial
    if (reflexivo == 1 && antisimetria == 1 && transitiva == 1)
    {
        fprintf(arq,"Relação de ordem parcial: V\n");
    }
    else
    {
        fprintf(arq,"Relação de ordem parcial: F\n");
    }

    fprintf(arq,"\nFecho transitivo da relação: \n");
    //seta as relações nao transitivas
    for (l = 0; l < NUMERO_DE_LINHAS; l++)
    {
        for (j = 0; j < NUMERO_DE_COLUNAS; j++)
        {
            for (z = 0; z < NUMERO_DE_COLUNAS; z++)
            {
                if (matriz[l][j] == 1 && matriz[j][z] == 1)
                {
                    matriz[l][z] = 1;
                }
            }
        }
    }
    // printa o feixo transitivo
    fprintf(arq,"{");
    for (l = 0; l < NUMERO_DE_LINHAS; l++)
    {
        for (j = 0; j < NUMERO_DE_COLUNAS; j++)
        {
            if (matriz[l][j] == 1)
            {
                fprintf(arq,"(%d,%d), ", numeros[l], numeros[j]);
            }
        }
    }
    fprintf(arq,"}");
    fclose(arq);
}