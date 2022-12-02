
#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include<stdbool.h>

#define MAXCHAR 1000

int main(int argc, char **argv){

    FILE *arquivo1;
    FILE *arquivo2;
    char row[MAXCHAR];
    char *token;
    char **token2 = NULL, **instruments = NULL;

    arquivo1 = fopen(argv[1],"r");
    arquivo2 = fopen(argv[2],"r");    
    
    if(argc < 2){
        printf("Utilização: ./csv_reader <nome do arquivo .csv>\n");
        exit(0);
    }

    if(arquivo1 == NULL)
    {
        printf("Não foi possível abrir o arquivo\n");
        // Encerra o programa
        return 1;
    }

    while (feof(arquivo1) != true)
    {
        fgets(row, MAXCHAR, arquivo1);
        printf("\nRow: %s", row);

        token = strtok(row, ";");

        if (token != NULL)
        {
            //Ponteiro de ponteiro
            for (int i = 0; token != NULL; i++)
            {
                token2 = realloc(token2, sizeof(char *) * (i + 1));
                token2[i] = token;
                token = strtok(NULL, ";");
                //printf("\nToken2: %s", token2[i]);
            }

            printf("\nRptDt: %s", token2[0]);
            printf("\nTckrSymb: %s", token2[1]);
            printf("\nAsst: %s", token2[2]);
        }


       /* while(token != NULL)
        {            
            printf("Token: %s\n", token);
            token = strtok(NULL, ";");
        }*/

    }    
    printf("\nFim do arquivo\n");

    return 0;

}
