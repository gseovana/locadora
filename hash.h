//
// Created by geovana on 1/30/24.
//

#ifndef LOCADORA_TAGEO_HASH_H
#define LOCADORA_TAGEO_HASH_H
#include <stdio.h>
#include "locadora.h"

TabelaHash* criarTabelaHash(int tamanho, FILE* file);
void inserirHashFile(TabelaHash* tabela, TDvd dvd, FILE* arquivo);
void buscarHashFile(TabelaHash* tabela, int id, FILE* arquivo);
void removerHashFile(TabelaHash* tabela, int id, FILE* file);
void imprimirHashTable(TabelaHash* tabela, FILE* file);

#endif //LOCADORA_TAGEO_HASH_H
