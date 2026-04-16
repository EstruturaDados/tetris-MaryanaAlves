#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
    char nome;
    int id;
} Peca;

#define MAX 5

typedef struct{
    Peca pecas[MAX];
    int contadorID;
    int inicio;
    int fim;
    int total;
} Fila;

void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
    f->contadorID = 0;
}

int filaCheia(Fila *f) {
    return f->total == MAX;
}

int filaVazia(Fila *f) {
    return f->total == 0;
}

Peca gerarPeca(Fila *f) {
    Peca p;
    char tipos[] = {'I', 'O', 'T', 'L'};

    int indice = rand() % 4;

    p.nome = tipos[indice];
    p.id = f->contadorID++;

    return p;
}

void jogarPeca(Fila *f, Peca *p) {
    if (filaVazia(f)) {
        printf("Sem pecas disponiveis. Nao e possivel jogar.\n");
        return;
    }

    *p = f->pecas[f->inicio];

    printf("Peca jogada: [%c %d]\n", p->nome, p->id);

    f->inicio = (f->inicio + 1) % MAX;
    f->total--;
}

void inserirPeca(Fila *f) {
    if (filaCheia(f)) {
        printf("Fila cheia. Nao e possivel inserir nova peca.\n");
        return;
    }

    Peca nova = gerarPeca(f);

    f->pecas[f->fim] = nova;
    f->fim = (f->fim + 1) % MAX;
    f->total++;

    printf("Peca inserida: [%c %d]\n", nova.nome, nova.id);
}

void mostrarFila(Fila *f) {
    printf("Pecas: ");

    for(int i=0, idc = f->inicio; i < f->total; i++, idc = (idc + 1) % MAX) {
        printf("[%c %d] ", f->pecas[idc].nome, f->pecas[idc].id);
    }

    printf("\n");
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    srand((unsigned int) time(NULL));

    Fila f;
    int opcao;
    Peca removida;

    inicializarFila(&f);

    for(int i=0; i<MAX; i++) {
        inserirPeca(&f);
    }

    mostrarFila(&f);

    do {
        printf("\n-------- MENU --------\n");
        printf("1. Jogar peca\n");
        printf("2. Inserir nova peca\n");
        printf("0. Sair\n");
        printf("\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        printf("\n");

        if(opcao == 1) {
            jogarPeca(&f, &removida);
            printf("Pressione enter para continuar!\n");
            getchar();
        } else if (opcao == 2) {
            inserirPeca(&f);
            printf("Pressione enter para continuar!\n");
            getchar();
        } else if (opcao == 0) {
            printf("Encerrando programa...\n");
            break;
        } else {
            printf("Opcao invalida, pressione enter para tentar novamente!\n");
            getchar();
        } 

        mostrarFila(&f);

    } while (opcao != 0);

    return 0;
}

    // 🧠 Nível Aventureiro: Adição da Pilha de Reserva
    //
    // - Implemente uma pilha linear com capacidade para 3 peças.
    // - Crie funções como inicializarPilha(), push(), pop(), pilhaCheia(), pilhaVazia().
    // - Permita enviar uma peça da fila para a pilha (reserva).
    // - Crie um menu com opção:
    //      2 - Enviar peça da fila para a reserva (pilha)
    //      3 - Usar peça da reserva (remover do topo da pilha)
    // - Exiba a pilha junto com a fila após cada ação com mostrarPilha().
    // - Mantenha a fila sempre com 5 peças (repondo com gerarPeca()).


    // 🔄 Nível Mestre: Integração Estratégica entre Fila e Pilha
    //
    // - Implemente interações avançadas entre as estruturas:
    //      4 - Trocar a peça da frente da fila com o topo da pilha
    //      5 - Trocar os 3 primeiros da fila com as 3 peças da pilha
    // - Para a opção 4:
    //      Verifique se a fila não está vazia e a pilha tem ao menos 1 peça.
    //      Troque os elementos diretamente nos arrays.
    // - Para a opção 5:
    //      Verifique se a pilha tem exatamente 3 peças e a fila ao menos 3.
    //      Use a lógica de índice circular para acessar os primeiros da fila.
    // - Sempre valide as condições antes da troca e informe mensagens claras ao usuário.
    // - Use funções auxiliares, se quiser, para modularizar a lógica de troca.
    // - O menu deve ficar assim:
    //      4 - Trocar peça da frente com topo da pilha
    //      5 - Trocar 3 primeiros da fila com os 3 da pilha
