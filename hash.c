//
// Created by geovana on 1/30/24.
//Tabela
#include "locadora.h"
#include "hash.h"

TabelaHash* criarTabelaHash(int tamanho, FILE* file) {

    //aloca memoria para uma nova tabela hash
    //tabela hash é uma strcut que contem o amanho e uma outra struct que contem o dvd e um ponteiro para o prox

    TabelaHash* novaTabela = (TabelaHash*) malloc(sizeof(TabelaHash));
    novaTabela->tamanho = tamanho;

    //aloca memoeria para o struct TDVdHash da tabelaHash
    //essa tabela hash é como se fosse a "cabeça" da lista encadeade de aeds 1
    TDvdHash* noVazio = (TDvdHash*) malloc(sizeof(TDvdHash));

    // inicializa os valores padrão
    noVazio->dvdH.id_dvd = -1;
    noVazio->proximo = NULL;

    //salva no arquivo a quantidade de nós vazios referentes ao tamanho da tabelaHash
    for(int i=0; i<tamanho; i++) {
        fwrite(noVazio, sizeof(TDvdHash), 1, file);
    }

    //libera noVazio e retorna a tabela
    free(noVazio);
    return novaTabela;
}

int funcaoHash(int id, int tamanho) {
    return id % tamanho;
}

void inserirHashFile(TabelaHash* tabela, TDvd dvd, FILE* arquivo) {

    //cria um novo struct TDvdHash
    TDvdHash* novoNoTDvdHash = (TDvdHash*) malloc(sizeof(TDvdHash));

    //inicializa ele colocando o dvd que veio como parametro e o proximo como NULL(até pq n sabemos quem é o proximo)
    novoNoTDvdHash->dvdH = dvd;
    novoNoTDvdHash->proximo = NULL;

    //usa o index para saber onde salvar o novoNoTDvdHash
    int index = funcaoHash(dvd.id_dvd, tabela->tamanho);

    //rebobina o arquivo
    rewind(arquivo);

    //vai até a posicao do index e lê o que tem lá
    fseek(arquivo, index * sizeof(TDvdHash), SEEK_SET);

    //cria um novo TDvdHash e lê o que tem na posicao do index
    TDvdHash* noAtual = (TDvdHash*) malloc(sizeof(TDvdHash));
    fread(noAtual, sizeof(TDvdHash), 1, arquivo);

    //se o que tem na posicao do index é NULL, ou seja, não tem nada lá, ele escreve o novoNoTDvdHash
    if(noAtual == NULL) {
        fwrite(novoNoTDvdHash, sizeof(TDvdHash), 1, arquivo);
    } else {
        //se não, ele vai até o final da lista encadeada e escreve o novoNoTDvdHash
        while(noAtual->proximo != NULL) {
            noAtual = noAtual->proximo;
        }
        //insere o novoNoTDvdHash no final da lista encadeada
        noAtual->proximo = novoNoTDvdHash;

        fseek(arquivo, -sizeof(TDvdHash), SEEK_CUR);
        fwrite(noAtual, sizeof(TDvdHash), 1, arquivo);
    }
}

void buscarHashFile(TabelaHash* tabela, int id, FILE* arquivo) {

    //usa o index para saber onde procurar o dvd
    int index = funcaoHash(id, tabela->tamanho);

    //vai ate a posicao do index e lê o que têm lá
    fseek(arquivo, index * sizeof(TDvdHash), SEEK_SET);
    TDvdHash* noAtual = (TDvdHash*) malloc(sizeof(TDvdHash));
    fread(noAtual, sizeof(TDvdHash), 1, arquivo);

    //enquanto o que tem na posicao do index é diferente de NULL e o id do dvd é diferente do id que estamos procurando
    while(noAtual != NULL && noAtual->dvdH.id_dvd != id) {
        noAtual = noAtual->proximo;
    }
    if(noAtual == NULL) {
        printf("Dvd não encontrado.\n");
    } else {
        printf("Dvd encontrado!\n");
        imprimeDvd(&noAtual->dvdH);
    }
}

void removerHashFile(TabelaHash* tabela, int id, FILE* file) {
    int index = funcaoHash(id, tabela->tamanho);

    fseek(file, index * sizeof(TDvdHash), SEEK_SET);
    TDvdHash* noAtual = (TDvdHash*) malloc(sizeof(TDvdHash));
    fread(noAtual, sizeof(TDvdHash), 1, file);

    TDvdHash* noAnterior = NULL;
    while(noAtual != NULL && noAtual->dvdH.id_dvd != id) {
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
    //noAtual->dvdHash = dvd; // Initialize the TDvdHash object
    noAtual->proximo = NULL; // Initialize the proximo field

    for(int i=0; i<tabela->tamanho; i++) {
        fseek(file, i * sizeof(TDvdHash), SEEK_SET);
        fread(noAtual, sizeof(TDvdHash), 1, file);

        while(noAtual->dvdH.id_dvd != NULL) {
            printf("ID: %d\n", noAtual->dvdH.id_dvd);
            printf("Titulo: %s\n", noAtual->dvdH.nome_dvd);
            printf("Genero: %s\n", noAtual->dvdH.genero);
            printf("Emprestimo: %d\n", noAtual->dvdH.emprestimo);
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