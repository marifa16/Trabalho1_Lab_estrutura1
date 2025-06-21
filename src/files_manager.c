#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#include "../include/estruturas.h"
#include "../include/auxiliar.h"

void create_files()
{
    setlocale(LC_ALL, ".UTF8"); // Configura o locale para portugues do Brasil com suporte a UTF-8
    struct stat buffer;

    int books_stats = (stat(books_file, &buffer) == 0); // se existe retorna 0
    int emprestimo_stats = (stat(emprestimos_file, &buffer) == 0);

    if (!books_stats) // se não existir então crie
    {
        FILE *arquivo = fopen(books_file, "w");
        if (arquivo == NULL)
        {
            printf("Erro ao criar o arquivo '%s'.\n", books_file);
            return;
        }

        fprintf(arquivo, "ID,TITULO,AUTOR,ISBN,GENERO,STATUS\n");
        fclose(arquivo);
    }

    if (!emprestimo_stats)
    {
        FILE *arquivo = fopen(emprestimos_file, "w");
        if (arquivo == NULL)
        {
            printf("Erro ao criar o arquivo '%s'.\n", emprestimos_file);
            return;
        }

        fprintf(arquivo, "ID,LEITOR,LIVRO,DATA,STATS\n");
        fclose(arquivo);
    }
}

void start_files()
{
    create_files();
    printf("\n Inicialização concluida \n");
}
