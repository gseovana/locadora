//
// Created by geovana on 1/5/24.
//

#ifndef LOCADORA_TAGEO_ARVOREBINARIAVENCEDORES_H
#define LOCADORA_TAGEO_ARVOREBINARIAVENCEDORES_H

#include "locadora.h"

void arvoreVencDvd(TDvd **dvd, FILE *arq, int tam, int *arvoreAux);
void arvoreBinariaVencDvd(int qtdParticoes);

void arvoreVencCliente(TCliente **cliente, FILE *arq, int tam, int *arvoreAux);
void arvoreBinariaVencCliente(int qtdParticoes);

#endif //LOCADORA_TAGEO_ARVOREBINARIAVENCEDORES_H
