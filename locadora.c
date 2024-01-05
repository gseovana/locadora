#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <math.h>
#include "locadora.h"

void shuffle(int *vet,int MAX,int MIN) {
    srand(time(NULL));
    for (int i = MAX - MIN - 1; i > 0; i--) {
        int j = rand() % (i);
        int tmp = vet[j];
        vet[j] = vet[i];
        vet[i] = tmp;
    }
}

int tamanhoArquivoDvd(FILE *arqD, int contSizeFile) {
    int i = 0;
    TDvd *dvd;

    while ((dvd = lerDvd(arqD)) != NULL) {
        fseek(arqD, i * sizeof(TDvd), SEEK_SET);
        TDvd *aux = lerDvd(arqD);
        if(aux != NULL) {
            contSizeFile++;
        }
        i++;
    }
    return contSizeFile;
}

int tamanhoArquivoCliente(FILE *arqC, int contSizeFile) {
    int i = 0;
    while(!feof(arqC)) {
        fseek(arqC, i * sizeof(TCliente), SEEK_SET);
        TCliente *aux = lerCliente(arqC);
        if(aux != NULL) {
            contSizeFile++;
        }
        i++;
    }
    return contSizeFile;
}

//Cliente
TCliente *criarCliente(int idC, char *nomeC , char *dataNascimentoC, char *cpfC, char *telefoneC){

    TCliente *cliente = (TCliente *) malloc(sizeof(TCliente));

    if(cliente) memset(cliente, 0, sizeof(TCliente)); // memset( lugar que vai guardar a copia, o que vai ser copiado, n� de bytes que recebera a copia);
    cliente->idC = idC;
    strcpy(cliente->nomeC, nomeC);
    strcpy(cliente->dataNascimentoC, dataNascimentoC); //strcpy copia uma string para outra
    strcpy(cliente->cpfC, cpfC);
    strcpy(cliente->telefoneC, telefoneC);

    return cliente;
}

void salvarCliente(TCliente *cliente, FILE *arq){
    fwrite(&cliente->idC, sizeof(int), 1, arq);
    fwrite(cliente->nomeC, sizeof(char), sizeof(cliente->nomeC), arq); //fwrite(onde na memoria esta os dados, tamanho de unidade que vai salvar, total de dados que v�o ser gravados, arquivo onde vai salvar).
    fwrite(cliente->dataNascimentoC, sizeof(char), sizeof(cliente->dataNascimentoC), arq);
    fwrite(cliente->cpfC, sizeof(char), sizeof(cliente->cpfC), arq);
    fwrite(cliente->telefoneC, sizeof(char), sizeof(cliente->telefoneC), arq);
}

TCliente *lerCliente(FILE *arq){
    TCliente *cliente = (TCliente *) malloc(sizeof(TCliente));

    if (0 >= fread(&cliente->idC, sizeof(int), 1, arq)) {
        free(cliente);
        return NULL;
    }
    fread(cliente->nomeC, sizeof(char), sizeof(cliente->nomeC), arq);
    fread(cliente->dataNascimentoC, sizeof(char), sizeof(cliente->dataNascimentoC), arq);
    fread(cliente->cpfC, sizeof(char), sizeof(cliente->cpfC), arq);
    fread(cliente->telefoneC, sizeof(char), sizeof(cliente->telefoneC), arq);

    return cliente;

}

TCliente *buscaSequencialCliente(int chave, FILE *arq, const char *nomeArquivoLog) {
    TCliente *cliente;
    int achou = 0;
    struct timespec inicioTime, fimTime;
    double tempoGasto;
    clock_t inicioClock, fimClock;
    int contComparacao=0;

    FILE *logFile = fopen(nomeArquivoLog, "a"); // Abre o arquivo de log em modo de acréscimo
    if (logFile == NULL) {
        printf("Erro ao abrir arquivo de log\n");
        return NULL;
    }

    clock_gettime(CLOCK_MONOTONIC, &inicioTime);
    rewind(arq);
    while ((cliente = lerCliente(arq)) != NULL) {
        contComparacao++;

        if (cliente->idC == chave) {
            achou = 1;
            break;
        }

        free(cliente); // Libera o cliente se não for o procurado
    }
    clock_gettime(CLOCK_MONOTONIC, &fimTime);
    tempoGasto = (fimTime.tv_sec - inicioTime.tv_sec) * 1000.0; // seconds to milliseconds
    tempoGasto += (fimTime.tv_nsec - inicioTime.tv_nsec) / 1000000.0; // nanoseconds to milliseconds

    // Escrevendo no arquivo de log
    fprintf(logFile, "Busca pela chave %d: \nComparações = %d, Tempo = %f milissegundos\n", chave, contComparacao, tempoGasto);
    fclose(logFile);

    if (achou == 1) {
        return cliente;
    } else {
        printf("Cliente não encontrado\n");
    }

    //printf("Tempo gasto: %f milissegundos\n", tempoGasto);

    return NULL;
}



