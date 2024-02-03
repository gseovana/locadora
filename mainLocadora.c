#include <stdio.h>
#include <stdlib.h>
#include "locadora.c"
#include "selectionSort.h"
#include "selecaoNatural.h"
#include "arvoreBinariaVencedores.h"
#include "hash.h"

#define TAM_DVD 300
#define TAM_CLIENTE 100
#define TAM_LOCADORA 4
int main() {

    FILE *arqClientes, *arqDvds, *arqLocadora, *arqHash, *logFileDvd, *logFileCliente, *logSelecaoDvd, *logSelecaoCliente, *logArvoreVencDvd, *logArvoreVencCliente;
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

    if ((logFileDvd = fopen("logSelectionSortDvd.txt", "w")) == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }

    if ((logFileCliente = fopen("logSelectionSortCliente.txt", "w")) == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }

    if ((logSelecaoDvd = fopen("logSelecaoDVD.txt", "w")) == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }

    if ((logSelecaoCliente = fopen("logSelecaoCliente.txt", "w")) == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }

    if ((logArvoreVencDvd = fopen("logArvoreDVD.txt", "w")) == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }

    if ((logArvoreVencCliente = fopen("logArvoreCliente.txt", "w")) == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }

    if ((arqHash = fopen("hashTable.dat", "w+b")) == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }

    criarBaseDvd(arqDvds, TAM_DVD);
    criarBaseCliente(arqClientes, TAM_CLIENTE);
    criarBaseLocadora(arqLocadora, arqClientes, arqDvds, TAM_LOCADORA);

    int gerador_id_locadora = 1,
            opcao = -1,
            gerador_id_dvd_hash = 0,
            gerador_id_dvd = 0,
            gerador_id_cliente = 0, c;


    while (opcao != 0) {
        system("clear");
        printf("\n***************************** LOCADORA TAGEO  ********************************");
        printf("\n1. Cadastrar DVD \n2. Buscar DVD \n3. Excluir DVD \n4. Imprimir todos os DVDs \n-----------------------------\n"
               "5. Cadastrar cliente \n6. Buscar cliente \n7. Excluir cliente \n8. Imprimir todos os clientes \n-----------------------------"
               "\n9. Alugar DVD\n10. Buscar locacao \n11. Imprimir todas as locacoes\n12. Devolver DVD\n---------------------------"
               "\n13. SelectionSort\n14. Arvore binaria de vencedores\n15. Tabela hash\n---------------------------\n0. Sair\n\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        //fflush(arq);

        switch (opcao) {
            case 1:
                system("clear");
                printf("\n************************* CADASTRAR DVD *******************************\n");

                dvd = (TDvd *) malloc(sizeof(TDvd));

                // Limpar o buffer, consumindo o caractere de nova linha remanescente
                while (getchar() != '\n');

                gerador_id_dvd++;
                dvd->id_dvd = TAM_DVD + gerador_id_dvd;


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

                gerador_id_cliente++;
                cliente->idC = TAM_CLIENTE + gerador_id_cliente;


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


                locacao = buscaBinariaLocacao(id_locacao, arqLocadora, 0, tamanho_arquivo_locadora(arqLocadora),
                                              "locadora.txt");

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
                selectionSortDvd(arqDvds, TAM_DVD, logFileDvd);

                imprimirBaseDvd(arqDvds);
                //printf("\033[H\033[J");

                printf("\n\n\n\n\n\n\n\n\n");
                imprimirBaseCliente(arqClientes);

                printf("\nAplicando SelectionSort na base de clientes.......\n");
                printf("\n\n\n\n\n\n\n\n\n");
                selectionSortCliente(arqClientes, TAM_CLIENTE, logFileCliente);

                imprimirBaseCliente(arqClientes);
                break;
            case 14:
                printf("\n********************** ARVORE BINARIA DE VENCEDORES ************************\n");

                imprimirBaseDvd(arqDvds);
                //printf("\033[H\033[J");

                printf("\n\n\n\n");
                printf("\nAplicando metodo de arvore binaria de vencedores na base de DVDs.......\n");
                int qtd = 1;

                qtd += selecaoNaturalDvd(arqDvds, tamanho_arquivo_dvd(arqDvds), logSelecaoDvd);

                arvoreBinariaVencDvd(qtd, logArvoreVencDvd);
                printf("\n\n\n\n");

                imprimirBaseCliente(arqClientes);
                printf("\n\n\n\n");
                printf("\nAplicando metodo de arvore binaria de vencedores na base de clientes.......\n");

                qtd = 1;

                //printf("\033[H\033[J");
                qtd += selecaoNaturalCliente(arqClientes, tamanho_arquivo_cliente(arqClientes), logSelecaoCliente);


                arvoreBinariaVencCliente(qtd, logArvoreVencCliente);
                break;
            case 15:
                printf("\033[H\033[J");
                int opcaoHash = -1;

                TabelaHash *novaTabela = criarTabelaHash(TAM_CLIENTE, arqHash);

                printf("\n********************** TABELA HASH ************************\n");

                while (opcaoHash != 0) {
                    printf("1. Inserir DVD\n2. Buscar DVD\n3. Excluir DVD\n4. Imprimir DVDs\n0. Sair\n\nEscolha uma opcao: ");
                    scanf("%d", &opcaoHash);

                    switch (opcaoHash) {
                        case 1:
                            printf("\n************************* INSERIR DVD HASH *******************************\n");

                            dvd = (TDvd *) malloc(sizeof(TDvd));

                            // Limpar o buffer, consumindo o caractere de nova linha remanescente
                            while (getchar() != '\n');

                            gerador_id_dvd_hash++;
                            dvd->id_dvd = gerador_id_dvd_hash;

                            printf("ID: %d", dvd->id_dvd);

                            printf("\nTítulo: ");
                            fgets(dvd->nome_dvd, 100, stdin);

                            printf("Gênero: ");
                            fgets(dvd->genero, 100, stdin);

                            dvd->emprestimo = 0;

                            inserirHashFile(novaTabela, *dvd, arqHash);

                            opcaoHash = -1;

                            free(dvd);

                            break;
                        case 2:
                            printf("\n**************************** BUSCAR DVD HASH ******************************\n");

                            printf("Informe o id do dvd: ");
                            scanf("%d", &id_dvd);

                            buscarHashFile(novaTabela, id_dvd, arqHash);

                            opcaoHash = -1;

                            break;
                        case 3:
                            printf("\n**************************** EXCLUIR DVD HASH ****************************\n");
                            printf("Informe o id do dvd: ");
                            scanf("%d", &id_dvd);

                            removerHashFile(novaTabela, id_dvd, arqHash);

                            opcaoHash = -1;

                            break;
                        case 4:
                            printf("\n********************** IMPRIMIR BASE DE DADOS DE DVDs HASH ************************\n");
                            //imprimirHashTable(novaTabela, arqHash);

                            opcaoHash = -1;

                            break;

                    }

                    break;
                }
        }
    }
}