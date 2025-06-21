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
    int valor;
    char buffer[100];

    printf("Escolha uma opcao: ");
    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
        return -1; // Erro de leitura
    }

    // Tenta ler um inteiro da string. Se conseguir e não houver lixo depois, sscanf retorna 1.
    if (sscanf(buffer, "%d", &valor) == 1)
    {
        if (valor >= min && valor <= max)
        {
            return valor; // Sucesso
        }
    }

    printf("Opcao invalida. Tente novamente.\n");
    return -1; // Indica falha, para ser tratada em um loop
}

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
    if (fgets(texto, tamanho, stdin) == NULL)
        return 0;

    // Se a string lida não contém '\n', significa que a entrada foi maior que o buffer.
    // Nesse caso, limpamos o restante da entrada para evitar problemas futuros.
    if (strchr(texto, '\n') == NULL)
    {
        limpar_buffer();
    }
    else
    {
        // Se a entrada coube, apenas removemos o '\n' do final.
        texto[strcspn(texto, "\n\r")] = 0;
    }

    if (strlen(texto) == 0)
    {
        printf("O titulo não pode estar vazio.\n");
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
    if (so_espacos)
    {
        printf("O titulo não pode estar vazio.\n");
        return 0;
    }

    return 1;
}

int validar_autor(char *texto, size_t tamanho)
{
    if (fgets(texto, tamanho, stdin) == NULL)
        return 0;

    // Se a string lida não contém '\n', significa que a entrada foi maior que o buffer.
    // Nesse caso, limpamos o restante da entrada para evitar problemas futuros.
    if (strchr(texto, '\n') == NULL)
    {
        limpar_buffer();
    }
    else
    {
        // Se a entrada coube, apenas removemos o '\n' do final.
        texto[strcspn(texto, "\n\r")] = 0;
    }

    if (strlen(texto) == 0)
    {
        printf("O nome do autor não pode estar vazio.\n");
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
    if (fgets(texto, tamanho, stdin) == NULL)
        return 0;

    // Se a string lida não contém '\n', significa que a entrada foi maior que o buffer.
    // Nesse caso, limpamos o restante da entrada para evitar problemas futuros.
    if (strchr(texto, '\n') == NULL)
    {
        limpar_buffer();
    }
    else
    {
        // Se a entrada coube, apenas removemos o '\n' do final.
        texto[strcspn(texto, "\n\r")] = 0;
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

struct tm get_data()
{
    time_t t = time(NULL);
    return *localtime(&t);
}

const char *status_to_string(status s)
{
    switch (s)
    {
    case CONCLUIDO:
        return "Concluído";
    case EM_ANDAMENTO:
        return "Em Andamento";
    case CANCELADO:
        return "Cancelado";
    default:
        return "Desconhecido";
    }
}

const char *status_book_to_string(status_book sb)
{
    switch (sb)
    {
    case EMPRESTADO:
        return "Emprestado";
    case DISPONIVEL:
        return "Disponível";
    case INDISPONIVEL:
        return "Indisponível";
    default:
        return "Desconhecido";
    }
}

char *strptime(const char *s, const char *format, struct tm *tm)
{
    char *p = (char *)s;
    while (*format)
    {
        if (*format == '%')
        {
            format++;
            switch (*format)
            {
            case 'y':
            {
                int year = 0;
                if (sscanf(p, "%2d", &year) == 1)
                {
                    tm->tm_year = year + 100; // Anos 2000
                    p += 2;
                }
                else
                    return NULL;
                break;
            }
            case 'm':
            {
                if (sscanf(p, "%2d", &tm->tm_mon) == 1)
                {
                    tm->tm_mon--; // Mês é 0-11
                    p += 2;
                }
                else
                    return NULL;
                break;
            }
            case 'd':
            {
                if (sscanf(p, "%2d", &tm->tm_mday) == 1)
                {
                    p += 2;
                }
                else
                    return NULL;
                break;
            }
            default:
                return NULL;
            }
        }
        else
        {
            if (*p == *format)
            {
                p++;
            }
            else
            {
                return NULL;
            }
        }
        format++;
    }
    return p;
}