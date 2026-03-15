#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include "dados_vendas.hpp"

using namespace std;

int main(){

    string caminho = "coloque o caminho do arquivo no seu computador";

    Dados dados = ListaCompras(caminho);

    int opcao = 1;

    do{
        printf("\nDigite 1 se você quer pesquisar um cliente ou digite 0 para encerrar o programa: ");
        scanf("%d", &opcao);

        if (opcao == 1){

            char cd[9];
            printf("\nDigite o código do cliente: ");
            scanf("%8s", cd);

            string codigo = cd; //passa para string do C++

            int indice_cliente = dados.mapClientes[codigo]; 

            printf("Produto(s) comprado(s) pelo cliente: \n");

            for (size_t i = 0; i < dados.comprasPorCliente[indice_cliente].size(); i++){ //a função .size() retorna um valor de tipo size_t, então o i tem que ser declarado como size_t tbm. Ou senão pode colocar um (int) antes do dados.comprasPorCliente
            //o for tem o tamanho do número de produtos comprado pelo cliente

                int indice_produto = dados.comprasPorCliente[indice_cliente][i]; //recebe o indice de um produto por vez 

                printf("%s\n", dados.nomeProdutos[indice_produto].c_str()); //printa o nome do produto acessado
                
            }
        }

        

    } while (opcao != 0);

    return 0;
}