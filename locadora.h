#ifndef LOCADORA_H_INCLUDED
#define LOCADORA_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

typedef struct{
    char cliente[50];
    char funcionario[50];
    int cod;
    char tipo[50];//filme ou musica
    char genero[50]; // ação , comédia, pagode, sertanejo
    int emprestimo; //Se esta emprestado ou não 0 false , 1 true
}TLocadora;


int tamanho_registro();

TLocadora *CriarLocadora(char *cliente , char *funcionario, int cod, char *tipo, char *genero, int emprestimo);

void salva(TLocadora *locadora, FILE *arq);

int tamanho_arquivo(FILE *arq);

TLocadora *ler(FILE *arq);

void imprime(TLocadora *locadora);

void criarBase(FILE *arq, int tam);

void shuffle(int *vet,int MAX,int MIN);

void imprimirBase(FILE *arq);

#endif
