//
// Created by geovana on 1/30/24.
//Tabela
//#include "locadora.h"
#include "hash.h"
#include <sys/time.h>
#include <time.h>

TabelaHash* criarTabelaHash(int tamanho, FILE* file, FILE* logHash) {  // recebe o tamanho desejado da tabela hash e um ponteiro para um arquivo onde a tabela hash será armazenada.
    struct timespec inicioTime, fimTime;
    double tempoGasto;
    clock_t inicioClock, fimClock;

    clock_gettime(CLOCK_MONOTONIC, &inicioTime);

    TabelaHash* novaTabela = (TabelaHash*) malloc(sizeof(TabelaHash)); //Aloca dinamicamente espaço na memória para armazenar a estrutura TabelaHash, que representa a tabela hash.
    novaTabela->tamanho = tamanho; //Atribui o tamanho desejado para a nova tabela hash.

    TDvdHash* noVazio = (TDvdHash*) malloc(sizeof(TDvdHash)); //Aloca dinamicamente espaço para um nó que será utilizado para representar uma posição vazia na tabela hash.
    noVazio->dvdH.id_dvd = -1; //mostra que o id e o ponteiro esta vazio
    noVazio->proximoIndex = -1;

    for(int i=0; i<tamanho; i++) {
        fwrite(noVazio, sizeof(TDvdHash), 1, file); // Utiliza um loop para escrever o nó vazio em cada posição da tabela hash no arquivo. Isso inicializa o arquivo com todas as posições marcadas como vazias.
    }

    free(noVazio);

    clock_gettime(CLOCK_MONOTONIC, &fimTime);
    tempoGasto = (fimTime.tv_sec - inicioTime.tv_sec) * 1000.0; // seconds to milliseconds
    tempoGasto += (fimTime.tv_nsec - inicioTime.tv_nsec) / 1000000.0; // nanoseconds to milliseconds

    // Escrevendo no arquivo de log
    fprintf(logHash, "CRIAR TABELA HASH %f milissegundos",tempoGasto);
    fclose(logHash);


    return novaTabela;// Retorna o ponteiro para a tabela hash recém-criada.
}

int funcaoHash(int id, int tamanho) {
    return id % tamanho; // resto da divisão do numero do id pelo tamanho da hash. Achar qual posição da tabela hash vai ficar

}

