
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<locale.h>

#define MAXCHAR 3000

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
    //Declaração de variáveis
    FILE *arquivo1, *arquivo2, *arquivoNovo;    
    char row1[MAXCHAR];
    char row2[MAXCHAR];
    char *token1, *token2;
    char **derivatives = NULL, **instruments = NULL;
    char resposta;

    printf("Utilização: ./csv-reader <nome do arquivo de derivativos .csv> <nome do arquivo de instrumentos .csv>\n");

    //Abre os arquivos de entrada
    arquivo1 = fopen(argv[1],"r");
    arquivo2 = fopen(argv[2],"r");        
    
    //Encerra o programa caso não tenha sido informado os dois arquivos de entrada
    if(argc < 2){
        printf("Utilização: ./csv-reader <nome do arquivo de derivativos .csv> <nome do arquivo de instrumentos .csv>\n");
        exit(0);
    }
    
    //Encerra o programa caso não consiga abrir o(s) arquivo(s) de entrada(s)
    if(arquivo1 == NULL || arquivo2 == NULL){
        printf("Não foi possível abrir um ou mais arquivos\n");
        printf("Verifique se os arquivos existem e se o nome está correto\n");
        printf("Não esqueça de incluir a extensão do arquivo (.csv)\n");
        exit(0);
    }
               
    //Pergunta ao usuario se ele quer exibir as informacoes ou salvar em um arquivo            
    printf("\nDeseja exibir as informações ou prefere salvar em um arquivo .csv?\n");
    printf("Digite 'e' para exibir ou 's' para salvar: ");
    scanf("%c", &resposta);
    
    if (resposta == 'e')
    {      
        printf("\n=====Dados dos Derivativos=====\n\n");
        printf("| DataDoRelatório |  Codigo     | Ativo |   Vcto     | Strike | Tipo |  Coberto  |  Travado  |  Descob.  |\n");
    }
    else if (resposta == 's')
    {
        printf("\nCerto, então vou salvar as informações em um arquivo .csv\n");
        arquivoNovo = fopen("DerivativosComFiltro.csv", "w+");
        fprintf(arquivoNovo, "DataDoRelatório,Codigo,Ativo,Vcto,Strike,Tipo,Coberto,Travado,Descoberto\n");
    }       
    else
    {
        printf("\nResposta inválida. Digite 's' para salvar ou 'e' para exibir.\n");
        return main(argc, argv);
    }           
        
    //Laço para ler os arquivos de entrada linha por linha, até o final do arquivo    
    for (int i=0; feof(arquivo1) != true && feof(arquivo2) != true; i++)
    {                
        
        /*
        Libera a memória alocada para o ponteiro de ponteiros do arquivo 2 se ele não for nulo
        e atribui o valor NULL para ele, para que não seja possível acessar a memória liberada                
        */

        if (instruments != NULL)
        {            
            free(instruments);
            instruments = NULL;
        }

        //Lê a linha do arquivo 1
        fgets(row1, MAXCHAR, arquivo1);
        //Tokeniza a linha do arquivo 1 lida
        token1 = tokenize(row1, ";");
        
        //Pula a primeira linha do arquivo        
        if(i==0){
            continue;
        }

        do 
        {
            if (row1 != NULL)
            {                
                //Ponteiro de ponteiros para os tokens do arquivo 1
                //Com laço for, para percorrer o ponteiro de ponteiros e imprimir todos os tokens
                for (int k=0; token1 != NULL; k++)
                {                                        
                    derivatives = realloc(derivatives, sizeof(char *) * (k+1));
                    derivatives[k] = token1;
                    token1 = tokenize(NULL, ";");
                }
            }

            if (row1 == NULL)
            {
                printf("\nFim do arquivo 1\n");
            }

            //Lê a linha do arquivo 2
            fgets(row2, MAXCHAR, arquivo2);
            //Tokeniza a linha do arquivo 2 lida
            token2 = tokenize(row2, ";");

            if (row2 != NULL)
            {                                                
                //Ponteiro de ponteiros para os tokens do arquivo 2
                //Com laço for, para percorrer o ponteiro de ponteiros e imprimir todos os tokens
                for (int j=0; token2 != NULL; j++)
                {
                    instruments = realloc(instruments, sizeof(char *) * (j+1));
                    instruments[j] = token2;
                    token2 = tokenize(NULL, ";");
                }
            }        
        //Compara o TckrSymb do arquivo 1 com o TckrSymb do arquivo 2      
        } while ((strcmp(derivatives[1], instruments[1])));
        
        //Converte um valor decimal para o formato americano (ponto ao invés de vírgula)
        
        char *ponto = strchr(instruments[35], ',');
        
        if ( ponto != NULL)
        {
            *ponto = '.';
        }
        
        /*
        Imprime os dados dos derivativos
        Na seguinte ordem:
        RptDt, TckrSymb,  Asst,  XprtnDt,  ExrcPric, OptnStyle,  CvrdQty,  TtlBlckdPos,  UcvrdQty
        
        Em português:
        DataDoRelatório, Codigo, Ativo, Vcto, Strike, Tipo, Coberto, Travado, Descoberto
        */

        if (resposta == 'e')
        {
            printf("| %-15s ", derivatives[0]);
            printf("|  %-10s | %4s | %-10s ", derivatives[1], instruments[2], instruments[7]); 
            printf("| %6s | %4s ", instruments[35], instruments[36]);
            printf("| %9s | %9s | %9s |\n", derivatives[9], derivatives[10], derivatives[11]);       
        }
        
        //Salva os dados dos derivativos em um arquivo .csv           
        if (resposta == 's')
        {
            fprintf(arquivoNovo, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n", derivatives[0], derivatives[1], instruments[2], instruments[7], instruments[35], instruments[36], derivatives[9], derivatives[10], derivatives[11]);
        }
        
        //Libera a memória alocada para o ponteiro de ponteiros do arquivo 1
        free(derivatives);

    //Fim do laço for
    }
    
    //Libera a memória alocada para o ponteiro de ponteiros do arquivo 2
    free(instruments);

    if (resposta == 'e'){
        printf("\nFim do arquivo\n");        
    }
    else if (resposta == 's'){
        printf("\nArquivo salvo com sucesso!\n");
    }
    
    //Fecha os arquivos de entrada
    fclose(arquivo1);
    fclose(arquivo2);
    fclose(arquivoNovo);
    return 0;
}
