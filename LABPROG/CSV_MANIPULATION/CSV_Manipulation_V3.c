
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
    char row1[MAXCHAR];
    char row2[MAXCHAR];
    char *token1;
    char *token2;
    char **derivatives= NULL, **instruments = NULL;


    arquivo1 = fopen(argv[1],"r");
    arquivo2 = fopen(argv[2],"r");    
    
    if(argc < 2){
        printf("Utilização: ./csv_reader <nome do arquivo .csv>\n");
        exit(0);
    }

    if(arquivo1 == NULL || arquivo2 == NULL){
        printf("Não foi possível abrir um ou mais arquivos\n");        
        exit(0);
    }
    
    for (int i=0; i<8; i++)
    {
        fgets(row1, MAXCHAR, arquivo1);
        token1 = tokenize(row1, ";");

        do 
        {                        
            if (row1 != NULL)
            {
                for (int k=0; token1 != NULL; k++)
                {
                    derivatives = realloc(derivatives, sizeof(char *) * (k+1));
                    derivatives[k] = token1;
                    token1 = tokenize(NULL, ";");
                }
            }

            fgets(row2, MAXCHAR, arquivo2);
            
            if (row2 != NULL)
            {                
                token2 = tokenize(row2, ";");
                
                for (int j=0; token2 != NULL; j++)
                {
                    instruments = realloc(instruments, sizeof(char *) * (j+1));
                    instruments[j] = token2;
                    token2 = tokenize(NULL, ";");
                }
            }
        } while ((strcmp(derivatives[1], instruments[1])));

        printf("\nTckrSymb: %s", derivatives[1]);
        printf("\nCvrdQty: %s", derivatives[9]);
        printf("\nTtlBlckdPos: %s", derivatives[10]);
        printf("\nUcvrdQty: %s", derivatives[11]);

        printf("\nRptDt: %s", instruments[0]);
        printf("\nTckrSymb: %s", instruments[1]);
        printf("\nAsst: %s", instruments[2]);
        printf("\nXprtnDt: %s", instruments[7]);
        printf("\nExrcPric: %s", instruments[35]);
        printf("\nOptnStyle: %s", instruments[36]);

    } 
    
    /*
    while (feof(arquivo1) != true){
        
        //Arquivo 1 - Derivatives
        fgets(row1, MAXCHAR, arquivo1);
        //printf("\nRow: %s", row);

        //token = strtok(row, ";");        
        token1 = tokenize(row1, ";");


        //Ponteiro de ponteiros para armazenar os tokens
        //Com laço for, para percorrer o ponteiro de ponteiros e imprimir todos os tokens

        for (int i=0; token1 != NULL; i++)
        {
            derivatives = realloc(derivatives, sizeof(char *) * (i+1));
            derivatives[i] = token1;
            token1 = tokenize(NULL, ";");                       
        }
                
        /*
        printf("\nTckrSymb: %s", derivatives[1]);
        printf("\nCvrdQty: %s", derivatives[9]);
        printf("\nTtlBlckdPos: %s", derivatives[10]);
        printf("\nUcvrdQty: %s", derivatives[11]);
        */

    //}
    

   /*
   while (feof(arquivo2) != true)
    {
        fgets(row2, MAXCHAR, arquivo2);
        //printf("\nRow: %s", row);

        //token = strtok(row, ";");        
        token2 = tokenize(row2, ";");

        //Ponteiro de ponteiros para armazenar os tokens
        //Com laço for, para percorrer o ponteiro de ponteiros e imprimir todos os tokens

        for (int i=0; token2 != NULL; i++)
        {
            instruments = realloc(instruments, (i+1) * sizeof(char *) * (i+1));            
            instruments[i] = token2;
            token2 = tokenize(NULL, ";");            
        }
       
        /*
        printf("\nRptDt: %s", instruments[0]);
        printf("\nTckrSymb: %s", instruments[1]);
        printf("\nAsst: %s", instruments[2]);
        printf("\nXprtnDt: %s", instruments[7]);
        printf("\nExrcPric: %s", instruments[35]);
        printf("\nOptnStyle: %s", instruments[36]);
        */
    //}

    //Pergunta ao usuario se ele quer exibir as informacoes
    
    /*
    char resposta;
    printf("\nDeseja exibir as informações? (s/n): ");
    scanf("%c", &resposta);
    if (resposta == 's')
    {      

    }
    else if (resposta == 'n')
    {
        exit(0);
    }
    else
    {
        printf("\nResposta inválida. Digite 's' para sim ou 'n' para não.");        
    }   
    */

    printf("\nFim do arquivo\n");
    fclose(arquivo1);
    fclose(arquivo2);
    return 0;

}
