#ifndef PLAYER_H
#define PLAYER_H

#include "zombie.h"

typedef struct {
    int hp;
    int hpMax;
    int balas;
    int balasMax;
    int kills;
    int dano;
} Player;

void inicializarPlayer(Player *p);
void atacarZombie(Player *p, Zombie *z);
void recarregar(Player *p);
void receberDano(Player *p, int dano);

#endif