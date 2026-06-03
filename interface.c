#include <stdio.h>
#include <stdlib.h>
#include "interface.h"

void limparTerminal() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void mostrarMenu() {
    limparTerminal();
    printf("===================================\n");
    printf("        ZOMBIE SURVIVAL - ED2      \n");
    printf("===================================\n");
    printf("Presione ENTER para comecar...\n");
    getchar();
}

void mostrarBarra(int atual, int max) {
    int tamanhoBarra = 10; 
    // Calcula quantos palitinhos mostrar baseado na proporção da vida
    int preenchimento = (atual * tamanhoBarra) / max;
    
    printf("|");
    for (int i = 0; i < tamanhoBarra; i++) {
        if (i < preenchimento) printf("|");
        else printf(" ");
    }
    printf("| %d/%d\n", atual, max);
}

void mostrarHUD(Player *p, Zombie *z, int wave) {
    printf("\n===================================\n");
    printf("              WAVE %d              \n", wave);
    printf("===================================\n");
    
    // Alerta Fixo no Topo se o pente estiver zerado
    if (p->balas == 0) {
        printf(" [!] SEM BALAS! VOCE PRECISA RECARREGAR [!]\n");
        printf("-----------------------------------\n");
    }
    
    printf("Player HP:   ");
    mostrarBarra(p->hp, p->hpMax);
    printf("Balas: %d/%d\n", p->balas, p->balasMax);
    printf("Kills: %d\n", p->kills);
    printf("-----------------------------------\n");
    
    if (z != NULL) {
        printf("Zombie Actual: %s\n", z->nome);
        printf("Zombie HP:   ");
        mostrarBarra(z->hp, z->hpMax);
    }
    printf("-----------------------------------\n");
    printf("1 - Atacar\n");
    printf("2 - Recarregar\n");
    printf("3 - Fugir/Recuar\n");
    printf("Escolha: ");
}

int obterEscolhaMenu() {
    int opcao;
    scanf("%d", &opcao);
    return opcao;
}

void mostrarGameOver(int kills) {
    limparTerminal();
    printf("===================================\n");
    printf("             GAME OVER             \n");
    printf("===================================\n");
    printf(" Voce sobreviveu ate onde deu!\n");
    printf(" Total de Zumbis Mortos: %d\n", kills);
    printf("===================================\n");
    printf("\nDeseja jogar novamente?\n");
    printf("1 - Sim, quero revanche!\n");
    printf("0 - Nao, sair do jogo\n");
    printf("Escolha: ");
}

void mostrarAnimacao(char *texto) {
    printf("\n... %s ...\n", texto);
}