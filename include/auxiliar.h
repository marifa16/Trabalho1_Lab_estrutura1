#ifndef AUXILIAR_H
#define AUXILIAR_H

void limpar_buffer();
int opcao_menu(int min, int max);
int get_maior_id(const char *nome_arquivo);

int validar_titulo(char *texto, size_t tamanho);
int validar_nome(char *texto, size_t tamanho);
int validar_autor(char *texto, size_t tamanho);
int validar_ISBN(char *texto, size_t tamanho);
int escolher_genero();
const char *genero_to_string(genero g);

#endif