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

#ifndef _EqHeat1D_CrankNicolsonMethod_H
#include "EqHeat1D_CrankNicolsonMethod.h"
#endif

#include "ProcessMatrix.h"

//extern bool processTerminated = false;

//---------------------------------------------------------------------------
class TFormSolver : public TForm
{
__published:	// IDE-managed Components
        TStatusBar *StatusBar1;
        TPanel *Panel1;
        TButton *btnDiscretizarP;
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
        TButton *btnAbrirArq;
        TLabel *Label10;
        TGroupBox *GroupBox6;
        TLabel *Label8;
        TEdit *EditUzero;
        TLabel *Label9;
        TEdit *EditUL;
        TGroupBox *GroupBox7;
        TEdit *EditUInter;
        TLabel *Label11;
        TCheckBox *CkBoxEstabilizaU;
        void __fastcall btnSairClick(TObject *Sender);
        void __fastcall btnDiscretizarPClick(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall btnAbrirArqClick(TObject *Sender);
        void __fastcall EditValorLKeyPress(TObject *Sender, char &Key);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall EditValorLChange(TObject *Sender);
        void __fastcall CkBoxEstabilizaUClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        //EqHeat mesh;
        bool flagEstabilizarU;
        bool flagThreadStarted;

        __fastcall TFormSolver(TComponent* Owner);
        void __fastcall ProcessMatrixDone(TObject *Sender);
        void __fastcall SolveMethodDone(TObject *Sender);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSolver *FormSolver;
//---------------------------------------------------------------------------
#endif
