#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#include "../include/estruturas.h"
#include "../include/auxiliar.h"
#include "../include/book_manager.h"

void create_book(book *temp_book)
{
    int id = get_maior_id(books_file) + 1;
    temp_book->stats_bk = DISPONIVEL;

    FILE *arquivo = fopen(books_file, "a"); // Abre o arquivo para adicionar no final
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo '%s' para escrita.\n", books_file);
        return;
    }

    fprintf(arquivo, "%d,%s,%s,%s,%d,%d\n", id, temp_book->title, temp_book->autor, temp_book->ISBN, temp_book->gen, temp_book->stats_bk); // Escreve o novo id                                                                                   // Nova linha
    fclose(arquivo);
}

void read_book(int id)
{
    book temp_book = get_book(id);

    if (temp_book.id != -1)
    {
        printf("========================================\n");
        printf("ID LIVRO : %d\n", temp_book.id);
        printf("TITULO   : %s\n", temp_book.title);
        printf("AUTOR    : %s\n", temp_book.autor);
        printf("ISBN     : %s\n", temp_book.ISBN);
        printf("GENERO   : %s\n", genero_to_string(temp_book.gen));
        printf("STATUS   : %s\n", status_book_to_string(temp_book.stats_bk));
        printf("========================================\n");
    }
    else
    {
        printf("\nLivro com ID %d não encontrado!\n", id);
    }
}

void update_book(int id, book *temp_book)
{
    FILE *arquivo = fopen(books_file, "r"); // Abre o arquivo para criar uma cópia
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo '%s' para leitura.\n", books_file);
        return;
    }
    FILE *temp = fopen("temp.csv", "w");
    if (!temp)
    {
        fclose(arquivo);
        printf("Erro ao criar arquivo temporario.\n");
        return;
    }

    char linha[512];
    int id_atual;
    int executado = 0; // atualizar ou deletar a linha

    // Copia o cabecalho
    if (fgets(linha, sizeof(linha), arquivo))
    {
        fputs(linha, temp);
    }

    // Copia as linhas, pulando a que sera deletada
    while (fgets(linha, sizeof(linha), arquivo))
    {
        if (sscanf(linha, "%d,", &id_atual) == 1 && id_atual == id)
        {
            // Encontrou a linha para atualizar, escreve os novos dados
            fprintf(temp, "%d,%s,%s,%s,%d,%d\n",
                    temp_book->id, temp_book->title, temp_book->autor,
                    temp_book->ISBN, temp_book->gen, temp_book->stats_bk);
            executado = 1;
        }
        else
        {
            // Copia a linha original para o arquivo temporário
            fputs(linha, temp);
        }
    }

    fclose(arquivo);
    fclose(temp);

    remove(books_file);
    rename("temp.csv", books_file);

    if (executado)
    {
        printf("\nLivro com ID %d foi atualizado com sucesso.\n", id);
    }
    else
    {
        printf("\nAVISO: Livro com ID %d não foi encontrado para atualização.\n", id);
    }
}

void delete_book(int id)
{
    FILE *arquivo = fopen(books_file, "r"); // Abre o arquivo para criar uma cópia
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo '%s' para escrita.\n", books_file);
        return;
    }
    FILE *temp = fopen("temp.csv", "w");
    if (!temp)
    {
        fclose(arquivo);
        printf("Erro ao criar arquivo temporario.\n");
        return;
    }

    char linha[512];
    int id_atual;
    int executado = 0;

    // Copia o cabecalho
    if (fgets(linha, sizeof(linha), arquivo))
    {
        fputs(linha, temp);
    }

    // Copia as linhas, pulando a que sera deletada
    while (fgets(linha, sizeof(linha), arquivo))
    {
        if (sscanf(linha, "%d,", &id_atual) == 1)
        {
            if (id_atual == id)
            {
                executado = 1;
                continue;
            }
        }
        // Se não for o ID a ser deletado, copia a linha para o arquivo temporário
        fputs(linha, temp);
    }

    fclose(arquivo);
    fclose(temp);

    remove(books_file);
    rename("temp.csv", books_file);

    if (executado)
    {
        printf("\nLivro com ID %d foi removido com sucesso.\n", id);
    }
    else
    {
        printf("\nAVISO: Livro com ID %d não foi encontrado para remoção.\n", id);
    }
}

