//
// Created by geovana on 1/30/24.
//Tabela
#include "locadora.h"
#include "hash.h"

TabelaHash* criarTabelaHash(int tamanho, FILE* file) {
    TabelaHash* novaTabela = (TabelaHash*) malloc(sizeof(TabelaHash));
    novaTabela->tamanho = tamanho;

    TDvdHash* noVazio = (TDvdHash*) malloc(sizeof(TDvdHash));
    noVazio->proximo = NULL;

    rewind(file);
    for(int i=0; i<tamanho; i++) {
        fwrite(noVazio, sizeof(TDvdHash), 1, file);
    }

    free(noVazio);
    return novaTabela;
}

int funcaoHash(int id, int tamanho) {
    return id % tamanho;
}

void inserirHashFile(TabelaHash* tabela, TDvd dvd, FILE* arquivo) {
    TDvdHash* novoNoTDvdHash = (TDvdHash*) malloc(sizeof(TDvdHash));
    novoNoTDvdHash->dvdHash = dvd;
    novoNoTDvdHash->proximo = NULL;

    int index = funcaoHash(dvd.id_dvd, tabela->tamanho);

    rewind(arquivo);

    fseek(arquivo, index * sizeof(TDvdHash), SEEK_SET);
    TDvdHash* noAtual = (TDvdHash*) malloc(sizeof(TDvdHash));
    fread(noAtual, sizeof(TDvdHash), 1, arquivo);

    if(noAtual == NULL) {
        fwrite(novoNoTDvdHash, sizeof(TDvdHash), 1, arquivo);
    } else {
        while(noAtual->proximo != NULL) {
            noAtual = noAtual->proximo;
        }
        noAtual->proximo = novoNoTDvdHash;
        fseek(arquivo, -sizeof(TDvdHash), SEEK_CUR);
        fwrite(noAtual, sizeof(TDvdHash), 1, arquivo);
    }
}

void buscarHashFile(TabelaHash* tabela, int id, FILE* arquivo) {
    int index = funcaoHash(id, tabela->tamanho);

    fseek(arquivo, index * sizeof(TDvdHash), SEEK_SET);
    TDvdHash* noAtual = (TDvdHash*) malloc(sizeof(TDvdHash));
    fread(noAtual, sizeof(TDvdHash), 1, arquivo);

    while(noAtual != NULL && noAtual->dvdHash.id_dvd != id) {
        noAtual = noAtual->proximo;
    }
    if(noAtual == NULL) {
        printf("Dvd não encontrado\n");
    } else {
        printf("Dvd encontrado: %s\n", noAtual->dvdHash.nome_dvd);
    }
}

void removerHashFile(TabelaHash* tabela, int id, FILE* file) {
    int index = funcaoHash(id, tabela->tamanho);

    fseek(file, index * sizeof(TDvdHash), SEEK_SET);
    TDvdHash* noAtual = (TDvdHash*) malloc(sizeof(TDvdHash));
    fread(noAtual, sizeof(TDvdHash), 1, file);

    TDvdHash* noAnterior = NULL;
    while(noAtual != NULL && noAtual->dvdHash.id_dvd != id) {
        noAnterior = noAtual;
        noAtual = noAtual->proximo;
    }
    if(noAtual == NULL) {
        printf("Dvd não encontrado\n");
    } else {
        if(noAnterior == NULL) {
            fseek(file, index * sizeof(TDvdHash), SEEK_SET);
            fwrite(noAtual->proximo, sizeof(TDvdHash), 1, file);
            printf("Dvd removido com sucesso.\n");
        } else {
            noAnterior->proximo = noAtual->proximo;
            fseek(file, -sizeof(TDvdHash), SEEK_CUR);
            fwrite(noAnterior, sizeof(TDvdHash), 1, file);
            printf("Dvd removido com sucesso!");
        }
        free(noAtual);
    }
}
/*In your imprimirHashTable function, you're trying to access the proximo field of noAtual in the while loop:
However, noAtual->proximo is never initialized or assigned a value in the function.
This means that it's likely pointing to an invalid memory location, causing a segmentation fault
when you try to access it.  Remember that when you read from the file with fread, it only reads
 the data for the TDvdHash structure. It doesn't set up the proximo pointers to form a linked list
 in memory. If your hash table uses chaining with linked lists to resolve collisions, you'll need
 to set up these links manually after reading the data from the file.  Also, note that the fread
 function does not return a null pointer when it reaches the end of the file. Instead, it returns
 the number of items successfully read. If this number is less than the number of items you asked
 for, it means that the end of the file was reached or an error occurred. You should check this
 return value to determine when to stop reading from the file.*/

void imprimirHashTable(TabelaHash* tabela, FILE* file) {
    TDvdHash* noAtual = (TDvdHash*) malloc(sizeof(TDvdHash));

    for(int i=0; i<tabela->tamanho; i++) {
        fseek(file, i * sizeof(TDvdHash), SEEK_SET);
        fread(noAtual, sizeof(TDvdHash), 1, file);

        while(noAtual->dvdHash.id_dvd != -1) {
            printf("ID: %d\n", noAtual->dvdHash.id_dvd);
            printf("Titulo: %s\n", noAtual->dvdHash.nome_dvd);
            printf("Genero: %s\n", noAtual->dvdHash.genero);
            printf("Emprestimo: %d\n", noAtual->dvdHash.emprestimo);
            printf("--------------------\n");

            if(noAtual->proximo != -1) {
                fseek(file, (long)noAtual->proximo * sizeof(TDvdHash), SEEK_SET);
                fread(noAtual, sizeof(TDvdHash), 1, file);
            } else {
                break;
            }
        }
    }

    free(noAtual);
}