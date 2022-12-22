
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>

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

//Função para imprimir o topo da tabela de exibição
void exibirTopoTabela()
{
    printf("\n=====Dados dos Derivativos=====\n\n");
    printf("| DataDoRelatório |  Codigo     | Ativo |   Vcto     | Strike | Tipo |  Coberto  |  Travado  |  Descob.  |\n");
}

//Função para interagir com o usuário e perguntar se ele quer filtrar os dados
char respostaFiltroDeDados()
{
    char respostaFiltro;
    printf("\nDeseja filtrar os dados?\n");
    printf("Digite 'a' para filtrar por ativo (Asst)\n");
    printf("Digite 'q' para filtrar por quantidade (Coberto, Travado ou Descoberto)(CvrdQty, TtlBlckPos ou UcvrdQty)\n");
    printf("Digite 'c' para filtro combinado (Asst e CvrdQty, TtlBlckPos ou UcvrdQty)\n");
    printf("Digite 'n' para não filtrar");
    printf("\nSelecione a opção desejada: ");
    scanf("%c", &respostaFiltro);        
    //Consome o caractere de nova linha
    getchar();
    
    if (respostaFiltro == 'n')
    {
        printf("\nCerto, então vou exibir todas as informações\n");
    }    
    else if (respostaFiltro == 'a')
    {
        printf("\nCerto, então vou exibir as informações filtradas por ativo (Asst)\n");        
    }
    else if (respostaFiltro == 'q')
    {
        printf("\nCerto, então vou exibir as informações filtradas por quantidade (Coberto, Travado ou Descoberto)\n");
    }
    else if (respostaFiltro == 'c')
    {
        printf("\nCerto, então vou exibir as informações filtradas por ativo e quantidade (Asst e CvrdQty, TtlBlckPos ou UcvrdQty)\n");
    }
    else
    {
        printf("\nOpção inválida, vou exibir todas as informações\n");
        respostaFiltro = 'n';
    }       
    return respostaFiltro;
}

//Função para perguntar ao usuário se ele quer exibir as informações ou salvar em um arquivo .csv
char respostaSalvarExibir()
{
    char resposta;
    printf("\nDeseja exibir as informações ou prefere salvar em um arquivo .csv?\n");
    printf("Digite 'e' para exibir ou 's' para salvar: ");
    scanf("%c", &resposta);
    //Consome o caractere de nova linha
    getchar();
    return resposta;
}


//Função para imprimir a tabela de exibição
void exibirTabela(char *derivatives[], char *instruments[])
{
    printf("| %-15s ", derivatives[0]);
    printf("|  %-10s | %4s | %-10s ", derivatives[1], instruments[2], instruments[7]); 
    printf("| %6s | %4s ", instruments[35], instruments[36]);
    printf("| %9s | %9s | %9s |\n", derivatives[9], derivatives[10], derivatives[11]);    
}

//Função para receber o filtro de ativo
char *filtroAtivo()
{
    static char respostaFiltroAsst[100];
    printf("Informe o ativo que deseja filtrar: ");
    scanf("%s", respostaFiltroAsst);            
    //Consome o caractere de nova linha
    getchar();
    return respostaFiltroAsst;
}

//Função para receber o filtro de quantidade
char *filtroQuantidade()
{
    static char respostaFiltroQuantidade[100];
    printf("Informe a quantidade que deseja filtrar: ");
    scanf("%s", respostaFiltroQuantidade);            
    //Consome o caractere de nova linha
    getchar();
    return respostaFiltroQuantidade;
}

//Função para o ponteiro do filtro selecionado
char *allocEcopyPonteiroFiltroSelecionado(char respostaFiltroSelecionado[], int tipoFiltro)
{    
    char *ponteiroFiltroAtivo;
    char *ponteiroFiltroQuantidade;
    
    /*
    Aloca o tamanho da variavel respostaFiltroSelecionado na variavel de ponteiro do filtro selecionado
    O +1 é para alocar o caractere de fim de string
    */

    /*
    Se o tipo de filtro for 1, então o filtro é por ativo
    Se o tipo de filtro for 2, então o filtro é por quantidade
    */

    //Condicionais para verificar qual o tipo de filtro selecionado e alocar o ponteiro do filtro selecionado
    if (tipoFiltro == 1)
    {
        ponteiroFiltroAtivo = malloc(strlen(respostaFiltroSelecionado) + 1);
        //Copia o conteudo da variavel respostaFiltroSelecionado, recebida por parâmetro, para a variavel ponteiroFiltroAtivo
        strcpy(ponteiroFiltroAtivo, respostaFiltroSelecionado);
        return ponteiroFiltroAtivo;
    }
    else if (tipoFiltro == 2)
    {
        ponteiroFiltroQuantidade = malloc(strlen(respostaFiltroSelecionado) + 1);
        //Copia o conteudo da variavel respostaFiltroSelecionado, recebida por parâmetro, para a variavel ponteiroFiltroAtivo
        strcpy(ponteiroFiltroQuantidade, respostaFiltroSelecionado);
        return ponteiroFiltroQuantidade;
    }
    else
    {
        printf("Erro na função allocEcopyPonteiroFiltroSelecionado");
        return 0;
    }
}

