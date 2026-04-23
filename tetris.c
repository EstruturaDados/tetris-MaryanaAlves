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

int contadorID = 0;

typedef struct{
    Peca pecas[MAX];
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
Peca gerarPecaFila(){
    Peca p;
    char tipos[] = {'I', 'O', 'T', 'L'};

    int indice = rand() % 4;

    p.nome = tipos[indice];
    p.id = contadorID++;

    return p;
}

Peca gerarPecaPilha(){
    Peca p;
    char tipos[] = {'I', 'O', 'T', 'L'};

    int indice = rand() % 3;

    p.nome = tipos[indice];
    p.id = contadorID++;

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

    Peca nova = gerarPecaFila();

    f->pecas[f->fim] = nova;
    f->fim = (f->fim + 1) % MAX;
    f->total++;

    printf("Peca inserida Fila: [%c %d]\n", nova.nome, nova.id);
}

//insere uma peça no topo da pilha (LIFO)
void inserirPilha(Pilha *p, Peca nova) {
    if (pilhaCheia(p)) {
        printf("Pilha cheia. Nao foi possivel inserir");
        return;
    }

    p->topo++;
    p->pecas[p->topo] = nova;

    printf("Peca inserida Pilha: [%c %d]\n", nova.nome, nova.id);
}

void trocarPeca(Fila *f, Pilha *p) {
    if (filaVazia(f)) {
        printf("Fila vazia. Nao e possivel trocar.\n");
        return;
    }

    if (pilhaVazia(p)) {
        printf("Pilha vazia. Nao e possivel trocar.\n");
        return;
    }

    Peca filaFrente = f->pecas[f->inicio];

    Peca pilhaTopo = p->pecas[p->topo];

    f->pecas[f->inicio] = pilhaTopo;

    p->pecas[p->topo] = filaFrente;

    printf("Fila recebeu: [%c %d]\n", pilhaTopo.nome, pilhaTopo.id);
    printf("Pilha recebeu: [%c %d]\n", filaFrente.nome, filaFrente.id);
}

void trocaMultipla(Fila *f, Pilha *p) {
    if (f->total < 3) {
        printf("Fila nao tem 3 pecas.\n");
        return;
    }

    if (p->topo < 2) {
        printf("Pilha nao tem 3 pecas.\n");
        return;
    }

    for (int i = 0; i < 3; i++) {

        int idxFila = (f->inicio + i) % MAX;
        int idxPilha = p->topo - i;

        Peca temp = f->pecas[idxFila];

        f->pecas[idxFila] = p->pecas[idxPilha];
        p->pecas[idxPilha] = temp;
    }

    printf("Troca multipla realizada!\n");
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

    for(int i = 0; i < MAX; i++) {
        inserirFila(&f);
    }

    for(int i = 0; i < LIM; i++) {
        Peca nova = gerarPecaPilha();
        inserirPilha(&p, nova);
    }

    do {
        printf("----------------------------------------------------\n");
        mostrarFila(&f);
        mostrarPilha(&p);

        printf("\n-------- MENU --------\n");
        printf("1. Jogar peca da frente da fila\n");
        printf("2. Enviar peca da fila para a pilha de reserva\n");
        printf("3. Usar peca da pilha de reserva\n");
        printf("4. Trocar peca da frente da fila com o topo da pilha\n");
        printf("5. Trocar os 3 primeiros da fila com as 3 pecas da pilha\n");
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
            case 4:
                trocarPeca(&f, &p);
                printf("Pressione enter para continuar!\n");
                getchar();
                break;
            case 5:
                trocaMultipla(&f, &p);
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

    } while (opcao != 0);

    return 0;
}
