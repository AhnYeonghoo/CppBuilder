object Form2: TForm2
  Left = 0
  Top = 0
  Caption = 'Employee Name:'
  ClientHeight = 485
  ClientWidth = 558
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Bevel1: TBevel
    Left = 24
    Top = 16
    Width = 513
    Height = 57
  end
  object Label1: TLabel
    Left = 40
    Top = 40
    Width = 81
    Height = 13
    Caption = 'Employee Name:'
  end
  object Label2: TLabel
    Left = 320
    Top = 40
    Width = 68
    Height = 13
    Caption = 'Hourly Salary:'
  end
  object Bevel2: TBevel
    Left = 24
    Top = 96
    Width = 513
    Height = 137
  end
  object Monday: TLabel
    Left = 104
    Top = 120
    Width = 38
    Height = 13
    Caption = 'Monday'
  end
  object Tuesday: TLabel
    Left = 160
    Top = 120
    Width = 41
    Height = 13
    Caption = 'Tuesday'
  end
  object Wednesday: TLabel
    Left = 223
    Top = 120
    Width = 57
    Height = 13
    Caption = 'Wednesday'
  end
  object Thursday: TLabel
    Left = 296
    Top = 120
    Width = 45
    Height = 13
    Caption = 'Thursday'
  end
  object Friday: TLabel
    Left = 358
    Top = 120
    Width = 30
    Height = 13
    Caption = 'Friday'
  end
  object Saturday: TLabel
    Left = 408
    Top = 120
    Width = 44
    Height = 13
    Caption = 'Saturday'
  end
  object Sunday: TLabel
    Left = 471
    Top = 120
    Width = 36
    Height = 13
    Caption = 'Sunday'
  end
  object Label3: TLabel
    Left = 40
    Top = 152
    Width = 40
    Height = 13
    Caption = 'Week 1:'
  end
  object Label4: TLabel
    Left = 40
    Top = 192
    Width = 40
    Height = 13
    Caption = 'Week 2:'
  end
  object Bevel3: TBevel
    Left = 24
    Top = 256
    Width = 513
    Height = 185
  end
  object Label5: TLabel
    Left = 223
    Top = 280
    Width = 22
    Height = 13
    Caption = 'Time'
  end
  object Label6: TLabel
    Left = 296
    Top = 280
    Width = 58
    Height = 13
    Caption = 'Pay Amount'
  end
  object Label7: TLabel
    Left = 160
    Top = 310
    Width = 41
    Height = 13
    Caption = 'Regular:'
  end
  object Label8: TLabel
    Left = 160
    Top = 348
    Width = 48
    Height = 13
    Caption = 'Overtime:'
  end
  object Label9: TLabel
    Left = 230
    Top = 400
    Width = 42
    Height = 13
    Caption = 'Net Pay:'
  end
  object Label10: TLabel
    Left = 394
    Top = 310
    Width = 53
    Height = 13
    Caption = 'Total Time:'
  end
  object Label11: TLabel
    Left = 394
    Top = 348
    Width = 49
    Height = 13
    Caption = 'Total Pay:'
  end
  object edtEmployeeName: TEdit
    Left = 127
    Top = 37
    Width = 178
    Height = 21
    TabOrder = 0
    OnChange = edtEmployeeNameChange
  end
  object edtHourlySalary: TEdit
    Left = 394
    Top = 37
    Width = 121
    Height = 21
    Alignment = taRightJustify
    TabOrder = 1
    Text = '0.00'
  end
  object edtWeek1Monday: TEdit
    Left = 104
    Top = 149
    Width = 38
    Height = 21
    Alignment = taRightJustify
    TabOrder = 2
    Text = '0.00'
  end
  object edtWeek2Monday: TEdit
    Left = 104
    Top = 189
    Width = 38
    Height = 21
    Alignment = taRightJustify
    TabOrder = 3
    Text = '0.00'
  end
  object edtWeek1Tuesday: TEdit
    Left = 160
    Top = 149
    Width = 38
    Height = 21
    Alignment = taRightJustify
    TabOrder = 4
    Text = '0.00'
  end
  object edtWeek2Tuesday: TEdit
    Left = 160
    Top = 189
    Width = 38
    Height = 21
    Alignment = taRightJustify
    TabOrder = 5
    Text = '0.00'
  end
  object edtWeek2Wednesday: TEdit
    Left = 223
    Top = 189
    Width = 38
    Height = 21
    Alignment = taRightJustify
    TabOrder = 6
    Text = '0.00'
  end
  object edtWeek1Wednesday: TEdit
    Left = 223
    Top = 149
    Width = 38
    Height = 21
    Alignment = taRightJustify
    TabOrder = 7
    Text = '0.00'
  end
  object edtWeek2Thursday: TEdit
    Left = 296
    Top = 189
    Width = 38
    Height = 21
    Alignment = taRightJustify
    TabOrder = 8
    Text = '0.00'
  end
  object edtWeek1Thursday: TEdit
    Left = 296
    Top = 149
    Width = 38
    Height = 21
    Alignment = taRightJustify
    TabOrder = 9
    Text = '0.00'
  end
  object edtWeek2Friday: TEdit
    Left = 358
    Top = 189
    Width = 38
    Height = 21
    Alignment = taRightJustify
    TabOrder = 10
    Text = '0.00'
  end
  object edtWeek1Friday: TEdit
    Left = 358
    Top = 149
    Width = 38
    Height = 21
    Alignment = taRightJustify
    TabOrder = 11
    Text = '0.00'
  end
  object edtWeek2Saturday: TEdit
    Left = 414
    Top = 189
    Width = 38
    Height = 21
    Alignment = taRightJustify
    TabOrder = 12
    Text = '0.00'
  end
  object edtWeek1Saturday: TEdit
    Left = 414
    Top = 149
    Width = 38
    Height = 21
    Alignment = taRightJustify
    TabOrder = 13
    Text = '0.00'
  end
  object Edit13: TEdit
    Left = 471
    Top = 189
    Width = 38
    Height = 21
    Alignment = taRightJustify
    TabOrder = 14
    Text = '0.00'
  end
  object edtWeek1Sunday: TEdit
    Left = 471
    Top = 149
    Width = 38
    Height = 21
    Alignment = taRightJustify
    TabOrder = 15
    Text = '0.00'
  end
  object btnCalculate: TButton
    Left = 27
    Top = 288
    Width = 115
    Height = 73
    Caption = 'Calculate'
    TabOrder = 16
    OnClick = btnCalculateClick
  end
  object edtRegularTime: TEdit
    Left = 223
    Top = 307
    Width = 48
    Height = 21
    Alignment = taRightJustify
    TabOrder = 17
    Text = '0.00'
  end
  object edtRegularPay: TEdit
    Left = 306
    Top = 307
    Width = 48
    Height = 21
    Alignment = taRightJustify
    TabOrder = 18
    Text = '0.00'
  end
  object edtOvertime: TEdit
    Left = 223
    Top = 345
    Width = 48
    Height = 21
    Alignment = taRightJustify
    TabOrder = 19
    Text = '0.00'
  end
  object edtOvertimePay: TEdit
    Left = 306
    Top = 345
    Width = 48
    Height = 21
    Alignment = taRightJustify
    TabOrder = 20
    Text = '0.00'
  end
  object edtNetPay: TEdit
    Left = 278
    Top = 397
    Width = 76
    Height = 21
    Alignment = taRightJustify
    TabOrder = 21
    Text = '0.00'
  end
  object StaticText1: TStaticText
    Left = 381
    Top = 280
    Width = 134
    Height = 17
    Caption = 'Pay Without Overtime Rule'
    TabOrder = 22
  end
  object edtTotaltime: TEdit
    Left = 467
    Top = 303
    Width = 48
    Height = 21
    Alignment = taRightJustify
    TabOrder = 23
    Text = '0.00'
  end
  object edtTotalpay: TEdit
    Left = 467
    Top = 345
    Width = 48
    Height = 21
    Alignment = taRightJustify
    TabOrder = 24
    Text = '0.00'
  end
  object btnClose: TButton
    Left = 372
    Top = 395
    Width = 157
    Height = 25
    Caption = 'Close'
    TabOrder = 25
  end
  object chkApplyOvertimeRules: TCheckBox
    Left = 45
    Top = 239
    Width = 132
    Height = 17
    Caption = 'Apply Overtime Rules'
    TabOrder = 26
  end
end
