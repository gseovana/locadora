//
// Created by geovana on 1/3/24.
//
#include <stdio.h>
#include "locadora.h"
#include "selectionSort.h"
#include <sys/time.h>
#include <time.h>

void selectionSortDvd(FILE *arqD, int tam, FILE *logFileDvd) {
    struct timespec inicioTime, fimTime;
    double tempoGasto;
    clock_t inicioClock, fimClock;

    int i, j, min_idx, qntComp = 0;


    clock_gettime(CLOCK_MONOTONIC, &inicioTime);


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
            qntComp++;
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

    // Escrevendo no arquivo de log
    clock_gettime(CLOCK_MONOTONIC, &fimTime);
    tempoGasto = (fimTime.tv_sec - inicioTime.tv_sec) * 1000.0; // seconds to milliseconds
    tempoGasto += (fimTime.tv_nsec - inicioTime.tv_nsec) / 1000000.0; // nanoseconds to milliseconds

    // Escrevendo no arquivo de log
    fprintf(logFileDvd, "SELECTION SORT DVD - Tempo de execucao em milissegundos: %f\nQuantidade comparacoes: %d\n", tempoGasto, qntComp);
    fclose(logFileDvd);

}

void selectionSortCliente(FILE *arqC, int tam, FILE *logFileCliente) {
    struct timespec inicioTime, fimTime;
    double tempoGasto;
    clock_t inicioClock, fimClock;
    int i, j, min_idx, qntComp = 0;

    clock_gettime(CLOCK_MONOTONIC, &inicioTime);

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
            qntComp++;
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
    clock_gettime(CLOCK_MONOTONIC, &fimTime);
    tempoGasto = (fimTime.tv_sec - inicioTime.tv_sec) * 1000.0; // seconds to milliseconds
    tempoGasto += (fimTime.tv_nsec - inicioTime.tv_nsec) / 1000000.0; // nanoseconds to milliseconds

    fprintf(logFileCliente, "SELECTION SORT CLIENTE - Tempo de execucao em milissegundos: %f\nQuantidade comparacoes: %d\n", tempoGasto, qntComp);
    fclose(logFileCliente);
}
