
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Numero maximo de candidatos e votos
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// Preferencias[i][j] é j-ésima preferência do i-ésimo eleitor
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidatos têm nome, número de votos e status eliminado
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array de candidatos
candidate candidates[MAX_CANDIDATES];

// Numero de candidatos e eleitores
int voter_count;
int candidate_count;

// Prototipos de funções
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);
void bubble_sort(int nums[]);

int main(int argc, string argv[])
{
    // Verifica uso invalido
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Popula array de candidatos
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Continua pedindo votos até que todos os eleitores tenham votado
    for (int i = 0; i < voter_count; i++)
    {
        
        // Pede a preferência de cada eleitor
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Grava a preferência, ignorando votos inválidos
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    //Continua até que um candidato tenha mais da metade dos votos
    while (true)
    {
        // Calcula o número de votos recebidos por cada candidato
        tabulate();

        // Verifica se o eleição tem um vencedor
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Elimina o candidato (ou candidatos) em último lugar
        int min = find_min();
        bool tie = is_tie(min);

        // Se há empate, todos ganham
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }
        
        // Elimina qualquer um com o número mínimo de votos
        eliminate(min);

        // Reseta o número de votos de cada candidato
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Grava um voto dado por um eleitor
bool vote(int voter, int rank, string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i].name) == 0)
        {            
            // Popula o array de preferências com os rankings dos eleitores (i = candidato)
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Conta os votos de cada candidato não eliminado
void tabulate(void)
{
    int candidate;
    
    // Adiciona um voto ao candidato não eliminado com a maior preferência
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            candidate = preferences[i][j];
            if (!candidates[candidate].eliminated)
            {
                candidates[candidate].votes++;
                break;
            }
        }
    }
}

// Informa o vencedor da eleição, se houver
bool print_winner(void)
{
    // Verifica se algum candidato tem mais da metade dos votos
    int majority = round(voter_count / 2);
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > majority)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Retorna o número mínimo de votos de qualquer candidato que ainda esteja na corrida
int find_min(void)
{
    // Seta o valor inicial do mínimo como o número de votos do primeiro candidato não eliminado
    int min_votes = candidates[0].votes;

    // Se qualquer candidato tiver menos votos, então atualiza o número mínimo de votos
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes < min_votes)
        {
            min_votes = candidates[i].votes;
        }
    }
    return min_votes;
}

// Retorna true se houver empate entre todos os candidatos, false caso contrário
bool is_tie(int min)
{
    // Verifica se todos os candidatos têm o mesmo número de votos que o mínimo
    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated && candidates[i].votes != min)
        {
            return false;
        }
    }
    return true;
}

// Elimina o candidato (ou candidatos) em último lugar
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
}
