
#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include<stdbool.h>

#define MAXCHAR 1000

/*
Tokeniza uma string, separando-a em tokens, de acordo com o delimitador, passado como parâmetro
Aceita valores vazios entre delimitadores, como em "a;;b"
*/
char *tokenize(char *input, char const *delim) {
    static char *current;
    char *pos, *ret;
    
    if (input != NULL)
        current = input;

    if (current == NULL)
        return current;

    ret = current;
    pos = strpbrk(current, delim);
    
    if (pos == NULL) 
        current = NULL;
    else {
        *pos = '\0';
        current = pos+1;
    }
    return ret;
}

int main(int argc, char **argv){

    FILE *arquivo1;
    FILE *arquivo2;
    char row[MAXCHAR];
    char *token;
    char **derivatives = NULL, **instruments = NULL;   

    arquivo1 = fopen(argv[1],"r");
    arquivo2 = fopen(argv[2],"r");    
    
    if(argc < 2){
        printf("Utilização: ./csv_reader <nome do arquivo .csv>\n");
        exit(0);
    }

    if(arquivo1 == NULL)
    {
        printf("Não foi possível abrir o arquivo 1\n");
        // Encerra o programa
        return 1;
    }

    if(arquivo2 == NULL)
    {
        printf("Não foi possível abrir o arquivo 2\n");
        // Encerra o programa
        return 1;
    }

    while (feof(arquivo1) != true)
    {
        fgets(row, MAXCHAR, arquivo1);
        //printf("\nRow: %s", row);

        //token = strtok(row, ";");        
        token = tokenize(row, ";");


        //Ponteiro de ponteiros para armazenar os tokens
        //Com laço for, para percorrer o ponteiro de ponteiros e imprimir todos os tokens

        for (int i=0; token != NULL; i++)
        {
            derivatives = realloc(derivatives, (i+1) * sizeof(char *) * (i+1));            
            derivatives[i] = token;
            token = tokenize(NULL, ";");
            //printf("\nDerivatives: %s", derivatives[i]);
        }
      
            printf("\nTckrSymb: %s", derivatives[1]);
            printf("\nCvrdQty: %s", derivatives[9]);
            printf("\nTtlBlckdPos: %s", derivatives[10]);
            printf("\nUcvrdQty: %s", derivatives[11]);                        
    }

   while (feof(arquivo2) != true)
    {
        fgets(row, MAXCHAR, arquivo2);
        //printf("\nRow: %s", row);

        //token = strtok(row, ";");        
        token = tokenize(row, ";");

        //Ponteiro de ponteiros para armazenar os tokens
        //Com laço for, para percorrer o ponteiro de ponteiros e imprimir todos os tokens        
        for (int i=0; token != NULL; i++)
        {
            instruments = realloc(instruments, (i+1) * sizeof(char *) * (i+1));            
            instruments[i] = token;
            token = tokenize(NULL, ";");            
        }
        
        printf("\nRptDt: %s", instruments[0]);
        printf("\nTckrSymb: %s", instruments[1]);
        printf("\nAsst: %s", instruments[2]);
        printf("\nXprtnDt: %s", instruments[7]);
        printf("\nExrcPric: %s", instruments[35]);
        printf("\nOptnStyle: %s", instruments[36]);
    }
   
    printf("\nFim do arquivo\n");
    fclose(arquivo1);
    fclose(arquivo2);
    return 0;

}
