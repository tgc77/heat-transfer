
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <Dialogs.hpp>

#ifndef _EqHeat1DImplicitMethod_H
#include "EqHeat1DImplicitMethod.h"
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
     if(!mesh->node){
            ShowMessage("Erro, mem�ria n�o alocada !!!");
            Abort();
     }
     for (register int n = 0; n < (mesh->N + 1); n++)
     {
            mesh->node[n] = (NO*) malloc(mesh->I * sizeof(struct NO));
            if(!mesh->node[n]){
                  ShowMessage("Erro, mem�ria n�o alocada !!!");
                  Abort();
            }
            for (register int i = 0; i < mesh->I; i++){
                  mesh->node[n][i].t = (n * mesh->deltaT);
                  mesh->node[n][i].x = (i * mesh->deltaX);
                  mesh->node[n][i].u = 0.0;
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
void solveEqHeatImplicitMethod(EqHeat mesh)
{
     register int i, n, k, lin, col;

     mesh->lambda = calcularLambda(mesh);
     alocar_SEL(mesh->I-2, mesh->I-1);

     U = new(REAL[mesh->I-2]);

     for(n = 0; n < (mesh->N); n++) {
          //-------------------------------------------------------------------------------
          for(lin = 0; lin < mesh->I-2; lin++) {
               //-------------------------------------------------------------------------------
               for(col = 0; col < (mesh->I - 2); col++) {
                    //------------------------------------------------------------------------------
                    if(lin == col)
                        SEL[lin][col] = (1 + 2*mesh->lambda);
                    else
                      if( (lin == col-1)||(lin == col+1) )
                           SEL[lin][col] = (-1)*(mesh->lambda);
               }
               //-------------------------------------------------------------------------------
               if(lin == 0)
                   SEL[lin][mesh->I-2] = mesh->node[n][lin+1].u + (mesh->lambda * mesh->node[n+1][0].u);
               else
                 if(lin < mesh->I-3)
                     SEL[lin][mesh->I-2] = mesh->node[n][lin+1].u;
                 else
                    SEL[lin][mesh->I-2] = mesh->node[n][mesh->I-2].u + (mesh->lambda * mesh->node[n+1][mesh->I-1].u);
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
void salvarDadosEmArquivo(EqHeat mesh)
{
     FILE *arq;
     register int i, n;

     if ((arq = fopen("MeshPoints_ImplicitMethod.txt", "w")) == NULL){
           ShowMessage("Erro, o arquivo n�o pode ser aberto!");
           fclose(arq);
           Abort();
     }

     fprintf(arq, "==========================================================================" \
                  "==============================================\n");
     fprintf(arq, "      Distribui��o de temperatura nos pontos (Xi) da malha calculados " \
                  "pelo metodo Impl�cito por diferen�as finitas.\n");
     fprintf(arq, "===========================================================================" \
                  "=============================================\n");
     fprintf(arq, "\nComprimento da barra (L): %.5f cm\n", mesh->L);
     fprintf(arq, "\nN� de pontos discretizados (I): %d n�s\n", mesh->I);
     fprintf(arq, "\nValor da varia��o do tempo (delta t) para cada itera��o: %.3f segundos\n", mesh->deltaT);
     fprintf(arq, "\nN� de itera��es no tempo (N): %ld itera��es em delta t\n", mesh->N);
     fprintf(arq, "\nValores dos par�metros de alfa...\n");
     fprintf(arq, "\nConstante k: %.6f\n", mesh->k);
     fprintf(arq, "\nCalor espec�fico c: %.6f\n", mesh->c);
     fprintf(arq, "\nrho: %.6f\n\n", mesh->rho);

     fprintf(arq, "u(t, xi) , com t variando de 0 at� %d, e xi com i = 0, 1,..., %d s�o " \
           "os n�s da malha...\n\n", mesh->N-1, mesh->I-1);
     for(n = 0; n < mesh->N; n++) {
          for(i = 0; i < mesh->I; i++) {
               fprintf(arq, "u(%d,%d): %.6f\t", n, i, mesh->node[n][i].u);
          }
          fprintf(arq, "\n");
     }
     fclose(arq);
}

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
              ShowMessage("Sistema de equa��es lineares indeterminado.");
              delete []U;
              Abort();
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
          ShowMessage("Erro, mem�ria n�o alocada !!!");
          Abort();
     }
     for(register int i = 0; i < LIN; i++) {
            SEL[i] = (REAL*) calloc(COL, sizeof(REAL));
            if(!SEL[i]) {
                 ShowMessage("Erro, mem�ria n�o alocada !!!");
                 Abort();
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

     if ((arqSEL = fopen("SEL.txt", "r")) != NULL) {
            for(lin = 0; lin < 3; lin++) {
                  for(col = 0; col < 4; col++) {
                        fscanf(arqSEL, "%f", (*(SEL+lin)+col));
                  }
            }
     }
     else
        ShowMessage("Erro, o arquivo n�o pode ser aberto!");
        
     fclose(arqSEL);
}
//==================================================================================================
     

