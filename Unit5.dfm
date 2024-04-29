object frmBoolean: TfrmBoolean
  Left = 0
  Top = 0
  Caption = 'Boolean Algebra'
  ClientHeight = 231
  ClientWidth = 505
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clBlue
  Font.Height = -43
  Font.Name = 'Source Code Pro Light'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 54
  object sbtOperand1: TSpeedButton
    Left = 16
    Top = 86
    Width = 81
    Height = 40
    AllowAllUp = True
    GroupIndex = 12
    Caption = 'False'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -13
    Font.Name = 'Source Code Pro'
    Font.Style = []
    ParentFont = False
    OnClick = sbtOperand1Click
  end
  object sbtOperand2: TSpeedButton
    Left = 103
    Top = 86
    Width = 81
    Height = 40
    AllowAllUp = True
    GroupIndex = 14
    Caption = 'False'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -13
    Font.Name = 'Source Code Pro Light'
    Font.Style = []
    ParentFont = False
    OnClick = sbtOperand2Click
  end
  object sbtResult: TSpeedButton
    Left = 240
    Top = 88
    Width = 134
    Height = 40
    AllowAllUp = True
    GroupIndex = 16
    Caption = 'False'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -13
    Font.Name = 'Source Code Pro Light'
    Font.Style = []
    ParentFont = False
    OnClick = sbtResultClick
  end
  object sttOperand1: TStaticText
    Left = 40
    Top = 24
    Width = 30
    Height = 56
    Caption = 'A'
    Color = clBlue
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlue
    Font.Height = -43
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentColor = False
    ParentFont = False
    TabOrder = 0
  end
  object sttOperand2: TStaticText
    Left = 120
    Top = 24
    Width = 30
    Height = 58
    Caption = 'B'
    TabOrder = 1
  end
  object sttOperation: TStaticText
    Left = 240
    Top = 24
    Width = 134
    Height = 58
    Caption = 'A ^ B'
    TabOrder = 2
  end
  object btnCheck: TButton
    Left = 380
    Top = 86
    Width = 117
    Height = 40
    Caption = 'Check'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -27
    Font.Name = 'Source Code Pro Light'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
    OnClick = btnCheckClick
  end
  object btnNewOperation: TButton
    Left = 22
    Top = 166
    Width = 352
    Height = 40
    Caption = 'New Operation'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -37
    Font.Name = 'Source Code Pro Light'
    Font.Style = []
    ParentFont = False
    TabOrder = 4
    OnClick = btnNewOperationClick
  end
  object btnClose: TButton
    Left = 380
    Top = 166
    Width = 117
    Height = 40
    Caption = 'Close'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -13
    Font.Name = 'Source Code Pro Light'
    Font.Style = []
    ParentFont = False
    TabOrder = 5
    OnClick = btnCloseClick
  end
end
