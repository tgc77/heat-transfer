//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#pragma hdrstop

#include "MDF_Solve.h"

#ifndef PlotadorH
#include "Plotador.h"
#endif

#ifndef _EqHeat1DImplicitMethod_H
#include "EqHeat1DImplicitMethod.h"
#endif

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormSolver *FormSolver;
REAL **SEL;
//extern EqHeat mesh;
//---------------------------------------------------------------------------
__fastcall TFormSolver::TFormSolver(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormSolver::btnSairClick(TObject *Sender)
{
     Close();
}
//---------------------------------------------------------------------------

void __fastcall TFormSolver::btnPlotGraphicClick(TObject *Sender)
{
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
     //*********************************************************************************************

     mesh->deltaX = calcularDeltaX(mesh);
     mesh->alfa = calcularAlfa(mesh);
     
     iniciarConditionContorno(mesh);
     solveEqHeatImplicitMethod(mesh);
     desaloca_SEL();
     salvarDadosEmArquivo(mesh);

     btnAbrirArq->Enabled = true;
     FormPlotGraphic->Show();
     FormPlotGraphic->PlotarMesh(mesh);
}
//---------------------------------------------------------------------------

void __fastcall TFormSolver::FormClose(TObject *Sender,
      TCloseAction &Action)
{
     free(mesh->node);
     free(mesh);
     Action = caFree;
}
//---------------------------------------------------------------------------

void __fastcall TFormSolver::btnAbrirArqClick(TObject *Sender)
{
     AnsiString mCurrentDir = GetCurrentDir();

     ShellExecute(Handle, "open", "MeshPoints_ImplicitMethod.txt", "", mCurrentDir.c_str(), SW_MAXIMIZE);
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
              btnPlotGraphic->Enabled = true; 
}
//---------------------------------------------------------------------------

