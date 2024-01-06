//#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include "selecaoNatural.h"
#include "locadora.h"



int selecaoNatural(FILE *arq, int tam) {

    int pos = 0;
    int quantidadeParticoes = 0;
    int menor = 10000000;
    int posMenor = 0;
    int tamReservatorio = 0;
    int opc = 0;

    TDvd dvd[6];

    int auxDvdVet[6] = {0, 0, 0, 0, 0, 0};

    rewind(arq);

    while (!feof(arq)) {

        FILE *arqReservatorio = fopen("reservatorio.dat", "wb+");

        if (arqReservatorio == NULL) {
            printf("ERRO AO ABRIR ARQUIVO");
        }

        char nomeParticao[100];
        char nome1[100];
        char nome2[100] = ".dat";

        itoa(quantidadeParticoes, nome1, 10);
        strcat(strcpy(nomeParticao, "selecaoNatural"), nome1);
        strcat(nomeParticao, nome2);

        FILE *arqParticao = fopen(nomeParticao, "wb+");

        //preenche o vetor com registros do arquivo
        if (opc == 0) {
            for (int i = 0; i < 6; ++i) {

                TDvd *auxDvd = lerDvd(arq);
                pos++;

                dvd[i] = *auxDvd;
                auxDvdVet[i] = auxDvd->id_dvd;
            }
        }

        //fclose(arqReservatorio);

        while (!feof(arq)) {
            for (int i = 0; i < 6; ++i) {
                if (auxDvdVet[i] < menor) {
                    menor = auxDvdVet[i];
                    posMenor = i;
                }
            }

            TDvd *auxDvd = lerDvd(arq);
            pos++;
            if (auxDvd->id_dvd < dvd[posMenor].id_dvd) {
                salvarDvd(auxDvd, arqReservatorio);
                tamReservatorio++;

                if (tamReservatorio == 6) {

                    break;
                }

            } else {
                salvarDvd(&dvd[posMenor], arqParticao);
                auxDvdVet[posMenor] = auxDvd->id_dvd;
                dvd[posMenor] = *auxDvd;
            }

            menor = 999999999;

            if (pos >= tam) {
                break;
            }

        }

        TDvd aux;

        int k, j;

        for (k = 1; k < 6; k++) {

            for (j = 0; j < 6 - 1; j++) {
                if (dvd[j].id_dvd > dvd[j + 1].id_dvd) {
                    aux = dvd[j];
                    dvd[j] = dvd[j + 1];
                    dvd[j + 1] = aux;
                }
            }
        }

        for (int i = 0; i < 6; ++i) {
            salvarDvd(&dvd[i], arqParticao);
        }

        rewind(arqReservatorio);

        for (int i = 0; i < tamReservatorio; ++i) {
            TDvd *auxDvdReservatorio = lerDvd(arqReservatorio);
            dvd[i] = *auxDvdReservatorio;
            auxDvdVet[i] = auxDvdReservatorio->id_dvd;
            opc = 1;
        }


        fclose(arqReservatorio);
        fclose(arqParticao);

        if (pos >= tam) {
            break;
        }

        tamReservatorio = 0;
        quantidadeParticoes++;

    }

    for (int i = 0; i <= quantidadeParticoes; ++i) {

        char nomeParticao[100];
        char str1[100];
        char str2[100] = ".dat";

        itoa(i, str1, 10);
        strcat(strcpy(nomeParticao, "selecaoNatural"), str1);
        strcat(strcpy(nomeParticao, nomeParticao), str2);

        FILE *arqParticao = fopen(nomeParticao, "rb+");
        fclose(arqParticao);
    }

    return quantidadeParticoes;
}