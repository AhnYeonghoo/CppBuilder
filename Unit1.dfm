object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 623
  ClientWidth = 505
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
    Left = 32
    Top = 112
    Width = 22
    Height = 13
    Caption = #54617#48264
    OnClick = Label1Click
  end
  object Label2: TLabel
    Left = 32
    Top = 144
    Width = 22
    Height = 13
    Caption = #51316#54632
    OnClick = Label1Click
  end
  object Label3: TLabel
    Left = 32
    Top = 171
    Width = 22
    Height = 13
    Caption = #50672#49464
    OnClick = Label1Click
  end
  object Label4: TLabel
    Left = 40
    Top = 485
    Width = 22
    Height = 13
    Caption = #54617#48264
    OnClick = Label1Click
  end
  object ListBox1: TListBox
    Left = 248
    Top = 112
    Width = 217
    Height = 441
    ItemHeight = 13
    TabOrder = 6
  end
  object studentNumber: TEdit
    Left = 80
    Top = 109
    Width = 121
    Height = 21
    TabOrder = 0
    OnChange = studentNumberChange
  end
  object studentName: TEdit
    Left = 80
    Top = 136
    Width = 121
    Height = 21
    TabOrder = 1
    OnChange = studentNumberChange
  end
  object studentAge: TEdit
    Left = 80
    Top = 168
    Width = 121
    Height = 21
    TabOrder = 2
    OnChange = studentNumberChange
  end
  object addButton: TButton
    Left = 80
    Top = 216
    Width = 121
    Height = 49
    Caption = 'addButton'
    TabOrder = 3
    OnClick = addButtonClick
  end
  object confirmStudentNumber: TEdit
    Left = 80
    Top = 477
    Width = 121
    Height = 21
    TabOrder = 4
    OnChange = studentNumberChange
  end
  object Delete: TButton
    Left = 80
    Top = 520
    Width = 121
    Height = 49
    Caption = 'deleteButton'
    TabOrder = 5
    OnClick = DeleteClick
  end
end
