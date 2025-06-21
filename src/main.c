#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>

#include "../include/estruturas.h"    // Inclui o cabeçalho das estruturas
#include "../include/files_manager.h" // Inclui o cabeçalho do arquivo de gerenciamento de arquivos
#include "../include/menus.h"

int main()
{
    SetConsoleOutputCP(CP_UTF8); // Configura a saída do console para UTF-8
    SetConsoleCP(CP_UTF8);       // Configura a entrada do console para UTF-8

    setlocale(LC_ALL, ".UTF8"); // Configura o locale para português do Brasil com suporte a UTF-8
    state state_atual = MAIN_MENU;

    start_files();

    printf("Bem vindo ao sistema de gerenciamento de livros\n"
           "Desenvolvido por:\n"
           "ANDERSON CARLOS DA SILVA MORAIS\n"
           "MARILIA FONSECA ANDRADE\n"
           "Versão 1.0\n");

    while (state_atual != SAIR) // enquanto o estado não for o estado de sair o código permanece em um loop principal
    {
        switch (state_atual) // o estado atual é a saída de cada módulo do código
        {
        case MAIN_MENU:
        {
            state_atual = main_menu(); // lógica do menu principal
            break;
        }
        case BOOK_MENU:
        {
            state_atual = book_menu(); // lógica do módulo livros
            break;
        }
        case EMPRESTIMO_MENU:
            state_atual = emprestimo_menu(); // lógica do módulo emprestimo
            break;
        case RELATORIO_MENU:
            state_atual = relatorio_menu(); // lógica do módulo relatorios
            break;
        case SAIR:
            state_atual = SAIR;
            break;
        default:
            state_atual = MAIN_MENU; // Permanece no módulo atual
        }
    }

    return 0;
}