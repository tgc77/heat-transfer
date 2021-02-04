//---------------------------------------------------------------------------

#ifndef PlotadorH
#define PlotadorH
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

#ifndef _EqHeat1DImplicitMethod_H
#include "EqHeat1DImplicitMethod.h"
#endif

//---------------------------------------------------------------------------
class TFormPlotGraphic : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TButton *Button1;
        TButton *Button2;
        TButton *Button3;
        TChart *Chart1;
        TPointSeries *Series1;
        TPointSeries *Series2;
        TPointSeries *Series3;
        TPointSeries *Series4;
        TPointSeries *Series5;
        TPointSeries *Series6;
        TPanel *Panel2;
        TStringGrid *StringGrid1;
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
        //double **mMesh;
        //int lin, col;
        //bool mStopSimulation;

        __fastcall TFormPlotGraphic(TComponent* Owner);

        void __fastcall PlotarMesh(EqHeat mesh);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormPlotGraphic *FormPlotGraphic;
//---------------------------------------------------------------------------
#endif
