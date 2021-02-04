//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "MDF_Solve.h"

#ifndef GraphicMesh_H
#include "GraphicMesh.h"
#endif

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormSolver *FormSolver;
REAL **SEL;
EqHeat mesh;

TProcessMatrix *processMatrix;
TSolveMethod   *solveMethod;

//---------------------------------------------------------------------------
__fastcall TFormSolver::TFormSolver(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormSolver::btnSairClick(TObject *Sender)
{
     if (flagThreadStarted) {
            processMatrix->Terminate();
            solveMethod->Terminate();
     }
     if(mesh != NULL) {
          free(mesh->node);
          free(mesh);
     }
     Close();
}
//---------------------------------------------------------------------------

void __fastcall TFormSolver::btnDiscretizarPClick(TObject *Sender)
{
     if (mesh != NULL) {
          free(mesh->node);
          free(mesh);
     }
     mesh = (EqHeat) malloc(sizeof(struct EqCondutionHeat));
     if(!mesh) {
          ShowMessage("Erro, memória não alocada !!!");
          Abort();
     }
     //*******************************< Parâmetros de entrada >*************************************
     mesh->L = StrToFloat(EditValorL->Text);
     mesh->I = StrToFloat(EditValorI->Text);
     mesh->N = StrToFloat(EditIncrementoDeltaT->Text);
     mesh->deltaT = StrToFloat(EditValorDeltaT->Text);
     mesh->k = StrToFloat(EditValorK->Text);
     mesh->c = StrToFloat(EditValorC->Text);
     mesh->rho = StrToFloat(EditValorRho->Text);
     mesh->Uo = StrToFloat(EditUzero->Text);
     mesh->UL = StrToFloat(EditUL->Text);
     mesh->Ui = StrToFloat(EditUInter->Text);
     //*********************************************************************************************

     mesh->deltaX = calcularDeltaX(mesh);
     mesh->alfa = calcularAlfa(mesh);

     processMatrix = new TProcessMatrix();
     processMatrix->OnTerminate = ProcessMatrixDone;
     flagThreadStarted = true;

     btnDiscretizarP->Enabled = false;
     /*
     iniciarConditionContorno(mesh);
     solveEqHeat_CrankNicolsonMethod(mesh);

     desaloca_SEL();
     salvarDadosEmArquivo(mesh);

     btnDiscretizarP->Enabled = true;
     btnAbrirArq->Enabled = true;
     */
     Application->CreateForm(__classid(TFormGraphicMesh), &FormGraphicMesh);
     FormGraphicMesh->Show();
     FormGraphicMesh->Update();
     FormGraphicMesh->inicializaTabela(mesh);
}
//---------------------------------------------------------------------------

void __fastcall TFormSolver::FormClose(TObject *Sender,
      TCloseAction &Action)
{
     Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TFormSolver::btnAbrirArqClick(TObject *Sender)
{
     AnsiString mCurrentDir = GetCurrentDir();

     ShellExecute(Handle, "open", "MeshPoints_Crank-NicolsonMethod.txt", "", mCurrentDir.c_str(), SW_MAXIMIZE);
}
//---------------------------------------------------------------------------

void __fastcall TFormSolver::EditValorLKeyPress(TObject *Sender, char &Key)
{
     if(Key == '.')
         Key = ',';
}
//---------------------------------------------------------------------------

void __fastcall TFormSolver::FormShow(TObject *Sender)
{
     EditValorL->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TFormSolver::EditValorLChange(TObject *Sender)
{
     if(EditUL->Text != "" && EditUzero->Text != "" && EditValorL->Text != "" &&
         EditValorI->Text != "" && EditValorDeltaT->Text != "" && EditValorC->Text != "" &&
         EditIncrementoDeltaT->Text != "" && EditValorK->Text != "" && EditValorRho->Text != "")
              btnDiscretizarP->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TFormSolver::ProcessMatrixDone(TObject *Sender)
{
     //ShowMessage("processMatrix Terminated...");
     solveMethod = new TSolveMethod();
     solveMethod->OnTerminate = SolveMethodDone;

     //solveEqHeat_CrankNicolsonMethod(mesh);
     //processTerminated = true;
}
//---------------------------------------------------------------------------

void __fastcall TFormSolver::SolveMethodDone(TObject *Sender)
{
     desaloca_SEL();
     salvarDadosEmArquivo(mesh);

     FormGraphicMesh->carregaTabela(mesh);

     btnDiscretizarP->Enabled = true;
     btnAbrirArq->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TFormSolver::CkBoxEstabilizaUClick(TObject *Sender)
{
     if (CkBoxEstabilizaU->Checked == true) {
           EditIncrementoDeltaT->Enabled = false;
           flagEstabilizarU = true;
     }
     else {
         EditIncrementoDeltaT->Enabled = true;
         flagEstabilizarU = false;
     }    
}
//---------------------------------------------------------------------------

