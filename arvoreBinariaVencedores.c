#include "locadora.h"
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>

void arvoreVencDvd(TDvd **dvd, FILE *arqD, int tam, int *arvoreAuxd) {
    int aux;

    for (int i = tam - 1; i > 0; i--){

        if (i % 2 != 0 && i == tam - 1){
            aux = (i - 1) / 2;
            *dvd[aux] = *dvd[i];
        }
        else{
            if (i % 2 == 0 && dvd[i]->id_dvd < dvd[i-1]->id_dvd){
                aux = (i - 2) / 2;
                *dvd[aux] = *dvd[i];
            }
            else if (i % 2 == 0 && dvd[i-1]->id_dvd < dvd[i]->id_dvd){
                aux = (i - 2) / 2;
                *dvd[aux] = *dvd[i - 1];
            }
        }
    }

    salvarDvd(dvd[0], arqD);
    *arvoreAuxd +=1;
}


void arvoreBinariaVencDvd(int qtdParticoes, FILE *logArvoreVencDvd){
    struct timespec inicioTime, fimTime;
    double tempoGasto;
    clock_t inicioClock, fimClock;

    int auxQtdParticoes = qtdParticoes;
    int flagAuxFinal = 0;
    int arvoreAuxd = 0;
    int tam;

    clock_gettime(CLOCK_MONOTONIC, &inicioTime);

    if (qtdParticoes % 2 == 0){
        tam = 2 * qtdParticoes - 1;
        auxQtdParticoes--;
    }
    else {
        tam = 2 * qtdParticoes;
    }

    int aux = tam - 1;

    TDvdFile *auxArqd = calloc(sizeof(*auxArqd), qtdParticoes);
    TDvd *menord = calloc(sizeof(*menord), 1);
    TDvd **dvdAux = calloc(sizeof(**dvdAux), tam);

    for (int i = 0; i < auxQtdParticoes; i++){
        dvdAux[i] = calloc(sizeof(TDvd), 1);
    }

    FILE *arvoreBinariad = fopen("arvoreBinariad.dat", "wb+");

    for (int i = 0; i < qtdParticoes; i++){
        auxArqd[i].init_pd = 0;

        char nomeParticao[100];
        char nome1[50];
        char nome2[50] = ".dat";

        itoa(i, nome1, 10);
        strcat(strcpy(nomeParticao, "selecaoNaturald"), nome1);
        strcat(strcpy(nomeParticao, nomeParticao), nome2);

        auxArqd[i].filePartitiond = fopen(nomeParticao, "rb+");
        if (auxArqd[i].filePartitiond == NULL) {
            fprintf(stderr, "Erro ao abrir o arquivo %s. Motivo: %s\n", nomeParticao, strerror(errno));
        }
        fseek(auxArqd[i].filePartitiond, 0 * sizeof(TDvd), SEEK_SET);

        if (aux+1 >= qtdParticoes){
            dvdAux[aux] = lerDvd(auxArqd[i].filePartitiond);
            aux--;
        }
        auxArqd[i].end_pd = 0;
    }

    arvoreVencDvd(dvdAux, arvoreBinariad, tam, &arvoreAuxd);

    while (flagAuxFinal < qtdParticoes){
        aux = tam - 1;

        for (int i = 0; i < qtdParticoes; i++){

            if (fgetc(auxArqd[i].filePartitiond) == EOF && auxArqd[i].end_pd == 0 && menord->id_dvd == dvdAux[aux]->id_dvd){
                flagAuxFinal++;
                auxArqd[i].end_pd = 1;
                i--;

                if (flagAuxFinal == qtdParticoes) {
                    break;
                }

                for (int j = 0; j < tam; j++){
                    if (dvdAux[j]->id_dvd == menord->id_dvd) dvdAux[j]->id_dvd = 15000;
                }

                arvoreVencDvd(dvdAux, arvoreBinariad, tam, &arvoreAuxd);
            } else {
                *menord = *dvdAux[0];

                if (menord->id_dvd == dvdAux[aux]->id_dvd && auxArqd[i].end_pd == 0){
                    auxArqd[i].init_pd += 1;

                    if (fgetc(auxArqd[i].filePartitiond) != EOF){
                        //int currentPos = ftell(auxArqd[i].filePartitiond);
                        fseek (auxArqd[i].filePartitiond, auxArqd[i].init_pd * sizeof(TDvd), SEEK_SET);
                        //int newPos = ftell(auxArqd[i].filePartitiond);
                        free(dvdAux[aux]);
                        dvdAux[aux] = lerDvd(auxArqd[i].filePartitiond);
                        arvoreVencDvd(dvdAux, arvoreBinariad, tam, &arvoreAuxd);
                    }
                }
                aux--;
            }
        }
    }

    for (int i = 0; i < qtdParticoes; i++) {
        fclose(auxArqd[i].filePartitiond);
    }

    for (int i = 0; i < tam; i++){
        free(dvdAux[i]);
    }

    free(dvdAux);
    free(menord);
    free(auxArqd);
    imprimirBaseDvd(arvoreBinariad);
    fclose(arvoreBinariad);

    clock_gettime(CLOCK_MONOTONIC, &fimTime);
    tempoGasto = (fimTime.tv_sec - inicioTime.tv_sec) * 1000.0; // seconds to milliseconds
    tempoGasto += (fimTime.tv_nsec - inicioTime.tv_nsec) / 1000000.0; // nanoseconds to milliseconds

    fprintf(logArvoreVencDvd, "ARVORE BINARIA VENCEDORES DVD - Tempo de execucao: %f", tempoGasto);
    fclose(logArvoreVencDvd);

}

