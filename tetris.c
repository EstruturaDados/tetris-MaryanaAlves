// Simulação de jogo utilizando Fila (FIFO) e Pilha (LIFO)
// A fila representa as peças disponíveis para jogo
// A pilha representa as peças reservadas pelo jogador
// A cada ação, uma nova peça é gerada mantendo a fila sempre cheia

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
    char nome;
    int id;
} Peca;

#define MAX 5
#define LIM 3

typedef struct{
    Peca pecas[MAX];
    int contadorID;
    int inicio;
    int fim;
    int total;
} Fila;

typedef struct{
    Peca pecas[LIM];
    int topo;
} Pilha;

void inserirFila(Fila *f);
void inserirPilha(Pilha *p, Peca nova);
void jogarPecaFila(Fila *f, Peca *p);
void jogarReservadaPilha(Pilha *p, Peca *removida);
void reservarPecaPilha(Fila *f, Pilha *p);
int removerPecaFila(Fila *f, Peca *p);

//inicializa a pilha como vazia
void inicializarPilha(Pilha *p) {
    p->topo = -1;
}

//inicializa a fila zerando índices
void inicializarFila(Fila *f){
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
    f->contadorID = 0;
}

//verifica se a fila está cheia
int filaCheia(Fila *f){
    return f->total == MAX;
}

//verifica se a pilha está cheia
int pilhaCheia(Pilha *p) {
    return p->topo == LIM - 1;
}

//verifica se a fila está vazia
int filaVazia(Fila *f){
    return f->total == 0;
}

//verifica se a pilha está vazia
int pilhaVazia(Pilha *p) {
    return p->topo == -1;
}

//gera novas peças com tipos aleatórios e ID
Peca gerarPecaFila(Fila *f){
    Peca p;
    char tipos[] = {'I', 'O', 'T', 'L'};

    int indice = rand() % 4;

    p.nome = tipos[indice];
    p.id = f->contadorID++;

    return p;
}

//remove a peça do início da fila 
int removerPecaFila(Fila *f, Peca *p){
    if (filaVazia(f)) {
        return 0;
    }
    *p = f->pecas[f->inicio];

    // Atualiza o índice
    f->inicio = (f->inicio + 1) % MAX;
    f->total--;

    return 1;
}

//remove a peça da fila, exibe na tela e gera uma nova peça
void jogarPecaFila(Fila *f, Peca *p){
    if (filaVazia(f)) {
        printf("Sem pecas disponiveis. Nao e possivel jogar.\n");
        return;
    }

    removerPecaFila(f, p);

    printf("Peca jogada: [%c %d]\n", p->nome, p->id);

    inserirFila(f);
}

//remove a peça do topo da pilha e exibe 
void jogarReservadaPilha(Pilha *p, Peca *removida){
    if (pilhaVazia(p)) {
        printf("Pilha vazia. Nao e possivel jogar peca reservada");
        return;
    }

    *removida = p->pecas[p->topo];
    printf("Peca jogada: [%c %d]\n", removida->nome, removida->id);
    p->topo--;
}

//move a peça da frente da fila para o topo da pilha
void reservarPecaPilha(Fila *f, Pilha *p) {
    if(filaVazia(f)) {
        printf("Fila vazia. Nada para reservar\n");
        return;
    }
    if(pilhaCheia(p)) {
        printf("Pilha cheia. Nao e possivel reservar\n");
        return;
    }

    Peca temp;

    removerPecaFila(f, &temp);

    inserirPilha(p, temp);

    printf("Peca [%c %d] foi para a pilha\n", temp.nome, temp.id);

    inserirFila(f);
}

//insere uma nova peça no final da fila (FIFO)
void inserirFila(Fila *f){
    if (filaCheia(f)) {
        printf("Fila cheia. Nao e possivel inserir nova peca.\n");
        return;
    }

    Peca nova = gerarPecaFila(f);

    f->pecas[f->fim] = nova;
    f->fim = (f->fim + 1) % MAX;
    f->total++;

    printf("Peca inserida: [%c %d]\n", nova.nome, nova.id);
}

//insere uma peça no topo da pilha (LIFO)
void inserirPilha(Pilha *p, Peca nova) {
    if (pilhaCheia(p)) {
        printf("Pilha cheia. Nao foi possivel inserir");
        return;
    }

    p->topo++;
    p->pecas[p->topo] = nova;
}

//exibe todas as peças da fila 
void mostrarFila(Fila *f){
    printf("Pecas: ");

    for(int i=0, idc = f->inicio; i < f->total; i++, idc = (idc + 1) % MAX) {
        printf("[%c %d] ", f->pecas[idc].nome, f->pecas[idc].id);
    }

    printf("\n");
}

//exibe as peças da pilha do topo até a base
void mostrarPilha(Pilha *p){
    printf("Pilha (topo -> base):");
    for(int i = p->topo; i >= 0; i--){
        printf("[%c %d] ", p->pecas[i].nome, p->pecas[i].id);
    }
    printf("\n");
}

//limpa o buffer de entrada para evitar problemas com scanf/getchar
void limparBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    srand((unsigned int) time(NULL));

    Fila f;
    Pilha p;
    int opcao;
    Peca removida;

    inicializarFila(&f);
    inicializarPilha(&p);

    for(int i=0; i<MAX; i++) {
        inserirFila(&f);
    }

    mostrarFila(&f);
    mostrarPilha(&p);

    do {
        printf("\n-------- MENU --------\n");
        printf("1. Jogar peca\n");
        printf("2. Reservar peca\n");
        printf("3. Jogar peca reservada\n");
        printf("0. Sair\n");
        printf("\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        printf("\n");

        switch(opcao){
            case 1:
                jogarPecaFila(&f, &removida);
                printf("Pressione enter para continuar!\n");
                getchar();
                break;
            case 2:
                reservarPecaPilha(&f, &p);
                printf("Pressione enter para continuar!\n");
                getchar();
                break;
            case 3:
                jogarReservadaPilha(&p, &removida);
                printf("Pressione enter para continuar!\n");
                getchar();
                break;
            case 0:
                printf("Encerrando programa...\n");
                break;
            default: 
                printf("Opcao invalida, pressione enter para tentar novamente!\n");
                getchar();
                break;
        }

        mostrarFila(&f);
        mostrarPilha(&p);

    } while (opcao != 0);

    return 0;
}


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
