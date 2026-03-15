#include <stdio.h>
#include <vector>
#include <map>
#include <string>
using namespace std;

typedef struct{
    //criação dos vetores e mapas
    vector<string> codClientes;
    map<string, int> mapClientes;

    vector<string> nomeProdutos;
    map<string, int> mapProdutos;

    vector<vector<int>> comprasPorCliente; //vetor de compras feitas por cada cliente


}Dados;

Dados ListaCompras(string pathArquivo){ //função que recebe o caminho do arquivo e retorna um struct com os vetores e mapas

    Dados dados;

    //abre o arquivo | copie o caminho do arquivo no seu computador na função fopen
    FILE *arquivo = fopen(pathArquivo.c_str(), "r");
    if (arquivo == NULL){
        printf("Erro ao tentar abrir o arquivo!\n");
        return dados; //retorna a struct vazia, (equivalente ao -1)
    }
    
    //ignora o cabeçalho
    char cabecalho[100];
    fgets(cabecalho, sizeof(cabecalho), arquivo);

    //variaveis para percorrer o arquivo
    char cliente[9], produto[50];


    //percorre o arquivo
    while (fscanf(arquivo,"%*d,%8[^,],%*d,%49[^\n]\n", cliente, produto) == 2){ //o * no "%*d" serve pra ignorar a data de compra e o cod de produto, já que não vamos usar

        //usa função .count pra verificar se o cliente ou produto já foi adicionado
        if (dados.mapClientes.count(cliente) == 0){
            dados.mapClientes[cliente] = dados.codClientes.size(); //a função .size vai retornar quantos elementos já tem no vetor para usar isso de índice
            dados.codClientes.push_back(cliente); //adiciona ao vetor.
        }

        //mesmo processo
        if (dados.mapProdutos.count(produto) == 0){
            dados.mapProdutos[produto] = dados.nomeProdutos.size();
            dados.nomeProdutos.push_back(produto);
        }

    }

    rewind(arquivo); //coloca o ponteiro no inicio do arquivo para podermos varrer ele dnv.

    fgets(cabecalho, sizeof(cabecalho), arquivo); //ignora o cabeçalho dnv

    dados.comprasPorCliente.resize(dados.codClientes.size()); //o vetor tem que ter dimensão igual ao número de clientes

    while (fscanf(arquivo,"%*d,%8[^,],%*d,%49[^\n]\n", cliente, produto) == 2){ //varre os arquivos pela segunda vez

        int idcl = dados.mapClientes[cliente]; //retorna o id do mapa do cliente
        int idpdrt = dados.mapProdutos[produto]; //retorna o id do mapa do produto

        dados.comprasPorCliente[idcl].push_back(idpdrt); //cada produto é colocado no vetor doo cliente comprador

    }

    fclose(arquivo);

    return dados;
}