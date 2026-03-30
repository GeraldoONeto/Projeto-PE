import csv
from dataclasses import dataclass
from time import process_time

import recomendador

@dataclass
class Dados:
    cod_clientes: list[str]
    map_clientes: dict[str,int]
    nome_produtos: list[str]
    map_produtos: dict[str,int]
    compras_por_cliente: list[list[int]]


def ler_arquivos(caminho_arquivo):

    dados = Dados([], {}, [], {}, [])

    with open(caminho_arquivo, 'r', encoding='utf-8') as arquivo:
        leitor = csv.reader(arquivo)
        next(leitor)
        for linha in leitor:
            cliente = linha[1]
            produto = linha[3]

            if cliente not in dados.map_clientes:
                id_c = len(dados.map_clientes)
                dados.cod_clientes.append(cliente)
                dados.map_clientes[cliente] = id_c
                
                dados.compras_por_cliente.append([])

            if produto not in dados.map_produtos:
                id_p = len(dados.map_produtos)
                dados.nome_produtos.append(produto)
                dados.map_produtos[produto] = id_p

            id_c = dados.map_clientes[cliente]
            id_p = dados.map_produtos[produto]
            dados.compras_por_cliente[id_c].append(id_p)

    return dados

def main():
    dados = ler_arquivos("dados_venda_cluster_2.csv")

    opcao = 1
    s_eficiente = 0

    while opcao != 0:
        if dados is None:
            print("Erro ao ler o arquivo!")
            break

        print("\n--- MENU ---")
        print("1. Historico de compras")
        print("2. Similaridade entre dois clientes")
        print("3. Produtos recomendados")
        print("4. Comparar algoritmos")
        print("0. Sair")
        opcao = int(input())

        if opcao == 1:
            cod = input("Digite o código do cliente: ")
            if dados.cod_clientes.count(cod) == 0:
                print("Cliente não encontraodo.")
                break
            
            id = dados.map_clientes[cod]
            print("Produtos comprados: ")
            compras = dados.compras_por_cliente[id]
            for produto in compras:
                print(dados.nome_produtos[produto])

        elif opcao == 2:
            print("Escolha o tipo da multiplicacao de similaridade")
            print("1 - Multiplicacao normal")
            print("2 - Multiplicacao eficiente")
            algoritmo = int(input("Opcao: "))
            
            cod1 = input("Digite o codigo do primeiro cliente: ")
            cod2 = input("Digite o codigo do segundo cliente: ")

            if dados.cod_clientes.count(cod1) == 0 or dados.cod_clientes.count(cod2) == 0:
                print("Um ou ambos clientes não existem")
                break

            id1 = dados.map_clientes[cod1]
            id2 = dados.map_clientes[cod2]

            if algoritmo == 1:
                sim = recomendador.similaridade_eficiente(dados.cod_clientes, dados.nome_produtos, dados.compras_por_cliente, id1, id2)
            
            else:
                sim = recomendador.similaridade_eficiente(dados.cod_clientes, dados.nome_produtos, dados.compras_por_cliente, id1, id2)

            print(f"Similaridade (Jaccard) do cliente {cod1} em relação ao ao cliente {cod2}: {sim}")

        elif opcao == 3:
            cod1 = input("Digite o codigo do primeiro cliente: ")
            cod2 = input("Digite o codigo do segundo cliente: ")
            cod3 = input("Digite o codigo do terceiro cliente: ")
            k = int(input("Digite o número de produtos recomendados que deseja ver: "))

            if dados.cod_clientes.count(cod1) == 0 or dados.cod_clientes.count(cod2) == 0 or dados.cod_clientes.count(cod3) == 0:
                    print("Um ou mais clientes não existem")
                    break
                    
            id1 = dados.map_clientes[cod1]
            id2 = dados.map_clientes[cod2]
            id3 = dados.map_clientes[cod3]

            if s_eficiente == 0:
                s_eficiente = recomendador.recomendador.obter_similaridade_eficiente(dados.cod_clientes, dados.nome_produtos, dados.compras_por_cliente)

            prod1 = recomendador.recomendacao(id1, dados.cod_clientes, dados.nome_produtos, dados.compras_por_cliente, s_eficiente, k)
            prod2 = recomendador.recomendacao(id2, dados.cod_clientes, dados.nome_produtos, dados.compras_por_cliente, s_eficiente, k)
            prod3 = recomendador.recomendacao(id3, dados.cod_clientes, dados.nome_produtos, dados.compras_por_cliente, s_eficiente, k)

            print("Primeiro Cliente: ")
            for produto in prod1:
                print(dados.nome_produtos[produto])
            
            print("Segundo Cliente: ")
            for produto in prod2:
                print(dados.nome_produtos[produto])

            print("Terceiro Cliente: ")
            for produto in prod3:
                print(dados.nome_produtos[produto])

        elif opcao == 4:
            print("Comparação de algoritmos")
            print(f"Clientes: {len(dados.cod_clientes)} | Produtos: {len(dados.nome_produtos)}")

            print("Algoritmo normal: ")

            inicio1 = process_time()

            s_normal = recomendador.similaridade_comum(dados.cod_clientes, dados.nome_produtos, dados.compras_por_cliente, 0, 0)

            fim1 = process_time()

            tempo1 = fim1 - inicio1

            print(f"{tempo1:.4f} segundos")
            #-----------------------------------------------------------
            print("Algoritmo otimizado: ")

            inicio2 = process_time()

            s_eficiente = recomendador.similaridade_eficiente(dados.cod_clientes, dados.nome_produtos, dados.compras_por_cliente, 0, 0)

            fim2 = process_time()
            
            tempo2 = fim2 - inicio2

            print(f"{tempo2:.4f} segundos")

if __name__ == "__main__":
    main()


# csv 0
# 99CL9Y01
# 9O6OSM01
# 99EF7201
# 56661201

# csv 2
# 99DL9N01
# 77602301
# 22047601
# 69222401
# 99L6ZO01