void imprimeCliente(TCliente *cliente){
    printf("\n*********** CLIENTE ***********");
    printf("\nID: ");
    printf("%d", cliente->idC);
    printf("\nNome: ");
    printf("%s", cliente->nomeC);
    printf("\nData de nascimento: ");
    printf("%s", cliente->dataNascimentoC);
    printf("\nCPF: ");
    printf("%s", cliente->cpfC);
    printf("\nTelefone: ");
    printf("%s", cliente->telefoneC);
    printf("\n");
}

void criarBaseCliente(FILE *arq, int tam){

    int vet[tam];
    TCliente *cliente;

    for(int i=0;i<tam;i++)
        vet[i] = i+1;

    shuffle(vet,tam,(tam*10)/100); // embaralhar

    for (int i=0;i<tam;i++){
        cliente = criarCliente(vet[i], "Talia", "09/03/200", "153.221.326-35","(30)92325-4153");
        salvarCliente(cliente, arq);
    }

    free(cliente);
}

void imprimirBaseCliente(FILE *arq){
    rewind(arq);
    TCliente *cliente;

    while ((cliente = lerCliente(arq)) != NULL){
        if(cliente->idC != 0 && cliente->idC < 300000)
            imprimeCliente(cliente);
    }


    free(cliente);
}

//Dvd
TDvd *criarDvd(int id_dvd, char *nome_dvd, char *genero, int emprestimo){

    TDvd *dvd = (TDvd *) malloc(sizeof(TDvd));

    if(dvd) memset(dvd, 0, sizeof(dvd)); // memset( lugar que vai guardar a copia, o que vai ser copiado, n� de bytes que recebera a copia);
    dvd->id_dvd = id_dvd;
    strcpy(dvd->nome_dvd, nome_dvd);//strcpy copia uma string para outra
    strcpy(dvd->genero, genero);
    dvd->emprestimo = emprestimo;

    return dvd;
}

void salvarDvd(TDvd *dvd, FILE *arq){
    fwrite(&dvd->id_dvd, sizeof(int), 1, arq);
    fwrite(dvd->nome_dvd, sizeof(char), sizeof(dvd->nome_dvd), arq); //fwrite(onde na memoria esta os dados, tamanho de unidade que vai salvar, total de dados que v�o ser gravados, arquivo onde vai salvar).
    fwrite(dvd->genero, sizeof(char), sizeof(dvd->genero), arq);
    fwrite(&dvd->emprestimo, sizeof(int), 1, arq);
}

TDvd *lerDvd(FILE *arq){
    TDvd *dvd = (TDvd *) malloc(sizeof(TDvd));

    if (0 >= fread(&dvd->id_dvd, sizeof(int), 1, arq)) {
        free(dvd);
        return NULL;
    }
    fread(dvd->nome_dvd, sizeof(char), sizeof(dvd->nome_dvd), arq);
    fread(dvd->genero, sizeof(char), sizeof(dvd->genero), arq);
    fread(&dvd->emprestimo, sizeof(int), 1, arq);

    return dvd;
}

void imprimeDvd(TDvd *dvd){
    printf("\n************** DVD ***************");
    printf("\nID: ");
    printf("%d", dvd->id_dvd);
    printf("\nNome: ");
    printf("%s", dvd->nome_dvd);
    printf("\nGenero: ");
    printf("%s", dvd->genero);
    printf("\nSituacao do emprestimo: ");
    printf("%d", dvd->emprestimo);
    printf("\n");
}

