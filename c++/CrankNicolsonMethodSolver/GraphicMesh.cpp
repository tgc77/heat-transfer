//--------------------------------------------------------------------------------------------------

#include <vcl.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#pragma hdrstop

#include "GraphicMesh.h"
#include "MDF_Solve.h"

//--------------------------------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "OpenGLPanel"
#pragma resource "*.dfm"
TFormGraphicMesh *FormGraphicMesh;

//--------------------------------------------------------------------------------------------------
__fastcall TFormGraphicMesh::TFormGraphicMesh(TComponent* Owner)
        : TForm(Owner)
{
      xRot = zRot = 0.0f;
      yRot = 55.0f;
      RotXv = 0.0f;
      
      xTransl = -80.0f;
      yTransl = zTransl = 0.0f;

      WindowState = wsMaximized;
}
//--------------------------------------------------------------------------------------------------

void __fastcall TFormGraphicMesh::inicializaTabela(EqHeat mesh)
{
     register int ln, k;
     AnsiString mMeshValues;

     StringGrid1->ColCount =  mesh->I;

     StringGrid1->Cells[0][0] = "u(t, Xi)";
     for(ln = 0; ln < mesh->N; ln++) {
          StringGrid1->Cells[0][ln+1] = "u(t"+IntToStr(ln)+", Xi)";
          for(k = 0; k < mesh->I; k++) {
                 mMeshValues = FormatFloat("0.000", mesh->node[ln][k].u);
                 StringGrid1->Cells[k+1][0] = "u(t, X"+IntToStr(k)+")";
                 StringGrid1->Cells[k+1][ln+1] = mMeshValues;
          }
     }
}
//--------------------------------------------------------------------------------------------------

void __fastcall TFormGraphicMesh::carregaTabela(EqHeat mesh)
{
     register int ln, k;
     AnsiString mMeshValues;

     for(ln = 0; ln < mesh->N; ln++) {
          for(k = 0; k < mesh->I; k++) {
                 mMeshValues = FormatFloat("0.000", mesh->node[ln][k].u);
                 StringGrid1->Cells[k+1][ln+1] = mMeshValues;
          }
     }
}
//--------------------------------------------------------------------------------------------------

void __fastcall TFormGraphicMesh::GerarMesh(EqHeat mesh)
{
     float raio_externo=20.0f, raio_interno=raio_externo-1;
     register p;

     glBegin(GL_LINES);
     z = 0.0f;
     for (p = 0; p < mesh->I; p++) {

             for (angle = 0.0f; angle <= (2.0*M_PI); angle +=0.1f) {

                       //--------------------------------------
                       mColor[0] = GetRValue(ColorToRGB(clAqua))/255.0f;
                       mColor[1] = GetGValue(ColorToRGB(clAqua))/255.0f;
                       mColor[2] = GetBValue(ColorToRGB(clAqua))/255.0f;
                       raio_externo = 20.0f;
                       while (raio_externo >= raio_interno) {
                                  x = raio_externo*sin(angle);
                                  y = raio_externo*cos(angle);

                                  glColor3fv(mColor);
                                  glVertex3f(x, y, z);

                                  x = raio_externo*sin(angle + M_PI);
                                  y = (raio_externo--)*cos(angle + M_PI);

                                  glColor3fv(mColor);
                                  glVertex3f(x, y, z);

                                  mColor[0] = GetRValue(ColorToRGB(clGray))/255.0f;
                                  mColor[1] = GetGValue(ColorToRGB(clGray))/255.0f;
                                  mColor[2] = GetBValue(ColorToRGB(clGray))/255.0f;
                       }
                       //--------------------------------------
                       z += (mesh->deltaX/50.0f);
             }
     }        
     glEnd();
     glPopMatrix();
}
//--------------------------------------------------------------------------------------------------

void __fastcall TFormGraphicMesh::gera_cilindro(EqHeat mesh, int mTime)
{
     //
}
//--------------------------------------------------------------------------------------------------

