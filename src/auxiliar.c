#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "../include/estruturas.h"

void limpar_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

int opcao_menu(int min, int max)
{
    char entrada[16];
    int valor;
    int tentativas = 0; // Para evitar loops infinitos em caso de erro persistente

    do
    {
        printf("Escolha uma opção: ");
        if (fgets(entrada, sizeof(entrada), stdin) == NULL)
        {
            // Tratar erro de leitura, se necessário
            if (tentativas++ > 5)
                return -1; // Evitar loop infinito
            continue;
        }
        entrada[strcspn(entrada, "\n")] = '\0'; // Remove o newline

        if (sscanf(entrada, "%d", &valor) == 1 && valor >= min && valor <= max)
        {
            return valor; // Retorna o valor válido
        }
        else
        {
            printf("Opção inválida. Tente novamente.\n");
            if (tentativas++ > 5)
            { // Limita o número de tentativas
                printf("Muitas tentativas inválidas. Retornando ao menu anterior.\n");
                return -1; // Ou um valor que indique falha/cancelamento
            }
        }
    } while (1); // Loop até obter uma entrada válida ou exceder tentativas
}

// Retorna o maior id da primeira coluna do arquivo CSV
int get_maior_id(const char *texto_arquivo)
{
    FILE *arquivo = fopen(texto_arquivo, "r");
    if (!arquivo)
        return 0;

    char linha[512];
    int maior_id = 0;
    fgets(linha, sizeof(linha), arquivo); // lê a primeira linha e fica por isso mesmo

    while (fgets(linha, sizeof(linha), arquivo)) // lê as demais linhas
    {
        int id_temp = 0;
        /* acessa a "linha" e extrai o primeiro numero inteiro antes da virgula em "%d," e armazena no endereco id_temp
        sscanf : ler dados formatados de uma string
        */
        sscanf(linha, "%d,", &id_temp);

        // verificar se o id_temp é o maior
        if (id_temp > maior_id)
            maior_id = id_temp;
    }

    fclose(arquivo); // fecha o arquivo

    return maior_id;
}

int validar_titulo(char *texto, size_t tamanho)
{
    fgets(texto, tamanho, stdin);
    texto[strcspn(texto, "\n")] = '\0';

    if (strlen(texto) == 0)
    {
        printf("O titulo não pode estar vazio.\n");
        // Se a entrada foi apenas '\n', o buffer de stdin está limpo.
        // Se a entrada foi "  \n" e texto ficou "", buffer limpo.
        // Se a entrada foi muito longa, o '\n' e o resto ficaram.
        limpar_buffer();
        return 0;
    }
    // Adicional: verificar se o texto não é composto apenas de espaços
    int so_espacos = 1;
    for (size_t i = 0; i < strlen(texto); i++)
    {
        if (!isspace((unsigned char)texto[i]))
        {
            so_espacos = 0;
            break;
        }
    }
    if (so_espacos && strlen(texto) > 0)
    {
        printf("O titulo não pode estar vazio.\n");
        return 0;
    }

    return 1;
}

int validar_autor(char *texto, size_t tamanho)
{
    fgets(texto, tamanho, stdin);
    texto[strcspn(texto, "\n")] = '\0';

    if (strlen(texto) == 0)
    {
        printf("O nome do autor não pode estar vazio.\n");
        limpar_buffer();
        return 0;
    }
    for (size_t i = 0; i < strlen(texto); i++) // funcao strlen retorna um tipo size_t, para evitar problema de comparar um unsigned com um int normal
    {
        if (isdigit((unsigned char)texto[i])) // acessa o caractere, realiza um cast para unsigned char, pois a bib ctype espera um int, verifica se é um digito (0-9), se for entra no laço
        {
            printf("O nome do autor não deve conter números.\n");
            return 0;
        }
    }
    int so_espacos = 1;
    for (size_t i = 0; i < strlen(texto); i++)
    {
        if (!isspace((unsigned char)texto[i]))
        {
            so_espacos = 0;
            break;
        }
    }
    if (so_espacos)
    {
        printf("O nome do autor não pode conter apenas espaços.\n");
        return 0;
    }
    return 1;
}

int validar_ISBN(char *texto, size_t tamanho)
{
    fgets(texto, tamanho, stdin);
    texto[strcspn(texto, "\n")] = '\0';

    if (strlen(texto) != 13)
    {
        printf("Erro: O ISBN deve conter exatamente 13 dígitos.\n");
        // Se a entrada foi maior que o buffer, o resto precisa ser limpo
        if (strlen(texto) == tamanho - 1)
        {
            limpar_buffer();
        }
        return 0;
    }

    for (int i = 0; i < 13; i++)
    {
        if (!isdigit((unsigned char)texto[i])) // acessa o caractere, realiza um cast para unsigned char, pois a bib ctype espera um int, verifica se é um digito (0-9), se não for entra no laço
        {
            printf("Erro: O ISBN deve conter apenas números.\n");
            return 0;
        }
    }

    return 1;
}

const char *genero_to_string(genero g)
{
    switch (g)
    {
    case FICCAO:
        return "Ficção";
    case DIDATICO:
        return "Didático";
    case BIOGRAFIA:
        return "Biografia";
    default:
        return "Desconhecido";
    }
}

char *strcasestr(const char *haystack, const char *needle)
{
    if (!*needle)
    {
        return (char *)haystack;
    }
    for (; *haystack; haystack++)
    {
        if (tolower((unsigned char)*haystack) == tolower((unsigned char)*needle))
        {
            const char *h, *n;
            for (h = haystack, n = needle; *h && *n; h++, n++)
            {
                if (tolower((unsigned char)*h) != tolower((unsigned char)*n))
                {
                    break;
                }
            }
            if (!*n)
            {
                return (char *)haystack;
            }
        }
    }
    return NULL;
}