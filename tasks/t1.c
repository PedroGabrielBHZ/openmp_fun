// Modifique o seguinte código, utilizando o padrão MAP (e outros comandos do OpenMP),

#include <stdio.h>
#include <omp.h>

int main()
{
    int i;

#pragma omp parallel num_threads(2) // seta o número de threads em 2
    {
        int tid = omp_get_thread_num(); // lê o identificador da thread
#pragma omp for ordered
        for (i = 1; i <= 3; i++)
        {
#pragma omp ordered
            {
                printf("[PRINT1] T%d = %d \n", tid, i);
                printf("[PRINT2] T%d = %d \n", tid, i);
            }
        }
    }
}

/*
para que a saída do programa seja: <- check

[PRINT1] T0 = 1
[PRINT2] T0 = 1
[PRINT1] T0 = 2
[PRINT2] T0 = 2
[PRINT1] T1 = 3
[PRINT2] T1 = 3

****************_my_run_**************
pedro@t14:~/Code/openmp/tasks$ g++ -fopenmp t1.c && ./a.out
[PRINT1] T0 = 1
[PRINT2] T0 = 1
[PRINT1] T0 = 2
[PRINT2] T0 = 2
[PRINT1] T1 = 3
[PRINT2] T1 = 3
**************************************

Obs: A saída deve ser 1 1, 2 2, 3 3, mas a ordem das threads pode variar. <- ah, ok.
Dica: https://bisqwit.iki.fi/story/howto/openmp/#OrderedClauseLinks <- nice docs, btw.
IMPORTANTE: A resposta deve ser um arquivo .c. <- that almost got me tbh
*/