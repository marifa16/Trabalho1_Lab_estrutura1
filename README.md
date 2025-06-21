# Sistema de Gerenciamento de Biblioteca

Este é um projeto de console desenvolvido em C para gerenciar o acervo de uma pequena biblioteca. O sistema permite o cadastro de livros, o registro de empréstimos e a geração de relatórios, com todos os dados persistidos em arquivos CSV.

## Funcionalidades

*   **Módulo de Livros:**
    *   Adicionar novos livros ao acervo.
    *   Remover livros existentes.
    *   Atualizar informações de um livro (título, autor, ISBN, gênero).
    *   Buscar livros por ID, título, autor, ISBN ou gênero.

*   **Módulo de Empréstimos:**
    *   Registrar um novo empréstimo, vinculando um leitor a um livro disponível.
    *   Marcar um empréstimo como devolvido, atualizando o status do livro para "Disponível".
    *   Buscar empréstimos por nome do leitor.

*   **Módulo de Relatórios:**
    *   Listar todos os livros filtrando por gênero.
    *   Listar todos os livros filtrando por status (Disponível, Emprestado, Indisponível).

*   **Persistência de Dados:**
    *   Todas as informações são salvas nos arquivos `data/books.csv` e `data/emprestimos.csv`.

## Tecnologias Utilizadas

*   **Linguagem:** C (Padrão C99)
*   **Compilador:** GCC (MinGW para Windows)
*   **Build System:** Makefile

## Estrutura do Projeto

```
.
├── Makefile
├── README.md
├── bin/            # Contém o executável gerado
├── data/           # Contém os arquivos de dados
│   ├── books.csv
│   └── emprestimos.csv
├── include/        # Contém os arquivos de cabeçalho (.h)
│   ├── auxiliar.h
│   ├── book_manager.h
│   ├── emprestimo_manager.h
│   ├── estruturas.h
│   ├── files_manager.h
│   ├── menus.h
│   └── relatorio.h
└── src/            # Contém os arquivos de código fonte (.c)
    ├── auxiliar.c
    ├── book_manager.c
    ├── emprestimo_manager.c
    ├── files_manager.c
    ├── main.c
    ├── menus.c
    ├── relatorio.c
    └── user_handle.c
```

## Como Compilar e Executar

Este projeto utiliza um `Makefile` para automatizar o processo de compilação no ambiente Windows com MinGW.

### Pré-requisitos

*   Ter o `mingw32-make` e o compilador `gcc` instalados e configurados no PATH do sistema.

### Comandos

1.  **Compilar o projeto:**
    Abra um terminal na raiz do projeto e execute o comando:
    ```bash
    mingw32-make
    ```
    Isso irá compilar todos os arquivos fonte e criar o executável `main.exe` dentro da pasta `bin/`.

2.  **Compilar e executar:**
    Para compilar e iniciar o programa diretamente, use:
    ```bash
    mingw32-make run
    ```

3.  **Limpar arquivos gerados:**
    Para remover a pasta `bin/` e todos os arquivos compilados, execute:
    ```bash
    mingw32-make clean
    ```

## Autores

*   **Anderson Carlos da Silva Morais**
*   **Marilia Fonseca**