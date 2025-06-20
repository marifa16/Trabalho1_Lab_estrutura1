#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#include "../include/estruturas.h"
#include "../include/auxiliar.h"
#include "../include/files_manager.h"
#include "../include/book_manager.h"

int add_book(book *temp_book)
{
    int opcao = 0;

    // titulo
    do
    {
        printf("===========================\n"
               "Insira o titulo do livro:\n"
               "===========================\n");
        if (!validar_titulo(temp_book->title, sizeof(temp_book->title)))
        {
            printf("===========================\n"
                   "Opção inválida.\n"
                   "Por favor, escolha dentre as opções disponíveis.\n"
                   "===========================\n");
            continue;
        }
        printf("Podemos seguir com a opção fornecida? %s\n"
               "[1] - SIM  \n"
               "[2] - NÃO  \n"
               "[3] - SAIR \n",
               temp_book->title);

        opcao = opcao_menu(1, 3);
        if (opcao == 1)
        {
            break;
        }
        else if (opcao == 2)
            continue;
        else if (opcao == 3)
        {
            printf("===========================\n"
                   "Retornando ao menu...\n"
                   "===========================\n");
            return -1;
        }
        else
        {
            printf("===========================\n"
                   "Opção inválida.\n"
                   "Por favor, escolha dentre as opções disponíveis.\n"
                   "===========================\n");
        }
    } while (1);

    // autor
    do
    {
        printf("===========================\n"
               "Insira o nome do autor do livro:\n"
               "===========================\n");
        if (!validar_autor(temp_book->autor, sizeof(temp_book->autor)))
        {
            continue;
        }
        printf("Podemos seguir com a opção fornecida? %s\n"
               "[1] - SIM  \n"
               "[2] - NÃO  \n"
               "[3] - SAIR \n",
               temp_book->autor);

        opcao = opcao_menu(1, 3);
        if (opcao == 1)
        {
            strcpy(temp_book->autor, temp_book->autor);
            break;
        }
        else if (opcao == 2)
            continue;
        else if (opcao == 3)
        {
            printf("===========================\n"
                   "Retornando ao menu...\n"
                   "===========================\n");
            return -1;
        }
        else
        {
            printf("===========================\n"
                   "Opção inválida.\n"
                   "Por favor, escolha dentre as opções disponíveis.\n"
                   "===========================\n");
        }
    } while (1);

    // ISBN
    do
    {
        printf("===========================================\n"
               "Insira o código ISBN do livro (13 digitos):\n"
               "===========================================\n");
        if (!validar_ISBN(temp_book->ISBN, sizeof(temp_book->ISBN)))
        {
            continue;
        }
        printf("Podemos seguir com a opção fornecida? %s\n"
               "[1] - SIM  \n"
               "[2] - NÃO  \n"
               "[3] - SAIR \n",
               temp_book->ISBN);

        limpar_buffer();
        opcao = opcao_menu(1, 3);
        if (opcao == 1)
        {
            break;
        }
        else if (opcao == 2)
            continue;
        else if (opcao == 3)
        {
            printf("===========================\n"
                   "Retornando ao menu...\n"
                   "===========================\n");
            return -1;
        }
        else
        {
            printf("===========================\n"
                   "Opção inválida.\n"
                   "Por favor, escolha dentre as opções disponíveis.\n"
                   "===========================\n");
        }
    } while (1);

    // genero
    do
    {
        printf("===========================\n"
               "Insira o gênero do livro:\n"
               "===========================\n");
        printf("[1] - Ficção\n");
        printf("[2] - Didático\n");
        printf("[3] - Biografia\n");

        int genero_choice = opcao_menu(1, 3);

        printf("Podemos seguir com a opção fornecida? %s\n"
               "[1] - SIM  \n"
               "[2] - NÃO  \n"
               "[3] - SAIR \n",
               genero_to_string((genero)genero_choice));

        opcao = opcao_menu(1, 3);

        if (opcao == 1)
        {
            temp_book->gen = (genero)genero_choice;
            break;
        }
        else if (opcao == 2)
            continue;
        else if (opcao == 3)
        {
            printf("===========================\n"
                   "Retornando ao menu...\n"
                   "===========================\n");
            return -1;
        }
        else
        {
            printf("===========================\n"
                   "Opção inválida.\n"
                   "Por favor, escolha dentre as opções disponíveis.\n"
                   "===========================\n");
        }
    } while (1);

    return 1;
}

