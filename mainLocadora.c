#include <stdio.h>
#include <stdlib.h>
#include "locadora.c"

int main(){

    FILE *arq;

    if ((arq = fopen("locadora.dat", "w+b")) == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }
    else{

        TLocadora *locad;

        locad = CriarLocadora("Samyla", "Talia", 2,"filme", "comedeia", 0);
        salva(locad, arq);

        locad = CriarLocadora("Carol", "Alex", 3,"filme", "acao",0);
        salva(locad, arq);

        locad = CriarLocadora("Ana", "Samyla", 1,"musica", "pagode", 0);
        salva(locad, arq);

        printf("\n\nLendo itens da locadora do arquivo...\n\n");
        rewind(arq);

        while ((locad = ler(arq)) != NULL) {
            imprime(locad);
        }

        system("pause");
        system("cls");


        printf("\n\nLendo segundo funcionario do arquivo...\n\n");


        fseek(arq, tamanho_registro(), SEEK_SET);
        locad = ler(arq);

        if (locad != NULL) {
            imprime(locad);
        }

        system("pause");
        system("cls");

        printf("\n\nAdicionando funcionario no final do arquivo...\n\n");

        fseek(arq, tamanho_registro() * 5, SEEK_SET);
        locad = CriarLocadora("Maria", "Samyla", 5,"musica", "samba", 0);
        salva(locad, arq);

        printf("\n\nLendo funcionarios do arquivo...\n\n");
        rewind(arq);

        while ((locad = ler(arq)) != NULL) {
            imprime(locad);
        }

        system("pause");
        system("cls");


        printf("\n\nSobrescrevendo quarto funcionario do arquivo...\n\n");
        fseek(arq, tamanho_registro() * 3, SEEK_SET);
        locad = CriarLocadora("Caio", "Ana", 9 ,"musica", "sertanejo", 0);
        salva(locad, arq);

        printf("\n\nLendo funcionarios do arquivo...\n\n");
        rewind(arq);

        while ((locad = ler(arq)) != NULL) {
            imprime(locad);
        }

        free(locad);

    }


}




