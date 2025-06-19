#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#include <locale.h>
#include "../include/estruturas.h"
#include "../include/auxiliar.h"

void create_emprestimo(emprestimo *temp_emprestio)
{
    FILE *arquivo = fopen(emprestimos_file, "a"); // Abre o arquivo para adicionar no final
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo '%s' para escrita.\n", emprestimos_file);
        return -1;
    }
}

void read_emprestimo()
{
}

void update_emprestimo()
{
}

void delete_emprestimo()
{
}