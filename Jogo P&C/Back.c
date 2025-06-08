#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Back.h"

char inventario[MAX_ITENS][TAM_NOME];
int total_itens = 0;

void limpar_tela(){
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif // _WIN32
}

int carregar_salas(Sala salas[], const char *arquivo) {
    FILE *fp = fopen(arquivo, "r");
    if (!fp) return 0;

    int i = 0;
    char linha[512];
    while (fgets(linha, sizeof(linha), fp) && i < MAX_SALAS) {
        char *nome = strtok(linha, ":");
        char *descricao = strtok(NULL, ":");
        char *item = strtok(NULL, ":");
        char *norte = strtok(NULL, ":");
        char *sul = strtok(NULL, ":");
        char *leste = strtok(NULL, ":");
        char *oeste = strtok(NULL, ":");
        char *item_necessario = strtok(NULL, ":");
        char *efeito = strtok(NULL, "\n");

        if (nome && descricao && item && norte && sul && leste && oeste) {
            strncpy(salas[i].nome, nome, TAM_NOME);
            strncpy(salas[i].descricao, descricao, TAM_DESC);
            strncpy(salas[i].item, item, TAM_NOME);
            strncpy(salas[i].item_necessario, item_necessario, TAM_NOME);
            salas[i].efeito_ativado = atoi(efeito);
            salas[i].item_coletado = 0;
            salas[i].sala_norte = atoi(norte);
            salas[i].sala_sul = atoi(sul);
            salas[i].sala_leste = atoi(leste);
            salas[i].sala_oeste = atoi(oeste);
            i++;
        }
    }
    fclose(fp);
    return i;
}

void mostrar_sala(Sala salas[], int index) {
    printf("\n[%s]\n%s\n", salas[index].nome, salas[index].descricao);
    if (!salas[index].item_coletado && strcmp(salas[index].item, "nada") != 0) {
        printf("Você vê algo aqui: %s\n", salas[index].item);
    }
}

void olhar(Sala salas[], int salaAtual) {
    limpar_tela();
    mostrar_sala(salas, salaAtual);
}

void pegar(Sala salas[], int salaAtual) {
    limpar_tela();
    if (salas[salaAtual].item_coletado || strcmp(salas[salaAtual].item, "nada") == 0) {
        printf("Não há nada para pegar aqui.\n");
        return;
    }
    if (total_itens >= MAX_ITENS) {
        printf("Seu inventário está cheio!\n");
        return;
    }
    strncpy(inventario[total_itens], salas[salaAtual].item, TAM_NOME);
    total_itens++;
    salas[salaAtual].item_coletado = 1;
    printf("Você pegou: %s\n", salas[salaAtual].item);
}

void ver_inventario() {
    limpar_tela();
    printf("\nInventário:\n");
    if (total_itens == 0) {
        printf("(vazio)\n");
        return;
    }
    for (int i = 0; i < total_itens; i++) {
        printf("- %s\n", inventario[i]);
    }
}

int tem_item(const char *item) {
    for (int i = 0; i < total_itens; i++) {
        if (strcmp(inventario[i], item) == 0) return 1;
    }
    return 0;
}

void usar_item(Sala salas[], int salaAtual) {
    limpar_tela();

    if (salas[salaAtual].efeito_ativado) {
        printf("Nada a fazer aqui, você já usou o item.\n");
        return;
    }

    if (strcmp(salas[salaAtual].item_necessario, "nada") == 0) {
        printf("Nada para usar aqui...\n");
        return;
    }

    if (tem_item(salas[salaAtual].item_necessario)) {
        printf("Você usou o item: %s\n", salas[salaAtual].item_necessario);
        salas[salaAtual].efeito_ativado = 1;

        if (strcmp(salas[salaAtual].nome, "Cozinha") == 0) {
            salas[salaAtual].sala_leste = 3;
            printf("Você destrancou uma porta para o leste!\n");
        }

        if (strcmp(salas[salaAtual].nome, "Corredor Escuro") == 0) {
            salas[salaAtual].sala_norte = 5;
            printf("Você agora consegue enxergar! Você vê uma sala ao norte\n");
        }

        if (strcmp(salas[salaAtual].nome, "Sala do Cofre") == 0) {
            printf("Incríveis tesouros estão aqui. Você venceu!\n");
            return 0;
        }

    } else {
        printf("Você não tem o item necessário: %s\n", salas[salaAtual].item_necessario);
    }
}


void mover(Sala salas[], int *salaAtual, char direcao) {
    int novaSala = -1;
    switch (direcao) {
        case 'n': novaSala = salas[*salaAtual].sala_norte; break;
        case 's': novaSala = salas[*salaAtual].sala_sul; break;
        case 'l': novaSala = salas[*salaAtual].sala_leste; break;
        case 'o': novaSala = salas[*salaAtual].sala_oeste; break;
        default: printf("Direção inválida!\\n"); return;
    }

    if (novaSala != -1) {
        *salaAtual = novaSala;
        printf("Você se moveu para a sala: %s\ \n", salas[*salaAtual].nome);
    } else {
        printf("Não há caminho nessa direção!\\n");
    }
}


void executar_comando(char comando, Sala salas[], int *salaAtual) {
    switch (comando) {
        case 'o': olhar(salas, *salaAtual); break;
        case 'p': pegar(salas, *salaAtual); break;
        case 'u': usar_item(salas, *salaAtual); break;
        case 'm':
            printf("Para onde deseja ir? (norte, sul, leste, oeste): ");
            char direcao;
            scanf(" %c", &direcao);
            mover(salas, salaAtual, direcao);
            break;
        case 'i': ver_inventario(); break;
        default:
            limpar_tela();
            printf("Comando inválido.\n");
    }
}
