#ifndef EMPRESTIMO_MANAGER_H
#define EMPRESTIMO_MANAGER_H

#include "../include/estruturas.h"

void create_emp(emprestimo *temp_emp);
void update_emp(int id, emprestimo *temp_emp);

emprestimo get_emp(int id);
emprestimo *search_emps(const char *leitor, int *count);
void view_emps(emprestimo *emps, int count);

#endif