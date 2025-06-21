#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#include <locale.h>

#include "../include/estruturas.h"
#include "../include/auxiliar.h"
#include "../include/emprestimo_manager.h"
#include "../include/book_manager.h"
#include "../include/relatorio.h"

void create_emp(emprestimo *temp_emp)
{
    temp_emp->id = get_maior_id(emprestimos_file) + 1;
    temp_emp->data = get_data();
    temp_emp->stats = EM_ANDAMENTO;

    FILE *arquivo = fopen(emprestimos_file, "a"); // Abre o arquivo para adicionar no final
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo '%s' para escrita.\n", emprestimos_file);
        return;
    }

    // Formata a data para o formato YY/MM/DD
    char data_formatada[9]; // "YY/MM/DD\0"
    strftime(data_formatada, sizeof(data_formatada), "%y/%m/%d", &temp_emp->data);

    // Escreve os dados formatados no arquivo, seguindo o cabeçalho do CSV
    fprintf(arquivo, "%d,%s,%d,%s,%d\n",
            temp_emp->id,
            temp_emp->leitor,
            temp_emp->livro.id, // Salva apenas o ID do livro
            data_formatada,     // Salva a data como string
            temp_emp->stats);   // Salva o status codificado

    fclose(arquivo);

    // Atualiza o status do livro no arquivo de livros para emprestado
    book book_updated = get_book(temp_emp->livro.id);
    book_updated.stats_bk = EMPRESTADO;
    update_book(book_updated.id, &book_updated);
}

void read_emp()
{
    printf("null");
}

void update_emp(int id, emprestimo *temp_emp)
{
    FILE *arquivo = fopen(emprestimos_file, "r"); // Abre o arquivo para criar uma cópia
    if (arquivo == NULL)
    {
        printf("Erro ao abrir o arquivo '%s' para leitura.\n", emprestimos_file);
        return;
    }
    FILE *temp = fopen("temp.csv", "w");
    if (!temp)
    {
        fclose(arquivo);
        printf("Erro ao criar arquivo temporario.\n");
        return;
    }

    char linha[512];
    int id_atual;
    int executado = 0; // atualizar ou deletar a linha

    // Copia o cabecalho
    if (fgets(linha, sizeof(linha), arquivo))
    {
        fputs(linha, temp);
    }

    // Copia as linhas, pulando a que sera deletada
    while (fgets(linha, sizeof(linha), arquivo))
    {
        if (sscanf(linha, "%d,", &id_atual) == 1 && id_atual == id)
        // Encontrou a linha para atualizar, escreve os novos dados
        {
            char data_formatada[9];
            strftime(data_formatada, sizeof(data_formatada), "%y/%m/%d", &temp_emp->data);

            fprintf(temp, "%d,%s,%d,%s,%d\n",
                    temp_emp->id, temp_emp->leitor, temp_emp->livro.id,
                    data_formatada, temp_emp->stats);
            executado = 1;
        }
        else
        {
            // Copia a linha original para o arquivo temporário
            fputs(linha, temp);
        }
    }

    fclose(arquivo);
    fclose(temp);

    remove(emprestimos_file);
    rename("temp.csv", emprestimos_file);

    if (executado)
    {
        printf("\nEmpréstimo com ID %d foi atualizado com sucesso.\n", id);
    }
    else
    {
        printf("\nAVISO: Emprésitmo com ID %d não foi encontrado para atualização.\n", id);
    }
}

emprestimo get_emp(int id)
{
    emprestimo temp_emp = {.id = -1}; // Inicia com ID inválido para indicar "não encontrado"
    FILE *arquivo = fopen(emprestimos_file, "r");
    if (arquivo == NULL)
    {
        printf("Erro ao abrir arquivo de empréstimo.\n");
        return temp_emp;
    }

    char linha[512];
    fgets(linha, sizeof(linha), arquivo); // Pula cabeçalho

    while (fgets(linha, sizeof(linha), arquivo))
    {
        int id_livro, stats_int;
        char data_str[9];
        if (sscanf(linha, "%d,%99[^,],%d,%8[^,],%d",
                   &temp_emp.id, temp_emp.leitor, &id_livro, data_str, &stats_int) == 5)
        {
            if (temp_emp.id == id)
            {
                temp_emp.livro = get_book(id_livro);
                temp_emp.stats = (status)stats_int;
                strptime(data_str, "%y/%m/%d", &temp_emp.data);
                fclose(arquivo);
                return temp_emp;
            }
        }
    }

    fclose(arquivo);
    temp_emp.id = -1; // Garante que o ID é inválido se não encontrou
    return temp_emp;
}

emprestimo *search_emps(const char *leitor, int *matchs)
{
    FILE *arquivo = fopen(emprestimos_file, "r");
    if (arquivo == NULL)
    {
        *matchs = 0;
        return NULL;
    }

    emprestimo *found_emps = NULL;
    *matchs = 0;

    char linha[512];
    fgets(linha, sizeof(linha), arquivo);

    while (fgets(linha, sizeof(linha), arquivo))
    {
        emprestimo aux_emp;
        int id_livro, stats_int;
        char data_str[9];

        if (sscanf(linha, "%d,%99[^,],%d,%8[^,],%d",
                   &aux_emp.id, aux_emp.leitor, &id_livro, data_str, &stats_int) != 5)
        {
            continue;
        }

        if (strcasestr(aux_emp.leitor, leitor) != NULL)
        {
            (*matchs)++;
            // Realoca memória para o novo empréstimo encontrado
            emprestimo *temp = realloc(found_emps, (*matchs) * sizeof(emprestimo));
            if (temp == NULL)
            {
                free(found_emps);
                return NULL;
            }
            found_emps = temp;

            aux_emp.livro = get_book(id_livro);
            aux_emp.stats = (status)stats_int;
            strptime(data_str, "%y/%m/%d", &aux_emp.data);
            found_emps[(*matchs) - 1] = aux_emp;
        }
    }
    fclose(arquivo);
    return found_emps;
}

void view_emps(emprestimo *emps, int matchs)
{
    if (matchs == 0)
    {
        printf("\nNenhum empréstimo encontrado para este leitor.\n");
        return;
    }

    printf("\n--- Empréstimos Encontrados (%d) ---\n", matchs);
    for (int i = 0; i < matchs; i++)
    {
        char data_formatada[11];
        strftime(data_formatada, sizeof(data_formatada), "%d/%m/%Y", &emps[i].data);

        printf("----------------------------------------\n");
        printf("  ID Empréstimo: %d\n", emps[i].id);
        printf("  Leitor: %s\n", emps[i].leitor);
        printf("  Livro: %s (ID: %d)\n", emps[i].livro.title, emps[i].livro.id);
        printf("  Data: %s\n", data_formatada);
        printf("  Status: %s\n", status_to_string(emps[i].stats));
    }
    printf("----------------------------------------\n");
}