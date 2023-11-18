#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
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

//Cliente
TCliente *criarCliente(int idC, char *nomeC , char *dataNascimentoC, char *cpfC, char *telefoneC){

    TCliente *cliente = (TCliente *) malloc(sizeof(TCliente));

    if(cliente) memset(cliente, 0, sizeof(cliente)); // memset( lugar que vai guardar a copia, o que vai ser copiado, n� de bytes que recebera a copia);
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
    clock_t inicio, fim;
    double tempoGasto;
    int contComparacao = 0;

    FILE *logFile = fopen(nomeArquivoLog, "a"); // Abre o arquivo de log em modo de acréscimo
    if (logFile == NULL) {
        printf("Erro ao abrir arquivo de log\n");
        return NULL;
    }

    inicio = clock();
    rewind(arq);
    while ((cliente = lerCliente(arq)) != NULL) {
        contComparacao++;

        if (cliente->idC == chave) {
            achou = 1;
            break;
        }

        free(cliente); // Libera o cliente se não for o procurado
    }
    fim = clock();

    tempoGasto = ((double)(fim - inicio) * 1000) / CLOCKS_PER_SEC;

    // Escrevendo no arquivo de log
    fprintf(logFile, "Busca pela chave %d: \nComparações = %d, Tempo = %f milissegundos\n", chave, contComparacao, tempoGasto);
    fclose(logFile);

    if (achou == 1) {
        return cliente;
    } else {
        printf("Cliente não encontrado\n");
    }

    printf("Tempo gasto: %f milissegundos\n", tempoGasto);

    return NULL;
}



void imprimeCliente(TCliente *cliente){
    printf("******************* CLIENTE ***************************");
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

    while ((cliente = lerCliente(arq)) != NULL)
        imprimeCliente(cliente);

    free(cliente);
}
//Funcionario
TFuncionario *criarFuncionario(int idF, char *nomeF, char *cpfF, double salarioF){

 TFuncionario *funcionario = (TFuncionario *) malloc(sizeof(TFuncionario));

    if(funcionario) memset(funcionario, 0, sizeof(funcionario)); // memset( lugar que vai guardar a copia, o que vai ser copiado, n� de bytes que recebera a copia);
        funcionario->idF = idF;
        strcpy(funcionario->nomeF, nomeF);
        strcpy(funcionario->cpfF, cpfF); //strcpy copia uma string para outra
        funcionario->salarioF = salarioF;

        return funcionario;
}

void salvarFuncionario(TFuncionario *funcionario, FILE *arq){
    fwrite(&funcionario->idF, sizeof(int), 1, arq);
    fwrite(funcionario->nomeF, sizeof(char), sizeof(funcionario->nomeF), arq); //fwrite(onde na memoria esta os dados, tamanho de unidade que vai salvar, total de dados que v�o ser gravados, arquivo onde vai salvar).
    fwrite(funcionario->cpfF, sizeof(char), sizeof(funcionario->cpfF), arq);
    fwrite(&funcionario->salarioF, sizeof(double), 1, arq);
}

TFuncionario *lerFuncionario(FILE *arq){
  TFuncionario *funcionario = (TFuncionario *) malloc(sizeof(TFuncionario));

     if (0 >= fread(&funcionario->idF, sizeof(int), 1, arq)) {
        free(funcionario);
        return NULL;
    }
    fread(funcionario->nomeF, sizeof(char), sizeof(funcionario->nomeF), arq);
    fread(funcionario->cpfF, sizeof(char), sizeof(funcionario->cpfF), arq);
    fread(&funcionario->salarioF, sizeof(double), 1, arq);

    return funcionario;
}

void imprimeFuncionario(TFuncionario *funcionario){
    printf("*******************FUNCIONARIO***************************");
    printf("\nID do funcionario: ");
    printf("%d", funcionario->idF);
    printf("\nNome do funcionario: ");
    printf("%s", funcionario->nomeF);
    printf("\nCPF do funcionario: ");
    printf("%s", funcionario->cpfF);
    printf("\nSalario do funcionario: ");
    printf("%4.2f", funcionario->salarioF);
    printf("\n");

}

void criarBaseFuncionario(FILE *arq, int tam){

int vet[tam];
    TFuncionario *funcionario;

    for(int i=0;i<tam;i++)
        vet[i] = i+1;

    shuffle(vet,tam,(tam*10)/100); // embaralhar

    for (int i=0;i<tam;i++){
        funcionario = criarFuncionario(vet[i], "Alex", "123511582", 2000);
        salvarFuncionario(funcionario, arq);
    }

    free(funcionario);
}

void imprimirBaseFuncionario(FILE *arq){
rewind(arq);
    TFuncionario *funcionario;

    while ((funcionario = lerFuncionario(arq)) != NULL)
        imprimeFuncionario(funcionario);

    free(funcionario);
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

    while ((dvd = lerDvd(out)) != NULL)
        imprimeDvd(dvd);

    free(dvd);

}

TDvd *buscaSequencialDvds(int chave, FILE *arq, const char *nomeArquivoLog) {
    TDvd *dvd;
    int achou = 0;
    clock_t inicio, fim;
    double tempoGasto;
    int contComparacao = 0;

    FILE *logFile = fopen(nomeArquivoLog, "a");
    if (logFile == NULL) {
        printf("Erro ao abrir arquivo de log\n");
        return NULL;
    }

    inicio = clock();
    rewind(arq);
    while ((dvd = lerDvd(arq)) != NULL) {
        contComparacao++;

        if (dvd->id_dvd == chave) {
            achou = 1;
            break;
        }

        free(dvd);
    }
    fim = clock();

    tempoGasto = ((double)(fim - inicio) * 1000) / CLOCKS_PER_SEC;

    // Escrevendo no arquivo de log
    fprintf(logFile, "Busca pelo DVD com chave %d: Comparações = %d, Tempo = %f milissegundos\n", chave, contComparacao, tempoGasto);
    fclose(logFile);

    if (achou == 1) {
        return dvd;
    }

    return NULL;
}

