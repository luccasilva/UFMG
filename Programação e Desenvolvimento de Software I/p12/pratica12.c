#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_TAM 5

int main()
{
	int countBuffer = 0;
	int counttotal = 0;
	char buffer[BUFFER_TAM];
	char c;
	char *texto = NULL/ (char *)malloc(sizeof(char));
	char *textoaux;
	int i,j;

	do
	{
		c = getchar();
		counttotal++;


		if(countBuffer < 5)
		{
			buffer[countBuffer] = c;
			countBuffer++;
		}
		if(countBuffer == 5 || c == '#')
		{
			textoaux = (char*)malloc(counttotal*sizeof(char));

			for(i=0; i<counttotal-countBuffer; i++)
			{
				textoaux[i] = texto[i];
			}

			for(j=i; j<counttotal;j++)
			{
				textoaux[j] = buffer[j + countBuffer - counttotal];
			}
			free(texto);
			texto = textoaux;
			countBuffer=0;

		}
	} while(c!= '#');

	texto[counttotal-1] = '\0';
	printf("\n\n%s\n\n", texto);
	free(textoaux);
}
