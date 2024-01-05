#include <stdio.h>
#include <stdlib.h>
#include "locadora.c"
#include "selectionSort.h"
#include "selecaoNatural.h"

int main() {

    FILE *arqClientes, *arqDvds, *arqLocadora, *arqSaida, *arqSaida2;
    TCliente *cliente;
    TDvd *dvd;
    TLocadora *locacao;


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


    criarBaseDvd(arqDvds, 30);
    criarBaseCliente(arqClientes, 10);
    criarBaseLocadora(arqLocadora, arqClientes, arqDvds, 4);
    int gerador_id_locadora = 4;

    int opcao = -1,
            gerador_id_dvd = 1,
            gerador_id_cliente = 1,c;


    while (opcao != 0) {
        system("clear");
        printf("\n***************************** LOCADORA TAGEO  ********************************");
        printf("\n1. Cadastrar DVD \n2. Buscar DVD \n3. Excluir DVD \n4. Imprimir todos os DVDs \n-----------------------------\n"
               "5. Cadastrar cliente \n6. Buscar cliente \n7. Excluir cliente \n8. Imprimir todos os clientes \n-----------------------------"
               "\n9. Alugar DVD\n10. Buscar locacao \n11. Imprimir todas as locacoes\n12. Devolver DVD\n---------------------------"
               "\n13. SelectionSort\n14. Partition: Selecao Natural\n15. blablabal\n---------------------------\n0. Sair\n\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        //fflush(arq);

        switch (opcao) {
            case 1:
                system("clear");
                printf("\n************************* CADASTRAR DVD *******************************\n");

                dvd = (TDvd *) malloc(sizeof(TDvd));

                // Limpar o buffer, consumindo o caractere de nova linha remanescente
                while (getchar() != '\n');

                dvd->id_dvd = 30 + gerador_id_dvd;
                gerador_id_dvd++;

                printf("ID: %d", dvd->id_dvd);

                printf("\nTítulo: ");
                fgets(dvd->nome_dvd, 100, stdin);

                printf("Gênero: ");
                fgets(dvd->genero, 100, stdin);

                dvd->emprestimo = 0;

                salvarDvd(dvd, arqDvds);
                printf("\nDVD salvo com sucesso!");
                opcao = -1;

                free(dvd);
                break;
            case 2:
                printf("\n**************************** BUSCAR DVD ******************************\n");

                int id_dvd;

                printf("Informe o codigo: ");
                scanf("%d", &id_dvd);

                dvd = buscaSequencialDvds(id_dvd, arqDvds, "buscaDvds-log.txt");
                if (dvd != NULL) {
                    imprimeDvd(dvd);
                } else {
                    printf("DVD não encontrado.");
                }

                free(dvd);
                break;
            case 3:
                printf("\n**************************** EXCLUIR DVD ****************************\n");

                printf("Informe o codigo: ");
                scanf("%d", &id_dvd);

                excluiDvd(id_dvd, arqDvds);

                break;
            case 4:
                printf("\n********************** IMPRIMIR BASE DE DADOS DE DVDs ************************\n");

                imprimirBaseDvd(arqDvds);
                break;
            case 5:
                system("clear");
                printf("\n****************** CADASTRAR CLIENTE ************************\n");

                cliente = (TCliente *) malloc(sizeof(TCliente));

                // Limpar o buffer, consumindo o caractere de nova linha remanescente
                while ((c = getchar()) != '\n' && c != EOF);

                cliente->idC = 10 + gerador_id_cliente;
                gerador_id_cliente++;

                printf("ID: %d", cliente->idC);

                printf("\nNome: ");
                fgets(cliente->nomeC, 100, stdin);

                printf("\nData nascimento: ");
                fgets(cliente->dataNascimentoC, 49, stdin);

                printf("CPF: ");
                fgets(cliente->cpfC, 49, stdin);

                printf("Telefone: ");
                fgets(cliente->telefoneC, 49, stdin);

                salvarCliente(cliente, arqClientes);
                printf("\nCliente salvo com sucesso!");
                opcao = -1;

                free(cliente);

                break;
            case 6:
                printf("\n******************* BUSCAR CLIENTE *******************\n");

                int id_cliente;

                printf("Informe o codigo: ");
                scanf("%d", &id_cliente);

                cliente = buscaSequencialCliente(id_cliente, arqClientes, "clientes-log.txt");
                if (cliente != NULL) {
                    imprimeCliente(cliente);
                } else {
                    printf("Cliente não encontrado.");
                }

                free(cliente);
                break;
            case 7:
                printf("\n**************************** EXCLUIR CLIENTE ****************************\n");

                printf("Informe o codigo: ");
                scanf("%d", &id_cliente);

                excluiCliente(id_cliente, arqClientes);
                break;
            case 8:
                printf("\n****************** IMPRIMIR BASE DE DADOS DE CLIENTES ********************\n");
                imprimirBaseCliente(arqClientes);
                break;
            case 9:
                printf("\n*************************** ALUGAR DVD **************************");

                gerador_id_locadora += 1;
                alugaDvd(gerador_id_locadora, arqClientes, arqDvds, arqLocadora);

                //imprimirDvdAlugado(arqLocadora, arqDvds, arqClientes);

                break;
            case 10:
                printf("*************************** BUSCAR LOCACAOO ********************************");
                int id_locacao;

                printf("\nInforme o codigo da locacao: ");
                scanf("%d", &id_locacao);


                locacao = buscaBinariaLocacao(id_locacao, arqLocadora, 0, tamanho_arquivo(arqLocadora),"locadora.txt");

                if (locacao != NULL) {
                    imprimeLocadora(locacao);
                } else
                    printf("Locacao não encontrada.");
                break;
            case 11:
                printf("\n********************** IMPRIMIR TODAS AS LOCACOES *************************\n");
                imprimirBaseLocadora(arqLocadora);
                break;
            case 12:
                printf("\n********************** DEVOLVER DVD *************************\n");
                devolverDvd(arqDvds);
                break;
            case 13:
                printf("\n************************* SELECTION SORT *******************************\n");
                imprimirBaseDvd(arqDvds);

                printf("\nAplicando SelectionSort na base de DVDs.......\n");
                printf("\n\n\n\n\n\n\n\n\n");
                selectionSortDvd(arqDvds, 30); //FICAR ATENTA AO TAMANHO DA BASE PASSADA COMO PARAMETRO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

                imprimirBaseDvd(arqDvds);
                //printf("\033[H\033[J");

                printf("\n\n\n\n\n\n\n\n\n");
                imprimirBaseCliente(arqClientes);

                printf("\nAplicando SelectionSort na base de clientes.......\n");
                printf("\n\n\n\n\n\n\n\n\n");
                selectionSortCliente(arqClientes, 10); //FICAR ATENTA AO TAMANHO DA BASE PASSADA COMO PARAMETRO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

                imprimirBaseCliente(arqClientes);
                break;
            case 14:
                printf("\n********************** PARTICOES ORDENADAS: SELECAO NATURAL ************************\n");

                imprimirBaseDvd(arqDvds);
                //printf("\033[H\033[J");

                printf("\n\n\n\n\n\n\n\n\n");
                printf("\nAplicando metodo de particoes ordenadas DVD.......\n");
                int tamArqDvd = tamanhoArquivoDvd(arqDvds, 0);
                selecaoNatural(arqDvds, 30);
                printf("\n\n\n\n\n\n\n\n\n");

                imprimirBaseDvd(arqDvds);
                printf("\n\n\n\n\n\n\n\n\n");

                imprimirBaseCliente(arqClientes);
                //printf("\033[H\033[J");

                printf("\n\n\n\n\n\n\n\n\n");
                printf("\nAplicando metodo de particoes ordenadas CLIENTES.......\n");
                int tamArqCliente = tamanhoArquivoCliente(arqClientes, 0);
                selecaoNatural(arqClientes, 10);
                printf("\n\n\n\n\n\n\n\n\n");

                imprimirBaseCliente(arqClientes);
                printf("\n\n\n\n\n\n\n\n\n");

                break;
            case 15:
                break;
        }
    }
}