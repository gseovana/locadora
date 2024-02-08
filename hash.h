//
// Created by geovana on 1/30/24.
//

#ifndef LOCADORA_TAGEO_HASH_H
#define LOCADORA_TAGEO_HASH_H
#include <stdio.h>
#include "locadora.h"

TabelaHash* criarTabelaHash(int tamanho, FILE* file, FILE* logHash); // recebe o tamanho desejado da tabela hash e um ponteiro para um arquivo onde a tabela hash será armazenada.
void inserirHashFile(TabelaHash* tabela, TDvd dvd, FILE* arquivo, FILE* logHashInserir); //  inserir um registro de DVD em uma tabela hash armazenada em um arquivo binário.
void buscarHashFile(TabelaHash* tabela, int id, FILE* arquivo, FILE* logHashBuscar);
void removerHashFile(TabelaHash* tabela, int id, FILE* file, FILE* logHashRemover);
void imprimirTabelaHash(TabelaHash* tabela, FILE* arquivo, FILE* logHashImprimir);
#endif //LOCADORA_TAGEO_HASH_H
