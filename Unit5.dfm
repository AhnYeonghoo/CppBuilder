object Form5: TForm5
  Left = 0
  Top = 0
  Caption = 'Form5'
  ClientHeight = 749
  ClientWidth = 1115
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
  object Label19: TLabel
    Left = 44
    Top = 704
    Width = 111
    Height = 13
    Caption = 'Repair Order to Open: '
  end
  object Label20: TLabel
    Left = 403
    Top = 704
    Width = 111
    Height = 13
    Caption = 'Save Repair Order As: '
  end
  object GroupBox1: TGroupBox
    Left = 32
    Top = 24
    Width = 537
    Height = 297
    Caption = 'Repair Identification'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    object Label1: TLabel
      Left = 24
      Top = 32
      Width = 83
      Height = 13
      Caption = 'Customer Name: '
    end
    object Label2: TLabel
      Left = 25
      Top = 64
      Width = 46
      Height = 13
      Caption = 'Address: '
    end
    object Label3: TLabel
      Left = 25
      Top = 95
      Width = 26
      Height = 13
      Caption = 'City: '
    end
    object Label4: TLabel
      Left = 226
      Top = 98
      Width = 33
      Height = 13
      Caption = 'State: '
    end
    object Label5: TLabel
      Left = 331
      Top = 100
      Width = 51
      Height = 13
      Caption = 'ZIP Code: '
    end
    object TLabel
      Left = 25
      Top = 135
      Width = 84
      Height = 13
      Caption = 'Car Make/Model: '
    end
    object Label6: TLabel
      Left = 329
      Top = 135
      Width = 29
      Height = 13
      Caption = 'Year: '
    end
    object TLabel
      Left = 25
      Top = 175
      Width = 88
      Height = 11
      Caption = 'Problem Description: '
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -9
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object edtCustomerName: TEdit
      Left = 113
      Top = 29
      Width = 345
      Height = 21
      TabOrder = 0
      OnExit = edtCustomerNameExit
    end
    object edtAddress: TEdit
      Left = 113
      Top = 61
      Width = 345
      Height = 21
      TabOrder = 1
    end
    object edtCity: TEdit
      Left = 113
      Top = 95
      Width = 103
      Height = 21
      TabOrder = 2
    end
    object edtState: TEdit
      Left = 262
      Top = 94
      Width = 59
      Height = 21
      TabOrder = 3
    end
    object edtZIPCode: TEdit
      Left = 384
      Top = 95
      Width = 75
      Height = 21
      TabOrder = 4
    end
    object edtMakeModel: TEdit
      Left = 115
      Top = 132
      Width = 206
      Height = 21
      TabOrder = 5
    end
    object edtYear: TEdit
      Left = 384
      Top = 132
      Width = 75
      Height = 21
      TabOrder = 6
    end
    object mmoProblemDescription: TMemo
      Left = 115
      Top = 170
      Width = 344
      Height = 111
      Lines.Strings = (
        'mmoProblemDescription')
      TabOrder = 7
    end
  end
  object GroupBox2: TGroupBox
    Left = 32
    Top = 327
    Width = 537
    Height = 178
    Caption = 'Repair Evaluation'
    TabOrder = 1
    object Label7: TLabel
      Left = 40
      Top = 40
      Width = 59
      Height = 13
      Caption = 'Total Parts: '
    end
    object Label8: TLabel
      Left = 40
      Top = 80
      Width = 51
      Height = 13
      Caption = 'Tax Rate: '
    end
    object Label9: TLabel
      Left = 299
      Top = 40
      Width = 61
      Height = 13
      Caption = 'Total Labor: '
    end
    object Label10: TLabel
      Left = 300
      Top = 122
      Width = 62
      Height = 13
      Caption = 'Total Order: '
    end
    object Label11: TLabel
      Left = 299
      Top = 80
      Width = 71
      Height = 13
      Caption = 'Total Amount: '
    end
    object Label12: TLabel
      Left = 262
      Top = 80
      Width = 11
      Height = 13
      Caption = '%'
    end
    object edtTotalParts: TEdit
      Left = 109
      Top = 37
      Width = 150
      Height = 21
      Alignment = taRightJustify
      TabOrder = 0
      Text = '0.00'
    end
    object edtTaxRate: TEdit
      Left = 109
      Top = 76
      Width = 150
      Height = 21
      Alignment = taRightJustify
      TabOrder = 1
      Text = '5.75'
      OnExit = edtTaxRateExit
    end
    object edtTotalLabor: TEdit
      Left = 371
      Top = 37
      Width = 150
      Height = 21
      Alignment = taRightJustify
      TabOrder = 2
      Text = '0.00'
    end
    object edtTotalAmount: TEdit
      Left = 371
      Top = 74
      Width = 150
      Height = 21
      Alignment = taRightJustify
      TabOrder = 3
      Text = '0.00'
    end
    object edtTotalOrder: TEdit
      Left = 371
      Top = 118
      Width = 150
      Height = 21
      Alignment = taRightJustify
      TabOrder = 4
      Text = '0.00'
    end
  end
  object GroupBox3: TGroupBox
    Left = 584
    Top = 24
    Width = 523
    Height = 245
    Caption = 'Parts Used'
    TabOrder = 2
    object Label13: TLabel
      Left = 16
      Top = 29
      Width = 50
      Height = 13
      Caption = 'Part Name'
    end
    object Label14: TLabel
      Left = 286
      Top = 29
      Width = 45
      Height = 13
      Caption = 'Unit Price'
    end
    object Label15: TLabel
      Left = 377
      Top = 29
      Width = 18
      Height = 13
      Caption = 'Qty'
    end
    object Label16: TLabel
      Left = 431
      Top = 29
      Width = 46
      Height = 13
      Caption = 'Sub-Total'
    end
    object edtPartName1: TEdit
      Left = 16
      Top = 48
      Width = 257
      Height = 21
      TabOrder = 0
    end
    object edtPartName2: TEdit
      Left = 16
      Top = 87
      Width = 257
      Height = 21
      TabOrder = 1
    end
    object edtPartName3: TEdit
      Left = 16
      Top = 126
      Width = 257
      Height = 21
      TabOrder = 2
    end
    object edtPartName4: TEdit
      Left = 17
      Top = 161
      Width = 257
      Height = 21
      TabOrder = 3
    end
    object edtPartName5: TEdit
      Left = 17
      Top = 202
      Width = 257
      Height = 21
      TabOrder = 4
    end
    object edtUnitPrice1: TEdit
      Left = 283
      Top = 48
      Width = 83
      Height = 21
      Alignment = taRightJustify
      TabOrder = 5
      Text = '0.00'
    end
    object edtUnitPrice2: TEdit
      Left = 284
      Top = 85
      Width = 83
      Height = 21
      Alignment = taRightJustify
      TabOrder = 6
      Text = '0.00'
    end
    object edtUnitPrice3: TEdit
      Left = 284
      Top = 125
      Width = 83
      Height = 21
      Alignment = taRightJustify
      TabOrder = 7
      Text = '0.00'
    end
    object edtUnitPrice4: TEdit
      Left = 283
      Top = 163
      Width = 83
      Height = 21
      Alignment = taRightJustify
      TabOrder = 8
      Text = '0.00'
    end
    object edtUnitPrice5: TEdit
      Left = 285
      Top = 201
      Width = 83
      Height = 21
      Alignment = taRightJustify
      TabOrder = 9
      Text = '0.00'
    end
    object edtQty1: TEdit
      Left = 372
      Top = 48
      Width = 49
      Height = 21
      Alignment = taRightJustify
      TabOrder = 10
      Text = '0'
    end
    object edtQty2: TEdit
      Left = 373
      Top = 85
      Width = 49
      Height = 21
      Alignment = taRightJustify
      TabOrder = 11
      Text = '0'
    end
    object edtQty3: TEdit
      Left = 373
      Top = 125
      Width = 49
      Height = 21
      Alignment = taRightJustify
      TabOrder = 12
      Text = '0'
    end
    object edtQty4: TEdit
      Left = 372
      Top = 161
      Width = 49
      Height = 21
      Alignment = taRightJustify
      TabOrder = 13
      Text = '0'
    end
    object edtQty5: TEdit
      Left = 374
      Top = 201
      Width = 49
      Height = 21
      Alignment = taRightJustify
      TabOrder = 14
      Text = '0'
    end
    object edtSubTotal1: TEdit
      Left = 427
      Top = 48
      Width = 83
      Height = 21
      Alignment = taRightJustify
      TabOrder = 15
      Text = '0.00'
    end
    object edtSubTotal3: TEdit
      Left = 428
      Top = 125
      Width = 83
      Height = 21
      Alignment = taRightJustify
      TabOrder = 16
      Text = '0.00'
    end
    object edtSubTotal4: TEdit
      Left = 427
      Top = 161
      Width = 83
      Height = 21
      Alignment = taRightJustify
      TabOrder = 17
      Text = '0.00'
    end
    object edtSubTotal5: TEdit
      Left = 429
      Top = 201
      Width = 83
      Height = 21
      Alignment = taRightJustify
      TabOrder = 18
      Text = '0.00'
    end
    object edtSubTotal2: TEdit
      Left = 428
      Top = 85
      Width = 83
      Height = 21
      Alignment = taRightJustify
      TabOrder = 19
      Text = '0.00'
    end
  end
  object GroupBox4: TGroupBox
    Left = 584
    Top = 275
    Width = 523
    Height = 230
    Caption = 'Jobs Performed'
    TabOrder = 3
    object Label17: TLabel
      Left = 32
      Top = 30
      Width = 73
      Height = 13
      Caption = 'Job Description'
    end
    object Label18: TLabel
      Left = 398
      Top = 33
      Width = 42
      Height = 13
      Caption = 'Job Cost'
    end
    object edtJobDescription1: TEdit
      Left = 32
      Top = 56
      Width = 361
      Height = 21
      TabOrder = 0
    end
    object edtJobDescription2: TEdit
      Left = 33
      Top = 90
      Width = 361
      Height = 21
      TabOrder = 1
    end
    object edtJobDescription3: TEdit
      Left = 34
      Top = 125
      Width = 361
      Height = 21
      TabOrder = 2
    end
    object edtJobDescription4: TEdit
      Left = 34
      Top = 157
      Width = 361
      Height = 21
      TabOrder = 3
    end
    object edtJobDescription5: TEdit
      Left = 34
      Top = 189
      Width = 361
      Height = 21
      TabOrder = 4
    end
    object edtJobCost1: TEdit
      Left = 399
      Top = 52
      Width = 83
      Height = 21
      Alignment = taRightJustify
      TabOrder = 5
      Text = '0.00'
    end
    object edtJobCost2: TEdit
      Left = 403
      Top = 90
      Width = 83
      Height = 21
      Alignment = taRightJustify
      TabOrder = 6
      Text = '0.00'
    end
    object edtJobCost3: TEdit
      Left = 404
      Top = 124
      Width = 83
      Height = 21
      Alignment = taRightJustify
      TabOrder = 7
      Text = '0.00'
    end
    object edtJobCost4: TEdit
      Left = 406
      Top = 156
      Width = 83
      Height = 21
      Alignment = taRightJustify
      TabOrder = 8
      Text = '0.00'
    end
    object edtJobCost5: TEdit
      Left = 407
      Top = 188
      Width = 83
      Height = 21
      Alignment = taRightJustify
      TabOrder = 9
      Text = '0.00'
    end
  end
  object GroupBox5: TGroupBox
    Left = 32
    Top = 520
    Width = 1075
    Height = 153
    Caption = 'Recommendations'
    TabOrder = 4
    object mmoRecommendations: TMemo
      Left = 12
      Top = 19
      Width = 1045
      Height = 118
      Lines.Strings = (
        'mmoRecommendations')
      TabOrder = 0
    end
  end
  object edtFileOpen: TEdit
    Left = 170
    Top = 701
    Width = 121
    Height = 21
    TabOrder = 5
  end
  object btnOpen: TButton
    Left = 297
    Top = 699
    Width = 75
    Height = 25
    Caption = 'Open'
    TabOrder = 6
    OnClick = btnOpenClick
  end
  object edtFileSave: TEdit
    Left = 520
    Top = 701
    Width = 121
    Height = 21
    TabOrder = 7
  end
  object edtSave: TButton
    Left = 647
    Top = 699
    Width = 75
    Height = 25
    Caption = 'Save'
    TabOrder = 8
    OnClick = edtSaveClick
  end
  object btnReset: TButton
    Left = 744
    Top = 699
    Width = 233
    Height = 25
    Caption = 'Reset/Start New Repair Order'
    TabOrder = 9
    OnClick = btnResetClick
  end
  object btnClose: TButton
    Left = 998
    Top = 699
    Width = 75
    Height = 25
    Caption = 'Close'
    TabOrder = 10
    OnClick = btnCloseClick
  end
end
