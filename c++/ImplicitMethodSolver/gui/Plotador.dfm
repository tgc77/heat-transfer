object FormPlotGraphic: TFormPlotGraphic
  Left = 9
  Top = 103
  Width = 957
  Height = 648
  Caption = 'Points calculed of the mesh ploted'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 573
    Width = 949
    Height = 41
    Align = alBottom
    TabOrder = 0
    object Button1: TButton
      Left = 104
      Top = 8
      Width = 89
      Height = 25
      Caption = 'Plotar gr'#225'fico'
      TabOrder = 0
    end
    object Button2: TButton
      Left = 752
      Top = 8
      Width = 75
      Height = 25
      Caption = 'Sair'
      TabOrder = 1
      OnClick = Button2Click
    end
    object Button3: TButton
      Left = 400
      Top = 9
      Width = 129
      Height = 25
      Caption = 'Parar simula'#231#227'o'
      TabOrder = 2
    end
  end
  object Chart1: TChart
    Left = 0
    Top = 156
    Width = 949
    Height = 417
    BackWall.Brush.Color = clWhite
    BackWall.Brush.Style = bsClear
    LeftWall.Brush.Color = clWhite
    Title.Text.Strings = (
      'TChart')
    BottomAxis.AxisValuesFormat = '0.00'
    BottomAxis.ExactDateTime = False
    BottomAxis.Increment = 0.1
    BottomAxis.LabelsSeparation = 2
    BottomAxis.LabelStyle = talValue
    BottomAxis.MinorTickLength = 3
    BottomAxis.RoundFirstLabel = False
    BottomAxis.TickInnerLength = 4
    BottomAxis.TickLength = 0
    DepthAxis.Automatic = False
    DepthAxis.AutomaticMaximum = False
    DepthAxis.AutomaticMinimum = False
    DepthAxis.Maximum = 5.5
    DepthAxis.Minimum = -0.5
    LeftAxis.AxisValuesFormat = '0.00###'
    LeftAxis.ExactDateTime = False
    LeftAxis.Increment = 0.1
    LeftAxis.LabelStyle = talValue
    LeftAxis.MinorTickLength = 3
    LeftAxis.RoundFirstLabel = False
    MaxPointsPerPage = 100
    RightAxis.AxisValuesFormat = '0.00###'
    RightAxis.LabelStyle = talValue
    RightAxis.RoundFirstLabel = False
    TopAxis.Automatic = False
    TopAxis.AutomaticMaximum = False
    TopAxis.AutomaticMinimum = False
    TopAxis.LabelsSeparation = 0
    Align = alClient
    TabOrder = 1
    object Series1: TPointSeries
      Marks.ArrowLength = 0
      Marks.Style = smsValue
      Marks.Visible = False
      SeriesColor = clRed
      Title = 'Xo'
      ValueFormat = '0.000'
      VertAxis = aBothVertAxis
      Pointer.HorizSize = 3
      Pointer.InflateMargins = True
      Pointer.Style = psDiamond
      Pointer.VertSize = 3
      Pointer.Visible = True
      XValues.DateTime = False
      XValues.Name = 'X'
      XValues.Multiplier = 1
      XValues.Order = loAscending
      YValues.DateTime = False
      YValues.Name = 'Y'
      YValues.Multiplier = 1
      YValues.Order = loNone
    end
    object Series2: TPointSeries
      Marks.ArrowLength = 0
      Marks.Visible = False
      SeriesColor = clRed
      Title = 'X1'
      VertAxis = aBothVertAxis
      Pointer.Brush.Color = 16777088
      Pointer.HorizSize = 3
      Pointer.InflateMargins = True
      Pointer.Style = psDiamond
      Pointer.VertSize = 3
      Pointer.Visible = True
      XValues.DateTime = False
      XValues.Name = 'X'
      XValues.Multiplier = 1
      XValues.Order = loAscending
      YValues.DateTime = False
      YValues.Name = 'Y'
      YValues.Multiplier = 1
      YValues.Order = loNone
    end
    object Series3: TPointSeries
      Marks.ArrowLength = 0
      Marks.Visible = False
      SeriesColor = clRed
      Title = 'X2'
      VertAxis = aBothVertAxis
      Pointer.Brush.Color = 65408
      Pointer.HorizSize = 3
      Pointer.InflateMargins = True
      Pointer.Style = psDiamond
      Pointer.VertSize = 3
      Pointer.Visible = True
      XValues.DateTime = False
      XValues.Name = 'X'
      XValues.Multiplier = 1
      XValues.Order = loAscending
      YValues.DateTime = False
      YValues.Name = 'Y'
      YValues.Multiplier = 1
      YValues.Order = loNone
    end
    object Series4: TPointSeries
      Marks.ArrowLength = 0
      Marks.Visible = False
      SeriesColor = clRed
      Title = 'X3'
      VertAxis = aBothVertAxis
      Pointer.Brush.Color = 4227327
      Pointer.HorizSize = 3
      Pointer.InflateMargins = True
      Pointer.Style = psDiamond
      Pointer.VertSize = 3
      Pointer.Visible = True
      XValues.DateTime = False
      XValues.Name = 'X'
      XValues.Multiplier = 1
      XValues.Order = loAscending
      YValues.DateTime = False
      YValues.Name = 'Y'
      YValues.Multiplier = 1
      YValues.Order = loNone
    end
    object Series5: TPointSeries
      Marks.ArrowLength = 0
      Marks.Visible = False
      SeriesColor = clRed
      Title = 'X4'
      VertAxis = aBothVertAxis
      Pointer.Brush.Color = clTeal
      Pointer.HorizSize = 3
      Pointer.InflateMargins = True
      Pointer.Style = psDiamond
      Pointer.VertSize = 3
      Pointer.Visible = True
      XValues.DateTime = False
      XValues.Name = 'X'
      XValues.Multiplier = 1
      XValues.Order = loAscending
      YValues.DateTime = False
      YValues.Name = 'Y'
      YValues.Multiplier = 1
      YValues.Order = loNone
    end
    object Series6: TPointSeries
      Marks.ArrowLength = 0
      Marks.Visible = False
      SeriesColor = clRed
      Title = 'X5'
      VertAxis = aBothVertAxis
      Pointer.Brush.Color = clBlue
      Pointer.HorizSize = 3
      Pointer.InflateMargins = True
      Pointer.Style = psDiamond
      Pointer.VertSize = 3
      Pointer.Visible = True
      XValues.DateTime = False
      XValues.Name = 'X'
      XValues.Multiplier = 1
      XValues.Order = loAscending
      YValues.DateTime = False
      YValues.Name = 'Y'
      YValues.Multiplier = 1
      YValues.Order = loNone
    end
  end
  object Panel2: TPanel
    Left = 0
    Top = 0
    Width = 949
    Height = 156
    Align = alTop
    TabOrder = 2
    object StringGrid1: TStringGrid
      Left = 1
      Top = 1
      Width = 947
      Height = 145
      Align = alTop
      ColCount = 6
      DefaultColWidth = 153
      FixedCols = 0
      RowCount = 100
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goRowSizing, goColSizing, goTabs]
      ParentFont = False
      TabOrder = 0
    end
  end
end