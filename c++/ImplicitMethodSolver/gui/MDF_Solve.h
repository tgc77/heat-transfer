//---------------------------------------------------------------------------

#ifndef MDF_SolveH
#define MDF_SolveH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>

#ifndef _EqHeat1DImplicitMethod_H
#include "EqHeat1DImplicitMethod.h"
#endif

//---------------------------------------------------------------------------
class TFormSolver : public TForm
{
__published:	// IDE-managed Components
        TStatusBar *StatusBar1;
        TPanel *Panel1;
        TButton *btnPlotGraphic;
        TButton *btnSair;
        TGroupBox *GroupBox1;
        TGroupBox *GroupBox2;
        TLabel *Label1;
        TEdit *EditValorL;
        TLabel *Label2;
        TEdit *EditValorI;
        TGroupBox *GroupBox3;
        TLabel *Label3;
        TEdit *EditValorDeltaT;
        TLabel *Label4;
        TEdit *EditIncrementoDeltaT;
        TGroupBox *GroupBox4;
        TLabel *Label5;
        TEdit *EditValorK;
        TLabel *Label6;
        TLabel *Label7;
        TEdit *EditValorC;
        TEdit *EditValorRho;
        TGroupBox *GroupBox5;
        TLabel *Label8;
        TEdit *EditUzero;
        TLabel *Label9;
        TEdit *EditUL;
        TButton *btnAbrirArq;
        void __fastcall btnSairClick(TObject *Sender);
        void __fastcall btnPlotGraphicClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall btnAbrirArqClick(TObject *Sender);
        void __fastcall EditValorLKeyPress(TObject *Sender, char &Key);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall EditValorLChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
        EqHeat mesh;

        __fastcall TFormSolver(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSolver *FormSolver;
//---------------------------------------------------------------------------
#endif
