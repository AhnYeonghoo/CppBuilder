object Form2: TForm2
  Left = 0
  Top = 0
  Caption = 'Form2'
  ClientHeight = 822
  ClientWidth = 1064
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
  object GroupBox1: TGroupBox
    Left = 32
    Top = 71
    Width = 121
    Height = 241
    Caption = 'Input'
    TabOrder = 0
    object btnInput0: TCheckBox
      Left = 16
      Top = 39
      Width = 41
      Height = 17
      Caption = '00'
      TabOrder = 0
      OnClick = btnInput0Click
    end
    object btnInput5: TCheckBox
      Left = 16
      Top = 154
      Width = 41
      Height = 17
      Caption = '05'
      TabOrder = 1
      OnClick = btnInput5Click
    end
    object btnInput1: TCheckBox
      Left = 16
      Top = 62
      Width = 41
      Height = 17
      Caption = '01'
      TabOrder = 2
      OnClick = btnInput1Click
    end
    object btnInput2: TCheckBox
      Left = 16
      Top = 85
      Width = 41
      Height = 17
      Caption = '02'
      TabOrder = 3
      OnClick = btnInput2Click
    end
    object btnInput3: TCheckBox
      Left = 16
      Top = 108
      Width = 41
      Height = 17
      Caption = '03'
      TabOrder = 4
      OnClick = btnInput3Click
    end
    object btnInput4: TCheckBox
      Left = 16
      Top = 131
      Width = 41
      Height = 17
      Caption = '04'
      TabOrder = 5
      OnClick = btnInput4Click
    end
    object btnInput6: TCheckBox
      Left = 16
      Top = 177
      Width = 41
      Height = 17
      Caption = '06'
      TabOrder = 6
      OnClick = btnInput6Click
    end
    object btnInput7: TCheckBox
      Left = 16
      Top = 200
      Width = 41
      Height = 17
      Caption = '07'
      TabOrder = 7
      OnClick = btnInput7Click
    end
    object btnInput8: TCheckBox
      Left = 63
      Top = 39
      Width = 41
      Height = 17
      Caption = '08'
      TabOrder = 8
      OnClick = btnInput8Click
    end
    object btnInput9: TCheckBox
      Left = 63
      Top = 62
      Width = 41
      Height = 17
      Caption = '09'
      TabOrder = 9
      OnClick = btnInput9Click
    end
    object btnInput10: TCheckBox
      Left = 63
      Top = 85
      Width = 41
      Height = 17
      Caption = '10'
      TabOrder = 10
      OnClick = btnInput10Click
    end
    object btnInput11: TCheckBox
      Left = 63
      Top = 108
      Width = 41
      Height = 17
      Caption = '11'
      TabOrder = 11
      OnClick = btnInput11Click
    end
    object btnInput12: TCheckBox
      Left = 63
      Top = 131
      Width = 41
      Height = 17
      Caption = '12'
      TabOrder = 12
      OnClick = btnInput12Click
    end
    object btnInput13: TCheckBox
      Left = 63
      Top = 154
      Width = 41
      Height = 17
      Caption = '13'
      TabOrder = 13
      OnClick = btnInput13Click
    end
    object btnInput14: TCheckBox
      Left = 63
      Top = 177
      Width = 41
      Height = 17
      Caption = '14'
      TabOrder = 14
      OnClick = btnInput14Click
    end
    object btnInput15: TCheckBox
      Left = 63
      Top = 200
      Width = 41
      Height = 17
      Caption = '15'
      TabOrder = 15
      OnClick = btnInput15Click
    end
  end
  object GroupBox2: TGroupBox
    Left = 184
    Top = 71
    Width = 121
    Height = 241
    Caption = 'Output'
    TabOrder = 1
    object btnOutput0: TCheckBox
      Left = 16
      Top = 39
      Width = 41
      Height = 17
      Caption = '00'
      TabOrder = 0
    end
    object btnOutput5: TCheckBox
      Left = 16
      Top = 154
      Width = 41
      Height = 17
      Caption = '05'
      TabOrder = 1
    end
    object btnOutput1: TCheckBox
      Left = 16
      Top = 62
      Width = 41
      Height = 17
      Caption = '01'
      TabOrder = 2
    end
    object btnOutput2: TCheckBox
      Left = 16
      Top = 85
      Width = 41
      Height = 17
      Caption = '02'
      TabOrder = 3
    end
    object btnOutput3: TCheckBox
      Left = 16
      Top = 108
      Width = 41
      Height = 17
      Caption = '03'
      TabOrder = 4
    end
    object btnOutput4: TCheckBox
      Left = 16
      Top = 131
      Width = 41
      Height = 17
      Caption = '04'
      TabOrder = 5
    end
    object btnOutput6: TCheckBox
      Left = 16
      Top = 177
      Width = 41
      Height = 17
      Caption = '06'
      TabOrder = 6
    end
    object btnOutput7: TCheckBox
      Left = 16
      Top = 200
      Width = 41
      Height = 17
      Caption = '07'
      TabOrder = 7
    end
    object btnOutput8: TCheckBox
      Left = 63
      Top = 39
      Width = 41
      Height = 17
      Caption = '08'
      TabOrder = 8
    end
    object btnOutput9: TCheckBox
      Left = 63
      Top = 62
      Width = 41
      Height = 17
      Caption = '09'
      TabOrder = 9
    end
    object btnOutput10: TCheckBox
      Left = 63
      Top = 85
      Width = 41
      Height = 17
      Caption = '10'
      TabOrder = 10
    end
    object btnOutput11: TCheckBox
      Left = 63
      Top = 108
      Width = 41
      Height = 17
      Caption = '11'
      TabOrder = 11
    end
    object btnOutput12: TCheckBox
      Left = 63
      Top = 131
      Width = 41
      Height = 17
      Caption = '12'
      TabOrder = 12
    end
    object btnOutput13: TCheckBox
      Left = 63
      Top = 154
      Width = 41
      Height = 17
      Caption = '13'
      TabOrder = 13
    end
    object btnOutput14: TCheckBox
      Left = 63
      Top = 177
      Width = 41
      Height = 17
      Caption = '14'
      TabOrder = 14
    end
    object btnOutput15: TCheckBox
      Left = 63
      Top = 200
      Width = 41
      Height = 17
      Caption = '15'
      TabOrder = 15
    end
  end
  object selectModule: TComboBox
    Left = 32
    Top = 24
    Width = 273
    Height = 21
    TabOrder = 2
    Text = 'selectModule'
  end
  object GroupBox3: TGroupBox
    Left = 328
    Top = 71
    Width = 385
    Height = 241
    Caption = 'Motor'
    TabOrder = 3
    object Label1: TLabel
      Left = 184
      Top = 20
      Width = 37
      Height = 13
      Caption = 'Position'
    end
    object Label2: TLabel
      Left = 183
      Top = 53
      Width = 22
      Height = 13
      Caption = #49549#46020
    end
    object Label3: TLabel
      Left = 183
      Top = 86
      Width = 59
      Height = 13
      Caption = #44032'/'#44048#49549#49884#44036
    end
    object GroupBox4: TGroupBox
      Left = 16
      Top = 20
      Width = 145
      Height = 181
      Caption = 'Settings'
      TabOrder = 0
      object chkEndLimitPlus: TCheckBox
        Left = 24
        Top = 32
        Width = 97
        Height = 17
        Caption = '+ End Limit'
        TabOrder = 0
        OnClick = chkEndLimitPlusClick
      end
      object chkEndLimitMinus: TCheckBox
        Left = 24
        Top = 55
        Width = 97
        Height = 17
        Caption = ' - End Limit'
        TabOrder = 1
        OnClick = chkEndLimitMinusClick
      end
      object chkSlowLimitPlus: TCheckBox
        Left = 24
        Top = 78
        Width = 97
        Height = 17
        Caption = '+ Slow Limit'
        TabOrder = 2
        OnClick = chkSlowLimitPlusClick
      end
      object chkSlowLimitMinus: TCheckBox
        Left = 24
        Top = 101
        Width = 97
        Height = 17
        Caption = '- Slow Limit'
        TabOrder = 3
        OnClick = chkSlowLimitMinusClick
      end
      object chkInposition: TCheckBox
        Left = 24
        Top = 124
        Width = 97
        Height = 17
        Caption = ' Inposition'
        TabOrder = 4
        OnClick = chkInpositionClick
      end
      object chkAlarm: TCheckBox
        Left = 24
        Top = 147
        Width = 97
        Height = 17
        Caption = ' Alarm'
        TabOrder = 5
        OnClick = chkAlarmClick
      end
    end
    object btnRotate: TButton
      Left = 48
      Top = 207
      Width = 75
      Height = 25
      Caption = #54924#51204
      TabOrder = 1
      OnClick = btnRotateClick
    end
    object edtPosition: TEdit
      Left = 240
      Top = 17
      Width = 97
      Height = 21
      TabOrder = 2
      Text = '0.00'
    end
    object edtSpeed: TEdit
      Left = 240
      Top = 44
      Width = 97
      Height = 21
      TabOrder = 3
      Text = '1000.00'
    end
    object edtAccel: TEdit
      Left = 248
      Top = 83
      Width = 97
      Height = 21
      TabOrder = 4
      Text = '500.00'
    end
  end
  object chkServoOn: TCheckBox
    Left = 512
    Top = 181
    Width = 97
    Height = 17
    Caption = 'Servo '#49888#54840' '#52636#47141
    TabOrder = 4
    OnClick = chkServoOnClick
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Left = 224
    Top = 80
  end
end
