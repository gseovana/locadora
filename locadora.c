#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "locadora.h"


int tamanho_registro(){
    return sizeof(char)*50 //cliente
         + sizeof(char)*50 //funcionario
         + sizeof(int); //cod
         + sizeof(char)*50 //tipo
         + sizeof(char)*50 //genero
         + sizeof(int); 
}

TLocadora *CriarLocadora(char *cliente , char *funcionario, int cod, char *tipo, char *genero,int emprestimo){

    TLocadora *locadora = (TLocadora *) malloc(sizeof(TLocadora));

    if(locadora) memset(locadora, 0, sizeof(locadora)); // memset( lugar que vai guardar a copia, o que vai ser copiado, n� de bytes que recebera a copia);
        strcpy(locadora->cliente, cliente);
        strcpy(locadora->funcionario, funcionario); //strcpy copia uma string para outra
        locadora->cod = cod;
        strcpy(locadora->tipo, tipo);
        strcpy(locadora->genero, genero);
        locadora->emprestimo = emprestimo;

        return locadora;
}

void salva(TLocadora *locadora, FILE *arq){
    fwrite(locadora->cliente, sizeof(char), sizeof(locadora->cliente), arq); //fwrite(onde na memoria esta os dados, tamanho de unidade que vai salvar, total de dados que v�o ser gravados, arquivo onde vai salvar).
    fwrite(locadora->funcionario, sizeof(char), sizeof(locadora->funcionario), arq);
    fwrite(&locadora->cod, sizeof(int), 1, arq);
    fwrite(locadora->genero, sizeof(char), sizeof(locadora->genero), arq);
    fwrite(locadora->tipo, sizeof(char), sizeof(locadora->tipo), arq);
    fwrite(&locadora->emprestimo, sizeof(int), 1, arq);
}

int tamanho_arquivo(FILE *arq){
    fseek(arq, 0, SEEK_END); // Fun�ao que inicia com o ponteiro no inicio do arquivo e pula para onde passar; fseek( arquivo que vai procurar, pular numero de bytes, a partir de qual origem). SEEK_END: esta no final do arquivo, dizer numeros negativos para pular do final em sentido do inicio.
    int tam = trunc(ftell(arq) / tamanho_registro());
    return tam;
}

TLocadora *ler(FILE *arq){
     TLocadora *locadora = (TLocadora *) malloc(sizeof(TLocadora));

     if (0 >= fread(&locadora->cod, sizeof(int), 1, arq)) {   //explica��o?
        free(locadora);
        return NULL;
    }
    fread(locadora->funcionario, sizeof(char), sizeof(locadora->funcionario), arq);
    fread(locadora->cliente, sizeof(char), sizeof(locadora->cliente), arq);
    fread(locadora->genero, sizeof(char), sizeof(locadora->genero), arq);
    fread(locadora->tipo, sizeof(char), sizeof(locadora->tipo), arq);
    fread(&locadora->emprestimo, sizeof(int), 1, arq);

    return locadora;
}

void imprime(TLocadora *locadora){
    printf("**********************************************");
    printf("\nNome do funcionario: ");
    printf("%s", locadora->funcionario);
    printf("\nNome do cliente: ");
    printf("%s", locadora->cliente);
    printf("\nCodigo do produto: ");
    printf("%d", locadora->cod);
    printf("\nTipo do produto: ");
    printf("%s", locadora->tipo);
    printf("\nGenero do produto: ");
    printf("%s", locadora->genero);
    printf("\n**********************************************");
}

void criarBase(FILE *arq, int tam){
int vet[tam];
    TLocadora *locad;

    for(int i=0;i<tam;i++)
        vet[i] = i+1;

    shuffle(vet,tam,(tam*10)/100); // embaralhar

    printf("\nGerando a base de dados...\n");

    for (int i=0;i<tam;i++){
        locad = CriarLocadora("Alex" , "Talia" , vet[i], "filme", "comedia", 0);
        salva(locad, arq);
    }

    free(locad);
}

void shuffle(int *vet,int MAX,int MIN) {
    srand(time(NULL));
    for (int i = MAX - MIN - 1; i > 0; i--) {
        int j = rand() % (i);
        int tmp = vet[j];
        vet[j] = vet[i];
        vet[i] = tmp;
    }
}

void imprimirBase(FILE *arq){

printf("\Imprimindo a base de dados...\n");

    rewind(arq);
    TLocadora *locad;

    while ((locad = ler(arq)) != NULL)
        imprime(locad);

    free(locad);

}