void __fastcall TFormGraphicMesh::define_cores(EqHeat mesh, int mTime)
{
     if (mesh->Uo >= 80.0f || mesh->UL >= 80.0f) {
             mColor[0] = GetRValue(ColorToRGB(clRed))/255.0f;
             mColor[1] = GetGValue(ColorToRGB(clRed))/255.0f;
             mColor[2] = GetBValue(ColorToRGB(clRed))/255.0f;
     }
     else
       if (mesh->Uo >= 60.0f || mesh->UL >= 60.0f) {
               mColor[0] = GetRValue(ColorToRGB(clInfoBk))/255.0f;
               mColor[1] = GetGValue(ColorToRGB(clInfoBk))/255.0f;
               mColor[2] = GetBValue(ColorToRGB(clInfoBk))/255.0f;
       }
       else
         if (mesh->Uo >= 40.0f || mesh->UL >= 40.0f) {
                 mColor[0] = GetRValue(ColorToRGB(clBlue))/255.0f;
                 mColor[1] = GetGValue(ColorToRGB(clBlue))/255.0f;
                 mColor[2] = GetBValue(ColorToRGB(clBlue))/255.0f;
         }
         else
           if (mesh->Uo >= 10.0f || mesh->UL >= 10.0f) {
                   mColor[0] = GetRValue(ColorToRGB(clSkyBlue))/255.0f;
                   mColor[1] = GetGValue(ColorToRGB(clSkyBlue))/255.0f;
                   mColor[2] = GetBValue(ColorToRGB(clSkyBlue))/255.0f;
           }
           else {
               mColor[0] = GetRValue(ColorToRGB(clAqua))/255.0f;
               mColor[1] = GetGValue(ColorToRGB(clAqua))/255.0f;
               mColor[2] = GetBValue(ColorToRGB(clAqua))/255.0f;
           }
}
//--------------------------------------------------------------------------------------------------

void __fastcall TFormGraphicMesh::Button2Click(TObject *Sender)
{
     Close();
}
//--------------------------------------------------------------------------------------------------

void __fastcall TFormGraphicMesh::FormShow(TObject *Sender)
{
     Timer1->Interval = (mesh->deltaT * 1000);
}
//--------------------------------------------------------------------------------------------------

void __fastcall TFormGraphicMesh::iniciarSimulation(EqHeat mesh, int mTime)
{
     float raio_externo=20.0f, raio_interno=raio_externo-2;
     register int k;

     glBegin(GL_LINES);
     z = 0.0f;
     for (k = 0; k < mesh->I; k++) {

              for (angle = 0.0f; angle <= (2.0*M_PI); angle +=0.1f) {

                       if (mesh->node[mTime][k].u >= 0.0f && mesh->node[mTime][k].u <= 10.0f) {
                                     mColor[0] = GetRValue(ColorToRGB(clAqua))/255.0f;
                                     mColor[1] = GetGValue(ColorToRGB(clAqua))/255.0f;
                                     mColor[2] = GetBValue(ColorToRGB(clAqua))/255.0f;
                       }
                       else
                         if (mesh->node[mTime][k].u > 10.0f && mesh->node[mTime][k].u <= 20.0f) {
                                 mColor[0] = GetRValue(ColorToRGB(clSkyBlue))/255.0f;
                                 mColor[1] = GetGValue(ColorToRGB(clSkyBlue))/255.0f;
                                 mColor[2] = GetBValue(ColorToRGB(clSkyBlue))/255.0f;
                         }
                         else
                           if (mesh->node[mTime][k].u > 20.0f && mesh->node[mTime][k].u <= 30.0f) {
                                   mColor[0] = GetRValue(ColorToRGB(clBlue))/255.0f;
                                   mColor[1] = GetGValue(ColorToRGB(clBlue))/255.0f;
                                   mColor[2] = GetBValue(ColorToRGB(clBlue))/255.0f;
                           }
                           else
                             if (mesh->node[mTime][k].u > 30.0f && mesh->node[mTime][k].u <= 50.0f) {
                                     mColor[0] = GetRValue(ColorToRGB(clInfoBk))/255.0f;
                                     mColor[1] = GetGValue(ColorToRGB(clInfoBk))/255.0f;
                                     mColor[2] = GetBValue(ColorToRGB(clInfoBk))/255.0f;
                             }
                             else
                               if (mesh->node[mTime][k].u > 50.0f && mesh->node[mTime][k].u <= 100.0f) {
                                       mColor[0] = GetRValue(ColorToRGB(clRed))/255.0f;
                                       mColor[1] = GetGValue(ColorToRGB(clRed))/255.0f;
                                       mColor[2] = GetBValue(ColorToRGB(clRed))/255.0f;
                               }

                       //--------------------------------------
                       raio_externo = 20.0f;
                       while (raio_externo >= raio_interno) {
                                  x = raio_externo*sin(angle);
                                  y = raio_externo*cos(angle);
                                  glColor3fv(mColor);
                                  glVertex3f(x, y, z);

                                  x = raio_externo*sin(angle + M_PI);
                                  y = (raio_externo--)*cos(angle + M_PI);
                                  glColor3fv(mColor);
                                  glVertex3f(x, y, z);
                       }
                       //--------------------------------------
                       z += (mesh->deltaX/50.0f);
              }
     }
     glEnd();
     glPopMatrix();
}
//--------------------------------------------------------------------------------------------------