void inserirHashFile(TabelaHash* tabela, TDvd dvd, FILE* arquivo, FILE* logHashInserir) { //  inserir um registro de DVD em uma tabela hash armazenada em um arquivo binário.
    struct timespec inicioTime, fimTime;
    double tempoGasto;
    clock_t inicioClock, fimClock;

    clock_gettime(CLOCK_MONOTONIC, &inicioTime);

    TDvdHash* novoNoTDvdHash = (TDvdHash*) malloc(sizeof(TDvdHash)); // aloca espaço para o no a ser inserido na tabela hash
    novoNoTDvdHash->dvdH = dvd; // copia o dado dvd para o campo dvdH da tabela hash
    novoNoTDvdHash->proximoIndex = -1; // o ponteiro dele nao aponta para ngn

    int index = funcaoHash(dvd.id_dvd, tabela->tamanho);// calcula a posição que vai colocar na hash
    rewind(arquivo);
    fseek(arquivo, index * sizeof(TDvdHash), SEEK_SET);// coloca o cursor na posição que foi calculada para colocar o "dado"
    TDvdHash* noAtual = (TDvdHash*) malloc(sizeof(TDvdHash)); // Aloca dinamicamente espaço para um nó temporário, que será utilizado para ler o conteúdo do arquivo na posição indicada.
    fread(noAtual, sizeof(TDvdHash), 1, arquivo); //Lê o conteúdo do arquivo na posição indicada e armazena no nó temporário.

    if(noAtual->dvdH.id_dvd == -1) { //Verifica se o nó na posição atual está vazio.
        fseek(arquivo, index * sizeof(TDvdHash), SEEK_SET);// posiciona o cursor no local que foi calculado
        fwrite(novoNoTDvdHash, sizeof(TDvdHash), 1, arquivo);//Se estiver vazio, significa que não há colisão, e o novo nó é escrito diretamente no arquivo na posição calculada.
    } else {
        while(noAtual->proximoIndex != -1) { //Se não estiver vazio, significa que há colisão. Nesse caso, o código entra em um loop para encontrar a próxima posição disponível na tabela hash.
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

    clock_gettime(CLOCK_MONOTONIC, &fimTime);
    tempoGasto = (fimTime.tv_sec - inicioTime.tv_sec) * 1000.0; // seconds to milliseconds
    tempoGasto += (fimTime.tv_nsec - inicioTime.tv_nsec) / 1000000.0; // nanoseconds to milliseconds

    // Escrevendo no arquivo de log
    fprintf(logHashInserir, "INSERIR TABELA HASH %f milissegundos",tempoGasto);
    fclose(logHashInserir);
}

void buscarHashFile(TabelaHash* tabela, int id, FILE* arquivo, FILE* logHashBuscar) {
    struct timespec inicioTime, fimTime;
    double tempoGasto;
    clock_t inicioClock, fimClock;

    clock_gettime(CLOCK_MONOTONIC, &inicioTime);


    //Redefina o ponteiro do arquivo para o início do arquivo
    rewind(arquivo);

    // Usa a função hash para encontrar o índice onde o DVD esta
    int index = funcaoHash(id, tabela->tamanho);

    // Vai até a posição do índice e leia o que há lá
    fseek(arquivo, index * sizeof(TDvdHash), SEEK_SET); //Posiciona o indicador de posição do arquivo no índice calculado na tabela hash
    TDvdHash* noAtual = (TDvdHash*) malloc(sizeof(TDvdHash)); //Aloca dinamicamente espaço para um nó temporário, que será utilizado para ler o conteúdo do arquivo na posição indicada.
    int read = fread(noAtual, sizeof(TDvdHash), 1, arquivo); // le o dado procurado e coloca no noAtual


    while(read > 0 && noAtual->dvdH.id_dvd != id) { //enquanto a posição nao é nula e nao acha o valor procurado faz:

        if(noAtual->proximoIndex != -1) { //Se o nó atual não é o que estamos procurando e há um próximo nó na lista encadeada, o código avança para o próximo nó na lista.
            fseek(arquivo, noAtual->proximoIndex * sizeof(TDvdHash), SEEK_SET);
            read = fread(noAtual, sizeof(TDvdHash), 1, arquivo);  //Leia o próximo nó do arquivo em noAtual
        } else {
            // Se não houver próximo nó, para
            break;
        }
    }
    if(read == 0 || noAtual->dvdH.id_dvd != id) {
        printf("Dvd nao encontrado.\n");
    } else {
        printf("Dvd encontrado!\n");
        imprimeDvd(&noAtual->dvdH);
    }
    free(noAtual);

    clock_gettime(CLOCK_MONOTONIC, &fimTime);
    tempoGasto = (fimTime.tv_sec - inicioTime.tv_sec) * 1000.0; // seconds to milliseconds
    tempoGasto += (fimTime.tv_nsec - inicioTime.tv_nsec) / 1000000.0; // nanoseconds to milliseconds

    // Escrevendo no arquivo de log
    fprintf(logHashBuscar, "BUSCAR TABELA HASH %f milissegundos",tempoGasto);
    fclose(logHashBuscar);
}

void removerHashFile(TabelaHash* tabela, int id, FILE* file, FILE* logHashRemover) {
    struct timespec inicioTime, fimTime;
    double tempoGasto;
    clock_t inicioClock, fimClock;

    clock_gettime(CLOCK_MONOTONIC, &inicioTime);

    int index = funcaoHash(id, tabela->tamanho);
    TDvdHash* dvdHash = (TDvdHash*) malloc(sizeof(TDvdHash));
    TDvdHash* prevDvdHash = NULL;

    fseek(file, index * sizeof(TDvdHash), SEEK_SET);
    fread(dvdHash, sizeof(TDvdHash), 1, file);

    while(dvdHash->dvdH.id_dvd != id && dvdHash->proximoIndex != -1) {
        if (prevDvdHash != NULL) {
            free(prevDvdHash);
        }
        prevDvdHash = dvdHash;
        index = dvdHash->proximoIndex;
        dvdHash = (TDvdHash*) malloc(sizeof(TDvdHash));
        fseek(file, index * sizeof(TDvdHash), SEEK_SET);
        fread(dvdHash, sizeof(TDvdHash), 1, file);
    }

    if(dvdHash->dvdH.id_dvd == id) {
        if (prevDvdHash != NULL) {
            prevDvdHash->proximoIndex = dvdHash->proximoIndex;
            fseek(file, (index - 1) * sizeof(TDvdHash), SEEK_SET);
            fwrite(prevDvdHash, sizeof(TDvdHash), 1, file);
        }

        TDvdHash* emptyRecord = (TDvdHash*) malloc(sizeof(TDvdHash));
        emptyRecord->dvdH.id_dvd = -1;
        emptyRecord->proximoIndex = -1;

        fseek(file, index * sizeof(TDvdHash), SEEK_SET);
        fwrite(emptyRecord, sizeof(TDvdHash), 1, file);
        printf("DVD removido com sucesso.\n");

        free(emptyRecord);
    } else {
        printf("DVD nao encontrado.\n");
    }

    if (prevDvdHash != NULL) {
        free(prevDvdHash);
    }
    free(dvdHash);

    clock_gettime(CLOCK_MONOTONIC, &fimTime);
    tempoGasto = (fimTime.tv_sec - inicioTime.tv_sec) * 1000.0;
    tempoGasto += (fimTime.tv_nsec - inicioTime.tv_nsec) / 1000000.0;

    fprintf(logHashRemover, "REMOVER TABELA HASH %f milissegundos",tempoGasto);
    fclose(logHashRemover);
}

void imprimirTabelaHash(TabelaHash* tabela, FILE* arquivo, FILE* logHashImprimir) {
    struct timespec inicioTime, fimTime;
    double tempoGasto;
    clock_t inicioClock, fimClock;

    clock_gettime(CLOCK_MONOTONIC, &inicioTime);

    TDvdHash* noAtual = (TDvdHash*) malloc(sizeof(TDvdHash)); // Aloca espaço para um nó temporário que será usado para ler o conteúdo do arquivo.

    for(int i=0; i<tabela->tamanho; i++) { // Percorre todas as posições da tabela hash.
        fseek(arquivo, i * sizeof(TDvdHash), SEEK_SET); // Posiciona o indicador de posição do arquivo na posição atual da tabela hash.
        fread(noAtual, sizeof(TDvdHash), 1, arquivo); // Lê o conteúdo do arquivo na posição atual e armazena no nó temporário.

        if(noAtual->dvdH.id_dvd != -1) { // Verifica se a posição atual da tabela hash não está vazia.
            printf("Posicao %d:\n", i); // Imprime o índice da posição atual.
            imprimeDvd(&noAtual->dvdH); // Imprime o DVD na posição atual.

            while(noAtual->proximoIndex != -1) { // Se houver um próximo nó na lista encadeada, entra em um loop para imprimir todos os nós na lista.
                fseek(arquivo, noAtual->proximoIndex * sizeof(TDvdHash), SEEK_SET);
                fread(noAtual, sizeof(TDvdHash), 1, arquivo);
                imprimeDvd(&noAtual->dvdH);
            }
        }else{
            if (noAtual->proximoIndex != -1){
                fseek(arquivo, noAtual->proximoIndex * sizeof(TDvdHash), SEEK_SET);
                fread(noAtual, sizeof(TDvdHash), 1, arquivo);
                imprimeDvd(&noAtual->dvdH);
            }
        }
    }

    free(noAtual);

    clock_gettime(CLOCK_MONOTONIC, &fimTime);
    tempoGasto = (fimTime.tv_sec - inicioTime.tv_sec) * 1000.0; // seconds to milliseconds
    tempoGasto += (fimTime.tv_nsec - inicioTime.tv_nsec) / 1000000.0; // nanoseconds to milliseconds

    // Escrevendo no arquivo de log
    fprintf(logHashImprimir, "IMPRIMIR TABELA HASH %f milissegundos",tempoGasto);
    fclose(logHashImprimir);
}