book *search_books(int search_key, book *target_book, int *matchs)
{
    FILE *arquivo = fopen(books_file, "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo de livros para busca.\n");
        *matchs = 0;
        return NULL;
    }

    book *temp_books = NULL; // Ponteiro do array dinâmico
    *matchs = 0;

    char linha[512];
    fgets(linha, sizeof(linha), arquivo); // Pula cabeçalho

    while (fgets(linha, sizeof(linha), arquivo))
    {
        book aux_book;
        int genero_int, status_int;
        if (sscanf(linha, "%d,%99[^,],%99[^,],%13[^,],%d,%d",
                   &aux_book.id, aux_book.title, aux_book.autor, aux_book.ISBN, &genero_int, &status_int) != 6)
        {
            continue;
        }
        aux_book.gen = (genero)genero_int;
        aux_book.stats_bk = (status_book)status_int;

        int found = 0;
        switch (search_key)
        {
        case 1: // ID
            if (aux_book.id == target_book->id)
                found = 1;
            break;
        case 2: // Título
            if (strcasestr(aux_book.title, target_book->title) != NULL)
                found = 1;
            break;
        case 3: // Autor
            if (strcasestr(aux_book.autor, target_book->autor) != NULL)
                found = 1;
            break;
        case 4: // ISBN
            if (strcmp(aux_book.ISBN, target_book->ISBN) == 0)
                found = 1;
            break;
        case 5: // Genero
            if (aux_book.gen == target_book->gen)
                found = 1;
            break;
        }

        if (found)
        {
            (*matchs)++;
            // Realoca memória para o novo livro encontrado
            book *temp = realloc(temp_books, (*matchs) * sizeof(book));
            if (temp == NULL)
            {
                printf("Erro de alocação de memória!\n");
                free(temp_books);
                fclose(arquivo);
                return NULL;
            }
            temp_books = temp;
            // Copia o livro encontrado para o final do array dinâmico
            temp_books[(*matchs) - 1] = aux_book;
        }
    }

    fclose(arquivo);
    return temp_books; // Retorna o ponteiro para o array de livros
}

void view_books(book *books, int count)
{
    if (count == 0)
    {
        printf("\nNenhum livro encontrado com o critério fornecido.\n");
        return;
    }

    printf("\n--- Resultados da Busca (%d encontrado(s)) ---\n", count);
    for (int i = 0; i < count; i++)
    {
        printf("----------------------------------------\n");
        printf("  ID: %d\n", books[i].id);
        printf("  Título: %s\n", books[i].title);
        printf("  Autor: %s\n", books[i].autor);
        printf("  Status: %s\n", status_book_to_string(books[i].stats_bk));
    }
    printf("----------------------------------------\n");
}

book get_book(int id)
{
    book temp_book = {.id = -1}; // Inicia com ID inválido para indicar "não encontrado"
    FILE *arquivo = fopen(books_file, "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir arquivo de livros.\n");
        return temp_book;
    }

    char linha[512];
    fgets(linha, sizeof(linha), arquivo); // Pula cabeçalho

    while (fgets(linha, sizeof(linha), arquivo))
    {
        int genero_int, status_int;
        if (sscanf(linha, "%d,%99[^,],%99[^,],%13[^,],%d,%d",
                   &temp_book.id, temp_book.title, temp_book.autor, temp_book.ISBN, &genero_int, &status_int) == 6)
        {
            if (temp_book.id == id)
            {
                temp_book.gen = (genero)genero_int;
                temp_book.stats_bk = (status_book)status_int;
                fclose(arquivo);
                return temp_book; // Retorna o livro encontrado
            }
        }
    }

    fclose(arquivo);
    temp_book.id = -1; // Garante que o ID é inválido se não encontrou
    return temp_book;
}
