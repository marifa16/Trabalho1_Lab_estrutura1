#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../include/estruturas.h"
#include "../include/menus.h"
#include "../include/user_handle.h"
#include "../include/book_manager.h"
#include "../include/emprestimo_manager.h"
#include "../include/auxiliar.h"
#include "../include/relatorio.h"

state temp_state;

state main_menu()
{
    printf("===========================\n"
           "      Módulo Principal      \n"
           "===========================\n"
           "O que deseja realizar hoje?\n\n"
           "[1] - Gerenciar livros\n"
           "[2] - Gerenciar Empréstimos\n"
           "[3] - Módulo Relatório\n"
           "[4] - Sair\n"
           "===========================\n");

    int escolha = opcao_menu(1, 4);

    switch (escolha) // o estado atual é a saída de cada módulo do código
    {
    case 1:
        return BOOK_MENU; // módulo livros
    case 2:
        return EMPRESTIMO_MENU; // módulo emprestimo
    case 3:
        return RELATORIO_MENU; // módulo relatorios
    case 4:
        return SAIR;
    default:
    {
        printf("===========================\n"
               "Opção inválida.\n"
               "Por favor, escolha dentre as opções disponíveis.\n"
               "===========================\n");
        return MAIN_MENU; // Permanece no módulo atual
    }
    }
}

state book_menu()
{
    book temp_book;
    book *ptr_book = &temp_book;

    int escolha = 0;

    printf("===========================\n"
           "  Gerenciamento de livros  \n"
           "===========================\n"
           "Opções disponíveis:\n\n"
           "[1] - Adicionar livro\n"
           "[2] - Remover livro\n"
           "[3] - Atualizar\n"
           "[4] - Voltar\n"
           "[5] - Sair\n"
           "===========================\n");

    escolha = opcao_menu(1, 5);

    switch (escolha) // o estado atual é a saída de cada módulo do código
    {
    case 1: // adicionar livro
    {
        printf("===========================\n"
               "  Cadastro de Novo Livro    \n"
               "===========================\n");
        if (add_book(ptr_book) != -1)
        {
            create_book(ptr_book);
            printf("\n livro adicionado com sucesso!\n");
        }

        return BOOK_MENU; // voltar para o módulo livros
    }
    case 2: // remover um livro
    {
        int count = 0;

        printf("===========================\n"
               "       Remover livro     \n"
               "===========================\n");
        book *books = searching_book(&count);

        if (count > 0)
        {
            printf("\nDigite o ID do livro que deseja remover: ");
            int id_del = 0;
            scanf(" %d", &id_del);
            limpar_buffer();

            delete_book(id_del);
        }

        free(books); // libera os livros da função searching_book

        return BOOK_MENU; // voltar para o módulo livros
    }
    case 3: // atualizar um livro
    {

        printf("===========================\n"
               "       Atualizar livro     \n"
               "===========================\n");

        printf("\nDigite o ID do livro que deseja atualizar: ");
        int id_upp = 0;
        scanf("%d", &id_upp);
        limpar_buffer();

        book aux_book = get_book(id_upp);
        if (aux_book.id != -1)
        {
            if (upp_book(&aux_book) == 1) // Se o usuário salvou as alterações
            {
                update_book(id_upp, &aux_book);
            }
            else
            {
                printf("\nAtualização cancelada.\n");
            }
        }
        else
        {
            printf("Livro de id %d não encontrado\n", id_upp);
        }

        return BOOK_MENU; // voltar para o módulo livros
    }
    case 4:
        printf("\n Retornando ao menu principal\n");
        return MAIN_MENU;
    case 5:
        return SAIR;
    default:
    {
        printf("===========================\n"
               "Opção inválida.\n"
               "Por favor, escolha dentre as opções disponíveis.\n"
               "===========================\n");

        return BOOK_MENU; // Permanece no módulo atual
    }
    }

    return temp_state;
}

