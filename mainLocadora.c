#include <stdio.h>
#include <stdlib.h>
#include "locadora.c"

int main() {

    FILE *arqClientes, *arqDvds, *arqLocadora;
    TCliente *cliente;
    TFuncionario *funcionario;
    TDvd *dvd;


    if ((arqClientes = fopen("clientes.dat", "w+b")) == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }

    if ((arqDvds = fopen("Dvds.dat", "w+b")) == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }

    if ((arqLocadora = fopen("locadora.dat", "w+b")) == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }

    criarBaseDvd(arqDvds, 600);
    criarBaseCliente(arqClientes, 350);

    int opcao = -1;
    int gerador_id_dvd = 1;

    while (opcao != 0) {
        system("clear");
        printf("\n****************** LOCADORA TAGEO  *******************");
        printf("\n1. Cadastrar DVD \n2. Buscar DVD \n3. Excluir DVD \n4. Imprimir todos os DVDs \n-----------------------------\n"
               "5. Cadastrar cliente \n6. Buscar cliente \n7. Excluir cliente \n8. Imprimir todos os clientes \n-----------------------------"
               "\n9. Novo funcionário \n10. Imprimir todos os funcionários \n---------------------------"
               "\n11. Nova transação\n12. Imprimir todas as transações \n0. Sair\n\nEscolha uma opção: ");
        scanf("%d", &opcao);
        //fflush(arq);

        switch (opcao) {
            case 1:
                system("clear");
                printf("\n********** CADASTRAR DVD **********\n");

                TDvd *dvd = (TDvd *) malloc(sizeof(TDvd));

                // Limpar o buffer, consumindo o caractere de nova linha remanescente
                while (getchar() != '\n');

                dvd->id_dvd = 600+gerador_id_dvd;
                gerador_id_dvd++;

                printf("ID: %d", dvd->id_dvd);

                printf("\nTítulo: ");
                fgets(dvd->nome_dvd, 51, stdin);

                printf("Gênero: ");
                fgets(dvd->genero, 51, stdin);

                dvd->emprestimo = 0;

                salvarDvd(dvd, arqDvds);
                printf("\nDVD salvo com sucesso!");
                opcao = -1;

                free(dvd);
                break;
            case 2:
                printf("\n********** BUSCAR DVD **********\n");

                int id_dvd;

                printf("Informe o codigo: ");
                scanf("%d", &id_dvd);

                dvd = buscaSequencialDvds(id_dvd, arqDvds, "buscaDvds-log.txt");
                if (dvd != NULL) {
                    imprimeDvd(dvd);
                }else{
                    printf("DVD não encontrado.");
                }

                free(dvd);
                break;
            case 3:
                printf("\n********** EXCLUIR DVD **********\n");

                printf("Informe o codigo: ");
                scanf("%d", &id_dvd);

                excluiDvd(id_dvd,  arqDvds);

                break;
            case 4:
                printf("\n********** IMPRIMIR BASE DE DADOS DE DVDs **********\n");
                imprimirBaseDvd(arqDvds);
                break;
            case 5:
                system("clear");
                printf("\n********** CADASTRAR CLIENTE **********\n");

                TCliente *cliente = (TCliente *) malloc(sizeof(TCliente));

                printf("\nNome: ");
                fgets(dvd->nome_dvd, 51, stdin);

                printf("\nGênero: ");
                fgets(dvd->genero, 51, stdin);

                dvd->emprestimo = 0;

                salvarDvd(dvd, arqDvds);
                printf("\nDVD salvo com sucesso!");
                opcao = -1;

                free(dvd);
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                printf("Saindo...");
                break;
        }
    }
}