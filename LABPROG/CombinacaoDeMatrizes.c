
#include<stdio.h>

int main (void)
{
  int nlin, ncol,linha, coluna, contador = 1;
  
  printf("Digite o numero de linhas da matriz: ");
  scanf("%d", &nlin);
  printf("Digite o numero de colunas da matriz: ");
  scanf("%d", &ncol);

  float matriz[nlin][ncol];
  float matriz2[nlin][ncol];
  float matriz3[nlin][ncol];
  float t = 0.0;
  
  printf ("\nDigite os valores para os elementos da primeira matriz \n\n");
  
  for (linha=0; linha<nlin; linha++)
    for (coluna=0; coluna<ncol; coluna++)
    {
      printf ("\nElemento[%d][%d] = ", linha, coluna);
      scanf ("%f", &matriz[linha][coluna]);
    }

  printf ("\nDigite os valores para os elementos da segunda matriz \n\n");

  for (linha=0; linha<nlin; linha++)
    for (coluna=0; coluna<ncol; coluna++)
    {
      printf ("\nElemento[%d][%d] = ", linha, coluna);
      scanf ("%f", &matriz2[linha][coluna]);
    }

  printf("\nmatriz 1:\n\n");

  for (linha=0; linha<nlin; linha++)
  {
    for (coluna=0; coluna<ncol; coluna++)
    {
      printf ("%0.1f", matriz[linha][coluna]);
      printf(" ");    
    }
    printf("\n");
  }

  printf("\nmatriz 2:\n\n");

  for (linha=0; linha<nlin; linha++)
  {
    for (coluna=0; coluna<ncol; coluna++)
    {
      printf ("%0.1f", matriz2[linha][coluna]);
      printf(" ");
    }
    printf("\n");
  }

  printf("\nusando (1-t*A+t*B): \n\n");
    while (t<1.1) 
    {
        printf("matriz %d com t=%0.1f:\n",contador,t);
        for (linha=0; linha<nlin; linha++)
        {
            for (coluna=0; coluna<ncol; coluna++)
            {
                matriz3[linha][coluna] = ((1-t)*matriz[linha][coluna]+t*matriz2[linha][coluna]);
                printf ("%0.1f", matriz3[linha][coluna]);
                printf(" ");
            }
            printf("\n");
        }
        printf("\n");
        t=t+0.1;
        contador++;
    }
    return(0);
}
