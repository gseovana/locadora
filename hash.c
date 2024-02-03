//
// Created by geovana on 1/30/24.
//Tabela
#include "locadora.h"
#include "hash.h"

TabelaHash* criarTabelaHash(int tamanho, FILE* file) {
    TabelaHash* novaTabela = (TabelaHash*) malloc(sizeof(TabelaHash));
    novaTabela->tamanho = tamanho;

    TDvdHash* noVazio = (TDvdHash*) malloc(sizeof(TDvdHash));
    noVazio->dvdH.id_dvd = -1;
    noVazio->proximoIndex = -1;

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
    novoNoTDvdHash->dvdH = dvd;
    novoNoTDvdHash->proximoIndex = -1;

    int index = funcaoHash(dvd.id_dvd, tabela->tamanho);
    rewind(arquivo);
    fseek(arquivo, index * sizeof(TDvdHash), SEEK_SET);
    TDvdHash* noAtual = (TDvdHash*) malloc(sizeof(TDvdHash));
    fread(noAtual, sizeof(TDvdHash), 1, arquivo);

    if(noAtual->dvdH.id_dvd == -1) {
        fseek(arquivo, index * sizeof(TDvdHash), SEEK_SET);
        fwrite(novoNoTDvdHash, sizeof(TDvdHash), 1, arquivo);
    } else {
        while(noAtual->proximoIndex != -1) {
            fseek(arquivo, noAtual->proximoIndex * sizeof(TDvdHash), SEEK_SET);
            fread(noAtual, sizeof(TDvdHash), 1, arquivo);
        }
        int nextIndex = index + 1;
        fseek(arquivo, nextIndex * sizeof(TDvdHash), SEEK_SET);
        fread(noAtual, sizeof(TDvdHash), 1, arquivo);
        while(noAtual->dvdH.id_dvd != -1) {
            nextIndex++;
            fseek(arquivo, nextIndex * sizeof(TDvdHash), SEEK_SET);
            fread(noAtual, sizeof(TDvdHash), 1, arquivo);
        }
        noAtual->proximoIndex = nextIndex;
        fseek(arquivo, nextIndex * sizeof(TDvdHash), SEEK_SET);
        fwrite(novoNoTDvdHash, sizeof(TDvdHash), 1, arquivo);
    }
    free(noAtual);
    free(novoNoTDvdHash);
}

void buscarHashFile(TabelaHash* tabela, int id, FILE* arquivo) {
    // Reset the file pointer to the beginning of the file
    rewind(arquivo);

    // Use the hash function to find the index where the DVD should be
    int index = funcaoHash(id, tabela->tamanho);

    // Go to the position of the index and read what's there
    fseek(arquivo, index * sizeof(TDvdHash), SEEK_SET);
    TDvdHash* noAtual = (TDvdHash*) malloc(sizeof(TDvdHash));
    int read = fread(noAtual, sizeof(TDvdHash), 1, arquivo);

    // While what's at the position of the index is not NULL and the DVD's id is not the id we're looking for
    while(read > 0 && noAtual->dvdH.id_dvd != id) {
        // If the current node is not the one we're looking for and there's a next node
        if(noAtual->proximoIndex != -1) {
            // Go to the next node in the chain
            fseek(arquivo, noAtual->proximoIndex * sizeof(TDvdHash), SEEK_SET);
            // Read the next node from the file into noAtual
            read = fread(noAtual, sizeof(TDvdHash), 1, arquivo);
        } else {
            // If there's no next node, stop the search
            break;
        }
    }
    if(read == 0 || noAtual->dvdH.id_dvd != id) {
        printf("Dvd não encontrado.\n");
    } else {
        printf("Dvd encontrado!\n");
        imprimeDvd(&noAtual->dvdH);
    }
    free(noAtual);
}

void removerHashFile(TabelaHash* tabela, int id, FILE* file) {
    int index = funcaoHash(id, tabela->tamanho);
    TDvdHash* dvdHash = (TDvdHash*) malloc(sizeof(TDvdHash));

    fseek(file, index * sizeof(TDvdHash), SEEK_SET);
    fread(dvdHash, sizeof(TDvdHash), 1, file);

    while(dvdHash->dvdH.id_dvd != id && dvdHash->proximoIndex != -1) {
        index = dvdHash->proximoIndex;
        fseek(file, index * sizeof(TDvdHash), SEEK_SET);
        fread(dvdHash, sizeof(TDvdHash), 1, file);
    }

    if(dvdHash->dvdH.id_dvd == id) {
        // Create an empty record
        TDvdHash* emptyRecord = (TDvdHash*) malloc(sizeof(TDvdHash));
        emptyRecord->dvdH.id_dvd = -1;
        emptyRecord->proximoIndex = dvdHash->proximoIndex;

        // Overwrite the record to be deleted with the empty record
        fseek(file, index * sizeof(TDvdHash), SEEK_SET);
        fwrite(emptyRecord, sizeof(TDvdHash), 1, file);
        printf("DVD removed successfully.\n");

        free(emptyRecord);
    } else {
        printf("DVD not found.\n");
    }

    free(dvdHash);
}