void criarBaseDvd(FILE *arq, int tam){
    int vet[tam];
    TDvd *Dvd;

    for(int i=0;i<tam;i++)
        vet[i] = i+1;

    shuffle(vet,tam,(tam*10)/100); // embaralhar

    for (int i=0;i<tam;i++){
        Dvd = criarDvd(vet[i], "O protetor", "Acao", 0);
        salvarDvd(Dvd, arq);
    }

    free(Dvd);
}

void imprimirBaseDvd(FILE *out){
    rewind(out);
    TDvd *dvd;

    while ((dvd = lerDvd(out)) != NULL ) {
        if (dvd->id_dvd != 0)
            imprimeDvd(dvd);
    }
    free(dvd);

}

TDvd *buscaSequencialDvds(int chave, FILE *arq, const char *nomeArquivoLog) {
    TDvd *dvd;
    int achou = 0;
    struct timespec inicioTime, fimTime;
    double tempoGasto;
    clock_t inicioClock, fimClock;
    int contComparacao = 0;

    FILE *logFile = fopen(nomeArquivoLog, "a");
    if (logFile == NULL) {
        printf("Erro ao abrir arquivo de log\n");
        return NULL;
    }

    clock_gettime(CLOCK_MONOTONIC, &inicioTime);
    rewind(arq);
    while ((dvd = lerDvd(arq)) != NULL) {
        contComparacao++;

        if (dvd->id_dvd == chave) {
            achou = 1;
            break;
        }

        free(dvd);
    }
    clock_gettime(CLOCK_MONOTONIC, &fimTime);

    tempoGasto = (fimTime.tv_sec - inicioTime.tv_sec) * 1000.0; // seconds to milliseconds
    tempoGasto += (fimTime.tv_nsec - inicioTime.tv_nsec) / 1000000.0; // nanoseconds to milliseconds

    // Escrevendo no arquivo de log
    if (fprintf(logFile, "Busca pelo DVD com chave %d: Comparações = %d, Tempo = %f milissegundos\n", chave, contComparacao, tempoGasto) < 0) {
        printf("Erro ao escrever no arquivo de log\n");
    }

    fclose(logFile);

    if (achou == 1) {
        return dvd;
    }

    return NULL;
}

//Locadora
TLocadora *criarLocadora(int id_locacao, TDvd dvd, TCliente cliente){

    TLocadora *locadora = (TLocadora *) malloc(sizeof(TLocadora));

    if(locadora) memset(locadora, 0, sizeof(locadora)); // memset( lugar que vai guardar a copia, o que vai ser copiado, n� de bytes que recebera a copia);
    locadora->id_locacao = id_locacao;
    locadora->dvdL = dvd;
    locadora->clienteL = cliente;

    return locadora;
}

void salvarLocadora(TLocadora *locadora, FILE *arqLocadora){
    fwrite(&locadora->id_locacao, sizeof(int), 1, arqLocadora);
    fwrite(&locadora->dvdL, sizeof(TDvd), 1, arqLocadora);
    fwrite(&locadora->clienteL, sizeof(TCliente), 1, arqLocadora);
}

TLocadora *lerRegistrosLocadora(FILE *arqLocadora){
    TLocadora *locadora = (TLocadora *) malloc(sizeof(TLocadora));

    if (0 >= fread(&locadora->id_locacao, sizeof(int), 1, arqLocadora)) {
        free(locadora);
        return NULL;
    }

    fread(&locadora->dvdL, sizeof(TDvd), 1, arqLocadora);
    fread(&locadora->clienteL, sizeof(TCliente), 1, arqLocadora);
    return locadora;
}

void imprimeLocadora(TLocadora *locadora){
    printf("**************** LOCADORA *****************");
    printf("\nID locacao: ");
    printf("%d", locadora->id_locacao);

    imprimeDvd(&locadora->dvdL);
    imprimeCliente(&locadora->clienteL);

}

