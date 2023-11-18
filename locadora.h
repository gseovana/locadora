#ifndef LOCADORA_H_INCLUDED
#define LOCADORA_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

typedef struct{
    int idC;
    char nomeC[100];
    char dataNascimentoC[50];
    char cpfC[50];
    char telefoneC[50];
}TCliente;

typedef struct{
    int idF;
    char nomeF[50];
    char cpfF[20];
    double salarioF;
}TFuncionario;

typedef struct dvd_est {
    int id_dvd;
    char nome_dvd[100];
    char genero[100];
    int emprestimo; // 0 disponivel , 1 emprestado
} TDvd;

typedef struct{
    int id_transacao;
    int id_dvd;
    int id_cliente;
}TLocadora;

typedef TDvd Dvds[1000];

//int tamanho_registro();
void shuffle(int *vet,int MAX,int MIN);

//Cliente
TCliente *criarCliente(int idC ,char *nomeC , char *dataNascimentoC, char *cpfC, char *telefoneC);

void salvarCliente(TCliente *cliente, FILE *arq);

TCliente *lerCliente(FILE *arq);

TCliente *buscaSequencial(int chave, FILE *arq, const char *nomeArquivoLog);

void imprimeCliente(TCliente *cliente);

void criarBaseCliente(FILE *arq, int tam);

void imprimirBaseCliente(FILE *arq);

//Funcionario
TFuncionario *criarFuncionario(int idF, char *nomeF, char *cpfF, double salarioF);

void salvarFuncionario(TFuncionario *funcionario, FILE *arq);

TFuncionario *lerFuncionario(FILE *arq);

void imprimeFuncionario(TFuncionario *funcionario);

void criarBaseFuncionario(FILE *arq, int tam);

void imprimirBaseFuncionario(FILE *arq);

//Dvd
TDvd *criarDvd(int id_dvd, char *nome_dvd, char *genero, int emprestimo);

void salvarDvd(TDvd *dvd, FILE *arq);

TDvd *lerDvd(FILE *arq);

void imprimeDvd(TDvd *dvd);

void criarBaseDvd(FILE *arq, int tam);

void imprimirBaseDvd(FILE *arq);

TDvd *buscaSequencialDvds(int chave, FILE *arq, const char *nomeArquivoLog);

//Locadora
TLocadora *lerRegistrosLocadora(FILE *arq);

TLocadora *criarLocadora(int id_dvd, int id_cliente);

void salvarLocadora(TLocadora *locadora, FILE *arqLocadora);

void imprimeLocadora(TLocadora *locadora);

void criarBaseLocadora(FILE *arqLocadora, int tam);

void imprimirBaseLocadora(FILE *arqLocadora);

//outros
void dvdsDisponiveis(FILE *arq);

void alugaDvd(FILE *arqClientes, FILE *arqDvds, FILE *arqLocadora);

void imprimirDvdsAlugados(FILE *arqDvds, FILE *arqLocadora);

int excluiDvd(int chave, FILE *in);


#endif
