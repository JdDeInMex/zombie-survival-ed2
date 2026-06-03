#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "zombie.h"

void inicializarFila(Fila *f) {
    f->inicio = NULL;
    f->fim = NULL;
}

int filaVazia(Fila *f) {
    return (f->inicio == NULL);
}

void enqueueZombie(Fila *f, char *nome, int hp, int dano) {
    Zombie *novo = (Zombie*) malloc(sizeof(Zombie));
    if (novo == NULL) return;
    
    strcpy(novo->nome, nome);
    novo->hp = hp;
    novo->hpMax = hp;
    novo->dano = dano;
    novo->prox = NULL;
    
    if (filaVazia(f)) {
        f->inicio = novo;
        f->fim = novo;
    } else {
        f->fim->prox = novo;
        f->fim = novo;
    }
}

void dequeueZombie(Fila *f) {
    if (filaVazia(f)) return;
    
    Zombie *aux = f->inicio;
    f->inicio = f->inicio->prox;
    
    if (f->inicio == NULL) {
        f->fim = NULL;
    }
    
    free(aux); // Libera memória em ED2
}