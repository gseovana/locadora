//
// Created by geovana on 1/3/24.
//
#include <stdio.h>
#include "locadora.h"
#include "selectionSort.h"

void selectionSortDvd(FILE *arqD, int tam) {
    int i, j, min_idx;

    for (i = 1; i <= tam - 1; i++) {
        // Assume que o elemento atual é o mínimo
        min_idx = i;

        // Procura o elemento mínimo no restante do array
        for (j = i + 1; j <= tam; j++) {
            // Posiciona o arquivo no registro j
            fseek(arqD, (j - 1) * tamanhoRegistroDvd(), SEEK_SET);
            TDvd *dvdj = lerDvd(arqD);

            // Posiciona o arquivo no registro min_idx
            fseek(arqD, (min_idx - 1) * tamanhoRegistroDvd(), SEEK_SET);
            TDvd *dvdMin = lerDvd(arqD);

            // Compara os códigos e atualiza min_idx se necessário
            if (dvdj->id_dvd < dvdMin->id_dvd) {
                min_idx = j;
            }
        }

        // Troca o elemento mínimo encontrado com o primeiro elemento não ordenado
        if (min_idx != i) {
            // Posiciona o arquivo no registro i
            fseek(arqD, (i - 1) * tamanhoRegistroDvd(), SEEK_SET);
            TDvd *dvdi = lerDvd(arqD);

            // Posiciona o arquivo no registro min_idx
            fseek(arqD, (min_idx - 1) * tamanhoRegistroDvd(), SEEK_SET);
            TDvd *dvdMinn = lerDvd(arqD);

            // Troca os registros
            fseek(arqD, (i - 1) * tamanhoRegistroDvd(), SEEK_SET);
            salvarDvd(dvdMinn, arqD);

            fseek(arqD, (min_idx - 1) * tamanhoRegistroDvd(), SEEK_SET);
            salvarDvd(dvdi, arqD);
        }
    }

    // Descarrega o buffer para ter certeza que dados foram gravados
    fflush(arqD);
}

void selectionSortCliente(FILE *arqC, int tam) {
    int i, j, min_idx;

    for (i = 1; i <= tam - 1; i++) {
        // Assume que o elemento atual é o mínimo
        min_idx = i;

        // Procura o elemento mínimo no restante do array
        for (j = i + 1; j <= tam; j++) {
            // Posiciona o arquivo no registro j
            fseek(arqC, (j - 1) * tamanhoRegistroCliente(), SEEK_SET);
            TCliente *clientej = lerCliente(arqC);

            // Posiciona o arquivo no registro min_idx
            fseek(arqC, (min_idx - 1) * tamanhoRegistroCliente(), SEEK_SET);
            TCliente *clienteMin = lerCliente(arqC);

            // Compara os códigos e atualiza min_idx se necessário
            if (clientej->idC < clienteMin->idC) {
                min_idx = j;
            }
        }

        // Troca o elemento mínimo encontrado com o primeiro elemento não ordenado
        if (min_idx != i) {
            // Posiciona o arquivo no registro i
            fseek(arqC, (i - 1) * tamanhoRegistroCliente(), SEEK_SET);
            TCliente *clientei = lerCliente(arqC);

            // Posiciona o arquivo no registro min_idx
            fseek(arqC, (min_idx - 1) * tamanhoRegistroCliente(), SEEK_SET);
            TCliente *clienteMinn = lerCliente(arqC);

            // Troca os registros
            fseek(arqC, (i - 1) * tamanhoRegistroCliente(), SEEK_SET);
            salvarCliente(clienteMinn, arqC);

            fseek(arqC, (min_idx - 1) * tamanhoRegistroCliente(), SEEK_SET);
            salvarCliente(clientei, arqC);
        }
    }

    // Descarrega o buffer para ter certeza que dados foram gravados
    fflush(arqC);
}
