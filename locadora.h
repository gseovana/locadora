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

typedef struct dvd_est {
    int id_dvd;
    char nome_dvd[100];
    char genero[100];
    int emprestimo; // 0 disponivel , 1 emprestado
} TDvd;

typedef struct{
    int id_locacao;
    TDvd dvdL;
    TCliente clienteL;
}TLocadora;

typedef struct{
    TDvd *dvd;
    long init_pd;
    long end_pd;
    FILE *filePartitiond;
}TDvdFile;

typedef struct{
    TCliente *cliente;
    long init_pc;
    long end_pc;
    FILE *filePartitionc;
}TClienteFile;

typedef struct TDvdHash {
    TDvd dvdH;
    struct TDvdHash* proximo;
} TDvdHash;

typedef struct TabelaHash {
    int tamanho;
    TDvdHash** tabelaHash;
} TabelaHash;

//int tamanho_registro();
void shuffle(int *vet,int MAX,int MIN);
int tamanho_arquivo_dvd(FILE *arq);
int tamanho_arquivo_cliente(FILE *arq);

//Cliente
TCliente *criarCliente(int idC ,char *nomeC , char *dataNascimentoC, char *cpfC, char *telefoneC);

void salvarCliente(TCliente *cliente, FILE *arq);

TCliente *lerCliente(FILE *arq);

TCliente *buscaSequencialCliente(int chave, FILE *arq, const char *nomeArquivoLog);

void imprimeCliente(TCliente *cliente);

void criarBaseCliente(FILE *arq, int tam);

void imprimirBaseCliente(FILE *arq);


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

TLocadora *criarLocadora(int id_locacao, TDvd dvd, TCliente cliente);

void salvarLocadora(TLocadora *locadora, FILE *arqLocadora);

void imprimeLocadora(TLocadora *locadora);

void criarBaseLocadora(FILE *arqLocadora, FILE *arqCliente, FILE *arqDvd, int tam);
void imprimirBaseLocadora(FILE *arqLocadora);
int quicksort(FILE *arq, int low, int high);

TLocadora *buscaBinariaLocacao(int chave, FILE *in, int inicio, int fim, const char *nomeArquivoLog);

void dvdsDisponiveis(FILE *arq);

void alugaDvd(int gerador_id_locadora, FILE *arqClientes, FILE *arqDvds, FILE *arqLocadora);
void imprimirDvdAlugado(FILE *arq, FILE *arqD, FILE *arqC);
void devolverDvd(FILE *arqDvds);


int excluiCliente(int chave, FILE *arqClientes);

int excluiDvd(int chave, FILE *arqDvds);
int tamanhoRegistroLocadora();
char* itoa(int value, char* result, int base);
int tamanhoRegistroDvd();
int tamanhoRegistroCliente();

#endif