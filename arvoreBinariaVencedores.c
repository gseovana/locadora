#include "locadora.h"
#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void arvoreVencDvd(TDvd **dvd, FILE *arq, int tam, int *arvoreAux) {
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

    salvarDvd(dvd[0], arq);
    *arvoreAux +=1;
}

void arvoreVencCliente(TCliente **cliente, FILE *arq, int tam, int *arvoreAux) {
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

    salvarCliente(cliente[0], arq);
    *arvoreAux +=1;
}

void arvoreBinariaVencDvd(int qtdParticoes, FILE *logFile){
    struct timeval current_time;
    gettimeofday(&current_time, NULL);

    int auxQtdParticoes = qtdParticoes;
    int flagAuxFinal = 0;
    int arvoreAux = 0;
    int tam;

    if (qtdParticoes % 2 == 0){
        tam = 2 * qtdParticoes - 1;
        auxQtdParticoes--;
    }
    else {
        tam = 2 * qtdParticoes;
    }

    int aux = tam - 1;

    TDvdFile *auxArq = calloc(sizeof(*auxArq), qtdParticoes);
    TDvd *menor = calloc(sizeof(*menor), 1);
    TDvd **dvdAux = calloc(sizeof(**dvdAux), tam);

    for (int i = 0; i < auxQtdParticoes; i++){
        dvdAux[i] = calloc(sizeof(TDvd), 1);
    }

    FILE *arvoreBinaria = fopen("arvoreBinaria.dat", "wb+");

    for (int i = 0; i < qtdParticoes; i++){
        auxArq[i].init_p = 0;

        char nomeParticao[100];
        char nome1[50];
        char nome2[50] = ".dat";

        itoa(i, nome1, 10);
        strcat(strcpy(nomeParticao, "slcNat"), nome1);
        strcat(strcpy(nomeParticao, nomeParticao), nome2);

        auxArq[i].filePartition = fopen (nomeParticao, "rb+");
        fseek(auxArq[i].filePartition, 0 * sizeof(TDvd), SEEK_SET);

        if (aux+1 >= qtdParticoes){
            dvdAux[aux] = lerDvd(auxArq[i].filePartition);
            aux--;
        }
        auxArq[i].end_p = 0;
    }

    arvoreVencDvd(dvdAux, arvoreBinaria, tam, &arvoreAux);

    while (flagAuxFinal < qtdParticoes){
        aux = tam - 1;

        for (int i = 0; i < qtdParticoes; i++){

            if (fgetc(auxArq[i].filePartition) == EOF && auxArq[i].end_p == 0 && menor->id_dvd == dvdAux[aux]->id_dvd){
                flagAuxFinal++;
                auxArq[i].end_p = 1;
                i--;

                if (flagAuxFinal == qtdParticoes) {
                    break;
                }

                for (int j = 0; j < tam; j++){
                    if (dvdAux[j]->id_dvd == menor->id_dvd) dvdAux[j]->id_dvd = 15000;
                }

                arvoreVencDvd(dvdAux, arvoreBinaria, tam, &arvoreAux);
            } else {
                *menor = *dvdAux[0];

                if (menor->id_dvd == dvdAux[aux]->id_dvd && auxArq[i].end_p == 0){
                    auxArq[i].init_p += 1;

                    if (fgetc(auxArq[i].filePartition) != EOF){
                        fseek (auxArq[i].filePartition, auxArq[i].init_p * sizeof(TDvd), SEEK_SET);
                        free(dvdAux[aux]);
                        dvdAux[aux] = lerDvd(auxArq[i].filePartition);
                        arvoreVencDvd(dvdAux, arvoreBinaria, tam, &arvoreAux);
                    }
                }
                aux--;
            }
        }
    }

    for (int i = 0; i < qtdParticoes; i++) {
        fclose(auxArq[i].filePartition);
    }

    for (int i = 0; i < tam; i++){
        free(dvdAux[i]);
    }

    free(dvdAux);
    free(menor);
    free(auxArq);
    imprimirBaseDvd(arvoreBinaria);
    fclose(arvoreBinaria);

    fprintf(logFile, "ARVORE BINARIA VENCEDORES DVD - Tempo de execucao: %f", current_time.tv_usec);

}

void arvoreBinariaVencCliente(int qtdParticoes, FILE *logFile){
    struct timeval current_time;
    gettimeofday(&current_time, NULL);

    int auxQtdParticoes = qtdParticoes;
    int flagAuxFinal = 0;
    int arvoreAux = 0;
    int tam;

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

    FILE *arvoreBinariaC = fopen("arvoreBinariaC.dat", "wb+");

    for (int i = 0; i < qtdParticoes; i++){
        auxArq[i].init_p = 0;

        char nomeParticao[100];
        char nome1[50];
        char nome2[50] = ".dat";

        itoa(i, nome1, 10);
        strcat(strcpy(nomeParticao, "slcNat"), nome1);
        strcat(strcpy(nomeParticao, nomeParticao), nome2);

        auxArq[i].filePartition = fopen (nomeParticao, "rb+");
        fseek(auxArq[i].filePartition, 0 * sizeof(TCliente), SEEK_SET);

        if (aux+1 >= qtdParticoes){
            clienteAux[aux] = lerCliente(auxArq[i].filePartition);
            aux--;
        }
        auxArq[i].end_p = 0;
    }

    arvoreVencCliente(clienteAux, arvoreBinariaC, tam, &arvoreAux);

    while (flagAuxFinal < qtdParticoes){
        aux = tam - 1;

        for (int i = 0; i < qtdParticoes; i++){

            if (fgetc(auxArq[i].filePartition) == EOF && auxArq[i].end_p == 0 && menor->idC == clienteAux[aux]->idC){
                flagAuxFinal++;
                auxArq[i].end_p = 1;
                i--;

                if (flagAuxFinal == qtdParticoes) {
                    break;
                }

                for (int j = 0; j < tam; j++){
                    if (clienteAux[j]->idC == menor->idC) clienteAux[j]->idC = 15000;
                }

                arvoreVencCliente(clienteAux, arvoreBinariaC, tam, &arvoreAux);
            } else {
                *menor = *clienteAux[0];

                if (menor->idC == clienteAux[aux]->idC && auxArq[i].end_p == 0){
                    auxArq[i].init_p += 1;

                    if (fgetc(auxArq[i].filePartition) != EOF){
                        fseek (auxArq[i].filePartition, auxArq[i].init_p * sizeof(TCliente), SEEK_SET);
                        free(clienteAux[aux]);
                        clienteAux[aux] = lerCliente(auxArq[i].filePartition);
                        arvoreVencCliente(clienteAux, arvoreBinariaC, tam, &arvoreAux);
                    }
                }
                aux--;
            }
        }
    }

    for (int i = 0; i < qtdParticoes; i++) {
        fclose(auxArq[i].filePartition);
    }

    for (int i = 0; i < tam; i++){
        free(clienteAux[i]);
    }

    free(clienteAux);
    free(menor);
    free(auxArq);
    imprimirBaseCliente(arvoreBinariaC);
    fclose(arvoreBinariaC);
    fprintf(logFile, "ARVORE BINARIA VENCEDORES CLIENTE - Tempo de execucao: %f", current_time.tv_usec);
    //fclose(logFile);
    //*tempoExecucao = current_time.tv_usec;
}