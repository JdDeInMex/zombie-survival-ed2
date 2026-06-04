#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "game.h"
#include "zombie.h"
#include "player.h"
#include "interface.h"

void iniciarWave(Fila *f, int wave) {
    // A horda cresce linearmente de forma infinita (ex: Wave 1 = 2 zumbis, Wave 5 = 10 zumbis)
    int qtdZumbis = wave * 2; 
    
    for (int i = 0; i < qtdZumbis; i++) {
        // Wave 1: Introdução suave para o jogador entender a mecânica de distância
        if (wave == 1) {
            enqueueZombie(f, "WALKER", 30, 8); 
        } 
        // Wave 2: Introdução do Runner para forçar o jogador a gerenciar o espaço
        else if (wave == 2) {
            if (i % 2 == 0) {
                enqueueZombie(f, "RUNNER", 40, 12);
            } else {
                enqueueZombie(f, "WALKER", 30, 8);
            }
        } 
        // Wave 3 em diante: Ondas infinitas com rotação cíclica perfeita de 3 estados
        else {
            if (i % 3 == 0) {
                enqueueZombie(f, "WALKER", 30, 8);   // Nó padrão (Avança 1)
            } else if (i % 3 == 1) {
                enqueueZombie(f, "RUNNER", 40, 12);  // Nó veloz (Avança 2)
            } else {
                enqueueZombie(f, "TANK", 80, 20);    // Nó massivo (Exige recuo + recarga)
            }
        }
    }
}
void loopJogo() {
    int continuarNoJogo = 1;

    // Esse loop gerencia se o jogador quer REINICIAR o game do zero
    while (continuarNoJogo == 1) {
        Player jogador;
        inicializarPlayer(&jogador);
        
        Fila filaZumbis;
        inicializarFila(&filaZumbis);
        
        int waveAtual = 1;
        bool rodandoWave = true;
        
        mostrarMenu();
        
        while (rodandoWave) {
            limparTerminal();
            iniciarWave(&filaZumbis, waveAtual);
            mostrarAnimacao("Zumbis se aproximando");
            
            int distancia = 4; 
            
            while (!filaVazia(&filaZumbis) && jogador.hp > 0) {
                Zombie *zumbiAtual = filaZumbis.inicio;
                
                printf("\n--- DISTANCIA DO ZUMBI: %d casas ---\n", distancia);
                mostrarHUD(&jogador, zumbiAtual, waveAtual);
                int opcao = obterEscolhaMenu();
                
                int avancoZombie = 1;
                if (strcmp(zumbiAtual->nome, "RUNNER") == 0) {
                    avancoZombie = 2;
                }

                if (opcao == 1) { // ATACAR
                    atacarZombie(&jogador, zumbiAtual);
                    limparTerminal();
                    
                    distancia -= avancoZombie;
                    
                    if (zumbiAtual->hp <= 0) {
                        mostrarAnimacao("ZUMBI ELIMINADO");
                        dequeueZombie(&filaZumbis);
                        jogador.kills++;
                        distancia = 4; 
                    }
                } 
                else if (opcao == 2) { // RECARREGAR
                    limparTerminal();
                    recarregar(&jogador);
                    distancia -= avancoZombie;
                } 
                else if (opcao == 3) { // FUGIR
                    limparTerminal();
                    printf("\n[>] Voce correu para tras! (+2 casas)\n");
                    distancia += 2; 
                    distancia -= avancoZombie;
                }

                if (distancia < 0) distancia = 0;
                
                if (!filaVazia(&filaZumbis) && jogador.hp > 0 && distancia == 0 && zumbiAtual->hp > 0) {
                    receberDano(&jogador, zumbiAtual->dano);
                    printf("\n[!] O %s colou em voce e te causou %d de dano!\n", zumbiAtual->nome, zumbiAtual->dano);
                }
            }
            
            // Se o jogador morreu, quebra o loop das waves para exibir a pontuação
            if (jogador.hp <= 0) {
                rodandoWave = false;
                
                // ED2: Limpa os zumbis restantes da fila para liberar memória antes do restart
                while (!filaVazia(&filaZumbis)) {
                    dequeueZombie(&filaZumbis);
                }
                
                // Exibe placar e captura a decisão do jogador (1 para recomeçar, 0 para sair)
                mostrarGameOver(jogador.kills);
                continuarNoJogo = obterEscolhaMenu();
            } else {
                waveAtual++;
                mostrarAnimacao("WAVE CONCLUIDA! PROXIMA ONDA CHEGANDO");
            }
        }
    }
    
    limparTerminal();
    printf("\nObrigado por jogar! Saindo...\n");
}