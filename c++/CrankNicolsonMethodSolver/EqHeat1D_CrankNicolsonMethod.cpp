
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <Dialogs.hpp>

#ifndef _EqHeat1D_CrankNicolsonMethod_H
#include "EqHeat1D_CrankNicolsonMethod.h"
#endif

extern REAL **SEL;
REAL *U;

//==================================================================================================
REAL calcularDeltaX(EqHeat mesh)
{
     return mesh->deltaX = (mesh->L / (REAL)(mesh->I - 1.0));
}

//==================================================================================================
void iniciarConditionContorno(EqHeat mesh)
{
     mesh->node = (NO**) malloc((mesh->N + 1) * sizeof(struct NO));
     if(!mesh->node) {
            //printf("\nErro, memoria não alocada !!!\n\n");
            //getch();
            ShowMessage("Erro, memória não alocada !!!");
            exit(1);
     }
     for (register int n = 0; n < (mesh->N + 1); n++) {
            mesh->node[n] = (NO*) malloc(mesh->I * sizeof(struct NO));
            if(!mesh->node[n]) {
                  //printf("\nErro, memoria não alocada !!!\n\n");
                  //getch();
                  ShowMessage("Erro, memória não alocada !!!");
                  exit(1);
            }

            for (register int i = 0; i < mesh->I; i++) {
                  //mesh->node[n][i].t = (n * mesh->deltaT);
                  //mesh->node[n][i].x = (i * mesh->deltaX);
                  mesh->node[n][i].u = mesh->Ui;
            }
            mesh->node[n][0].u = mesh->Uo;
            mesh->node[n][mesh->I-1].u = mesh->UL;
     }
}

//==================================================================================================
REAL calcularAlfa(EqHeat mesh)
{
     return mesh->alfa = (mesh->k / (mesh->rho * mesh->c));
}

//==================================================================================================
REAL calcularLambda(EqHeat mesh)
{
     return mesh->lambda = mesh->alfa*(mesh->deltaT/pow(mesh->deltaX, 2));
}

//==================================================================================================
void solveEqHeat_CrankNicolsonMethod(EqHeat mesh)
{
     register int i, n, k, lin, col;

     mesh->lambda = calcularLambda(mesh);
     alocar_SEL(mesh->I-2, mesh->I-1);

     U = new(REAL[mesh->I-2]);

     for(n = 0; n < (mesh->N); n++) {
          //-------------------------------------------------------------------------------
          for(lin = 0, i = 0; lin < mesh->I-2; lin++, i++) {
               //-------------------------------------------------------------------------------
               for(col = 0; col < (mesh->I - 2); col++) {
                    //------------------------------------------------------------------------------
                    if(lin == col)
                        SEL[lin][col] = 2*(1 + mesh->lambda);
                    else
                      if( (lin == col-1)||(lin == col+1) )
                           SEL[lin][col] = (-1)*(mesh->lambda);
               }
               //-------------------------------------------------------------------------------
               // O índice i sempre será igual ao índice lin
               if(lin == 0) {
                   SEL[lin][mesh->I-2] = (mesh->lambda * mesh->node[n][i].u) +
                                          2*(1 - mesh->lambda)* mesh->node[n][i+1].u +
                                           (mesh->lambda * mesh->node[n][i+2].u) +
                                            (mesh->lambda * mesh->node[n+1][i].u);
               }
               else
                 if(lin < mesh->I-3) {
                     SEL[lin][mesh->I-2] = (mesh->lambda * mesh->node[n][i].u) +
                                            2*(1 - mesh->lambda)* mesh->node[n][i+1].u +
                                             (mesh->lambda * mesh->node[n][i+2].u);
                 }
                 else {
                    SEL[lin][mesh->I-2] = (mesh->lambda * mesh->node[n][i].u) +
                                           2*(1 - mesh->lambda)* mesh->node[n][i+1].u +
                                            (mesh->lambda * mesh->node[n][i+2].u) +
                                             (mesh->lambda * mesh->node[n+1][i+2].u);
                 }
          }
          //-------------------------------------------------------------------------------
          U = method_Gauss_Jordan(SEL, mesh->I-2, mesh->I-1);

          //-------------------------------------------------------------------------------
          for(k = 1; k < mesh->I-1; k++) {
               mesh->node[n+1][k].u = U[k-1];
          }
     }
}