void criarBaseLocadora(FILE *arqLocadora, FILE *arqCliente, FILE *arqDvd, int tam){
    TLocadora *locadora;
    TCliente *cliente;
    TDvd *dvd;


    for (int i = 0; i < tam; i++) {
        //faz a busca sequencial de alguns dvds para criar a base de locacao
        dvd = buscaSequencialDvds(i+2, arqDvd, "buscaDvds-log.txt");
        dvd->emprestimo = 1;
        //faz a busca sequencial de alguns clientes para criar a base de locacao
        cliente = buscaSequencialCliente(i+3, arqCliente, "clientes-log.txt");

        if(dvd  != NULL && cliente != NULL) {
            locadora = criarLocadora(i+1, *dvd, *cliente);
            salvarLocadora(locadora, arqLocadora);
        }

    }

    free(locadora);
}

void imprimirBaseLocadora(FILE *arqLocadora){
    rewind(arqLocadora);
    TLocadora *locadora;

    while ((locadora = lerRegistrosLocadora(arqLocadora)) != NULL)
        imprimeLocadora(locadora);

    free(locadora);
}


void dvdsDisponiveis(FILE *arq){

    TDvd *dvd;
    // Reseta o ponteito e volta ao inicio do arquivo
    rewind(arq);
    while ((dvd = lerDvd(arq)) != NULL){

        if(dvd->emprestimo == 0 && dvd->id_dvd != 0){
            imprimeDvd(dvd);
        }

        free(dvd);
    }

}

void alugaDvd(int gerador_id_locadora, FILE *arqClientes, FILE *arqDvds, FILE *arqLocadora) {
    int res;
    int idCliente, idDvd, idLocadora;
    TCliente *cliente = NULL;
    TLocadora *locadora;
    struct dvd_est *dvd;


    do {
        printf("\n");
        imprimirBaseCliente(arqClientes);
        printf("---------------------------------------------------------\n");
        printf("Informe o ID do cliente: ");
        scanf("%d", &idCliente);

        cliente = buscaSequencialCliente(idCliente, arqClientes, "clientes-log.txt");

        if(cliente == NULL) {
            printf("Cliente nao encontrado.");
            break;
        }

        dvdsDisponiveis(arqDvds);

        printf("---------------------------------------------------------\n");
        printf("Informe o ID do DVD: ");
        scanf("%d", &idDvd);

        dvd = buscaSequencialDvds(idDvd, arqDvds, "buscaDvds-log.txt");

        if(dvd == NULL){
            printf("Dvd nao encontrado");
            break;
        }

        if(dvd->emprestimo == 1){
            printf("\nNAO FOI POSSIVEL REALIZAR O EMPRESTIMO, O DVD JA ESTA ALUGADO\n");
            break;
        }

        dvd->emprestimo = 1;
        fseek(arqDvds, -sizeof(TDvd), SEEK_CUR);
        salvarDvd(dvd, arqDvds);

        locadora = criarLocadora(gerador_id_locadora, *dvd, *cliente);
        salvarLocadora(locadora, arqLocadora);
        gerador_id_locadora++;

        printf("\nDvd alugado com sucesso!\n");

        printf("\n***************************\n");
        printf("1 - Alugar outro filme\n0 - Sair ");
        printf("\nEscolha uma opcao: ");
        scanf("%d", &res);

    } while(res != 0);

    free(cliente);
    free(dvd);

}

void imprimirDvdAlugado(FILE *arq, FILE *arqD, FILE *arqC){
    rewind(arq);
    TLocadora *locadora;
    TDvd *dvd;
    TCliente *cliente;

    while ((locadora = lerRegistrosLocadora(arq)) != NULL){
        printf("\n******************** DVDs ALUGADOS *********************");
        dvd = buscaSequencialDvds(locadora->dvdL.id_dvd, arqD, "buscaDvds-log.txt");

        if(dvd->id_dvd != 0)
            imprimeDvd(dvd);

        cliente = buscaSequencialCliente(locadora->clienteL.idC, arqC, "clientes-log.txt");

        if(cliente->idC != 0)
            imprimeCliente(cliente);
    }
    free(locadora);
    free(cliente);
    free(dvd);
}

