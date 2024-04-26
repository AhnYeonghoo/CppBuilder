//---------------------------------------------------------------------------

#include <vcl.h>
#include <string>
#pragma hdrstop

#include "Unit3.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm3 *Form3;
//---------------------------------------------------------------------------
__fastcall TForm3::TForm3(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm3::InfoBtnClick(TObject *Sender)
{
	int port = StrToInt(Port->Text);
	ClientSocket->Address = SerIP->Text;
	ClientSocket->Port = port;
	ClientSocket->Active = true;

	if (ServerSocket->OnClientConnect)
	{
		ChatList->Lines->Add("서버와 연결 오류");
	}
	else
	{
		ChatList->Lines->Add("서버와 연결 성공");
		ChatList->Lines->Add(UserID->Text + "님이 입장하였습니다.");
	}
}

void __fastcall TForm3::EchoWrite(TObject *Sender, TCustomWinSocket *Socket)
{
	String receivedData = Socket->ReceiveText();
	for (int i = 0; i < ServerSocket->Socket->ActiveConnections; i++)
	{
		TCustomWinSocket* clientSocket = ServerSocket->Socket->Connections[i];
		clientSocket->SendText(receivedData);
	}
}
//---------------------------------------------------------------------------


void __fastcall TForm3::TranBtnClick(TObject *Sender)
{
	String ServText = ChatEdit->Text;
	ClientSocket->Socket->SendText(UserID->Text + ": " + ServText);
}
//---------------------------------------------------------------------------


void __fastcall TForm3::ClientSocketRead(TObject* Sender, TCustomWinSocket* Socket)
{
	String receivedData = Socket->ReceiveText();
	ChatList->Lines->Add(receivedData);

}

void __fastcall TForm3::SelBtnClick(TObject *Sender)
{
	if (ComboBox1->Text == "Server")
	{
		ServerSocket->Active = true;
		ChatList->Lines->Add("서버 열기 성공");
    }
}
//---------------------------------------------------------------------------
