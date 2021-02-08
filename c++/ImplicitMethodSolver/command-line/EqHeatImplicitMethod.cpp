#include <iostream>
#include <sstream>
#include <math.h>

#ifndef _EqHeatImplicitMethod_H
#include "EqHeatImplicitMethod.h"
#endif

//=============================================================================
template<typename Type, typename TType>
void getInputNumber(Type &param, std::string label, TType default_val) {
    std::cout << label;
    if (std::cin.peek() == '\n') {
        param = default_val;
    } else {
        std::cin >> param;
    }
    std::cin.ignore();
}

//=============================================================================
EqHeatImplicitMethod::EqHeatImplicitMethod() : 
    _SEL(nullptr), U(nullptr), mesh(nullptr) {
}

//=============================================================================
void EqHeatImplicitMethod::alocateMeshMemory() {
     mesh = (EqHeat)malloc(sizeof(struct EqCondutionHeat));
     if (!mesh) {
          std::cout <<"\nErro, memoria nao alocada !!!\n";
          exit(EXIT_FAILURE);
     }
}

//=============================================================================
void EqHeatImplicitMethod::alocateSolverParametersMemory() {
     alocar_SEL(mesh->I - 2, mesh->I - 1);
     U = new REAL[mesh->I - 2];
}
//=============================================================================
void EqHeatImplicitMethod::initializeMeshParameters() {
    alocateMeshMemory();

    std::cout <<"=================================================================================\n";
    std::cout <<"--- CALCULO DA DISTRIBUICAO DE TEMPERATURA EM UMA MALHA PELO METODO IMPLICITO ---\n";
    std::cout <<"=================================================================================\n\n";
    std::cout <<"Entre com os valores para o calculo:";
    getInputNumber(mesh->L, "\nComprimento da barra (L): ", 20);
    getInputNumber(mesh->I, "Quantidade de pontos a discretizar (I): ", 5);
    
    getInputNumber(mesh->deltaT, 
        "Variacao do tempo (delta t): default = 0.1\n",
        DeltaT);
    getInputNumber(mesh->N, "N. de iteracoes sobre delta t (N): ", 33);
    std::cout <<"Valores para o calculo de alfa ==>\n";
    getInputNumber(mesh->k, "k: default = 0.4899\n", K);
    getInputNumber(mesh->c, "c: default = 0.2174\n", C);
    getInputNumber(mesh->rho, "rho: default = 2.7000\n", Rho);

    std::cout <<"\nCondicoes de contorno iniciais...";
    getInputNumber(mesh->Uo, "\nTemperatura no ponto x = 0 (Uo): ", 0);
    getInputNumber(mesh->UL, "Temperatura no ponto x = L (UL): ", 100);

    mesh->deltaX = calcularDeltaX();
    mesh->alfa = calcularAlfa();
}
//=============================================================================
REAL EqHeatImplicitMethod::calcularDeltaX()
{
     return mesh->deltaX = (mesh->L / (REAL)(mesh->I - 1.0));
}
//=============================================================================
void EqHeatImplicitMethod::applyInitialConditionBoundary()
{
     mesh->node = (NO **)malloc((mesh->N + 1) * sizeof(struct NO));
     if (!mesh->node)
     {
          printf("\nErro, memoria nao alocada !!!\n");
          exit(1);
     }
     for (int n = 0; n < (mesh->N + 1); n++)
     {
          mesh->node[n] = (NO *)malloc(mesh->I * sizeof(struct NO));
          if (!mesh->node[n])
          {
               printf("\nErro, memoria nao alocada !!!\n");
               free(mesh);
               exit(1);
          }
          for (int i = 0; i < mesh->I; i++)
          {
               mesh->node[n][i].t = (n * mesh->deltaT);
               mesh->node[n][i].x = (i * mesh->deltaX);
               mesh->node[n][i].u = 0.0;
          }
          mesh->node[n][0].u = mesh->Uo;
          mesh->node[n][mesh->I - 1].u = mesh->UL;
     }
}
//=============================================================================
REAL EqHeatImplicitMethod::calcularAlfa()
{
     return mesh->alfa = (mesh->k / (mesh->rho * mesh->c));
}
//=============================================================================
REAL EqHeatImplicitMethod::calcularLambda()
{
     return mesh->lambda = mesh->alfa * (mesh->deltaT / pow(mesh->deltaX, 2));
}
//=============================================================================
void EqHeatImplicitMethod::solve()
{
     int n, k, lin, col;

     mesh->lambda = calcularLambda();

     alocateSolverParametersMemory();

     for (n = 0; n < (mesh->N); n++)
     {
          //-------------------------------------------------------------------
          for (lin = 0; lin < mesh->I - 2; lin++)
          {
               //--------------------------------------------------------------
               for (col = 0; col < (mesh->I - 2); col++)
               {
                    //---------------------------------------------------------
                    if (lin == col)
                         _SEL[lin][col] = (1 + 2 * mesh->lambda);
                    else if ((lin == col - 1) || (lin == col + 1))
                         _SEL[lin][col] = (-1) * (mesh->lambda);
               }
               //--------------------------------------------------------------
               if (lin == 0) {
                    _SEL[lin][mesh->I - 2] = mesh->node[n][lin + 1].u + 
                                        (mesh->lambda * mesh->node[n + 1][0].u);
               }
               else if (lin < mesh->I - 3)
                    _SEL[lin][mesh->I - 2] = mesh->node[n][lin + 1].u;
               else {
                    _SEL[lin][mesh->I - 2] = mesh->node[n][mesh->I - 2].u + 
                              (mesh->lambda * mesh->node[n + 1][mesh->I - 1].u);
               }
          }
          //-------------------------------------------------------------------
          U = method_Gauss_Jordan(_SEL, mesh->I - 2, mesh->I - 1);
          //-------------------------------------------------------------------
          printf("\nu(%d): %.1f\t", 0, mesh->node[n + 1][0].u);
          for (k = 1; k < mesh->I - 1; k++)
          {
               mesh->node[n + 1][k].u = U[k - 1];
               printf("u(%d): %.5f\t", k, mesh->node[n + 1][k].u);
          }
          printf("u(%ld): %.1f", mesh->I - 1, mesh->node[n + 1][mesh->I - 1].u);
     }
}
//=============================================================================
void EqHeatImplicitMethod::imprimirMesh()
{
     int i, n;

     printf("\n\nDistribuicao de temperatura nos pontos (Xi) da malha calculados:\n u(t, x):\n\n");
     for (n = mesh->N; n >= 0; n--)
     {
          printf("u(%d,%d): %.1f\t", n, 0, mesh->node[n][0].u);
          for (i = 1; i < mesh->I - 1; i++)
          {
               printf("u(%d,%d): %.5f\t", n, i, mesh->node[n][i].u);
          }
          printf("u(%d,%ld): %.1f\n", n, mesh->I - 1, mesh->node[n][mesh->I - 1].u);
     }
}
//=============================================================================
void EqHeatImplicitMethod::salvarDadosEmArquivo()
{
     FILE *arq;
     int i, n;

     if ((arq = fopen("MeshPoints_ImplicitMethod.txt", "w")) == NULL)
     {
          printf("\nErro, o arquivo nao pode ser aberto!\n");
          exit(1);
     }

     fprintf(arq, "=========================================================================="
                  "==============================================\n");
     fprintf(arq, "      Distribuicao de temperatura nos pontos (Xi) da malha calculados "
                  "pelo metodo Implicito por diferencas finitas.\n");
     fprintf(arq, "==========================================================================="
                  "=============================================\n");
     fprintf(arq, "\nComprimento da barra (L): %.5f cm\n", mesh->L);
     fprintf(arq, "\nNo de pontos discretizados (I): %ld nos\n", mesh->I);
     fprintf(arq, "\nValor da variacao do tempo (delta t) para cada iteracao: %.3f segundos\n", mesh->deltaT);
     fprintf(arq, "\nNo de iteracoes no tempo (N): %ld iteracoes em delta t\n", mesh->N);
     fprintf(arq, "\nValores dos parametros de alfa...\n");
     fprintf(arq, "\nConstante k: %.6f\n", mesh->k);
     fprintf(arq, "\nCalor especifico c: %.6f\n", mesh->c);
     fprintf(arq, "\nrho: %.6f\n\n", mesh->rho);

     fprintf(arq, "u(t, xi) , com t variando de 0 ate %ld, e xi com i = 0, 1,..., %ld sao "
                  "os nos da malha...\n\n",
             mesh->N - 1, mesh->I - 1);
     for (n = 0; n < mesh->N; n++)
     {
          for (i = 0; i < mesh->I; i++)
          {
               fprintf(arq, "u(%d,%d): %.6f\t", n, i, mesh->node[n][i].u);
          }
          fprintf(arq, "\n");
     }
     fclose(arq);
}
//=============================================================================
void EqHeatImplicitMethod::imprimirSEL(const int LIN, const int COL)
{
     int ln, k;

     printf("\n\n");
     for (ln = 0; ln < LIN; ln++)
     {
          printf("L%d: ", ln);
          for (k = 0; k < COL; k++)
          {
               printf(" %.6f ", _SEL[ln][k]);
          }
          printf("\n\n");
     }
}
//=============================================================================
REAL* EqHeatImplicitMethod::method_Gauss_Jordan(REAL **SEL, const int LIN, const int COL)
{
     REAL *aux, divLn, multpLn;
     int lin, Ln, ln, k;
     bool mSysIndeterminado = false;

     ln = 0;
     for (lin = 0; lin < LIN; lin++)
     {
          //----------------------------------------------------
          do
          {
               k = 0;
               while (k < COL && SEL[ln][k] == 0.000000)
                    k++;
               if (k != 0)
               {
                    if (k > 0 && k < COL - 1)
                    {
                         if (ln < LIN - 1)
                              ln++;
                    }
                    else
                    {
                         mSysIndeterminado = true;
                    }
               }
          } while ((k != 0) && (k > 0 && k < COL - 1) && (ln < LIN - 1));
          //---------------------------------------------------------
          if (!mSysIndeterminado)
          {
               if (ln != 0)
               {
                    aux = SEL[lin];
                    SEL[lin] = SEL[ln];
                    SEL[ln] = aux;
               }
               //----------------------------------------------------
               divLn = SEL[lin][lin];
               for (k = 0; k < COL; k++)
               {
                    SEL[lin][k] /= divLn;
                    if (SEL[lin][k] == -0.000000)
                         SEL[lin][k] = 0.000000;
               }
               //----------------------------------------------------
               for (Ln = 0; Ln < LIN; Ln++)
               {
                    if (Ln != lin)
                    {
                         multpLn = SEL[Ln][lin];
                         for (k = lin; k < COL; k++)
                         {
                              SEL[Ln][k] -= (multpLn * SEL[lin][k]);
                         }
                    }
               }
               //----------------------------------------------------
          }
          else
          {
               printf("\nSistema indeterminado !!!\n");
               exit(1);
          }
     }
     //--------------------------------------------------------------
     for (lin = 0; lin < LIN; lin++)
     {
          U[lin] = SEL[lin][COL - 1];
     }
     return U;
}
//=============================================================================
void EqHeatImplicitMethod::alocar_SEL(const int LIN, const int COL)
{
     _SEL = new REAL*[LIN];
     if (!_SEL)
     {
          printf("\nErro, memoria nao alocada !!!\n\n");
          exit(1);
     }
     for (int i = 0; i < LIN; i++)
     {
          _SEL[i] = new REAL[COL];
          if (!_SEL[i])
          {
               printf("\nErro, memoria nao alocada !!!\n\n");
               delete[] _SEL;
               exit(1);
          }
     }
}
//=============================================================================
void EqHeatImplicitMethod::desaloca_SEL()
{
     const int LIN = mesh->I - 2;
     for (int i = 0; i < LIN; i++) {
          delete[] _SEL[i];
     }
     delete[] _SEL;
     delete[] U;
}
//=============================================================================
void EqHeatImplicitMethod::ler_SEL(REAL **SEL)
{
     FILE *arqSEL;
     int lin, col;

     if ((arqSEL = fopen("SEL.txt", "r")) == NULL)
     {
          printf("\nErro, o arquivo nao pode ser aberto!\n");
          exit(1);
     }
     for (lin = 0; lin < 3; lin++)
     {
          for (col = 0; col < 4; col++)
          {
               fscanf(arqSEL, "%f", (*(SEL + lin) + col));
          }
     }
}
//=============================================================================
