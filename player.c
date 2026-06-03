#include <stdio.h>
#include "player.h"
#include "zombie.h"

void inicializarPlayer(Player *p) {
    p->hp = 100;
    p->hpMax = 100;
    p->balas = 6;
    p->balasMax = 6;
    p->kills = 0;
    p->dano = 20;
}

void atacarZombie(Player *p, Zombie *z) {
    if (p->balas > 0) {
        p->balas--;
        z->hp -= p->dano;
        if (z->hp < 0) z->hp = 0;
    } else {
        printf("\nSem balas! Recarregue!\n");
    }
}

void recarregar(Player *p) {
    p->balas = p->balasMax;
    printf("\nArma recarregada!\n");
}

void receberDano(Player *p, int dano) {
    p->hp -= dano;
    if (p->hp < 0) p->hp = 0;
}