//Locadora
TLocadora *criarLocadora(int id_dvd, int id_cliente){

    TLocadora *locadora = (TLocadora *) malloc(sizeof(TLocadora));

    if(locadora) memset(locadora, 0, sizeof(locadora)); // memset( lugar que vai guardar a copia, o que vai ser copiado, n� de bytes que recebera a copia);
        locadora->id_dvd = id_dvd;
        locadora->id_cliente = id_cliente;

        return locadora;
}

void salvarLocadora(TLocadora *locadora, FILE *arqLocadora){
    fwrite(&locadora->id_cliente, sizeof(int), 1, arqLocadora);
    fwrite(&locadora->id_dvd, sizeof(int), 1, arqLocadora);
}

TLocadora *lerRegistrosLocadora(FILE *arqLocadora){
  TLocadora *locadora = (TLocadora *) malloc(sizeof(TLocadora));

     if (0 >= fread(&locadora->id_dvd, sizeof(int), 1, arqLocadora)) {
        free(locadora);
        return NULL;
    }

    fread(&locadora->id_dvd, sizeof(int), 1, arqLocadora);
    fread(&locadora->id_cliente, sizeof(int), 1, arqLocadora);
    return locadora;
}

void imprimeLocadora(TLocadora *locadora){
    printf("********************LOCADORA***************************");
    printf("\nID do dvd: ");
    printf("%d", locadora->id_dvd);
    printf("\nCliente: ");
    printf("%d", locadora->id_cliente);
    printf("\n");
}

void criarBaseLocadora(FILE *arqLocadora, int tam){
int vet[tam];
    TLocadora *locadora;

    for(int i=0;i<tam;i++)
        vet[i] = i+1;

    shuffle(vet,tam,(tam*10)/100); // embaralhar

    for (int i=0;i<tam;i++){
        locadora = criarLocadora(1,2);
        salvarLocadora(locadora, arqLocadora);
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

        if(dvd->emprestimo == 0 ){
            imprimeDvd(dvd);
        }

    free(dvd);
    }

}
void alugaDvd(FILE *arqClientes, FILE *arqDvds, FILE *arqLocadora) {
    int idCliente, idDvd;
    TCliente *cliente;
    TLocadora *locadora;
    TDvd *dvd;

    if ((arqClientes = fopen("clientes.dat", "r+b")) == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }

    if ((arqDvds = fopen("Dvds.dat", "r+b")) == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }

    printf("-------------------------------------------------------------\n");
    printf("Informe o ID do DVD: ");
    scanf("%d", &idDvd);

    dvd = buscaSequencialDvds(idDvd, arqDvds, "buscaDvds-logs.txt");
    if (dvd != NULL) {
        if(dvd->emprestimo != 0) {
            printf("Este dvd não está disponível para locacao.");
        }else
            imprimeDvd(dvd);
    }else
        printf("Dvd não encontrado.");

    printf("Informe o ID do cliente: ");
    scanf("%d", &idCliente);

    cliente = buscaSequencialCliente(idCliente, arqClientes, "clientes-log.txt");
    if (cliente != NULL) {
        imprimeCliente(cliente);
    }else{
        printf("Cliente não encontrado.");
    }
        dvd->emprestimo = 1;
        fseek(arqDvds, -sizeof(TDvd), SEEK_CUR);
        salvarDvd(dvd , arqDvds);

        locadora = criarLocadora(idDvd, idCliente);
        salvarLocadora(locadora, arqLocadora);
        fclose(arqClientes);
        fclose(arqDvds);
        free(cliente);
        free(dvd);
}
void imprimirDvdsAlugados(FILE *arqDvds, FILE *arqLocadora) {
    TLocadora *locadora;
    TDvd *dvd;


    if ((arqLocadora = fopen("locadora.dat", "r+b")) == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }

       if ((arqDvds = fopen("Dvds.dat", "r+b")) == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }
    while ((locadora = lerRegistrosLocadora(arqLocadora)) != NULL) {
            printf("opa");
        printf("%d", locadora->id_dvd);
        //dvd = buscaSequencialDvds(locadora->id_dvd, arqDvds,"buscaDvds-logs.txt");
        //if(dvd != NULL) {
          //  imprimeDvd(dvd);
            //free(dvd);
        //}
        free(locadora);
    }
    fclose(arqLocadora);
}

int excluiDvd(int chave, FILE *arqDvds) {
    TDvd *dvd;
    int encontrado = 0;

    // Abre o arquivo original para leitura e gravação binária
    if ((arqDvds = fopen("Dvds.dat", "rw")) == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    // Procura o registro pelo Id

    while ((dvd = lerDvd(arqDvds)) != NULL) {
        if (dvd->id_dvd == chave) {
            encontrado = 1;
            break;
        }
    }

    if (encontrado) {
        // Move o ponteiro do arquivo de volta para o início do registro
        fseek(arqDvds, -sizeof(TDvd), SEEK_CUR);

        // Preenche o registro com dados vazios (ou você pode excluir o registro de outra forma)
         TDvd dvdVazio = {0, "", "", 0}; // Preencha com valores padrão
        fwrite(&dvdVazio, sizeof(TDvd), 1, arqDvds);

        printf("Dvd excluido com sucesso.\n");
    } else {
        printf("Dvd nao encontrado.\n");
    }

    fclose(arqDvds); // Fecha o arquivo
    return 0; // Indica sucesso
}




