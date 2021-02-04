object FormSolver: TFormSolver
  Left = 233
  Top = 113
  BorderStyle = bsSingle
  Caption = 'Solve Equation Heat Condution - Implicit Method'
  ClientHeight = 324
  ClientWidth = 552
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object StatusBar1: TStatusBar
    Left = 0
    Top = 304
    Width = 552
    Height = 20
    Panels = <>
    SimplePanel = False
  end
  object Panel1: TPanel
    Left = 0
    Top = 263
    Width = 552
    Height = 41
    Align = alBottom
    TabOrder = 1
    object btnPlotGraphic: TButton
      Left = 65
      Top = 9
      Width = 89
      Height = 25
      Caption = 'Plotar gr'#225'fico'
      Enabled = False
      TabOrder = 0
      OnClick = btnPlotGraphicClick
    end
    object btnSair: TButton
      Left = 426
      Top = 9
      Width = 75
      Height = 25
      Caption = 'Sair'
      TabOrder = 1
      OnClick = btnSairClick
    end
    object btnAbrirArq: TButton
      Left = 216
      Top = 9
      Width = 97
      Height = 25
      Caption = 'Abrir arquivo'
      Enabled = False
      TabOrder = 2
      OnClick = btnAbrirArqClick
    end
  end
  object GroupBox1: TGroupBox
    Left = 0
    Top = -1
    Width = 552
    Height = 258
    Caption = 'Dados de entrada:'
    TabOrder = 2
    object GroupBox2: TGroupBox
      Left = 11
      Top = 21
      Width = 532
      Height = 48
      Caption = 'Par'#226'metros para c'#225'lculo de deltaX :'
      TabOrder = 0
      object Label1: TLabel
        Left = 13
        Top = 25
        Width = 124
        Height = 13
        Caption = 'Comprimento da barra (L) :'
      end
      object Label2: TLabel
        Left = 248
        Top = 23
        Width = 185
        Height = 13
        Caption = 'N'#250'mero de pontos de discretiza'#231#227'o (I) :'
      end
      object EditValorL: TEdit
        Left = 143
        Top = 18
        Width = 80
        Height = 21
        TabOrder = 0
        Text = '10'
        OnChange = EditValorLChange
        OnKeyPress = EditValorLKeyPress
      end
      object EditValorI: TEdit
        Left = 439
        Top = 16
        Width = 80
        Height = 21
        TabOrder = 1
        Text = '6'
        OnChange = EditValorLChange
        OnKeyPress = EditValorLKeyPress
      end
    end
    object GroupBox3: TGroupBox
      Left = 11
      Top = 77
      Width = 532
      Height = 49
      Caption = 'Par'#226'metros de discretiza'#231#227'o do tempo :'
      TabOrder = 1
      object Label3: TLabel
        Left = 16
        Top = 23
        Width = 78
        Height = 13
        Caption = 'Valor de deltaT :'
      end
      object Label4: TLabel
        Left = 204
        Top = 22
        Width = 112
        Height = 13
        Caption = 'Incrementos de deltaT :'
      end
      object EditValorDeltaT: TEdit
        Left = 100
        Top = 17
        Width = 80
        Height = 21
        TabOrder = 0
        Text = '0,1'
        OnChange = EditValorLChange
        OnKeyPress = EditValorLKeyPress
      end
      object EditIncrementoDeltaT: TEdit
        Left = 321
        Top = 17
        Width = 67
        Height = 21
        TabOrder = 1
        Text = '150'
        OnChange = EditValorLChange
        OnKeyPress = EditValorLKeyPress
      end
    end
    object GroupBox4: TGroupBox
      Left = 11
      Top = 135
      Width = 532
      Height = 49
      Caption = 'Par'#226'metros para c'#225'lculo de alfa :'
      TabOrder = 2
      object Label5: TLabel
        Left = 15
        Top = 25
        Width = 54
        Height = 13
        Caption = 'Valor de k :'
      end
      object Label6: TLabel
        Left = 177
        Top = 25
        Width = 54
        Height = 13
        Caption = 'Valor de c :'
      end
      object Label7: TLabel
        Left = 341
        Top = 25
        Width = 63
        Height = 13
        Caption = 'Valor de rho :'
      end
      object EditValorK: TEdit
        Left = 75
        Top = 18
        Width = 80
        Height = 21
        TabOrder = 0
        Text = '0,49'
        OnChange = EditValorLChange
        OnKeyPress = EditValorLKeyPress
      end
      object EditValorC: TEdit
        Left = 237
        Top = 18
        Width = 80
        Height = 21
        TabOrder = 1
        Text = '0,2174'
        OnChange = EditValorLChange
        OnKeyPress = EditValorLKeyPress
      end
      object EditValorRho: TEdit
        Left = 409
        Top = 18
        Width = 80
        Height = 21
        TabOrder = 2
        Text = '2,7'
        OnChange = EditValorLChange
        OnKeyPress = EditValorLKeyPress
      end
    end
    object GroupBox5: TGroupBox
      Left = 11
      Top = 195
      Width = 532
      Height = 50
      Caption = 'Condi'#231#245'es de contorno u( t, x ) , com t >= 0 :'
      TabOrder = 3
      object Label8: TLabel
        Left = 16
        Top = 24
        Width = 39
        Height = 13
        Caption = 'u( t, 0 ) :'
      end
      object Label9: TLabel
        Left = 174
        Top = 24
        Width = 39
        Height = 13
        Caption = 'u( t, L ) :'
      end
      object EditUzero: TEdit
        Left = 61
        Top = 18
        Width = 80
        Height = 21
        TabOrder = 0
        Text = '100'
        OnChange = EditValorLChange
        OnKeyPress = EditValorLKeyPress
      end
      object EditUL: TEdit
        Left = 222
        Top = 18
        Width = 80
        Height = 21
        TabOrder = 1
        Text = '50'
        OnChange = EditValorLChange
        OnKeyPress = EditValorLKeyPress
      end
    end
  end
end
