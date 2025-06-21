#include <stdio.h>
#include <stdlib.h>

#include "../include/estruturas.h"
#include "../include/auxiliar.h"
#include "../include/book_manager.h"
#include "../include/relatorio.h"

// VERSÃO CORRIGIDA
void list_book_genero()
{
    printf("\nSelecione o gênero para listar:\n"
           "[1] - Ficção\n"
           "[2] - Didático\n"
           "[3] - Biografia\n"
           "[4] - Todos\n"
           "[5] - Voltar\n");

    int escolha = opcao_menu(1, 5);
    if (escolha == 5)
    {
        return; // Usuário escolheu voltar
    }

    FILE *arquivo = fopen(books_file, "r");
    if (arquivo == NULL)
    {
        printf("Erro: Não foi possível abrir o arquivo de livros.\n");
        return;
    }

    if (escolha == 4)
    {
        printf("\n--- Listando Todos os Livros ---\n");
    }
    else
    {
        // Converte a escolha (1, 2, 3) para o enum (0, 1, 2)
        printf("\n--- Livros do Gênero: %s ---\n", genero_to_string((genero)(escolha - 1)));
    }

    char linha[512];
    int count = 0;

    fgets(linha, sizeof(linha), arquivo); // Pula o cabeçalho

    while (fgets(linha, sizeof(linha), arquivo))
    {
        book temp_book;
        int genero_int, status_int;
        if (sscanf(linha, "%d,%99[^,],%99[^,],%13[^,],%d,%d",
                   &temp_book.id, temp_book.title, temp_book.autor, temp_book.ISBN, &genero_int, &status_int) == 6)
        {
            temp_book.gen = (genero)genero_int;
            temp_book.stats_bk = (status_book)status_int;

            // Condição para imprimir: ou a escolha é 'Todos' (4) ou o gênero corresponde.
            if (escolha == 4 || temp_book.gen == (genero)(escolha - 1))
            {
                printf("----------------------------------------\n");
                printf(" ID: %d\n Título: %s\n Autor: %s\n ISBN: %s\n Gênero: %s\n Status: %s\n",
                       temp_book.id, temp_book.title, temp_book.autor, temp_book.ISBN, genero_to_string(temp_book.gen), status_book_to_string(temp_book.stats_bk));
                count++;
            }
        }
    }

    if (count == 0)
    {
        printf("Nenhum livro encontrado para este critério.\n");
    }
    printf("----------------------------------------\n");
    fclose(arquivo);
}

void list_emp_stats()
{
    printf("\nSelecione o status para listar:\n"
           "[1] - Concluído\n"
           "[2] - Em Andamento\n"
           "[3] - Cancelado\n"
           "[4] - Todos\n"
           "[5] - Voltar\n");

    int escolha = opcao_menu(1, 5);
    if (escolha == 5)
    {
        return;
    }

    FILE *arquivo = fopen(emprestimos_file, "r");
    if (arquivo == NULL)
    {
        printf("Erro: Não foi possível abrir o arquivo de empréstimos.\n");
        return;
    }

    if (escolha == 4)
    {
        printf("\n--- Listando Todos os Empréstimos ---\n");
    }
    else
    {
        printf("\n--- Empréstimos com Status: %s ---\n", status_to_string((status)(escolha - 1)));
    }

    char linha[512];
    int count = 0;

    fgets(linha, sizeof(linha), arquivo); // Pula o cabeçalho

    while (fgets(linha, sizeof(linha), arquivo))
    {
        emprestimo temp_emp;
        int id_livro, stats_int;
        char data_str[9];

        if (sscanf(linha, "%d,%99[^,],%d,%8[^,],%d",
                   &temp_emp.id, temp_emp.leitor, &id_livro, data_str, &stats_int) == 5)
        {
            temp_emp.stats = (status)stats_int;
            // Condição para imprimir: ou a escolha é 'Todos' (4) ou o status corresponde.
            if (escolha == 4 || temp_emp.stats == (status)(escolha - 1))
            {
                book aux_book = get_book(id_livro);
                printf("----------------------------------------\n");
                printf(" ID Empréstimo: %d\n Leitor: %s\n Livro: %s\n Data: %s\n Status: %s\n",
                       temp_emp.id, temp_emp.leitor, aux_book.title, data_str, status_to_string(temp_emp.stats));
                count++;
            }
        }
    }

    if (count == 0)
    {
        printf("Nenhum empréstimo encontrado para este critério.\n");
    }
    printf("----------------------------------------\n");
    fclose(arquivo);
}

void list_book_status()
{
    printf("\nSelecione o status do livro para listar:\n"
           "[1] - Disponível\n"
           "[2] - Emprestado\n"
           "[3] - Indisponível\n"
           "[4] - Todos\n"
           "[5] - Voltar\n");

    int escolha = opcao_menu(1, 5);
    if (escolha == 5)
        return;

    FILE *arquivo = fopen(books_file, "r");
    if (arquivo == NULL)
    {
        printf("Erro: Não foi possível abrir o arquivo de livros.\n");
        return;
    }

    status_book status_opc;
    if (escolha == 1)
        status_opc = DISPONIVEL;
    else if (escolha == 2)
        status_opc = EMPRESTADO;
    else
        status_opc = INDISPONIVEL;

    if (escolha == 4)
        printf("\n--- Listando Todos os Livros ---\n");
    else
        printf("\n--- Livros com Status: %s ---\n", status_book_to_string(status_opc));

    char linha[512];
    int count = 0;

    fgets(linha, sizeof(linha), arquivo); // Pula o cabeçalho

    while (fgets(linha, sizeof(linha), arquivo))
    {
        book temp_book;
        int genero_int, status_int;
        if (sscanf(linha, "%d,%99[^,],%99[^,],%13[^,],%d,%d",
                   &temp_book.id, temp_book.title, temp_book.autor, temp_book.ISBN, &genero_int, &status_int) == 6)
        {
            temp_book.stats_bk = (status_book)status_int;

            if (escolha == 4 || temp_book.stats_bk == status_opc)
            {
                printf("----------------------------------------\n");
                printf(" ID: %d\n Título: %s\n Autor: %s\n Status: %s\n",
                       temp_book.id, temp_book.title, temp_book.autor, status_book_to_string(temp_book.stats_bk));
                count++;
            }
        }
    }

    if (count == 0)
        printf("Nenhum livro encontrado para este critério.\n");
    printf("----------------------------------------\n");
    fclose(arquivo);
}