void __fastcall TFormGraphicMesh::btnIniciaSimulationClick(TObject *Sender)
{
     if (btnIniciaSimulation->Caption == "Iniciar simulação") {
          btnIniciaSimulation->Caption = "Parar simulação";
          Timer1->Enabled = true;
          iniciarSimulation(mesh, mTime);
          mStartSimulation = true;
     }
     else {
         btnIniciaSimulation->Caption = "Iniciar simulação";
         mStartSimulation = false;
         Timer1->Enabled = false;
     }
}
//--------------------------------------------------------------------------------------------------

void __fastcall TFormGraphicMesh::Timer1Timer(TObject *Sender)
{
     if (CkBoxRotX->Checked)
           xRot += 5.0f;

     if (CkBoxRotY->Checked)
           yRot += 5.0f;

     if (CkBoxRotZ->Checked)
           zRot += 5.0f;

     if (!CheckBoxRotManual->Checked) {
             RotX->Position = (int)xRot;
             RotY->Position = (int)yRot;
             RotZ->Position = (int)zRot;
     }

     if (xRot > 360.0f)
           xRot = 0.0f;

     if (yRot > 360.0f)
           yRot = 0.0f;

     if (zRot > 360.0f)
           zRot = 0.0f;
     
     time_animate += Timer1->Interval;
     EditTempo->Text = FloatToStr((float)time_animate/1000.0);
     EditTempo->Refresh();

     OpenGLPanel1->Repaint();
}
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------

void __fastcall TFormGraphicMesh::OpenGLPanel1Paint(TObject *Sender)
{

     glClearColor (0.0f, 0.0f, 0.0f, 1.0f);
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

     glPushMatrix();
     glTranslatef(xTransl, yTransl, zTransl);
     glRotatef(xRot, 1.0f, 0.0f, 0.0f);
     glRotatef(yRot, 0.0f, 1.0f, 0.0f);
     glRotatef(zRot, 0.0f, 0.0f, 1.0f);

     if (mStartSimulation) {
            iniciarSimulation(mesh, mTime);

            if (mTime < mesh->N)
                   mTime++;
            else {
               mTime = 0;
               time_animate = 0.0f;
            }
     } else
         GerarMesh(mesh);
          
     glPopMatrix();
}
//--------------------------------------------------------------------------------------------------

void __fastcall TFormGraphicMesh::openGLDisplay()
{
       /*
       glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
       glEnable(GL_TEXTURE_2D);
       glEnable(GL_LIGHTING);

       //-- sombreamento leve
       glShadeModel(GL_SMOOTH);

       //-- Antialiasing
       glEnable(GL_LINE_SMOOTH);
       glEnable(GL_BLEND);
       //-------------------

       //---- cores do cilíndro ----------------
       glEnable(GL_COLOR_MATERIAL);
       glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

       //----------------------------------------

       //------------------- verde e amarelo --------------------------
       //GLfloat Diffuse[] = {0.5f, 0.8f, 0.5f, 1.0f};
       //GLfloat Specular[]= {1.0f, 0.5f, 0.0f, 1.0f};
       //--------------------------------------------------------------

       GLfloat Diffuse[] = {0.0f, 0.5f, 0.5f, 0.0f};
       GLfloat Specular[]= {0.5f, 0.5f, 1.0f, 0.0f};

       GLfloat  Ambient = 0.5f;//GetRValue(ColorToRGB(clRed))/255.0f;
       glLightfv( GL_LIGHT0, GL_AMBIENT, &Ambient);
       glLightfv( GL_LIGHT0, GL_DIFFUSE, Diffuse);
       glLightfv( GL_LIGHT0, GL_SPECULAR, Specular);
       glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 1.0);

       glEnable(GL_LIGHT0);
       */
       //--------------------------------------------------------------
}
//--------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------

void __fastcall TFormGraphicMesh::OpenGLPanel1MouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
     GLfloat mParams;

     glGetFloatv(GL_AUTO_NORMAL, &mParams);

     Edit1->Text = FloatToStr(mParams);

     EditOpenGLPainelX->Text = IntToStr(X);
     EditOpenGLPainelY->Text = IntToStr(Y);
}
//---------------------------------------------------------------------------

