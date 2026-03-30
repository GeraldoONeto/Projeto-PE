#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "similaridade.hpp"
#include "recomendacao.hpp"

namespace py = pybind11;

PYBIND11_MODULE(recomendador, r){
    r.doc() = "Algoritmo de recomendação";

    r.def(
        "recomendacao", 
        &recomendacao,
        "Recebe os código do cliente e o vetor de similaridade pronto e retorna os produtos mais recomendados conforme o rank"
    );

    r.def(
        "similaridade_comum",
        &similaridadeComum,
        "Calcula a matriz de similaridade entre dois clientes e retorna a similaridade do primeiro em relação ao segundo"
    );

    r.def(
        "similaridade_eficiente",
        &similaridadeEficiente,
        "Calcula a matriz de similaridade de maneira eficiente entre dois clientes e retorna a similaridade do primeiro em relação ao segundo"
    );
}