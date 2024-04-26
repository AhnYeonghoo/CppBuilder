//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label1;
	TLabel *Label2;
	TLabel *Label3;
	TEdit *studentNumber;
	TEdit *studentName;
	TEdit *studentAge;
	TButton *addButton;
	TEdit *confirmStudentNumber;
	TLabel *Label4;
	TButton *Delete;
	TListBox *ListBox1;
	void __fastcall Label1Click(TObject *Sender);
	void __fastcall studentNumberChange(TObject *Sender);
	void __fastcall DeleteClick(TObject *Sender);
	void __fastcall addButtonClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
