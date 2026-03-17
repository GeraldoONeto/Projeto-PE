#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include "dados_vendas.hpp"
#include "similaridade.hpp"

using namespace std;

int main() {
    Dados bd = ListaCompras("dados_venda_cluster_0.csv");
    if (bd.codClientes.empty()) {
        printf("Erro: nenhum cliente carregado.\n");
        return 1;
    }

    vector<vector<int>> A = criarMatrizDensa(bd);
    vector<vector<int>> I = multiplicarMatrizes(A);
    vector<vector<double>> S = calcularSimilaridade(bd, I);

    int opcao;
    do {
        printf("\n--- MENU ---\n");
        printf("1. Historico de compras (Atividade 1)\n");
        printf("2. Similaridade entre dois clientes (Atividade 2)\n");
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

            double sim = obterSimilaridade(bd, S, id1, id2);
            printf("Similaridade (Jaccard) do cliente %s em relacao a %s: %.4f\n", cod1, cod2, sim);
        }
    } while (opcao != 0);

    return 0;
}
