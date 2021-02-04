//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <conio.h>
#pragma hdrstop

#include "Plotador.h"
#include "MDF_Solve.h"

//#ifndef _EqHeat1DImplicitMethod_H
//#include "EqHeat1DImplicitMethod.h"
//#endif

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormPlotGraphic *FormPlotGraphic;

//---------------------------------------------------------------------------
__fastcall TFormPlotGraphic::TFormPlotGraphic(TComponent* Owner)
        : TForm(Owner)
{
     //mStopSimulation = false;
}
//---------------------------------------------------------------------------

void __fastcall TFormPlotGraphic::PlotarMesh(EqHeat mesh)
{
     double mTempo=0.0; //,mValueX[6]={0.0, 2.0, 4.0, 6.0, 8.0, 10.0};
     register int ln, k;
     AnsiString mMeshValues;

     for(ln = 0; ln < mesh->N; ln++) {
          for(k = 0; k < mesh->I; k++) {
               mMeshValues = FormatFloat("0.00000", mesh->node[ln][k].u);
               StringGrid1->Cells[k][ln+1] = mMeshValues;
               Chart1->SeriesList->Series[k]->AddXY(mTempo, mesh->node[ln][k].u, "", (TColor) clTeeColor);
          }
          mTempo += 0.1;
     }
}
//---------------------------------------------------------------------------

void __fastcall TFormPlotGraphic::Button2Click(TObject *Sender)
{
     Close();
}
//---------------------------------------------------------------------------
void __fastcall TFormPlotGraphic::FormShow(TObject *Sender)
{
     StringGrid1->Cells[0][0] = "u(t, x0)";
     StringGrid1->Cells[1][0] = "u(t, x1)";
     StringGrid1->Cells[2][0] = "u(t, x2)";
     StringGrid1->Cells[3][0] = "u(t, x3)";
     StringGrid1->Cells[4][0] = "u(t, x4)";
     StringGrid1->Cells[5][0] = "u(t, x5)";
     //PlotarMesh(); 
}
//---------------------------------------------------------------------------


