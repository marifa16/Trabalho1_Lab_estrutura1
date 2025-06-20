#ifndef BOOK_MANAGER_H // Se ainda não definimos BOOK_MANAGER_H
#define BOOK_MANAGER_H // ... Agora definimos BOOK_MANAGER_H

#include "../include/estruturas.h"

void create_book(book *temp_book);
void read_book(int id);
void update_book(int id, book *temp_book);
void delete_book(int id);
book *search_books(int search_key, book *target_book, int *matchs);
void view_books(book *books, int count);
book get_book(int id);

#endif