void arvoreVencCliente(TCliente **cliente, FILE *arqC, int tam, int *arvoreAux) {
    int aux;

    for (int i = tam - 1; i > 0; i--){

        if (i % 2 != 0 && i == tam - 1){
            aux = (i - 1) / 2;
            *cliente[aux] = *cliente[i];
        }
        else{
            if (i % 2 == 0 && cliente[i]->idC < cliente[i-1]->idC){
                aux = (i - 2) / 2;
                *cliente[aux] = *cliente[i];
            }
            else if (i % 2 == 0 && cliente[i-1]->idC < cliente[i]->idC){
                aux = (i - 2) / 2;
                *cliente[aux] = *cliente[i - 1];
            }
        }
    }

    salvarCliente(cliente[0], arqC);
    *arvoreAux +=1;
}


void arvoreBinariaVencCliente(int qtdParticoes, FILE *logArvoreVencCliente){
    struct timespec inicioTime, fimTime;
    double tempoGasto;
    clock_t inicioClock, fimClock;

    int auxQtdParticoes = qtdParticoes;
    int flagAuxFinal = 0;
    int arvoreAux = 0;
    int tam;

    clock_gettime(CLOCK_MONOTONIC, &inicioTime);

    if (qtdParticoes % 2 == 0){
        tam = 2 * qtdParticoes - 1;
        auxQtdParticoes--;
    }
    else {
        tam = 2 * qtdParticoes;
    }

    int aux = tam - 1;

    TClienteFile *auxArq = calloc(sizeof(*auxArq), qtdParticoes);
    TCliente *menor = calloc(sizeof(*menor), 1);
    TCliente **clienteAux = calloc(sizeof(**clienteAux), tam);

    for (int i = 0; i < auxQtdParticoes; i++){
        clienteAux[i] = calloc(sizeof(TCliente), 1);
    }

    FILE *arvoreBinariac = fopen("arvoreBinariac.dat", "wb+");

    for (int i = 0; i < qtdParticoes; i++){
        auxArq[i].init_pc = 0;

        char nomeParticao[100];
        char nome1[50];
        char nome2[50] = ".dat";

        itoa(i, nome1, 10);
        strcat(strcpy(nomeParticao, "selecaoNaturalc"), nome1);
        strcat(strcpy(nomeParticao, nomeParticao), nome2);

        auxArq[i].filePartitionc = fopen(nomeParticao, "rb+");
        if (auxArq[i].filePartitionc == NULL) {
            fprintf(stderr, "Erro ao abrir o arquivo %s. Motivo: %s\n", nomeParticao, strerror(errno));
        }

        fseek(auxArq[i].filePartitionc, 0 * sizeof(TCliente), SEEK_SET);

        if (aux+1 >= qtdParticoes){
            clienteAux[aux] = lerCliente(auxArq[i].filePartitionc);
            aux--;
        }
        auxArq[i].end_pc = 0;
    }

    arvoreVencCliente(clienteAux, arvoreBinariac, tam, &arvoreAux);

    while (flagAuxFinal < qtdParticoes){
        aux = tam - 1;

        for (int i = 0; i < qtdParticoes; i++){

            if (fgetc(auxArq[i].filePartitionc) == EOF && auxArq[i].end_pc == 0 && menor->idC == clienteAux[aux]->idC){
                flagAuxFinal++;
                auxArq[i].end_pc = 1;
                i--;

                if (flagAuxFinal == qtdParticoes) {
                    break;
                }

                for (int j = 0; j < tam; j++){
                    if (clienteAux[j]->idC == menor->idC) clienteAux[j]->idC = 15000;
                }

                arvoreVencCliente(clienteAux, arvoreBinariac, tam, &arvoreAux);
            } else {
                *menor = *clienteAux[0];

                if (menor->idC == clienteAux[aux]->idC && auxArq[i].end_pc == 0){
                    auxArq[i].init_pc += 1;

                    if (fgetc(auxArq[i].filePartitionc) != EOF){

                        int currentPos = ftell(auxArq[i].filePartitionc);

                        fseek (auxArq[i].filePartitionc, auxArq[i].init_pc * sizeof(TCliente), SEEK_SET);
                        int newPos = ftell(auxArq[i].filePartitionc);

                        free(clienteAux[aux]);
                        clienteAux[aux] = lerCliente(auxArq[i].filePartitionc); //AQUI!!
                        arvoreVencCliente(clienteAux, arvoreBinariac, tam, &arvoreAux);
                    }
                }
                aux--;
            }
        }
    }

    for (int i = 0; i < qtdParticoes; i++) {
        fclose(auxArq[i].filePartitionc);
    }

    for (int i = 0; i < tam; i++){
        free(clienteAux[i]);
    }

    free(clienteAux);
    free(menor);
    free(auxArq);
    imprimirBaseCliente(arvoreBinariac);
    fclose(arvoreBinariac);

    clock_gettime(CLOCK_MONOTONIC, &fimTime);
    tempoGasto = (fimTime.tv_sec - inicioTime.tv_sec) * 1000.0;
    tempoGasto += (fimTime.tv_nsec - inicioTime.tv_nsec) / 1000000.0;

    fprintf(logArvoreVencCliente, "ARVORE BINARIA VENCEDORES CLIENTE - Tempo de execucao: %f", tempoGasto);
    fclose(logArvoreVencCliente);

}