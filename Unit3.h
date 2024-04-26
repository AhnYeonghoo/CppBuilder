//---------------------------------------------------------------------------

#ifndef Unit3H
#define Unit3H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <System.Win.ScktComp.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
//---------------------------------------------------------------------------
class TForm3 : public TForm
{
__published:	// IDE-managed Components
	TComboBox *ComboBox1;
	TImage *Image1;
	TButton *SelBtn;
	TEdit *SerIP;
	TEdit *Port;
	TEdit *UserID;
	TButton *InfoBtn;
	TEdit *ChatEdit;
	TButton *TranBtn;
	TMemo *ChatList;
	TClientSocket *ClientSocket;
	TServerSocket *ServerSocket;
	void __fastcall InfoBtnClick(TObject *Sender);
	void __fastcall TranBtnClick(TObject *Sender);
	void __fastcall SelBtnClick(TObject *Sender);
	void __fastcall ClientSocketRead(TObject* Sender, TCustomWinSocket* Socket);
	void __fastcall EchoWrite(TObject *Sender, TCustomWinSocket *Socket);

private:	// User declarations
public:		// User declarations
	__fastcall TForm3(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------
#endif
