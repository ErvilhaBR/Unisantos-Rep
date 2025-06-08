#ifndef BACK_H
#define BACK_H

#define MAX_SALAS 10
#define TAM_NOME 30
#define TAM_DESC 200
#define MAX_ITENS 10

typedef struct {
    char nome[TAM_NOME];
    char descricao[TAM_DESC];
    char item[TAM_NOME];
    int item_coletado;
    int sala_norte;
    int sala_sul;
    int sala_leste;
    int sala_oeste;

    char item_necessario[TAM_NOME];
    int efeito_ativado;
} Sala;

extern char inventario[MAX_ITENS][TAM_NOME];
extern int total_itens;

int carregar_salas(Sala salas[], const char *arquivo);
void mostrar_sala(Sala salas[], int index);
void executar_comando(char comando, Sala salas[], int *salaAtual);
void olhar(Sala salas[], int salaAtual);
void pegar(Sala salas[], int salaAtual);
void ver_inventario();
void usar_item(Sala salas[], int salaAtual);
int tem_item(const char *item);

#endif
