#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LIVROS 100
#define TAM_TITULO 100
#define FILENAME "biblioteca.dat"

// Estrutura para representar um livro
typedef struct {
    int id;
    char titulo[TAM_TITULO];
    char autor[TAM_TITULO];
    int ano;
} Livro;

Livro biblioteca[MAX_LIVROS]; // Array de livros
int contador_livros = 0; // Contador de livros na biblioteca

// Função para carregar os dados do arquivo
void carregarDados() {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        printf("Nenhum dado anterior encontrado. Iniciando nova biblioteca.\n");
        return;
    }

    fread(&contador_livros, sizeof(int), 1, file);
    fread(biblioteca, sizeof(Livro), contador_livros, file);

    fclose(file);
}

// Função para salvar os dados no arquivo
void salvarDados() {
    FILE *file = fopen(FILENAME, "wb");
    if (file == NULL) {
        printf("Erro ao salvar os dados!\n");
        return;
    }

    fwrite(&contador_livros, sizeof(int), 1, file);
    fwrite(biblioteca, sizeof(Livro), contador_livros, file);

    fclose(file);
}

// Função para adicionar um livro à biblioteca
void adicionarLivro() {
    if (contador_livros >= MAX_LIVROS) {
        printf("A biblioteca está cheia!\n");
        return;
    }

    Livro novoLivro;
    novoLivro.id = contador_livros + 1;

    printf("Digite o título do livro: ");
    fgets(novoLivro.titulo, TAM_TITULO, stdin);
    novoLivro.titulo[strcspn(novoLivro.titulo, "\n")] = '\0';

    printf("Digite o autor do livro: ");
    fgets(novoLivro.autor, TAM_TITULO, stdin);
    novoLivro.autor[strcspn(novoLivro.autor, "\n")] = '\0';

    printf("Digite o ano do livro: ");
    scanf("%d", &novoLivro.ano);
    getchar(); // Limpar o buffer do teclado

    biblioteca[contador_livros] = novoLivro;
    contador_livros++;

    salvarDados(); // Salvar dados após adicionar um livro

    printf("Livro adicionado com sucesso!\n");
}

// Função para listar todos os livros da biblioteca
void listarLivros() {
    if (contador_livros == 0) {
        printf("A biblioteca está vazia!\n");
        return;
    }

    printf("Lista de Livros:\n");
    for (int i = 0; i < contador_livros; i++) {
        printf("ID: %d\n", biblioteca[i].id);
        printf("Título: %s\n", biblioteca[i].titulo);
        printf("Autor: %s\n", biblioteca[i].autor);
        printf("Ano: %d\n", biblioteca[i].ano);
        printf("\n");
    }
}

// Função para buscar um livro pelo título
void buscarLivroPorTitulo() {
    char titulo[TAM_TITULO];
    printf("Digite o título do livro a ser buscado: ");
    fgets(titulo, TAM_TITULO, stdin);
    titulo[strcspn(titulo, "\n")] = '\0';

    for (int i = 0; i < contador_livros; i++) {
        if (strcmp(biblioteca[i].titulo, titulo) == 0) {
            printf("Livro encontrado!\n");
            printf("ID: %d\n", biblioteca[i].id);
            printf("Título: %s\n", biblioteca[i].titulo);
            printf("Autor: %s\n", biblioteca[i].autor);
            printf("Ano: %d\n", biblioteca[i].ano);
            return;
        }
    }

    printf("Livro não encontrado!\n");
}

// Função para remover um livro pelo ID
void removerLivroPorId() {
    int id;
    printf("Digite o ID do livro a ser removido: ");
    scanf("%d", &id);
    getchar(); // Limpar o buffer do teclado

    for (int i = 0; i < contador_livros; i++) {
        if (biblioteca[i].id == id) {
            for (int j = i; j < contador_livros - 1; j++) {
                biblioteca[j] = biblioteca[j + 1];
            }
            contador_livros--;
            salvarDados(); // Salvar dados após remover um livro
            printf("Livro removido com sucesso!\n");
            return;
        }
    }

    printf("Livro não encontrado!\n");
}

// Função para atualizar as informações de um livro pelo ID
void atualizarLivroPorId() {
    int id;
    printf("Digite o ID do livro a ser atualizado: ");
    scanf("%d", &id);
    getchar(); // Limpar o buffer do teclado

    for (int i = 0; i < contador_livros; i++) {
        if (biblioteca[i].id == id) {
            printf("Digite o novo título do livro: ");
            fgets(biblioteca[i].titulo, TAM_TITULO, stdin);
            biblioteca[i].titulo[strcspn(biblioteca[i].titulo, "\n")] = '\0';

            printf("Digite o novo autor do livro: ");
            fgets(biblioteca[i].autor, TAM_TITULO, stdin);
            biblioteca[i].autor[strcspn(biblioteca[i].autor, "\n")] = '\0';

            printf("Digite o novo ano do livro: ");
            scanf("%d", &biblioteca[i].ano);
            getchar(); // Limpar o buffer do teclado

            salvarDados(); // Salvar dados após atualizar um livro
            printf("Livro atualizado com sucesso!\n");
            return;
        }
    }

    printf("Livro não encontrado!\n");
}

// Função principal que exibe o menu e chama as funções apropriadas
int main() {
    carregarDados(); // Carregar dados ao iniciar o programa

    int opcao;

    do {
        printf("Bem-vindo à Biblioteca\n");
        printf("1. Adicionar Livro\n");
        printf("2. Listar Livros\n");
        printf("3. Buscar Livro por Título\n");
        printf("4. Remover Livro por ID\n");
        printf("5. Atualizar Livro por ID\n");
        printf("6. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar(); // Limpar o buffer do teclado

        switch (opcao) {
            case 1:
                adicionarLivro();
                break;
            case 2:
                listarLivros();
                break;
            case 3:
                buscarLivroPorTitulo();
                break;
            case 4:
                removerLivroPorId();
                break;
            case 5:
                atualizarLivroPorId();
                break;
            case 6:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 6);

    return 0;
}
