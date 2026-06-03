#ifndef ZOMBIE_H
#define ZOMBIE_H

typedef struct Zombie {
    char nome[30];
    int hp;
    int hpMax;
    int dano;
    struct Zombie *prox;
} Zombie;

typedef struct {
    Zombie *inicio;
    Zombie *fim;
} Fila;

void inicializarFila(Fila *f);
int filaVazia(Fila *f);
void enqueueZombie(Fila *f, char *nome, int hp, int dano);
void dequeueZombie(Fila *f);

#endif