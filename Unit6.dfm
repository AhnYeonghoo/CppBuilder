object frmRepairOrders: TfrmRepairOrders
  Left = 384
  Top = 185
  Caption = 'College Park Auto Repair'
  ClientHeight = 617
  ClientWidth = 1259
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesigned
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 32
    Top = 1
    Width = 1241
    Height = 600
    Caption = 'Repair Identification'
    TabOrder = 0
    object Label1: TLabel
      Left = 24
      Top = 32
      Width = 80
      Height = 13
      Caption = 'Customer Name:'
    end
    object Label2: TLabel
      Left = 24
      Top = 64
      Width = 43
      Height = 13
      Caption = 'Address:'
    end
    object Label3: TLabel
      Left = 24
      Top = 96
      Width = 23
      Height = 13
      Caption = 'City:'
    end
    object Label4: TLabel
      Left = 216
      Top = 96
      Width = 30
      Height = 13
      Caption = 'State:'
    end
    object Label5: TLabel
      Left = 311
      Top = 96
      Width = 30
      Height = 13
      Caption = 'State:'
    end
    object Label6: TLabel
      Left = 24
      Top = 128
      Width = 81
      Height = 13
      Caption = 'Car Make/Model:'
    end
    object Label7: TLabel
      Left = 311
      Top = 128
      Width = 26
      Height = 13
      Caption = 'Year:'
    end
    object Label8: TLabel
      Left = 24
      Top = 160
      Width = 98
      Height = 13
      Caption = 'Problem Description:'
    end
    object edtCustomerName: TEdit
      Left = 126
      Top = 29
      Width = 274
      Height = 21
      TabOrder = 0
    end
    object edtAddress: TEdit
      Left = 126
      Top = 61
      Width = 274
      Height = 21
      TabOrder = 1
    end
    object edtCity: TEdit
      Left = 126
      Top = 93
      Width = 75
      Height = 21
      TabOrder = 2
    end
    object edtState: TEdit
      Left = 252
      Top = 93
      Width = 53
      Height = 21
      TabOrder = 3
    end
    object edtZIPCode: TEdit
      Left = 347
      Top = 93
      Width = 53
      Height = 21
      TabOrder = 4
    end
    object edtMakeModel: TEdit
      Left = 127
      Top = 120
      Width = 178
      Height = 21
      TabOrder = 5
    end
    object edtYear: TEdit
      Left = 347
      Top = 125
      Width = 53
      Height = 21
      TabOrder = 6
    end
    object mmoProblemDescription: TMemo
      Left = 128
      Top = 157
      Width = 272
      Height = 89
      Lines.Strings = (
        'mmoProblemDescription')
      TabOrder = 7
    end
    object GroupBox2: TGroupBox
      Left = 16
      Top = 252
      Width = 393
      Height = 165
      Caption = 'Repair Evaluation'
      TabOrder = 8
      object Label9: TLabel
        Left = 20
        Top = 32
        Width = 56
        Height = 17
        Caption = 'Total Parts:'
      end
      object Label10: TLabel
        Left = 192
        Top = 32
        Width = 58
        Height = 13
        Caption = 'Total Labor:'
      end
      object Label11: TLabel
        Left = 20
        Top = 64
        Width = 48
        Height = 13
        Caption = 'Tax Rate:'
      end
      object Label12: TLabel
        Left = 175
        Top = 72
        Width = 11
        Height = 13
        Caption = '%'
      end
      object Label13: TLabel
        Left = 192
        Top = 72
        Width = 62
        Height = 13
        Caption = 'Tax Amount:'
      end
      object Label14: TLabel
        Left = 192
        Top = 104
        Width = 59
        Height = 13
        Caption = 'Total Order:'
      end
      object edtTotalParts: TEdit
        Left = 82
        Top = 24
        Width = 87
        Height = 21
        Alignment = taRightJustify
        TabOrder = 0
        Text = '0.00'
      end
      object edtTotalLabor: TEdit
        Left = 262
        Top = 24
        Width = 107
        Height = 21
        Alignment = taRightJustify
        TabOrder = 1
        Text = '0.00'
      end
      object edtTaxRate: TEdit
        Left = 82
        Top = 64
        Width = 87
        Height = 21
        Alignment = taRightJustify
        TabOrder = 2
        Text = '5.75'
      end
      object edtTaxAmount: TEdit
        Left = 262
        Top = 64
        Width = 107
        Height = 21
        Alignment = taRightJustify
        TabOrder = 3
        Text = '0.00'
      end
      object edtTotalOrder: TEdit
        Left = 262
        Top = 99
        Width = 107
        Height = 21
        Alignment = taRightJustify
        TabOrder = 4
        Text = '0.00'
      end
    end
    object GroupBox3: TGroupBox
      Left = 488
      Top = 29
      Width = 577
      Height = 196
      Caption = 'Parts Used'
      TabOrder = 9
      object Label15: TLabel
        Left = 32
        Top = 32
        Width = 50
        Height = 13
        Caption = 'Part Name'
      end
      object Label16: TLabel
        Left = 320
        Top = 32
        Width = 45
        Height = 13
        Caption = 'Unit Price'
      end
      object Label17: TLabel
        Left = 408
        Top = 32
        Width = 18
        Height = 13
        Caption = 'Qty'
      end
      object Label18: TLabel
        Left = 488
        Top = 32
        Width = 46
        Height = 13
        Caption = 'Sub-Total'
      end
      object edtPartName1: TEdit
        Left = 32
        Top = 51
        Width = 281
        Height = 21
        TabOrder = 0
      end
      object edtPartName2: TEdit
        Left = 32
        Top = 78
        Width = 281
        Height = 21
        TabOrder = 1
      end
      object edtPartName3: TEdit
        Left = 32
        Top = 105
        Width = 281
        Height = 21
        TabOrder = 2
      end
      object edtPartName4: TEdit
        Left = 32
        Top = 132
        Width = 281
        Height = 21
        TabOrder = 3
      end
      object edtPartName5: TEdit
        Left = 32
        Top = 159
        Width = 281
        Height = 21
        TabOrder = 4
      end
      object edtUnitPrice1: TEdit
        Left = 319
        Top = 51
        Width = 82
        Height = 21
        Alignment = taRightJustify
        TabOrder = 5
        Text = '0.00'
      end
      object edtUnitPrice2: TEdit
        Left = 319
        Top = 74
        Width = 82
        Height = 21
        Alignment = taRightJustify
        TabOrder = 6
        Text = '0.00'
      end
      object edtUnitPrice3: TEdit
        Left = 319
        Top = 101
        Width = 82
        Height = 21
        Alignment = taRightJustify
        TabOrder = 7
        Text = '0.00'
      end
      object edtUnitPrice4: TEdit
        Left = 319
        Top = 128
        Width = 82
        Height = 21
        Alignment = taRightJustify
        TabOrder = 8
        Text = '0.00'
      end
      object edtUnitPrice5: TEdit
        Left = 319
        Top = 155
        Width = 82
        Height = 21
        Alignment = taRightJustify
        TabOrder = 9
        Text = '0.00'
      end
      object edtQuantity1: TEdit
        Left = 407
        Top = 51
        Width = 50
        Height = 21
        Alignment = taRightJustify
        TabOrder = 10
        Text = '0'
      end
      object edtQuantity2: TEdit
        Left = 407
        Top = 74
        Width = 50
        Height = 21
        Alignment = taRightJustify
        TabOrder = 11
        Text = '0'
      end
      object edtQuantity3: TEdit
        Left = 407
        Top = 101
        Width = 50
        Height = 21
        Alignment = taRightJustify
        TabOrder = 12
        Text = '0'
      end
      object edtQuantity4: TEdit
        Left = 407
        Top = 128
        Width = 50
        Height = 21
        Alignment = taRightJustify
        TabOrder = 13
        Text = '0'
      end
      object edtQuantity5: TEdit
        Left = 407
        Top = 155
        Width = 50
        Height = 21
        Alignment = taRightJustify
        TabOrder = 14
        Text = '0'
      end
      object edtSubTotal1: TEdit
        Left = 471
        Top = 51
        Width = 82
        Height = 21
        Alignment = taRightJustify
        TabOrder = 15
        Text = '0.00'
      end
      object edtSubTotal2: TEdit
        Left = 471
        Top = 74
        Width = 82
        Height = 21
        Alignment = taRightJustify
        TabOrder = 16
        Text = '0.00'
      end
      object edtSubTotal3: TEdit
        Left = 471
        Top = 101
        Width = 82
        Height = 21
        Alignment = taRightJustify
        TabOrder = 17
        Text = '0.00'
      end
      object edtSubTotal4: TEdit
        Left = 471
        Top = 128
        Width = 82
        Height = 21
        Alignment = taRightJustify
        TabOrder = 18
        Text = '0.00'
      end
      object edtSubTotal5: TEdit
        Left = 471
        Top = 155
        Width = 82
        Height = 21
        Alignment = taRightJustify
        TabOrder = 19
        Text = '0.00'
      end
    end
    object GroupBox4: TGroupBox
      Left = 488
      Top = 231
      Width = 577
      Height = 186
      Caption = 'Jobs Performed'
      TabOrder = 10
      object Label19: TLabel
        Left = 24
        Top = 28
        Width = 73
        Height = 13
        Caption = 'Job Description'
      end
      object Label20: TLabel
        Left = 464
        Top = 28
        Width = 42
        Height = 13
        Caption = 'Job Cost'
      end
      object edtJobDescription2: TEdit
        Left = 24
        Top = 74
        Width = 417
        Height = 21
        TabOrder = 0
      end
      object edtJobDescription3: TEdit
        Left = 24
        Top = 101
        Width = 417
        Height = 21
        TabOrder = 1
      end
      object edtJobDescription4: TEdit
        Left = 24
        Top = 128
        Width = 417
        Height = 21
        TabOrder = 2
      end
      object edtJobDescription5: TEdit
        Left = 24
        Top = 155
        Width = 417
        Height = 21
        TabOrder = 3
      end
      object edtJobDescription1: TEdit
        Left = 24
        Top = 47
        Width = 417
        Height = 21
        TabOrder = 4
      end
      object edtJobCost1: TEdit
        Left = 455
        Top = 47
        Width = 65
        Height = 21
        Alignment = taRightJustify
        TabOrder = 5
        Text = '0.00'
      end
      object edtJobCost2: TEdit
        Left = 455
        Top = 70
        Width = 65
        Height = 21
        Alignment = taRightJustify
        TabOrder = 6
        Text = '0.00'
      end
      object edtJobCost3: TEdit
        Left = 455
        Top = 97
        Width = 65
        Height = 21
        Alignment = taRightJustify
        TabOrder = 7
        Text = '0.00'
      end
      object edtJobCost4: TEdit
        Left = 455
        Top = 124
        Width = 65
        Height = 21
        Alignment = taRightJustify
        TabOrder = 8
        Text = '0.00'
      end
      object edtJobCost5: TEdit
        Left = 455
        Top = 151
        Width = 65
        Height = 21
        Alignment = taRightJustify
        TabOrder = 9
        Text = '0.00'
      end
    end
    object GroupBox5: TGroupBox
      Left = 17
      Top = 423
      Width = 1048
      Height = 174
      Caption = 'Recommendations'
      TabOrder = 11
    end
  end
end
