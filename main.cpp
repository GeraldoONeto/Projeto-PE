#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <ctime> 
#include "dados_vendas.hpp"
#include "similaridade.hpp"
#include "recomendacao.hpp"

using namespace std;

int main() {
    Dados bd = listaCompras("dados_venda_cluster_0.csv");
    if (bd.codClientes.empty()) {
        printf("Erro: nenhum cliente carregado.\n");
        return 1;
    }

    vector<vector<int>> A = criarMatrizDensa(bd);
    
    vector<vector<int>> I_padrao = multiplicarMatrizes(A);
    vector<vector<double>> S_normal = calcularSimilaridade(bd, I_padrao);
    
    vector<vector<int>> I_eficiente = multiplicarEficiente(A);
    vector<vector<double>> S_eficiente = calcularSimEfi(bd, I_eficiente);

    int opcao;
    do {
        printf("\n--- MENU ---\n");
        printf("1. Historico de compras (Atividade 1)\n");
        printf("2. Similaridade entre dois clientes (Atividade 2)\n");
        printf("3. Produtos recomendados (Atividade 3)\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            char cod[9];
            printf("Codigo do cliente: ");
            scanf("%8s", cod);
            if (bd.mapClientes.count(cod) == 0) {
                printf("Cliente nao encontrado.\n");
                continue;
            }
            int id = bd.mapClientes[cod];
            printf("Produtos comprados:\n");
            const vector<int>& compras = bd.comprasPorCliente[id];
            for (size_t i = 0; i < compras.size(); i++) {
                int p = compras[i];
                printf("- %s\n", bd.nomeProdutos[p].c_str());
            }
        }
        else if (opcao == 2) {
            char cod1[9], cod2[9];
            int algoritmo;
            
            printf("Escolha o tipo da multiplicacao de similaridade:\n");
            printf("1 - Multiplicacao normal\n");
            printf("2 - Multiplicacao eficiente\n");
            printf("Opcao: ");
            scanf("%d", &algoritmo);
            
            printf("Digite o codigo do primeiro cliente: ");
            scanf("%8s", cod1);
            printf("Digite o codigo do segundo cliente: ");
            scanf("%8s", cod2);

            if (bd.mapClientes.count(cod1) == 0 || bd.mapClientes.count(cod2) == 0) {
                printf("Um ou ambos os clientes nao existem.\n");
                continue;
            }

            int id1 = bd.mapClientes[cod1];
            int id2 = bd.mapClientes[cod2];
            double sim;
            
            clock_t inicio = clock();
            
            if (algoritmo == 1) {
                printf("\nUsando algoritmo normal...\n");
                sim = obterSimilaridade(bd, S_normal, id1, id2);
            } else {
                printf("\nUsando algoritmo eficiente...\n");
                sim = obterSimEfi(bd, S_eficiente, id1, id2);
            }
            
            clock_t fim = clock();
            double tempo = double(fim - inicio) / CLOCKS_PER_SEC;
            
            printf("Similaridade (Jaccard) do cliente %s em relacao a %s: %.4f\n", cod1, cod2, sim);
            printf("Tempo de execucao: %.6f segundos\n", tempo);
        }
        else if (opcao == 3){
            char cod1[9], cod2[9], cod3[9];
            int k;
            
            printf("Usando algoritmo eficiente para recomendacoes...\n");
            printf("Digite o codigo do primeiro cliente: ");
            scanf("%8s", cod1);
            printf("Digite o codigo do segundo cliente: ");
            scanf("%8s", cod2);
            printf("Digite o código do terceiro cliente: ");
            scanf("%8s", cod3);
            printf("Digite o número de produtos recomendados que deseja ver: ");
            scanf("%d", &k);

            if (bd.mapClientes.count(cod1) == 0 || bd.mapClientes.count(cod2) == 0 || bd.mapClientes.count(cod3) == 0) {
                printf("Um ou mais clientes nao existem.\n");
                continue;
            }

            int id1 = bd.mapClientes[cod1];
            int id2 = bd.mapClientes[cod2];
            int id3 = bd.mapClientes[cod3];

            vector<RankProduto> rankcl1 = recomendacao(id1, bd, S_eficiente, k);
            vector<RankProduto> rankcl2 = recomendacao(id2, bd, S_eficiente, k);
            vector<RankProduto> rankcl3 = recomendacao(id3, bd, S_eficiente, k);
            
            printf("\nPrimeiro cliente: \n");
            for (int i = 0; i < k; i++){
                int idp = rankcl1[i].idProduto;
                printf("Produto recomendado n°%d: %s\n", i+1, bd.nomeProdutos[idp].c_str());
            }
            printf("\nSegundo Cliente: \n");
            for (int i = 0; i < k; i++){
                int idp = rankcl2[i].idProduto;
                printf("Produto recomendado n°%d: %s\n", i+1, bd.nomeProdutos[idp].c_str());
            }
            printf("\nTerceiro Cliente: \n");
            for (int i = 0; i < k; i++){
                int idp = rankcl3[i].idProduto;
                printf("Produto recomendado n°%d: %s\n", i+1, bd.nomeProdutos[idp].c_str());
            }
        }
    } while (opcao != 0);

    return 0;
}
/*
99CL9Y01
9O6OSM01
99EF7201
56661201
*/
