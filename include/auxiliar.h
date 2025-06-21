#ifndef AUXILIAR_H
#define AUXILIAR_H

#include "../include/estruturas.h"

void limpar_buffer();
int opcao_menu(int min, int max);
int get_maior_id(const char *nome_arquivo);

int validar_titulo(char *texto, size_t tamanho);
int validar_autor(char *texto, size_t tamanho);
int validar_ISBN(char *texto, size_t tamanho);

const char *genero_to_string(genero g);
char *strcasestr(const char *haystack, const char *needle);

struct tm get_data();
const char *status_to_string(status s);
const char *status_book_to_string(status_book sb);
char *strptime(const char *s, const char *format, struct tm *tm);

#endif