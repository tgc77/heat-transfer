//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ProcessMatrix.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall TProcessMatrix::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall TProcessMatrix::TProcessMatrix()
        : TThread(false)
{
      Priority = tpNormal;
      FreeOnTerminate = true;
}
//---------------------------------------------------------------------------
void TProcessMatrix::SetName()
{
        THREADNAME_INFO info;
        info.dwType = 0x1000;
        info.szName = "ProcessMatrix";
        info.dwThreadID = -1;
        info.dwFlags = 0;

        __try
        {
             RaiseException( 0x406D1388, 0, sizeof(info)/sizeof(DWORD),(DWORD*)&info );
        }
        __except (EXCEPTION_CONTINUE_EXECUTION)
        {
        }
}
//---------------------------------------------------------------------------
void __fastcall TProcessMatrix::Execute()
{
        SetName();
        iniciarConditionContorno(mesh);
        //processTerminated = true;
}
//---------------------------------------------------------------------------
//***************************************************************************
//---------------------------------------------------------------------------
__fastcall TSolveMethod::TSolveMethod()
        : TThread(false)
{
      Priority = tpNormal;
      FreeOnTerminate = true;
}
//---------------------------------------------------------------------------
void TSolveMethod::SetName()
{
        THREADNAME_INFO info;
        info.dwType = 0x1000;
        info.szName = "SolveMethod";
        info.dwThreadID = -1;
        info.dwFlags = 0;

        __try
        {
             RaiseException( 0x406D1388, 0, sizeof(info)/sizeof(DWORD),(DWORD*)&info );
        }
        __except (EXCEPTION_CONTINUE_EXECUTION)
        {
        }
}
//---------------------------------------------------------------------------
void __fastcall TSolveMethod::Execute()
{
        SetName();
        solveEqHeat_CrankNicolsonMethod(mesh);
}
//---------------------------------------------------------------------------
