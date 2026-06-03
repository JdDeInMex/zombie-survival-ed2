#ifndef INTERFACE_H
#define INTERFACE_H

#include "player.h"
#include "zombie.h"

void limparTerminal();
void mostrarMenu();
void mostrarBarra(int atual, int max);
void mostrarHUD(Player *p, Zombie *z, int wave);
int obterEscolhaMenu();
void mostrarGameOver(int kills);
void mostrarAnimacao(char *texto);

#endif