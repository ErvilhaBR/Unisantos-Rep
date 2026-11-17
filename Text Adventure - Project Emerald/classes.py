import openpyxl, sys
from pathlib import Path
from abc import ABC, abstractmethod

class Jogador:
    nome = str
    inventario = []

    def __init__(self, nome: str):
        self.__nome = nome
        self.inventario = []

class GameObject(ABC):
    def __init__(self, aba, nome_arquivo='pjemerald.xlsx'):
        caminho = Path(__file__).parent / nome_arquivo
        planilha = openpyxl.load_workbook(caminho)
        self.planilha = planilha[aba]

    def get_descricao(self, linha):
        return self.planilha[f'B{linha}']

    def get_nome(self, linha):
        return self.planilha[f'A{linha}']
        
class Cenario(GameObject):
    def __init__(self, nome_arquivo='pjemerald.xlsx'):
        super().__init__('Cenarios', nome_arquivo)
    
    def campo_visao(self, linha):
        return self.planilha[f'C{linha}']
    
    def eventos(self, linha):
        return self.planilha[f'D{linha}']
    
    def sala(self, linha):
        return self.planilha[f'E{linha}']

class Item(GameObject):
    def __init__(self, nome_arquivo='pjemerald.xlsx'):
        super().__init__('Itens', nome_arquivo)

class Acao_ler:
    def __init__(self, cenario: Cenario, item: Item):
        self.cenario = cenario
        self.item = item

    def ler_sala(self, linha):
        print("\n==============================")
        print(self.cenario.get_nome(linha).value)
        print("==============================")
        print(self.cenario.get_descricao(linha).value)
        print("==============================")

    def ler_nome(self, objeto, linha):
        print(objeto.get_nome(linha).value)

    def ler_descricao(self, objeto, linha):
        print(objeto.get_descricao(linha).value)

    def ler_cenario(self, linha):
        print(self.cenario.campo_visao(linha).value)

    def ler_eventos(self, linha):
        print(self.cenario.eventos(linha).value)
        
    def ler_numero_sala(self, linha):
        print(self.cenario.sala(linha).value)

class Comando(Acao_ler):
    def __init__(self, cenario, item):
        super().__init__(cenario, item)
    
        self.cenario_atual = 1
        self.salas_desbloqueadas = [1, 2, 3, 4]
        self.inventario_jogador = Jogador.inventario

    def jogar(self):
        comando = input("\nO que deseja fazer? ").lower().strip()

        if comando == "sair":
            print("Você encerrou o jogo.")
            sys.exit()

        elif comando == "olhar":
            self.ler_sala(self.cenario_atual)

        elif comando == "observar":
            self.ler_cenario(self.cenario_atual)
                
        elif comando == "inventario":
            self.interagir_inventario()

        elif comando == "ir para":
            linha = input("Para onde? (Digite o numero do [cenário]): ")
            self.trocar_sala(linha)

        elif comando == "ajuda":
            print("\n=== COMANDOS DISPONÍVEIS ===")
            print("olhar          - mostrar sala")
            print("observar       - olhar com detalhes")
            print("ir para        - ir para cenário disponível")
            print("inventario     - abrir inventario")
            print("ajuda          - mostrar os comandos")
            print("sair           - encerrar o jogo")
            
        else:
            raise Exception("Comando não reconhecido. Digite 'ajuda'.")
    
    def desbloquear_sala(self, linha):
        if linha not in self.salas_desbloqueadas:
            self.salas_desbloqueadas.append(linha)

    def trocar_sala(self, linha):
        linha = int(linha)
        
        if linha in self.salas_desbloqueadas:
            self.cenario_atual = linha
            self.ler_sala(linha)

        else:
            raise Exception("Você ainda não descobriu essa sala.")


    def interagir_inventario(self):
        while True:
            print("\n=== INVENTARIO ===")
            print("\n1 - Ver inventário")
            print("\n2 - Adicionar item")
            print("\n3 - Remover item")
            print("\n4 - Fechar inventario")

            opcao = input("Escolha uma opção: ")

            if opcao == "1":
                self.ver_inventario()
            elif opcao == "2":
                item = input("Digite o item que deseja adicionar:" )
                self.adicionar_item(item)
            elif opcao == "3":
                item = input("Digite o item que deseja remover:" )
                self.remover_item(item)
            elif opcao == "4":
                print("Inventário fechado")
                break
            else:
                raise Exception("Opção inválida.")

    def ver_inventario(self):
        print(self.inventario_jogador)

    def adicionar_item(self, item):
        if item not in self.inventario_jogador:
            raise Exception("item não válido")
        else:
            self.inventario_jogador.append(item)