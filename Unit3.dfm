object Form3: TForm3
  Left = 0
  Top = 0
  Caption = 'Form3'
  ClientHeight = 488
  ClientWidth = 505
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object lblOperand1: TLabel
    Left = 189
    Top = 248
    Width = 12
    Height = 13
    Alignment = taRightJustify
    Caption = '00'
    Color = clBlue
    ParentColor = False
  end
  object lblOperand2: TLabel
    Left = 189
    Top = 280
    Width = 12
    Height = 13
    Alignment = taRightJustify
    Caption = '00'
    Color = clBlue
    ParentColor = False
  end
  object lblOperation: TLabel
    Left = 101
    Top = 263
    Width = 8
    Height = 13
    Alignment = taCenter
    Caption = '+'
    Color = clBlue
    ParentColor = False
  end
  object Label1: TLabel
    Left = 101
    Top = 312
    Width = 108
    Height = 13
    Caption = '---------------------------'
  end
  object pnlLevel: TPanel
    Left = 8
    Top = 8
    Width = 225
    Height = 185
    TabOrder = 0
    object btnLevel1: TSpeedButton
      Left = 15
      Top = 24
      Width = 193
      Height = 32
      Caption = 'Level 1'
      OnClick = btnLevel1Click
    end
    object btnLevel2: TSpeedButton
      Left = 15
      Top = 62
      Width = 193
      Height = 29
      Caption = 'Level 2'
      OnClick = btnLevel2Click
    end
    object btnLevel3: TSpeedButton
      Left = 15
      Top = 97
      Width = 193
      Height = 28
      Caption = 'Level 3'
      OnClick = btnLevel3Click
    end
    object btnLevel4: TSpeedButton
      Left = 15
      Top = 131
      Width = 193
      Height = 28
      Caption = 'Level 4'
      OnClick = btnLevel4Click
    end
  end
  object pnlOperation: TPanel
    Left = 271
    Top = 8
    Width = 226
    Height = 185
    TabOrder = 1
    object btnAddition: TSpeedButton
      Left = 13
      Top = 17
      Width = 193
      Height = 31
      Caption = 'Addition'
      OnClick = btnAdditionClick
    end
    object btnSubtraction: TSpeedButton
      Left = 15
      Top = 54
      Width = 193
      Height = 31
      Caption = 'Subtraction'
      OnClick = btnSubtractionClick
    end
    object btnMultiplication: TSpeedButton
      Left = 16
      Top = 91
      Width = 193
      Height = 31
      Caption = 'Multiplication'
      OnClick = btnMultiplicationClick
    end
    object btnDivision: TSpeedButton
      Left = 16
      Top = 126
      Width = 193
      Height = 31
      Caption = 'Division'
      OnClick = btnDivisionClick
    end
  end
  object edtResult: TEdit
    Left = 101
    Top = 331
    Width = 115
    Height = 84
    Alignment = taRightJustify
    Color = clMaroon
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clAqua
    Font.Height = -63
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    Text = '000'
  end
  object btnClose: TButton
    Left = 296
    Top = 331
    Width = 145
    Height = 30
    Caption = 'Close'
    TabOrder = 3
    OnClick = btnCloseClick
  end
  object btnCheckResult: TButton
    Left = 296
    Top = 379
    Width = 145
    Height = 30
    Caption = 'Check Result'
    TabOrder = 4
    OnClick = btnCheckResultClick
  end
end