void __fastcall TFormGraphicMesh::OpenGLPanel1Init(TObject *Sender)
{
     //
}
//---------------------------------------------------------------------------

void __fastcall TFormGraphicMesh::CheckBoxAnimatedClick(TObject *Sender)
{
     if (CheckBoxAnimated->Checked) {
           Timer1->Enabled = true;
           //PanelRot->Enabled = false;
     }
     else {
            Timer1->Enabled = false;
            //PanelRot->Enabled = true;
            //EditRotXv->Text = FloatToStr(RotXv);
            //time_animate = 0;
     }
}
//---------------------------------------------------------------------------

void __fastcall TFormGraphicMesh::RotXChange(TObject *Sender)
{
     //if (mEnterRotX == true) {
            xRot = (float)RotX->Position;
            EditPosX->Text = IntToStr(RotX->Position);
            OpenGLPanel1->Repaint();
            EditPosX->Refresh();
     //}
}
//---------------------------------------------------------------------------

void __fastcall TFormGraphicMesh::RotYChange(TObject *Sender)
{

     yRot = (float)RotY->Position;
     EditPosY->Text = IntToStr(RotY->Position);
     OpenGLPanel1->Repaint();
     EditPosY->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TFormGraphicMesh::RotZChange(TObject *Sender)
{
     zRot = (float)RotZ->Position;
     EditPosZ->Text = IntToStr(RotZ->Position);
     OpenGLPanel1->Repaint();
     EditPosZ->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TFormGraphicMesh::btnZeraRotXvClick(TObject *Sender)
{
     //EditRotXv->Text = FloatToStr(RotXv);
}
//---------------------------------------------------------------------------

void __fastcall TFormGraphicMesh::OpenGLPanel1Resize(TObject *Sender)
{
    GLsizei w, h;
    GLfloat mRange = 100.0f;


    w = OpenGLPanel1->Width;
    h = OpenGLPanel1->Height;

    if (h == 0)
         h = 1;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (w >= h) {
        glOrtho(-mRange, mRange, -mRange*h/w, mRange*h/w, -mRange, mRange);

        TrackBarTransX->Min = -mRange;
        TrackBarTransX->Max = mRange;

        TrackBarTransY->Min = -mRange*h/w;
        TrackBarTransY->Max = mRange*h/w;
    }
    else {
        glOrtho(-mRange*w/h, mRange*w/h, -mRange, mRange, -mRange, mRange);

        TrackBarTransX->Min = -mRange*w/h;
        TrackBarTransX->Max = mRange*w/h;

        TrackBarTransY->Min = -mRange;
        TrackBarTransY->Max = mRange;
    }
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
//---------------------------------------------------------------------------

void __fastcall TFormGraphicMesh::RotXEnter(TObject *Sender)
{
     mEnterRotX = true;        
}
//---------------------------------------------------------------------------

void __fastcall TFormGraphicMesh::RotYEnter(TObject *Sender)
{
     mEnterRotY = true;
}
//---------------------------------------------------------------------------

void __fastcall TFormGraphicMesh::RotZEnter(TObject *Sender)
{
     mEnterRotZ = true;
}
//---------------------------------------------------------------------------


void __fastcall TFormGraphicMesh::TrackBarTransXChange(TObject *Sender)
{
     xTransl = (float)TrackBarTransX->Position;
     EditPosTransX->Text = IntToStr(TrackBarTransX->Position);
     OpenGLPanel1->Repaint();
     EditPosTransX->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TFormGraphicMesh::TrackBarTransYChange(TObject *Sender)
{
     yTransl = (float)TrackBarTransY->Position;
     EditPosTransY->Text = IntToStr(TrackBarTransY->Position);
     OpenGLPanel1->Repaint();
     EditPosTransY->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TFormGraphicMesh::TrackBarTransZChange(TObject *Sender)
{
     zTransl = (float)TrackBarTransZ->Position;
     EditPosTransZ->Text = IntToStr(TrackBarTransZ->Position);
     OpenGLPanel1->Repaint();
     EditPosTransZ->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TFormGraphicMesh::TimerMeshTTimer(TObject *Sender)
{
     //GerarMesh(FormSolver->mesh, mTime);
     //mTime++;
}
//---------------------------------------------------------------------------

void __fastcall TFormGraphicMesh::FormResize(TObject *Sender)
{
     if (ScrollBox1->Height < (GroupBoxTempoAnimate->Top + GroupBoxTempoAnimate->Height))
           PanelRot->Width += 14;
     else
         PanelRot->Width -= 14;
}
//---------------------------------------------------------------------------

