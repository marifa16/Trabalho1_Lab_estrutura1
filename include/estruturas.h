#ifndef ESTRUTURAS_H // Se ainda não definimos ESTRUTURAS_H

#define ESTRUTURAS_H // ... Agora definimos ESTRUTURAS_H
#define books_file "data/books.csv"
#define emprestimos_file "data/emprestimos.csv"

#include <time.h> // Inclui a biblioteca para usar struct tm

typedef enum
{
    MAIN_MENU,
    BOOK_MENU,
    EMPRESTIMO_MENU,
    RELATORIO_MENU,
    SAIR
} state;

typedef enum
{
    FICCAO,
    DIDATICO,
    BIOGRAFIA
} genero;

typedef enum
{
    CONCLUIDO,
    EM_ANDAMENTO,
    CANCELADO,
} status;

typedef enum
{
    EMPRESTADO,
    DISPONIVEL,
    INDISPONIVEL
} status_book;

typedef struct
{
    int id;
    char title[100];
    char autor[100];
    char ISBN[14];
    genero gen;
    status_book stats_bk;
} book;

typedef struct
{
    int id;
    char leitor[100];
    book livro;
    struct tm data;
    status stats;
} emprestimo;

#endif