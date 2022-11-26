
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Numero maximo de candidatos
#define MAX 9

typedef struct
{
    string name;
    int votes;
}
candidate;

// Array de candidatos
candidate candidates[MAX];

// Numero de candidatos
int candidate_count;

// Prototipos de funções	
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Verifica uso invalido
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Popula array de candidatos
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop por cada voto
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Verifica se o voto é valido
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Mostra vencedor
    print_winner();
}

// Atualiza contagem de votos dado o nome do candidato
bool vote(string name)
{
    // Loop por cada candidato
    for (int i = 0; i < candidate_count; i++)
    {
        // Verifica se o nome do candidato é igual ao nome do voto
        if (strcmp(candidates[i].name, name) == 0)
        {
            // Se for igual, atualiza a contagem de votos, retorna verdadeiro e sai da função
            candidates[i].votes++;
            return true;
        }
    }
    // Se não for igual, retorna falso
    return false;
}

// Mostra o vencedor (ou vencedores) da eleição
void print_winner(void)
{
    // Criar variavel para armazenar o maior numero de votos
    int maximum_vote = 0;

    // Iterar sobre os candidatos para encontrar o maior numero de votos
    for (int i = 0; i < candidate_count; i++)
    {
        // Verifica se o numero de votos do candidato é maior que o numero de votos do candidato com o maior numero de votos
        if (candidates[i].votes > maximum_vote)
        {
            maximum_vote = candidates[i].votes;
        }
    }

    // Iterar sobre os candidatos para imprimir o nome do candidato com o maior numero de votos
    for (int i = 0; i < candidate_count; i++)
    {
        // Verifica se o numero de votos do candidato é igual ao numero de votos do candidato com o maior numero de votos
        if (candidates[i].votes == maximum_vote)
        {
            printf("%s\n", candidates[i].name);
        }
    }

    return;
}