int main(int argc, char **argv){
    //Declaração de variáveis
    FILE *arquivo1, *arquivo2, *arquivoNovo;    
    char row1[MAXCHAR];
    char row2[MAXCHAR];
    char *token1, *token2, *ponteiroFiltroAtivo, *ponteiroFiltroQuantidade;
    char **derivatives = NULL, **instruments = NULL;
    char resposta, respostaFiltro;
    char respostaFiltroAsst[100], respostaFiltroQuantidade[100];
    

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
    resposta = respostaSalvarExibir();
        
    if (resposta == 'e')
    {      
        //Pergunta ao usuario se ele quer filtrar os dados
        respostaFiltro = respostaFiltroDeDados();        
        
        //Exibe os dados sem filtro
        if (respostaFiltro == 'n')
        {                        
            exibirTopoTabela();
        }

        //Filtro por ativo
        if (respostaFiltro == 'a')
        {                        
            //Pergunta ao usuário o ativo para o filtro
            char *respostaFiltroAsst = filtroAtivo();
            //Aloca e copia o ponteiro do filtro selecionado, o segundo parâmetro é o tipo de filtro, 1 é por ativo
            ponteiroFiltroAtivo = allocEcopyPonteiroFiltroSelecionado(respostaFiltroAsst, 1);
            exibirTopoTabela();
        }

        //Filtro por quantidade
        if (respostaFiltro == 'q')
        {
            //Pergunta ao usuário a quantidade para o filtro
            char *respostaFiltroQuantidade = filtroQuantidade(); 
            //Aloca e copia o ponteiro do filtro selecionado, o segundo parâmetro é o tipo de filtro, 2 é por quantidade 
            ponteiroFiltroQuantidade = allocEcopyPonteiroFiltroSelecionado(respostaFiltroQuantidade, 2);
            exibirTopoTabela();
        }
        
        //Filtro com ativo e quantidade
        if (respostaFiltro == 'c')
        {   
            //Pergunta ao usuário o ativo para o filtro
            char *respostaFiltroAsst = filtroAtivo();
            //Aloca e copia o ponteiro do filtro selecionado, o segundo parâmetro é o tipo de filtro, 1 é por ativo
            ponteiroFiltroAtivo = allocEcopyPonteiroFiltroSelecionado(respostaFiltroAsst, 1);            
            //Pergunta ao usuário a quantidade para o filtro
            char *respostaFiltroQuantidade = filtroQuantidade();
            //Aloca e copia o ponteiro do filtro selecionado, o segundo parâmetro é o tipo de filtro, 2 é por quantidade 
            ponteiroFiltroQuantidade = allocEcopyPonteiroFiltroSelecionado(respostaFiltroQuantidade, 2);
            exibirTopoTabela();
        }
    }
    else if (resposta == 's')
    {
        printf("\nCerto, então vou salvar as informações em um arquivo .csv\n");
        printf("Digite o nome do arquivo que deseja salvar (sem a extensão .csv): ");
        char nomeArquivo[100];
        scanf("%s", nomeArquivo);
        //Consome o caractere de nova linha
        getchar();
        //Adiciona a extensão .csv ao nome do arquivo
        strcat(nomeArquivo, ".csv");
        printf("\nSalvando as informações em %s\n", nomeArquivo);
        //Cria um arquivo .csv para salvar as informações
        arquivoNovo = fopen(nomeArquivo, "w+");
        //Escreve o cabeçalho do arquivo .csv
        fprintf(arquivoNovo, "DataDoRelatório,Codigo,Ativo,Vcto,Strike,Tipo,Coberto,Travado,Descoberto\n");
    }       
    else
    {
        printf("\nResposta inválida. Digite 's' para salvar ou 'e' para exibir.\n");
        //Retorna a função para que o usuário possa digitar uma resposta válida
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

        if (resposta == 'e' && respostaFiltro == 'n')
        {            
            //Chama a função para imprimir os dados da tabela de exibição
            exibirTabela(derivatives, instruments);
        }
        else if (resposta == 'e' && respostaFiltro == 'a')
        {                        
            //Compara o valor do filtro com o valor de intrumentos[2] (Ativo)
            if (strcmp(ponteiroFiltroAtivo, instruments[2]) == 0)
            {
                //Chama a função para imprimir os dados da tabela de exibição
                exibirTabela(derivatives, instruments);      
            }
        }
        else if (resposta == 'e' && respostaFiltro == 'q')
        {
            //Converte o valor de derivatives[9] (Coberto) para double
            double coberto = atof(derivatives[9]);
            //Converte o valor de derivatives[10] (Travado) para double
            double travado = atof(derivatives[10]);
            //Converte o valor de derivatives[11] (Descoberto) para double
            double descoberto = atof(derivatives[11]);
            //Converte o valor de ponteiroFiltro para double
            double filtroQuantidade = atof(ponteiroFiltroQuantidade);
            //Imprime os dados dos derivativos se o valor de coberto, travado ou descoberto for maior que o valor do filtro
            if (coberto >= filtroQuantidade && travado >= filtroQuantidade && descoberto >= filtroQuantidade)
            {
                //Chama a função para imprimir os dados da tabela de exibição
                exibirTabela(derivatives, instruments);       
            }            
        }
        else if (resposta == 'e' && respostaFiltro == 'c')
        {
            //Converte o valor de derivatives[9] (Coberto) para double
            double coberto = atof(derivatives[9]);
            //Converte o valor de derivatives[10] (Travado) para double
            double travado = atof(derivatives[10]);
            //Converte o valor de derivatives[11] (Descoberto) para double
            double descoberto = atof(derivatives[11]);
            //Converte o valor de ponteiroFiltro para double
            double filtroQuantidade = atof(ponteiroFiltroQuantidade);
            //Imprime os dados dos derivativos se o valor de coberto, travado ou descoberto for menor que o valor do filtro
            //Compara o valor do filtro com o valor de intrumentos[2] (Ativo)
            if ((coberto >= filtroQuantidade && travado >= filtroQuantidade && descoberto >= filtroQuantidade) && (strcmp(ponteiroFiltroAtivo, instruments[2]) == 0))
            {
                //Chama a função para imprimir os dados da tabela de exibição
                exibirTabela(derivatives, instruments);       
            }

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