int excluiDvd(int chave, FILE *arquivoD) {
    TDvd *dvd;
    int encontrado = 0;

    // Abre o arquivo original para leitura e gravação binária
    if ((arquivoD = fopen("Dvds.dat", "r+")) == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    // Procura o registro pelo Id

    while ((dvd = lerDvd(arquivoD)) != NULL) {
        if (dvd->id_dvd == chave) {
            encontrado = 1;
            break;
        }
    }

    if (encontrado) {
        // Move o ponteiro do arquivo de volta para o início do registro
        fseek(arquivoD, -sizeof(TDvd), SEEK_CUR);

        // Preenche o registro com dados vazios
        TDvd dvdVazio;
        dvdVazio.id_dvd = 0;
        strcpy(dvdVazio.nome_dvd, "");
        strcpy(dvdVazio.genero, "");
        dvdVazio.emprestimo = 0;

        fwrite(&dvdVazio, sizeof(TDvd), 1, arquivoD);

        printf("Dvd excluido com sucesso.\n");
    } else {
        printf("Dvd nao encontrado.\n");
    }

    fclose(arquivoD); // Fecha o arquivo
    return 0; // Indica sucesso
}

int tamanhoRegistroDvd() {
    return sizeof(int)  //id_dvd
           + sizeof(char)*100 //nome_dvd
           + sizeof(char)*100 //genero
           + sizeof(int); //emprestimo
}

int tamanhoRegistroCliente() {
    return sizeof(int)  //idC
           + sizeof(char)*100 //nomeC
           + sizeof(char)*50 //dataNascimento
           + sizeof(char)*50 //cpfC
           + sizeof(char)*50; //teleofneC
}

int tamanhoRegistroLocadora() {
    return sizeof(int)  //id_transacao
           + sizeof(TDvd) //id_dvd
           + sizeof(TCliente); //id_cliente
}

int tamanho_arquivo(FILE *arq) {
    fseek(arq, 0, SEEK_END);
    int tam = trunc(ftell(arq) / tamanhoRegistroLocadora());
    return tam;
}

TLocadora *buscaBinariaLocacao(int chave, FILE *in, int inicio, int fim, const char *nomeArquivoLog) {

    TLocadora *locadora = NULL;
    int cod = -1;
    int contComparacao = 0;

    struct timespec inicioTime, fimTime;
    double tempoGasto;
    clock_t inicioClock, fimClock;

    FILE *logFile = fopen(nomeArquivoLog, "a");
    if (logFile == NULL) {
        printf("Erro ao abrir arquivo de log\n");
        return NULL;
    }

    clock_gettime(CLOCK_MONOTONIC, &inicioTime);
    while (inicio <= fim && cod != chave) {

        contComparacao++;
        int meio = trunc((inicio + fim) / 2);
        //printf("Inicio: %d; Fim: %d; Meio: %d\n", inicio, fim, meio);
        fseek(in, (meio -1) * tamanhoRegistroLocadora(), SEEK_SET);
        locadora = lerRegistrosLocadora(in);
        cod = locadora->id_locacao;

        if (locadora) {
            if (cod > chave) {
                fim = meio - 1;
            } else {
                inicio = meio + 1;
            }
        }
    }

    clock_gettime(CLOCK_MONOTONIC, &fimTime);

    tempoGasto = (fimTime.tv_sec - inicioTime.tv_sec) * 1000.0; // seconds to milliseconds
    tempoGasto += (fimTime.tv_nsec - inicioTime.tv_nsec) / 1000000.0; // nanoseconds to milliseconds

    fprintf(logFile, "Busca pela chave %d: \nComparações = %d, Tempo = %f milissegundos\n", chave, contComparacao, tempoGasto);
    fclose(logFile);

    if (cod == chave) {
        return locadora;
    }
    else return NULL;
}

int excluiCliente(int chave, FILE *arquivoClientes) {
    TCliente *cliente;
    int encontrado = 0;

    if ((arquivoClientes = fopen("clientes.dat", "r+")) == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    // Procura o registro pelo Id
    while ((cliente = lerCliente(arquivoClientes)) != NULL) {
        if (cliente->idC == chave) {
            encontrado = 1;
            break;
        }
    }

    if (encontrado == 1) {
        // Move o ponteiro do arquivo para a posição correta
        fseek(arquivoClientes, -sizeof(TCliente), SEEK_CUR);

        // Preenche o registro com dados vazios
        TCliente clienteVazio;
        clienteVazio.idC = 0;
        strcpy(clienteVazio.nomeC, "");
        strcpy(clienteVazio.cpfC, "");
        strcpy(clienteVazio.dataNascimentoC, "");
        strcpy(clienteVazio.telefoneC, "");

        fwrite(&clienteVazio, sizeof(TCliente), 1, arquivoClientes);

        printf("Cliente excluido com sucesso.\n");
    } else {
        printf("Cliente nao encontrado.\n");
    }

    fclose(arquivoClientes);
    free(cliente);

    return 0; // Indica sucesso
}

void devolverDvd(FILE *arqDvdss) {
    int idDvd;
    struct dvd_est *dvd;

        printf("\n");

        printf("---------------------------------------------------------\n");
        printf("Informe o ID do DVD: ");
        scanf("%d", &idDvd);

        dvd = buscaSequencialDvds(idDvd, arqDvdss, "buscaDvds-log.txt");

        if(dvd == NULL){
            printf("Dvd nao encontrado");
        }

        if(dvd->emprestimo == 1) {
            dvd->emprestimo = 0;
            fseek(arqDvdss, -sizeof(TDvd), SEEK_CUR);
            salvarDvd(dvd, arqDvdss);

            printf("\nDvd devolvido com sucesso!\n");
        }else{
            if(dvd->emprestimo == 0)
                printf("Esse dvd nao estava alugado.");
        }
}



void gerarParticoesOrdenadasDvd(FILE *arquivoEntrada, int tamanho, int tam_reservatorio) {
    TDvd memoria[tamanho];  // Array em memória
    TDvd reservatorio[tam_reservatorio];  // Reservatório
    int qtdReservatorio = 0;
    int num_particao = 1;

    FILE *arquivoSaida = NULL;

    // Lê os primeiros M registros do arquivo para a memória
    for (int i = 0; i < tamanho; ++i) {
        if (fread(&memoria[i], sizeof(TDvd), 1, arquivoEntrada) != 1) {
            // Arquivo de entrada acabou
            break;
        }
    }

    // Enquanto houver registros no array em memória
    while (1) {
        // Encontrar o registro com a menor chave no array em memória
        int indiceMenorChave = 0;
        for (int i = 1; i < tamanho; ++i) {
            if (memoria[i].id_dvd < memoria[indiceMenorChave].id_dvd) {
                indiceMenorChave = i;
            }
        }

        // Se a chave do próximo registro for menor, gravá-lo no reservatório
        if (indiceMenorChave > 0 && memoria[indiceMenorChave].id_dvd < memoria[indiceMenorChave - 1].id_dvd) {
            if (qtdReservatorio < tam_reservatorio) {
                reservatorio[qtdReservatorio++] = memoria[indiceMenorChave];
            }
        }

        // Abrir nova partição de saída se ainda não foi aberta
        if (arquivoSaida == NULL) {
            char nomeArquivoSaida[30];
            sprintf(nomeArquivoSaida, "particao_saida_%d.bin", num_particao++);
            arquivoSaida = fopen(nomeArquivoSaida, "wb");

            // Verificar se a abertura foi bem-sucedida
            if (arquivoSaida == NULL) {
                perror("Erro ao abrir arquivo de saída");
                break;
            }
        }

        // Gravar o registro com menor chave na partição de saída
        fwrite(&memoria[indiceMenorChave], sizeof(TDvd), 1, arquivoSaida);

        // Substituir o registro pelo próximo registro do arquivo de entrada
        if (fread(&memoria[indiceMenorChave], sizeof(TDvd), 1, arquivoEntrada) != 1) {
            // Arquivo de entrada acabou
            break;
        }

        // Caso ainda exista espaço no reservatório, voltar ao passo 2
        if (qtdReservatorio < tam_reservatorio) {
            continue;
        }

        // Esvaziar o reservatório
        qtdReservatorio = 0;

        // Fechar a partição de saída atual
        fclose(arquivoSaida);
        arquivoSaida = NULL;
    }

    // Após o término do loop, fechar a última partição de saída, se estiver aberta
    if (arquivoSaida != NULL) {
        fclose(arquivoSaida);
    }
}

