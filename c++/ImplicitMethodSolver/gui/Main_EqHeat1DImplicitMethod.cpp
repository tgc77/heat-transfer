
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#ifndef _EqHeat1DImplicitMethod_H
#include "EqHeat1DImplicitMethod.h"
#endif

REAL **SEL;

int main(void)
{
    EqHeat mesh;

    mesh = (EqHeat) malloc(sizeof(struct EqCondutionHeat));
    if(!mesh)
    {
          printf("\nErro, memoria não alocada !!!\n\n");
          system("pause");
          exit(1);
    }
    printf("=================================================================================\n");
    printf("--- CALCULO DA DISTRIBUICAO DE TEMPERATURA EM UMA MALHA PELO METODO IMPLICITO ---\n");
    printf("=================================================================================\n\n");
    printf("Entre com o comprimento da barra (L): ");
    scanf("%f", &mesh->L);

    printf("Entre com a quantidade de pontos a discretizar (I): ");
    scanf("%ld", &mesh->I);

    printf("Entre com o valor da variacao do tempo (delta t): ");
    scanf("%f", &mesh->deltaT);

    printf("Entre com o n§ de iteracoes sobre delta t (N): ");
    scanf("%ld", &mesh->N);

    printf("Entre com os valores para o calculo de alfa...");
    printf("\nk: ");
    scanf("%f", &mesh->k);
    printf("c: ");
    scanf("%f", &mesh->c);
    printf("rho: ");
    scanf("%f", &mesh->rho);

    printf("\nEntre com os valores das condicoes de contorno iniciais...");
    printf("\nTemperatura no ponto x = 0 (Uo): ");
    scanf("%f", &mesh->Uo);
    printf("Temperatura no ponto x = L (UL): ");
    scanf("%f", &mesh->UL);
  /*
    //*******************************< Parâmetros de teste >****************************************
    mesh->L = L_;
    mesh->I = I_;
    mesh->N = N_;
    mesh->deltaT = DeltaT;
    mesh->k = K;
    mesh->c = C;
    mesh->rho = Rho;
    mesh->Uo = 100.0;
    mesh->UL = 50.0;
    //**********************************************************************************************
  */
    mesh->deltaX = calcularDeltaX(mesh);
    mesh->alfa = calcularAlfa(mesh);

    iniciarConditionContorno(mesh);
    solveEqHeatImplicitMethod(mesh);
    salvarDadosEmArquivo(mesh);
    printf("\n\nFoi gerado um arquivo chamado: MeshPoints_ImplicitMethod.txt, com os dados calculados...\n\n");

    desaloca_SEL();
    free(mesh->node);
    free(mesh);
    
    getch();
    return(0);
}
 