//==================================================================================================
/*
void imprimirMesh(EqHeat mesh)
{
     register int i, n;

     printf("\n\nDistribuicao de temperatura nos pontos (Xi) da malha calculados:\n u(t, x):\n\n");
     for(n = mesh->N; n >= 0; n--) {
          printf("u(%d,%d): %.1f\t", n, 0, mesh->node[n][0].u);
          for(i = 1; i < mesh->I-1; i++) {
               printf("u(%d,%d): %.5f\t", n, i, mesh->node[n][i].u);
          }
          printf("u(%d,%d): %.1f\n", n, mesh->I-1, mesh->node[n][mesh->I-1].u);
     }
}
*/
//==================================================================================================
void salvarDadosEmArquivo(EqHeat mesh)
{
     FILE *arq;
     register int i, n;
     REAL incDeltaT=0.0f, incDeltaX=0.0f;

     if ((arq = fopen("MeshPoints_Crank-NicolsonMethod.txt", "w")) == NULL){
           //printf("\nErro, o arquivo nao pode ser aberto!\n");
           //getch();
           ShowMessage("Erro ao abrir arquivo...");
           exit(1);
     }

     fprintf(arq, "==========================================================================" \
                  "=========================================================\n");
     fprintf(arq, "      Distribuicao de temperatura nos pontos (Xi) da malha\n" \
                  "  calculados pelo metodo de Crank-Nicolson por diferenças finitas.\n");
     fprintf(arq, "===========================================================================" \
                  "=========================================================\n");
     fprintf(arq, "\nComprimento da barra (L): %.5f cm\n", mesh->L);
     fprintf(arq, "\nNº de pontos discretizados (I): %d nós\n", mesh->I);
     fprintf(arq, "\nDelta x: %.3f cm\n", mesh->deltaX);
     fprintf(arq, "\nValor da variação do tempo (delta t) para cada iteração: %.3f segundos\n", mesh->deltaT);
     fprintf(arq, "\nNº de iterações no tempo (N): %ld iterações em delta t\n", mesh->N);
     fprintf(arq, "\nValores dos parâmetros de alfa...\n");
     fprintf(arq, "\nConstante k: %.6f\n", mesh->k);
     fprintf(arq, "\nCalor específico c: %.6f\n", mesh->c);
     fprintf(arq, "\nrho: %.6f\n\n", mesh->rho);

     fprintf(arq, "u(xi, t) , com t variando de 0 até %d, e xi com i = 0, 1, 2,..., %d representa " \
           "a temperatura em cada ponto discretizado\nvariando no tempo t...\n\n", mesh->N-1, mesh->I-1);
     for(n = 0; n < mesh->N; n++) {
          for(i = 0; i < mesh->I; i++) {
               incDeltaX += mesh->deltaX;
               incDeltaT += mesh->deltaT;
               fprintf(arq, "u(%.1f,%.1f): %.4f\t", incDeltaX, incDeltaT, mesh->node[n][i].u);
          }
          fprintf(arq, "\n");
     }
     fclose(arq);
}

//==================================================================================================
/*
void imprimirSEL(const int LIN, const int COL)
{
     register int ln, k;

     printf("\n\n");
     for(ln = 0; ln < LIN; ln++) {
          printf("U(%d): ", ln+1);
          for(k = 0; k < COL; k++) {
               printf(" %.6f ", SEL[ln][k]);
          }
          printf("\n\n");
     }
}
*/
//==================================================================================================
REAL *method_Gauss_Jordan(REAL **SEL, const int LIN, const int COL)
{
     REAL *aux, divLn, multpLn;
     register int lin, Ln, ln, k;
     bool mSysIndeterminado = false;

     ln = 0;
     for(lin = 0; lin < LIN; lin++) {
          //----------------------------------------------------
          do {
               k = 0;
               while(k < COL && SEL[ln][k] == 0.000000)
                   k++;
               if(k != 0) {
                   if(k > 0 && k < COL-1) {
                       if(ln < LIN-1)
                           ln++;
                   }
                   else {
                      mSysIndeterminado = true;
                   }
               }
          }while((k != 0) && (k > 0 && k < COL-1) && (ln < LIN-1));
          //---------------------------------------------------------
          if(!mSysIndeterminado) {
               if(ln != 0) {
                   aux = SEL[lin];
                   SEL[lin] = SEL[ln];
                   SEL[ln] = aux;
               }
               //----------------------------------------------------
               divLn = SEL[lin][lin];
               for(k = 0; k < COL; k++) {
                    SEL[lin][k] /= divLn;
                    if(SEL[lin][k] == -0.000000)
                        SEL[lin][k] = 0.000000;
               }
               //----------------------------------------------------
               for(Ln = 0; Ln < LIN; Ln++) {
                    if(Ln != lin) {
                        multpLn = SEL[Ln][lin];
                        for(k = lin; k < COL; k++) {
                             SEL[Ln][k] -= (multpLn * SEL[lin][k]);
                        }
                    }
               }
               //----------------------------------------------------
          }
          else {
              //printf("\nSistema indeterminado !!!\n");
              ShowMessage("Sistema indeterminado !!!");
              //getch();
              delete []U;
              exit(1);
          }
     }
     //--------------------------------------------------------------
     for(lin = 0; lin < LIN; lin++) {
          U[lin] = SEL[lin][COL-1];
     }
     return U;      
}
//==================================================================================================
void alocar_SEL(const int LIN, const int COL)
{
     SEL = (REAL**) calloc(LIN, sizeof(REAL));
     if(!SEL) {
          //printf("\nErro, memoria não alocada !!!\n\n");
          //getch();
          ShowMessage("Erro, memória não alocada !!!");
          exit(1);
     }
     for(register int i = 0; i < LIN; i++) {
            SEL[i] = (REAL*) calloc(COL, sizeof(REAL));
            if(!SEL[i]) {
                 //printf("\nErro, memoria não alocada !!!\n\n");
                 //getch();
                 ShowMessage("Erro, memória não alocada !!!");
                 exit(1);
            }
     }
}
//==================================================================================================
void desaloca_SEL()
{
     free(SEL);
     delete []U;
}
//==================================================================================================
void ler_SEL(EqHeat mesh, REAL **SEL)
{
     FILE *arqSEL;
     register int lin, col;
     
     if ((arqSEL = fopen("SEL.txt", "r")) == NULL) {
           //printf("\nErro, o arquivo nao pode ser aberto!\n");
           //getch();
           ShowMessage("Erro ao abrir arquivo...");
           exit(1);
     }
     //alocar_SEL(Linhas, Colunas);
     for(lin = 0; lin < 3; lin++) {
           for(col = 0; col < 4; col++) {
                  fscanf(arqSEL, "%f", (*(SEL+lin)+col));                   
           }
     }
}
//==================================================================================================
     

