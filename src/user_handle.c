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

int add_book(book *temp_book)
{
    char temp_str[100];
    int temp_gen;

    int opcao = 0;

    printf("===========================\n"
           "   Cadastro de Novo Livro  \n"
           "===========================\n");

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
        printf("[0] - Ficção\n");
        printf("[1] - Didático\n");
        printf("[2] - Biografia\n");

        int genero_choice = opcao_menu(0, 2);

        printf("Podemos seguir com a opção fornecida? %s\n"
               "[1] - SIM  \n"
               "[2] - NÃO  \n"
               "[3] - SAIR \n",
               (genero)genero_choice);

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
    book temp_book = {0}; // Struct para guardar o termo de busca
    *count = 0;
    int opc_search = 0;
    do
    {
        printf("Qual será o formato de busca do livro? %s\n"
               "[1] - ID  \n"
               "[2] - Título  \n"
               "[3] - Autor \n"
               "[4] - ISBN \n"
               "[5] - Genero \n"
               "[6] - Sair \n");

        int opc = opcao_menu(1, 6);
        switch (opc)
        {
        case 1: // ID
        {
            printf("===========================\n"
                   "Insira o ID do livro:\n"
                   "===========================\n");
            scanf("%d", &temp_book.id);
            limpar_buffer();
            opc_search = 1;
            break;
        }
        case 2: // titulo
        {
            printf("===========================\n"
                   "Insira o titulo do livro:\n"
                   "===========================\n");
            if (!validar_titulo(temp_book.title, sizeof(temp_book.title)))
            {
                printf("===========================\n"
                       "Opção de titulo inválida para busca.\n"
                       "Por favor, insira um nome válido.\n"
                       "===========================\n");
                continue;
            }
            opc_search = 2;
            break;
        }
        case 3: // Autor
        {
            printf("===========================\n"
                   "Insira o nome do autor do livro:\n"
                   "===========================\n");
            if (!validar_autor(temp_book.autor, sizeof(temp_book.autor)))
            {
                printf("===========================\n"
                       "Opção de nome do auto para busca.\n"
                       "Por favor, insira um nome válido.\n"
                       "===========================\n");
                continue;
            }
            opc_search = 3;
            break;
        }
        case 4: // ISBN
        {
            printf("===========================\n"
                   "Insira o código ISBN do livro\n"
                   "===========================\n");
            if (!validar_ISBN(temp_book.ISBN, sizeof(temp_book.ISBN)))
            {
                printf("===========================\n"
                       "Opção de código ISBN para busca.\n"
                       "Por favor, insira um nome válido.\n"
                       "===========================\n");
                continue;
            }
            opc_search = 4;
            break;
        }
        case 5: // Genero
        {
            printf("===========================\n"
                   "Insira o gênero do livro:\n"
                   "===========================\n");
            printf("[0] - Ficção\n");
            printf("[1] - Didático\n");
            printf("[2] - Biografia\n");

            int genero_choice = opcao_menu(0, 2);
            temp_book.gen = (genero)genero_choice;
            opc_search = 5;
            break;
        }
        case 6:
        {
            printf("===========================\n"
                   "Retornando ao menu...\n"
                   "===========================\n");
            return NULL;
        }
        }
    } while (1);

    book *found_books = search_books(opc_search, &temp_book, count);
    view_books(found_books, *count);
    return found_books;
}