state emprestimo_menu()
{

    emprestimo temp_emp;
    emprestimo *ptr_emp = &temp_emp;
    int escolha = 0;

    printf("===========================\n"
           "          Empréstimos      \n"
           "===========================\n"
           "Opções disponíveis:\n\n"
           "[1] - Registrar novo empréstimo\n"
           "[2] - Marcar devolução\n"
           "[3] - Listar empréstimos por status\n"
           "[4] - Voltar\n"
           "[5] - Sair\n"
           "===========================\n");

    escolha = opcao_menu(1, 5);

    switch (escolha) // o estado atual é a saída de cada módulo do código
    {
    case 1: // registrar empréstimo
    {
        printf("===========================\n"
               "  Cadastro novo empréstimo    \n"
               "===========================\n");
        if (add_emp(ptr_emp) == 1)
        {
            create_emp(ptr_emp);
            printf("\nEmpréstimo realizado com sucesso!\n");
        }
        return EMPRESTIMO_MENU; // Permanece no módulo empréstimo
    }
    case 2: // devolver empréstimo
    {
        int count = 0;

        printf("===========================\n"
               "       Devolver livro     \n"
               "===========================\n");

        emprestimo *emps = searching_emp(&count);

        if (count > 0)
        {
            printf("\nDigite o ID do empréstimo que deseja devolver: ");
            int id_emp = 0;
            scanf(" %d", &id_emp);
            limpar_buffer();
            if (id_emp > 0)
            {
                emprestimo temp_emp = get_emp(id_emp);

                if (temp_emp.id != -1)
                {
                    if (temp_emp.stats == CONCLUIDO)
                    {
                        printf("\nERRO: Este empréstimo já foi marcado como concluído.\n");
                    }
                    else if (upp_emp(&temp_emp) == 1) // upp_emp marca o empréstimo como CONCLUIDO
                    {
                        update_emp(id_emp, &temp_emp);

                        book aux_book = get_book(temp_emp.livro.id);
                        aux_book.stats_bk = DISPONIVEL;

                        update_book(aux_book.id, &aux_book);
                        printf("\nLivro devolvido e status atualizado para Disponível.\n");
                    }
                    else
                    {
                        printf("\nAtualização cancelada.\n");
                    }
                }
                else
                {
                    printf("O empréstimo de id %d não encontrado\n", temp_emp.id);
                }
            }
        }

        free(emps); // libera os livros da função searching_book

        return EMPRESTIMO_MENU; // Permanece no módulo empréstimo
    }
    case 3: // lista empréstimos
    {
        printf("=============================\n"
               "Listar empréstimos por status\n"
               "=============================\n");
        list_emp_stats();
        return EMPRESTIMO_MENU; // Permanece no módulo empréstimo
    }
    case 4: // voltar
        return MAIN_MENU;
    case 5: // voltar
        return SAIR;
    default: // sair
    {
        printf("===========================\n"
               "Opção inválida.\n"
               "Por favor, escolha dentre as opções disponíveis.\n"
               "===========================\n");
        return EMPRESTIMO_MENU; // Permanece no módulo empréstimo
    }
    }

    return temp_state;
}

state relatorio_menu()
{
    printf("===========================\n"
           "          Relatórios       \n"
           "===========================\n"
           "Opções disponíveis:\n\n"
           "[1] - Listar livros por status do livro\n"
           "[2] - Listar livros por gênero\n"
           "[3] - Voltar\n"
           "[4] - Sair\n"
           "===========================\n");

    int escolha = opcao_menu(1, 4);

    switch (escolha) // o estado atual é a saída de cada módulo do código
    {
    case 1:
    {
        list_book_status();
        return RELATORIO_MENU; // módulo relatorios
    }
    case 2:
    {
        list_book_genero();
        return RELATORIO_MENU; // módulo relatorios
    }
    case 3:
    {
        return MAIN_MENU; // retorna pro menu principal
    }
    case 4:
        return SAIR;
    default:
    {
        printf("===========================\n"
               "Opção inválida.\n"
               "Por favor, escolha dentre as opções disponíveis.\n"
               "===========================\n");
        return RELATORIO_MENU; // Permanece no módulo atual
    }
    }

    return temp_state;
}