from classes import *

def selecionar_jogo():
    print("===== ESCOLHA O JOGO =====")
    print("\n1 - Project Emerald\n")
    print("2 - Jogo da praia\n")
    print("3 - Jogo da Escola\n")
    escolha = int(input('Qual jogo deseja jogar? \n').strip())
    if escolha == 1:
        return "pjemerald.xlsx"
    elif escolha == 2:
        return "jogo_praia.xlsx"
    elif escolha == 3:
        return "jogo_escola.xlsx"
    else:
        print("Número indisponível, carregando jogo base Project Emerald...\n")
        return "pjemerald.xlsx"


if __name__ == '__main__':
    arquivo_escolhido = selecionar_jogo()
    c = Cenario(arquivo_escolhido)
    i = Item(arquivo_escolhido)
    jogo = Comando(c, i)

    nome = input("Digite o nome do personagem: ")
    jogador1 = Jogador(nome)
    
    print(f"Carregando {arquivo_escolhido}\n")
    
    jogo.ler_eventos(1)
    
    while True:
        jogo.jogar()
    