book *searching_book(int *count)
{
    book temp_book = {0};
    *count = 0;
    int opc_search = 0;

    while (1) // Loop infinito que só é quebrado por uma ação do usuário
    {
        // CORREÇÃO: Removido o '%s' extra que causava warning.
        printf("Qual será o formato de busca do livro?\n"
               "[1] - ID\n"
               "[2] - Título\n"
               "[3] - Autor\n"
               "[4] - ISBN\n"
               "[5] - Genero\n"
               "[6] - Sair\n");

        int opc = opcao_menu(1, 6);
        opc_search = opc;

        switch (opc)
        {
        case 1: // ID
            printf("Insira o ID do livro: ");
            scanf("%d", &temp_book.id);
            limpar_buffer();
            break; // Sai do switch e prossegue para a busca
        case 2:    // titulo
            printf("Insira o titulo do livro: ");
            if (validar_titulo(temp_book.title, sizeof(temp_book.title)))
            {
                break; // Validação OK, sai do switch e prossegue
            }
            continue; // Validação FALHOU, reinicia o loop do while(1)
        case 3:       // Autor
            printf("Insira o nome do autor do livro: ");
            if (validar_autor(temp_book.autor, sizeof(temp_book.autor)))
            {
                break; // Validação OK, sai do switch e prossegue
            }
            continue; // Validação FALHOU, reinicia o loop do while(1)
        case 4:       // ISBN
            printf("Insira o código ISBN do livro: ");
            if (validar_ISBN(temp_book.ISBN, sizeof(temp_book.ISBN)))
            {
                break; // Validação OK, sai do switch e prossegue
            }
            continue; // Validação FALHOU, reinicia o loop do while(1)
        case 5:       // Genero
            printf("Selecione o gênero:\n[0] - Ficção\n[1] - Didático\n[2] - Biografia\n");
            temp_book.gen = (genero)opcao_menu(0, 2);
            break; // Sai do switch e prossegue para a busca
        case 6:    // Sair
            printf("Retornando ao menu...\n");
            return NULL; // Sai da função imediatamente
        }

        // Se chegamos aqui, a entrada foi válida e o 'break' do switch foi atingido.
        // Podemos sair do loop while(1) e realizar a busca.
        break;
    }

    book *found_books = search_books(opc_search, &temp_book, count);
    view_books(found_books, *count);
    return found_books;
}

int upp_book(book *temp_book)
{
    int opcao = 0;

    while (1) // Loop principal para permitir múltiplas atualizações
    {
        printf("\nO que deseja atualizar no livro '%s'? (ID: %d)\n", temp_book->title, temp_book->id);
        printf("[1] - Titulo\n"
               "[2] - Autor\n"
               "[3] - ISBN\n"
               "[4] - Genero\n"
               "[5] - Salvar Alterações e Sair\n"
               "[6] - Cancelar e Sair\n");

        opcao = opcao_menu(1, 6);

        switch (opcao)
        {
        case 1:
            printf("Insira o novo titulo: ");
            validar_titulo(temp_book->title, sizeof(temp_book->title));
            printf("Título atualizado para: '%s'\n", temp_book->title);
            break;

        case 2:
            printf("Insira o novo autor: ");
            validar_autor(temp_book->autor, sizeof(temp_book->autor));
            printf("Autor atualizado para: '%s'\n", temp_book->autor);
            break;

        case 3:
            printf("Insira o novo ISBN (13 dígitos): ");
            validar_ISBN(temp_book->ISBN, sizeof(temp_book->ISBN));
            printf("ISBN atualizado para: '%s'\n", temp_book->ISBN);
            break;

        case 4:
            printf("Selecione o novo gênero:\n");
            printf("[0] - Ficção\n");
            printf("[1] - Didático\n");
            printf("[2] - Biografia\n");
            temp_book->gen = (genero)opcao_menu(0, 2);
            printf("Gênero atualizado para: '%s'\n", genero_to_string(temp_book->gen));
            break;

        case 5:
            printf("\nSalvando alterações...\n");
            return 1;

        case 6:
            printf("\nAlterações canceladas.\n");
            return -1;
        }
    }
}