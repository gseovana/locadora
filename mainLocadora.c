#include <stdio.h>
#include <stdlib.h>
#include "locadora.c"

int main(){

    FILE *arq;
    TCliente *cliente;
    TFuncionario *funcionario;
    TDvd *dvd;

    if ((arq = fopen("locadora.dat", "w+b")) == NULL) {
        printf("Erro ao abrir arquivo\n");
        exit(1);
    }
    else{
      /*  cliente = criarCliente("Talia", "09/03/2000", "12522163252", 1, "952428251");
        salvarCliente(cliente, arq);
        imprimeCliente(cliente);


        funcionario = criarFuncionario("Alex", "451516516465", 2, 2000);
        salvarFuncionario(funcionario, arq);
        imprimeFuncionario(funcionario);

        dvd = criarDvd(5, "estrela", 2015, "Maria", "terror", 0);
        salvarDvd(dvd, arq);
        imprimeDvd(dvd);
*/

    criarBaseCliente(arq, 20);
    imprimirBaseCliente(arq);

    //funcionario = criarBaseFuncionario(arq, 10);
    //imprimirBaseFuncionario(arq);
    }




}
