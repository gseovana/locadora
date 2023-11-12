#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "locadora.h"


/*int tamanho_registro(){
    return sizeof(char)*50 //cliente
         + sizeof(char)*50 //funcionario
         + sizeof(int); //cod
         + sizeof(char)*50 //tipo
         + sizeof(char)*50 //genero
         + sizeof(int);
}*/

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
TCliente *criarCliente(char *nomeC , char *dataNascimentoC, char *cpfC, int idC, char *telefoneC){

    TCliente *cliente = (TCliente *) malloc(sizeof(TCliente));

    if(cliente) memset(cliente, 0, sizeof(cliente)); // memset( lugar que vai guardar a copia, o que vai ser copiado, n� de bytes que recebera a copia);
        strcpy(cliente->nomeC, nomeC);
        strcpy(cliente->dataNascimentoC, dataNascimentoC); //strcpy copia uma string para outra
        strcpy(cliente->cpfC, cpfC);
        cliente->idC = idC;
        strcpy(cliente->telefoneC, telefoneC);

        return cliente;
}

void salvarCliente(TCliente *cliente, FILE *arq){
    fwrite(cliente->nomeC, sizeof(char), sizeof(cliente->nomeC), arq); //fwrite(onde na memoria esta os dados, tamanho de unidade que vai salvar, total de dados que v�o ser gravados, arquivo onde vai salvar).
    fwrite(cliente->dataNascimentoC, sizeof(char), sizeof(cliente->dataNascimentoC), arq);
    fwrite(cliente->cpfC, sizeof(char), sizeof(cliente->cpfC), arq);
    fwrite(&cliente->idC, sizeof(int), 1, arq);
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

void imprimeCliente(TCliente *cliente){
    printf("*******************CLIENTE***************************");
    printf("\nNome do Cliente: ");
    printf("%s", cliente->nomeC);
    printf("\nData de nascimento do cliente: ");
    printf("%s", cliente->dataNascimentoC);
    printf("\nCPF do cliente: ");
    printf("%d", cliente->cpfC);
    printf("\nID do cliente: ");
    printf("%d", cliente->idC);
    printf("\nTelefone do cliente: ");
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
        cliente = criarCliente("Talia", "09/03/200", "15322132635", vet[i], "23254153");
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
TFuncionario *criarFuncionario(char *nomeF, char *cpfF, int idF, double salarioF){

 TFuncionario *funcionario = (TFuncionario *) malloc(sizeof(TFuncionario));

    if(funcionario) memset(funcionario, 0, sizeof(funcionario)); // memset( lugar que vai guardar a copia, o que vai ser copiado, n� de bytes que recebera a copia);
        strcpy(funcionario->nomeF, nomeF);
        strcpy(funcionario->cpfF, cpfF); //strcpy copia uma string para outra
        funcionario->idF = idF;
        funcionario->salarioF = salarioF;

        return funcionario;
}

void salvarFuncionario(TFuncionario *funcionario, FILE *arq){
    fwrite(funcionario->nomeF, sizeof(char), sizeof(funcionario->nomeF), arq); //fwrite(onde na memoria esta os dados, tamanho de unidade que vai salvar, total de dados que v�o ser gravados, arquivo onde vai salvar).
    fwrite(funcionario->cpfF, sizeof(char), sizeof(funcionario->cpfF), arq);
    fwrite(&funcionario->idF, sizeof(int), 1, arq);
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
    printf("\nNome do funcionario: ");
    printf("%s", funcionario->nomeF);
    printf("\nCPF do funcionario: ");
    printf("%d", funcionario->cpfF);
    printf("\nID do funcionario: ");
    printf("%d", funcionario->idF);
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
        funcionario = criarFuncionario("Alex", "123511582", vet[i], 2000);
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
TDvd *criarDvd(int id_dvd, char *nome_dvd, int ano_lancamento, char *diretor, char *genero, int emprestimo){

    TDvd *dvd = (TDvd *) malloc(sizeof(TDvd));

    if(dvd) memset(dvd, 0, sizeof(dvd)); // memset( lugar que vai guardar a copia, o que vai ser copiado, n� de bytes que recebera a copia);
        dvd->id_dvd = id_dvd;
        strcpy(dvd->nome_dvd, nome_dvd);
        strcpy(dvd->ano_lancamento, ano_lancamento);
        strcpy(dvd->diretor, diretor); //strcpy copia uma string para outra
        strcpy(dvd->genero, genero);
        dvd->empretimo = emprestimo;

        return dvd;
}

void salvarDvd(TDvd *dvd, FILE *arq){
     fwrite(&dvd->id_dvd, sizeof(int), 1, arq);
     fwrite(dvd->nome_dvd, sizeof(char), sizeof(dvd->nome_dvd), arq); //fwrite(onde na memoria esta os dados, tamanho de unidade que vai salvar, total de dados que v�o ser gravados, arquivo onde vai salvar).
     fwrite(&dvd->ano_lancamento, sizeof(int), 1, arq);
     fwrite(dvd->diretor, sizeof(char), sizeof(dvd->diretor), arq);
     fwrite(dvd->genero, sizeof(char), sizeof(dvd->genero), arq);
     fwrite(&dvd->empretimo, sizeof(int), 1, arq);
}

TDvd *lerDvd(FILE *arq){
  TDvd *dvd = (TDvd *) malloc(sizeof(TDvd));

     if (0 >= fread(&dvd->id_dvd, sizeof(int), 1, arq)) {
        free(dvd);
        return NULL;
    }
    fread(dvd->nome_dvd, sizeof(char), sizeof(dvd->nome_dvd), arq);
    fread(&dvd->ano_lancamento, sizeof(int), 1, arq);
    fread(dvd->diretor, sizeof(char), sizeof(dvd->diretor), arq);
    fread(dvd->genero, sizeof(char), sizeof(dvd->genero), arq);
    fread(&dvd->empretimo, sizeof(int), 1, arq);

    return dvd;
}

void imprimeDvd(TDvd *dvd){
    printf("********************DVD***************************");
    printf("\nID do dvd: ");
    printf("%d", dvd->id_dvd);
    printf("\nNome do dvd: ");
    printf("%s", dvd->nome_dvd);
    printf("\nAno do lancamento: ");
    printf("%d", dvd->ano_lancamento);
    printf("\nDireto do dvd: ");
    printf("%s", dvd->diretor);
    printf("\nGednero do dvd: ");
    printf("%s", dvd->genero);
    printf("\nSituacao do emprestimo: ");
    printf("%d", dvd->empretimo);
    printf("\n**********************************************");
}

void criarBaseDvd(FILE *arq, int tam){
int vet[tam];
    TDvd *Dvd;

    for(int i=0;i<tam;i++)
        vet[i] = i+1;

    shuffle(vet,tam,(tam*10)/100); // embaralhar

    for (int i=0;i<tam;i++){
        Dvd = criarDvd(vet[i], "O protetor", 2020, "Joao", "Acao", 0);
        salvarDvd(Dvd, arq);
    }

    free(Dvd);
}

void imprimirBaseDvd(FILE *arq){
rewind(arq);
    TDvd *Dvd;

    while ((Dvd = lerDvd(arq)) != NULL)
        imprimeDvd(Dvd);

    free(Dvd);
}

/*TDvd emprestimoDvd(int id_dvdDesejado , char *nome_dvdDesejado){

    TDvd *dvd;

    if(id_dvdDesejado == dvd->id_dvd && dvd->empretimo == 0){
        return dvd->nome_dvd;
    }
    else{
        return 0;
    }

}

void devolucaoDvd(int id_dvdDevolver){
    TDvd *dvd;

    if(dvd->id_dvd == id_dvdDevolver){
        dvd->id_dvd = 0;
    }
}

void dvdsDisponiveis(){

 TDvd *dvd;

    while(dvd->empretimo != 1){
        //imprimirDvds
    }

}
*/





/*
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
*/

