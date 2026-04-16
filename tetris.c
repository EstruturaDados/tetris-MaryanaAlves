#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char nome[30];
    int idade;
} Pessoa;

#define MAX 5

//Cria uma fila para armazenar as informacoes adicionadas
typedef struct {
    Pessoa itens[MAX];
    int inicio;
    int fim;
    int total;
} Fila;

// Inicializa a fila zerando os indices
void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->total = 0;
}

//Retorna true se estiver cheia
int filaCheia(Fila *f) {
    return f->total == MAX;
}

//retorna true se estiver vazia
int filaVazia(Fila *f){
    return f->total == 0;
}

//Insere uma nova pessoa na fila caso nao esteja cheia
void inserir(Fila *f, Pessoa p) {
    if(filaCheia(f)) {
        printf("Fila cheia. Não é possível inserir.\n");
        return;
    }

    f->itens[f->fim] = p;
    //Avança o fim da fila de forma circular
    f->fim = (f->fim + 1) % MAX;
    f->total++;
}

//Remove uma pessoa caso exista alguem na fila
void remover(Fila *f, Pessoa *p) {
    if (filaVazia(f)) {
        printf("Fila vazia. Não é possível remover.\n");
        return;
    }

    *p = f->itens[f->inicio];
    //Avança o início da fila de forma circular
    f->inicio = (f->inicio + 1) % MAX;
    f->total--;
}

//Exibe a fila 
void mostrarFila(Fila *f) {
    printf("Fila: ");

    for (int i = 0, idx = f->inicio; i < f->total; i++, idx = (idx + 1) % MAX) {
        printf("[%s, %d] ", f->itens[idx].nome, f->itens[idx].idade);
    }

    printf("\n");
}

int main() {
    Fila f;
    inicializarFila(&f);

    //Adiciona pessoas para inserir posteriormente
    Pessoa p1 = {"João", 25};
    Pessoa p2 = {"Maria", 30};
    Pessoa p3 = {"Luiza", 32};
    
    inserir(&f, p1);
    inserir(&f, p2);

    mostrarFila(&f);

    //Remove a primeira pessoa da fila (FIFO)
    Pessoa removida;
    remover(&f, &removida);
    printf("Pessoa removida: %s, %d\n", removida.nome, removida.idade);
    remover(&f, &removida);

    mostrarFila(&f);

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
