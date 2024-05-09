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
  object VrArrow1: TVrArrow
    Left = 448
    Top = 544
    Width = 50
    Height = 45
    Direction = pdRight
    Palette.Low = clGreen
    Palette.High = clLime
  end
  object VrArrow2: TVrArrow
    Left = 392
    Top = 544
    Width = 50
    Height = 45
    Direction = pdLeft
    Palette.Low = clGreen
    Palette.High = clLime
  end
  object GroupBox1: TGroupBox
    Left = 32
    Top = 70
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
    Left = 188
    Top = 72
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
    Left = 554
    Top = 8
    Width = 233
    Height = 529
    Caption = 'Read Information'
    TabOrder = 3
    object Label1: TLabel
      Left = 16
      Top = 24
      Width = 80
      Height = 13
      Caption = #52880#47532#50612#48372#46300' '#48264#54840
    end
    object Label2: TLabel
      Left = 16
      Top = 56
      Width = 80
      Height = 13
      Caption = #52880#47532#50612#48372#46300' '#44060#49688
    end
    object Label4: TLabel
      Left = 24
      Top = 81
      Width = 72
      Height = 13
      Caption = #47784#46280#51032' '#52629' '#44060#49688
    end
    object Label6: TLabel
      Left = 16
      Top = 105
      Width = 99
      Height = 13
      Caption = 'PC'#51204#52404' '#47784#46280' '#52629' '#44060#49688
    end
    object Label10: TLabel
      Left = 16
      Top = 137
      Width = 58
      Height = 13
      Caption = #44144#47532#45817' '#54148#49828
    end
    object Label11: TLabel
      Left = 48
      Top = 194
      Width = 95
      Height = 13
      Caption = 'Setting '#44050' '#51069#50612#50724#44592
    end
    object Label12: TLabel
      Left = 18
      Top = 219
      Width = 70
      Height = 13
      Caption = 'Servo On '#50668#48512
    end
    object Label13: TLabel
      Left = 18
      Top = 246
      Width = 72
      Height = 13
      Caption = 'Inposition '#50668#48512
    end
    object Label14: TLabel
      Left = 15
      Top = 272
      Width = 77
      Height = 13
      Caption = 'Alarm '#49324#50857' '#50668#48512
    end
    object Label15: TLabel
      Left = 17
      Top = 296
      Width = 72
      Height = 13
      Caption = '+EndLimit '#50668#48512
    end
    object Label16: TLabel
      Left = 18
      Top = 322
      Width = 68
      Height = 13
      Caption = '-EndLimit '#50668#48512
    end
    object Label19: TLabel
      Left = 15
      Top = 348
      Width = 76
      Height = 13
      Caption = '+SlowLimit '#50668#48512
    end
    object Label20: TLabel
      Left = 16
      Top = 373
      Width = 72
      Height = 13
      Caption = '-SlowLimit '#50668#48512
    end
    object edtCarrierBoardNo: TEdit
      Left = 102
      Top = 24
      Width = 81
      Height = 21
      TabOrder = 0
    end
    object edtCarrierBoardCount: TEdit
      Left = 102
      Top = 51
      Width = 81
      Height = 21
      TabOrder = 1
    end
    object edtAxisCount: TEdit
      Left = 102
      Top = 78
      Width = 81
      Height = 21
      TabOrder = 2
    end
    object edtTotalAxisCount: TEdit
      Left = 121
      Top = 105
      Width = 81
      Height = 21
      TabOrder = 3
    end
    object edtMovePulseRead: TEdit
      Left = 105
      Top = 132
      Width = 81
      Height = 21
      TabOrder = 4
    end
    object edtReadServoOn: TEdit
      Left = 96
      Top = 215
      Width = 121
      Height = 21
      TabOrder = 5
    end
    object edtReadInposition: TEdit
      Left = 96
      Top = 241
      Width = 121
      Height = 21
      TabOrder = 6
    end
    object edtReadAlarm: TEdit
      Left = 95
      Top = 267
      Width = 121
      Height = 21
      TabOrder = 7
    end
    object edtReadEndLimitPlus: TEdit
      Left = 96
      Top = 293
      Width = 121
      Height = 21
      TabOrder = 8
    end
    object edtReadEndLimitMinus: TEdit
      Left = 97
      Top = 320
      Width = 121
      Height = 21
      TabOrder = 9
    end
    object edtReadSlowLimitPlus: TEdit
      Left = 97
      Top = 345
      Width = 121
      Height = 21
      TabOrder = 10
    end
    object edtReadSlowLimitMinus: TEdit
      Left = 98
      Top = 369
      Width = 121
      Height = 21
      TabOrder = 11
    end
  end
  object GroupBox4: TGroupBox
    Left = 799
    Top = 8
    Width = 257
    Height = 529
    Caption = 'Write Information'
    TabOrder = 4
    object Label5: TLabel
      Left = 16
      Top = 32
      Width = 69
      Height = 13
      Caption = #46300#46972#51060#48652' '#47784#46300
    end
    object Label3: TLabel
      Left = 16
      Top = 64
      Width = 36
      Height = 13
      Caption = #52629' '#49444#51221
    end
    object Label7: TLabel
      Left = 24
      Top = 100
      Width = 58
      Height = 13
      Caption = #47700#51064' '#53364#46973#49688
    end
    object Label8: TLabel
      Left = 16
      Top = 137
      Width = 88
      Height = 13
      Caption = #44160#52636#45824#49345#49888#54840#51648#51221
    end
    object Label9: TLabel
      Left = 16
      Top = 172
      Width = 58
      Height = 13
      Caption = #44144#47532#45817' '#54148#49828
    end
    object cbDriveModeList: TComboBox
      Left = 106
      Top = 24
      Width = 116
      Height = 21
      TabOrder = 0
      Items.Strings = (
        'hi')
    end
    object cbAxisList: TComboBox
      Left = 98
      Top = 64
      Width = 116
      Height = 21
      TabOrder = 1
      Text = '0'
      Items.Strings = (
        'hi')
    end
    object edtMainClock: TEdit
      Left = 104
      Top = 97
      Width = 121
      Height = 21
      TabOrder = 2
    end
    object cbDetectList: TComboBox
      Left = 110
      Top = 134
      Width = 116
      Height = 21
      TabOrder = 3
      Items.Strings = (
        'hi')
    end
    object edtMovePulseWrite: TEdit
      Left = 104
      Top = 169
      Width = 121
      Height = 21
      TabOrder = 4
      Text = '100.00'
    end
    object btndd: TButton
      Left = -1008
      Top = 472
      Width = 75
      Height = 25
      Caption = 'Setting'
      TabOrder = 5
    end
  end
  object btnStopModule: TButton
    Left = 961
    Top = 773
    Width = 95
    Height = 41
    Caption = #47784#46280#51473#51648
    TabOrder = 5
    OnClick = btnStopModuleClick
  end
  object GroupBox5: TGroupBox
    Left = 315
    Top = 8
    Width = 233
    Height = 313
    Caption = 'Setting'
    TabOrder = 6
    object Label17: TLabel
      Left = 96
      Top = 23
      Width = 28
      Height = 13
      Caption = ' Pulse'
    end
    object Label18: TLabel
      Left = 95
      Top = 46
      Width = 39
      Height = 13
      Caption = 'Encoder'
    end
    object Label21: TLabel
      Left = 48
      Top = 217
      Width = 22
      Height = 13
      Caption = #49549#47141
    end
    object Label22: TLabel
      Left = 144
      Top = 217
      Width = 33
      Height = 13
      Caption = #44032#49549#47141
    end
    object cbMovePulse: TComboBox
      Left = 138
      Top = 19
      Width = 89
      Height = 21
      TabOrder = 0
    end
    object cbEncoder: TComboBox
      Left = 138
      Top = 44
      Width = 89
      Height = 21
      TabOrder = 1
    end
    object chkServoOn: TCheckBox
      Left = 14
      Top = 154
      Width = 153
      Height = 17
      Caption = 'Servo On('#52636#47141' 0)'
      TabOrder = 2
      OnClick = chkServoOnClick
    end
    object btnSetting: TButton
      Left = 126
      Top = 102
      Width = 75
      Height = 25
      Caption = 'Setting!'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clHighlight
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
    end
    object chkEndLimitPlus: TCheckBox
      Left = 12
      Top = 20
      Width = 129
      Height = 17
      Caption = '  +End Limit'
      TabOrder = 4
      OnClick = chkEndLimitPlusClick
    end
    object chkEndLimitMinus: TCheckBox
      Left = 12
      Top = 43
      Width = 129
      Height = 17
      Caption = '  -End Limit'
      TabOrder = 5
      OnClick = chkEndLimitMinusClick
    end
    object chkSlowLimitPlus: TCheckBox
      Left = 12
      Top = 66
      Width = 129
      Height = 17
      Caption = '  +Slow Limit'
      TabOrder = 6
      OnClick = chkSlowLimitPlusClick
    end
    object chkSlowLimitMinus: TCheckBox
      Left = 13
      Top = 89
      Width = 129
      Height = 17
      Caption = '  -Slow Limit'
      TabOrder = 7
      OnClick = chkSlowLimitMinusClick
    end
    object chkInposition: TCheckBox
      Left = 14
      Top = 111
      Width = 129
      Height = 17
      Caption = '  Inposition'
      TabOrder = 8
      OnClick = chkInpositionClick
    end
    object chkAlarm: TCheckBox
      Left = 15
      Top = 133
      Width = 129
      Height = 17
      Caption = '  Alarm'
      TabOrder = 9
      OnClick = chkAlarmClick
    end
    object edtSpeed: TEdit
      Left = 19
      Top = 236
      Width = 86
      Height = 21
      TabOrder = 10
      Text = '4000.00'
    end
    object edtAccel: TEdit
      Left = 120
      Top = 236
      Width = 92
      Height = 21
      TabOrder = 11
      Text = '1000.00'
    end
  end
  object btnRotate: TButton
    Left = 384
    Top = 286
    Width = 75
    Height = 25
    Caption = #54924#51204#54616#44592
    TabOrder = 7
    OnClick = btnRotateClick
  end
  object Timer1: TTimer
    OnTimer = Timer1Timer
    Left = 224
    Top = 80
  end
  object Timer2: TTimer
    OnTimer = Timer2Timer
    Left = 664
    Top = 8
  end
end
