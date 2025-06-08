#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Back.h"

int main() {
    Sala salas[MAX_SALAS];
    int total_salas = carregar_salas(salas, "salas.txt");
    if (total_salas == 0) {
        printf("Erro ao carregar salas.\n");
        return 1;
    }

    int salaAtual = 0;
    char resposta[100];
    char comando;

    mostrar_sala(salas, salaAtual);

    while (1) {
        printf("\nComandos: o=olhar, p=pegar, u=usar, m=mover, i=inventario, q=sair\n");
        printf("> ");
        scanf("%s", resposta);
        comando = tolower(resposta[0]);

        if (comando == 'q') {
            printf("Saindo do jogo...\n");
            break;
        }

        executar_comando(comando, salas, &salaAtual);
    }

    return 0;
}
