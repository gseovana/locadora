#ifndef LOCADORA_H_INCLUDED
#define LOCADORA_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

typedef struct{
    char nomeC[50];
    char dataNascimentoC[20];
    char cpfC[20];
    int idC;
    char telefoneC[10];
}TCliente;

typedef struct{
    char nomeF[50];
    char cpfF[20];
    int idF;
    double salarioF;
}TFuncionario;

typedef struct dvd_est {
    int id_dvd;
    char nome_dvd[100];
    int ano_lancamento;
    char diretor[50];
    char genero[100];
    int empretimo; // 0 disponivel , 1 emprestado
} TDvd;



//int tamanho_registro();
void shuffle(int *vet,int MAX,int MIN);

//Cliente
TCliente *criarCliente(char *nomeC , char *dataNascimentoC, char *cpfC, int idC, char *telefoneC);

void salvarCliente(TCliente *cliente, FILE *arq);

TCliente *lerCliente(FILE *arq);

void imprimeCliente(TCliente *cliente);

void criarBaseCliente(FILE *arq, int tam);

void imprimirBaseCliente(FILE *arq);

//Funcionario
TFuncionario *criarFuncionario(char *nomeF, char *cpfF, int idF, double salarioF);

void salvarFuncionario(TFuncionario *funcionario, FILE *arq);

TFuncionario *lerFuncionario(FILE *arq);

void imprimeFuncionario(TFuncionario *funcionario);

void criarBaseFuncionario(FILE *arq, int tam);

void imprimirBaseFuncionario(FILE *arq);

//Dvd
TDvd *criarDvd(int id_dvd, char *nome_dvd, int ano_lancamento, char *diretor, char *genero, int emprestimo);

void salvarDvd(TDvd *dvd, FILE *arq);

TDvd *lerDvd(FILE *arq);

void imprimeDvd(TDvd *dvd);

void criarBaseDvd(FILE *arq, int tam);

void imprimirBaseDvd(FILE *arq);

/*int tamanho_arquivo(FILE *arq);

void imprime(TLocadora *locadora);

void shuffle(int *vet,int MAX,int MIN);

void imprimirBase(FILE *arq); */

#endif
