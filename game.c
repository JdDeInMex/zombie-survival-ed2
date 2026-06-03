#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "game.h"
#include "zombie.h"
#include "player.h"
#include "interface.h"

void iniciarWave(Fila *f, int wave) {
    int qtdZumbis = wave * 2;
    for (int i = 0; i < qtdZumbis; i++) {
        if (wave == 1) {
            enqueueZombie(f, "WALKER", 30, 8);
        } else if (wave == 2) {
            if (i % 2 == 0) enqueueZombie(f, "RUNNER", 40, 12);
            else enqueueZombie(f, "WALKER", 30, 8);
        } else {
            if (i == 0) enqueueZombie(f, "TANK", 80, 20);
            else enqueueZombie(f, "RUNNER", 40, 12);
        }
    }
}

void loopJogo() {
    Player jogador;
    inicializarPlayer(&jogador);
    
    Fila filaZumbis;
    inicializarFila(&filaZumbis);
    
    int waveAtual = 1;
    bool jogando = true;
    
    mostrarMenu();
    
    while (jogando) {
        limparTerminal();
        iniciarWave(&filaZumbis, waveAtual);
        mostrarAnimacao("Zumbis se aproximando");
        
        // Todo zumbi novo começa a 4 casas de distância
        int distancia = 4; 
        
        while (!filaVazia(&filaZumbis) && jogador.hp > 0) {
            Zombie *zumbiAtual = filaZumbis.inicio;
            
            // Exibe a distância atual no painel
            printf("\n--- DISTANCIA DO ZUMBI: %d casas ---\n", distancia);
            mostrarHUD(&jogador, zumbiAtual, waveAtual);
            int opcao = obterEscolhaMenu();
            
            int avancoZombie = 1; // Padrão para Walker e Tank
            if (strcmp(zumbiAtual->nome, "RUNNER") == 0) {
                avancoZombie = 2; // Runner corre 2 casas por turno!
            }

            if (opcao == 1) { // ATACAR
                atacarZombie(&jogador, zumbiAtual);
                limparTerminal();
                
                // O zumbi avança após o tiro
                distancia -= avancoZombie;
                
                if (zumbiAtual->hp <= 0) {
                    mostrarAnimacao("ZUMBI ELIMINADO");
                    dequeueZombie(&filaZumbis);
                    jogador.kills++;
                    distancia = 4; // Reseta a distância para o próximo zumbi da fila
                }
            } 
            else if (opcao == 2) { // RECARREGAR
                limparTerminal();
                recarregar(&jogador);
                // O zumbi avança enquanto você recarrega
                distancia -= avancoZombie;
            } 
            else if (opcao == 3) { // FUGIR (RECUAR)
                limparTerminal();
                printf("\n[>] Voce correu para tras! (+2 casas)\n");
                distancia += 2; 
                // O zumbi continua correndo atrás de você
                distancia -= avancoZombie;
            }

            // Garante que a distância não fique negativa
            if (distancia < 0) distancia = 0;
            
            // REGRA DE DANO: O zumbi só morde se colou no jogador (distancia == 0)
            if (!filaVazia(&filaZumbis) && jogador.hp > 0 && distancia == 0 && zumbiAtual->hp > 0) {
                receberDano(&jogador, zumbiAtual->dano);
                printf("\n[!] O %s colou em voce e te causou %d de dano!\n", zumbiAtual->nome, zumbiAtual->dano);
                
                // Se ele atacou e colou, na próxima rodada ele continua ali colado (distancia 0)
                // a menos que o jogador use a opção Fugir para se afastar.
            }
        }
        
        if (jogador.hp <= 0) {
            mostrarGameOver(jogador.kills);
            jogando = false;
        } else {
            waveAtual++;
            mostrarAnimacao("WAVE CONCLUIDA! PROXIMA ONDA CHEGANDO");
        }
    }
}