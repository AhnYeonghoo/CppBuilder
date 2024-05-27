object Form4: TForm4
  Left = 0
  Top = 0
  Caption = 'Form4'
  ClientHeight = 299
  ClientWidth = 635
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 64
    Top = 48
    Width = 35
    Height = 13
    Caption = 'Hours: '
  end
  object Label2: TLabel
    Left = 64
    Top = 88
    Width = 44
    Height = 13
    Caption = 'Minutes: '
  end
  object Label3: TLabel
    Left = 64
    Top = 128
    Width = 47
    Height = 13
    Caption = 'Seconds: '
  end
  object lblMinutes: TLabel
    Left = 568
    Top = 88
    Width = 12
    Height = 13
    Caption = '00'
  end
  object lblHours: TLabel
    Left = 568
    Top = 48
    Width = 12
    Height = 13
    Caption = '00'
  end
  object lblSeconds: TLabel
    Left = 568
    Top = 128
    Width = 12
    Height = 13
    Caption = '00'
  end
  object pgrHours: TProgressBar
    Left = 136
    Top = 48
    Width = 185
    Height = 17
    TabOrder = 0
  end
  object pgrMinutes: TProgressBar
    Left = 136
    Top = 87
    Width = 401
    Height = 17
    TabOrder = 1
  end
  object pgrSeconds: TProgressBar
    Left = 136
    Top = 126
    Width = 401
    Height = 17
    TabOrder = 2
  end
  object bkClose: TBitBtn
    Left = 478
    Top = 176
    Width = 75
    Height = 25
    Caption = 'Close'
    TabOrder = 3
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Left = 120
    Top = 160
  end
end
