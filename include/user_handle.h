#ifndef USER_HANDLE_H // Se ainda não definimos USER_HANDLE_H
#define USER_HANDLE_H // ... Agora definimos USER_HANDLE_H

#include "../include/estruturas.h"

int add_book(book *temp_book);
book *searching_book(int *count);
int upp_book(book *temp_book);

int add_emp(emprestimo *temp_emp);
emprestimo *searching_emp(int *count);
int upp_emp(emprestimo *temp_emp);

#endif