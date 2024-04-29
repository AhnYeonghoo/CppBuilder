object frmMain: TfrmMain
  Left = 0
  Top = 0
  Caption = 'Progressive Clock'
  ClientHeight = 299
  ClientWidth = 635
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 48
    Top = 48
    Width = 32
    Height = 13
    Caption = 'Hours:'
  end
  object Label2: TLabel
    Left = 48
    Top = 112
    Width = 41
    Height = 13
    Caption = 'Minutes:'
  end
  object Label3: TLabel
    Left = 48
    Top = 176
    Width = 44
    Height = 13
    Caption = 'Seconds:'
  end
  object lblHours: TLabel
    Left = 512
    Top = 48
    Width = 12
    Height = 13
    Caption = '00'
  end
  object lblMinutes: TLabel
    Left = 512
    Top = 108
    Width = 12
    Height = 13
    Caption = '00'
  end
  object lblSeconds: TLabel
    Left = 512
    Top = 176
    Width = 12
    Height = 13
    Caption = '00'
  end
  object pgrHours: TProgressBar
    Left = 104
    Top = 48
    Width = 150
    Height = 17
    TabOrder = 0
  end
  object pgrMinutes: TProgressBar
    Left = 104
    Top = 108
    Width = 385
    Height = 17
    TabOrder = 1
  end
  object pgrSeconds: TProgressBar
    Left = 104
    Top = 172
    Width = 385
    Height = 17
    TabOrder = 2
  end
  object bkClose: TBitBtn
    Left = 414
    Top = 240
    Width = 75
    Height = 25
    Caption = 'Close'
    TabOrder = 3
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Left = 104
    Top = 216
  end
end
