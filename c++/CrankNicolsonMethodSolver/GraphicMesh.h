//---------------------------------------------------------------------------

#ifndef GraphicMesh_H
#define GraphicMesh_H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Chart.hpp>
#include <ExtCtrls.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <Series.hpp>
#include <Grids.hpp>

#include <time.h>
#include <ComCtrls.hpp>
#include "OpenGLPanel.h"

#ifndef _EqHeat1D_CrankNicolsonMethod_H
#include "EqHeat1D_CrankNicolsonMethod.h"
#endif

//---------------------------------------------------------------------------
class TFormGraphicMesh : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TButton *Button2;
        TButton *btnIniciaSimulation;
        TPanel *Panel2;
        TStringGrid *StringGrid1;
        TOpenGLPanel *OpenGLPanel1;
        TGroupBox *GroupBox1;
        TEdit *EditOpenGLPainelX;
        TLabel *Label3;
        TLabel *Label4;
        TEdit *EditOpenGLPainelY;
        TEdit *Edit1;
        TTimer *Timer1;
        TTimer *TimerMeshT;
        TPanel *PanelRot;
        TScrollBox *ScrollBox1;
        TGroupBox *GroupBoxTempoAnimate;
        TGroupBox *GroupBox3;
        TStaticText *StaticText4;
        TTrackBar *TrackBarTransZ;
        TEdit *EditPosTransZ;
        TStaticText *StaticText5;
        TTrackBar *TrackBarTransY;
        TEdit *EditPosTransY;
        TStaticText *StaticText6;
        TTrackBar *TrackBarTransX;
        TEdit *EditPosTransX;
        TCheckBox *CheckBox2;
        TStaticText *StaticText8;
        TGroupBox *GroupBox2;
        TStaticText *StaticText3;
        TTrackBar *RotZ;
        TEdit *EditPosZ;
        TStaticText *StaticText2;
        TTrackBar *RotY;
        TEdit *EditPosY;
        TStaticText *StaticText1;
        TTrackBar *RotX;
        TEdit *EditPosX;
        TCheckBox *CheckBoxRotManual;
        TGroupBox *GroupBox4;
        TCheckBox *CkBoxRotX;
        TCheckBox *CkBoxRotY;
        TCheckBox *CkBoxRotZ;
        TStaticText *StaticText7;
        TCheckBox *CheckBoxAnimated;
        TGroupBox *GroupBox5;
        TLabel *Label1;
        TEdit *EditTempo;
        TLabel *Label2;
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall btnIniciaSimulationClick(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall OpenGLPanel1Paint(TObject *Sender);
        void __fastcall OpenGLPanel1MouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall OpenGLPanel1Init(TObject *Sender);
        void __fastcall CheckBoxAnimatedClick(TObject *Sender);
        void __fastcall RotXChange(TObject *Sender);
        void __fastcall RotYChange(TObject *Sender);
        void __fastcall RotZChange(TObject *Sender);
        void __fastcall btnZeraRotXvClick(TObject *Sender);
        void __fastcall OpenGLPanel1Resize(TObject *Sender);
        void __fastcall RotXEnter(TObject *Sender);
        void __fastcall RotYEnter(TObject *Sender);
        void __fastcall RotZEnter(TObject *Sender);
        void __fastcall TrackBarTransXChange(TObject *Sender);
        void __fastcall TrackBarTransYChange(TObject *Sender);
        void __fastcall TrackBarTransZChange(TObject *Sender);
        void __fastcall TimerMeshTTimer(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
private:	// User declarations

        bool mStartSimulation;
        bool mBreakProcess;
        time_t  start, end, count;
        struct tm *local_t;
        float diff;
        GLfloat mColor[3];
        GLfloat RotXv, RotYv;
        GLfloat xRot, yRot, zRot;
        GLfloat xTransl, yTransl, zTransl;
        int time_animate, mTime;

        GLfloat x, y, z;
        GLfloat angle;
        
        bool mEnterRotX;
        bool mEnterRotY;
        bool mEnterRotZ;

public:		// User declarations

        __fastcall TFormGraphicMesh(TComponent* Owner);

        void __fastcall GerarMesh(EqHeat mesh);
        void __fastcall gera_cilindro(EqHeat mesh, int mTime);
        void __fastcall iniciarSimulation(EqHeat mesh, int mTime);
        void __fastcall openGLDisplay();
        void __fastcall changeSize(int peWidth, int peHeight);
        void __fastcall inicializaTabela(EqHeat mesh);
        void __fastcall carregaTabela(EqHeat mesh);
        void __fastcall define_cores(EqHeat mesh, int mTime);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormGraphicMesh *FormGraphicMesh;
//---------------------------------------------------------------------------
#endif
