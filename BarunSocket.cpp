//---------------------------------------------------------------------------
#include <System.DateUtils.hpp>

#pragma hdrstop

#include "BarunSocket.h"
#include "NormalOvenChamber.h"
#include "Database.h"
#include "BarunMES.h"
#include "HelperFunctions.h"
//---------------------------------------------------------------------------

//#pragma link "inetwinsockets.lib"

#pragma package(smart_init)

#define MAX_RETRY_COUNT	10

const AnsiString BarunMESCommand[CMD_COUNT] =
{
	CMDSTR_BIND,
	CMDSTR_ALIVE,
	CMDSTR_ALARM,
	CMDSTR_LOTSCAN,
	CMDSTR_LOTSCAN_DEL,
	CMDSTR_LOTSCAN_CANCEL,
	CMDSTR_LOTSTART,
	CMDSTR_LOTEND
};

String SocketTypeString[SOCKETTYPE_COUNT] =
{
	"Alive Socket",
	"Command Socket",
	"Error Socket"
};

void __fastcall TSocketReadThread::Execute()
{
	while (!Terminated)
	{
		// 2023-01-10 임시제거
//		if( ClientSocket->WaitForData(100) )
		{
			CSLock->Acquire();
			// 2023-01-10 임시제거
//			ClientSocket->Receiveln("\r\n");
			CSLock->Release();
		}
		WaitForSingleObject((void*)Handle, 100);
	}
}
//---------------------------------------------------------------------------
BarunSocket::BarunSocket(NormalOvenChamber* chamber, int socketType)
	: MyChamber(chamber), SocketType(socketType)
{
//	Socket = new TTcpClient(nullptr);
	Socket = new TClientSocket(nullptr);
	CheckConnectedTimer = new TTimer(nullptr);
	CheckBindedTimer = new TTimer(nullptr);
	RetryConnectTimer = new TTimer(nullptr);
	ResendTimer = new TTimer(nullptr);
	AliveTimer = new TTimer(nullptr);
	BindTimer = new TTimer(nullptr);

	Socket->Active = false;

	CheckConnectedTimer->Enabled = false;
	CheckConnectedTimer->Interval = 1000;

	CheckBindedTimer->Enabled = false;
	CheckBindedTimer->Interval = 2000;

	RetryConnectTimer->Enabled = false;
	RetryConnectTimer->Interval = 10000;

	ResendTimer->Enabled = false;
	ResendTimer->Interval = 1000;

	AliveTimer->Enabled = false;
	AliveTimer->Interval = 60000;

	BindTimer->Enabled = false;
	BindTimer->Interval = 1000;

	// 2023-01-10 임시제거
//	Socket->OnConnect = OnSocketConnect;
//	Socket->OnDisconnect = OnSocketDisconnect;
//	Socket->OnSend = OnSocketSend;
//	Socket->OnReceive = OnSocketReceive;
//	Socket->OnError = OnSocketError;

	CheckConnectedTimer->OnTimer = OnCheckConnectedTimer;
	CheckBindedTimer->OnTimer = OnCheckBindedTimer;
	RetryConnectTimer->OnTimer = OnRetryConnectTimer;
	ResendTimer->OnTimer = OnResendTimer;
	AliveTimer->OnTimer = OnAliveTimer;
	BindTimer->OnTimer = OnBindTimer;

	ConnectTryCnt = 0;
	BindTryCnt = 0;
	IsTransfering = false;
	Connected = false;

	AliveCounter = 0;
	Binded = false;
	DoNotRetryConnect = false;
}
//---------------------------------------------------------------------------
__fastcall BarunSocket::~BarunSocket()
{
	if( Socket )
	{
		// 2023-01-10 임시제거
//		Socket->Disconnect();
		delete Socket;
	}
	if( CheckConnectedTimer )
		delete CheckConnectedTimer;
	if( CheckBindedTimer )
		delete CheckBindedTimer;
	if( RetryConnectTimer )
		delete RetryConnectTimer;
	if( ResendTimer )
		delete ResendTimer;
	if( AliveTimer )
		delete AliveTimer;
	if( BindTimer )
		delete BindTimer;
}
//---------------------------------------------------------------------------
void __fastcall BarunSocket::OnSocketConnect(TObject *Sender)
{
	if( CheckConnectedTimer->Enabled == false )
		CheckConnectedTimer->Enabled = true;

	String str;
	str.sprintf(L"[Chamber %c] %s Connected", MyChamber->ChamberID + 'A', SocketTypeString[SocketType].c_str());
	GetOvenDB()->SaveLog(str, MESSAGES, MyChamber->ChamberID);
}
//---------------------------------------------------------------------------
void __fastcall BarunSocket::OnSocketDisconnect(TObject *Sender)
{
	Connected = false;
	Binded = false;
	IsTransfering = false;
	BindTryCnt = 0;
	ConnectTryCnt = 0;

	if( ReadThread )
	{
		ReadThread->Terminate();
		Sleep(100);
	}

	RxData.Empty();
	TxData.Empty();

	String str;
	str.sprintf(L"[Chamber %c] %s Disconnected", MyChamber->ChamberID + 'A', SocketTypeString[SocketType].c_str());
	GetOvenDB()->SaveLog(str, MESSAGES, MyChamber->ChamberID);

	if( BarunMESDlg->CimParam.AutoConnection &&
		DoNotRetryConnect == false )
		RetryConnectTimer->Enabled = true;

	DoNotRetryConnect = false;
}
//---------------------------------------------------------------------------
String ConvertMultibyteToUnicode(char* pMultibyte, int nLen)
{
//	int nLen = strlen(pMultibyte);

	WCHAR *pWideChar = new WCHAR[nLen];
	memset(pWideChar, 0x00, (nLen)*sizeof(WCHAR));

	MultiByteToWideChar(CP_ACP, 0, (LPCSTR)pMultibyte, -1, pWideChar, nLen);

	String strUnicode;
	strUnicode.sprintf(L"%s", pWideChar);

	delete [] pWideChar;

	return strUnicode;
}

void BarunSocket::OnSocketReceive(TObject *Sender, char *Buf, int &DataLen)
{
	try
	{
		unsigned int header[2]  = { 0, };
		char *dest = (char*)&header;
		char *src = (char*)Buf;

		for(int i=7; i>=0; i--)
		{
			*dest = *(src+i);
			dest++;
		}

		if( header[1] == 0 )
		{
			FirstData = true;
			FullDataLength = header[0];
		}
		else
			FirstData = false;

		if( FirstData )
		{
			RecvLength = DataLen - 8;
			ZeroMemory(RecvBuffer, RECV_BUFFER_SIZE);
			memcpy(RecvBuffer, Buf+8, DataLen-8);
		}
		else
		{
			memcpy(RecvBuffer+RecvLength, Buf, DataLen);
			RecvLength += DataLen;
        }

		// 데이터를 다 받음
		if( RecvLength == FullDataLength )
		{
			RxData.Length = FullDataLength;

			// UTF-8 --> 유니코드로 디코딩
			wchar_t strUnicode[RECV_BUFFER_SIZE] = {0,};
			int nLen = 	MultiByteToWideChar(CP_UTF8, 0, RecvBuffer, strlen(RecvBuffer), NULL, NULL);
			nLen = 		MultiByteToWideChar(CP_UTF8, 0, RecvBuffer, strlen(RecvBuffer), strUnicode, nLen);
			RxData.Message = strUnicode;

			TReplaceFlags Flags = TReplaceFlags() << rfReplaceAll;
			RxData.Message = StringReplace(RxData.Message, " ", "@", Flags);
			RxData.Message = StringReplace(RxData.Message, ",", "$", Flags);

			if( RxData.IsValid() )
			{
				if( SendedCommand.CommandType != CMD_ALIVE )
				{
					String str, myInfo;

					myInfo.sprintf(L"[Chamber %c %s]", MyChamber->ChamberID + 'A', SocketTypeString[SocketType].c_str());
					str = "[HOST->OVEN] " + RxData.Message;
					GetOvenDB()->SaveLog(myInfo + str, MESSAGES, MyChamber->ChamberID);
				}

				DecodeRxMsg();
				DoActionWithRx();

				IsTransfering = false;
				return;
			}
		}
	}
	catch(...)
	{
		return;
	}
}
//---------------------------------------------------------------------------
void BarunSocket::OnSocketSend(TObject* Sender, char *Buf, int &DataLen)
{
	IsTransfering = true;
}
//---------------------------------------------------------------------------
void BarunSocket::OnSocketError(TObject *Sender, int SocketError)
{
	String log, msg, myInfo;
	String section = "TCPIP Error";

	myInfo.sprintf(L"[Chamber %c %s] ", MyChamber->ChamberID + 'A', SocketTypeString[SocketType].c_str());
	switch (SocketError)
	{
	case 10022:	// WSAEINVAL
		msg = GetResStr(section, "WSAEINVAL");
//		Connected = false;
		break;
	case 10035:	// WSAEWOULDBLOCK
		msg = GetResStr(section, "WSAEWOULDBLOCK");
//		Connected = false;
		break;
	case 10038:	// WSAENOTSOCK
		msg = GetResStr(section, "WSAENOTSOCK");
//		Connected = false;
		break;
	case 10054: // WSAECONNRESET
		msg = GetResStr(section, "WSAECONNRESET");
//		Connected = false;
		break;
	case 10056: // WSAEISCONN
		msg = GetResStr(section, "WSAEISCONN");
		break;
	case 10060:	// WSAETIMEDOUT
		msg = GetResStr(section, "WSAETIMEDOUT");
//		Connected = false;
		break;
	case 10061:	// WSAECONNREFUSED
		msg = GetResStr(section, "WSAECONNREFUSED");
//		Connected = false;
		break;
	default:
		msg = "Socket Error : " + IntToStr(SocketError);
//		Connected = false;
		break;
	}

/*	if( Connected == false )
	{
		Connected = false;
		Binded = false;
		IsTransfering = false;
		BindTryCnt = 0;
		ConnectTryCnt = 0;

		if( BarunMESDlg->CimParam.AutoConnection )
			RetryConnectTimer->Enabled = true;
	} */

	log = myInfo + msg;
	GetOvenDB()->SaveLog(log, MESSAGES, MyChamber->ChamberID);
}
//---------------------------------------------------------------------------
void BarunSocket::OnCheckConnectedTimer(TObject *Sender)
{
	// 2023-01-10 임시제거
//	if( Socket->Connected )
	if (true)
	{
		CheckConnectedTimer->Enabled = false;

		ReadThread  = SocketReadPtr(new TSocketReadThread(false) );
		ReadThread->ClientSocket = Socket;
		ReadThread->Connected = &Connected;

		Connected = true;

		if( SocketType == ALIVE_SOCKET )
		{
			BindTimer->Enabled = true;
        }
	}
	else
	{
		ConnectTryCnt++;
		if( ConnectTryCnt >= 5 )
		{
			ConnectTryCnt = 0;
			CheckConnectedTimer->Enabled = false;

			String str;
			str.sprintf(L"[Chamber %c] %s Connection Timeout", MyChamber->ChamberID + 'A', SocketTypeString[SocketType].c_str());
			GetOvenDB()->SaveLog(str, MESSAGES, MyChamber->ChamberID);

			SetMessageStr(str);
			ShowMessageDlg();
		}
	}
}
//---------------------------------------------------------------------------
void BarunSocket::OnCheckBindedTimer(TObject *Sender)
{
	CheckBindedTimer->Enabled = false;

	if( Binded == false )
	{
		BindTryCnt++;
		if( BindTryCnt >= 5 )
		{
			BindTryCnt = 0;

			String str;
			str.sprintf(L"[Chamber %c] %s Binding Timeout", MyChamber->ChamberID + 'A', SocketTypeString[SocketType].c_str());
			GetOvenDB()->SaveLog(str, MESSAGES, MyChamber->ChamberID);

			SetMessageStr(str);
			ShowMessageDlg();
		}
		else
			BindTimer->Enabled = true;
	}
}
//---------------------------------------------------------------------------
void BarunSocket::OnRetryConnectTimer(TObject *Sender)
{
	RetryConnectTimer->Enabled = false;

/*	if( Socket->Connected ||
		IsTransfering )
	{
		return;
	}*/

	DoNotRetryConnect = true;
	// 2023-01-10 임시제거
//	Socket->Disconnect();

	Connected = false;
	Binded = false;
	IsTransfering = false;
	BindTryCnt = 0;
	ConnectTryCnt = 0;

	ConnectHost();
}
//---------------------------------------------------------------------------
void BarunSocket::OnResendTimer(TObject *Sender)
{
	ResendTimer->Enabled = false;
	SendCommand(SendedCommand);
}
//---------------------------------------------------------------------------
void __fastcall BarunSocket::OnAliveTimer(TObject *Sender)
{
	AliveTimer->Enabled = false;

	if( SocketType != ALIVE_SOCKET )
		return;

	Command.Empty();
	Command.CommandType = CMD_ALIVE;
	SendCommand(Command);
	AliveTimer->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall BarunSocket::OnBindTimer(TObject *Sender)
{
	BindTimer->Enabled = false;

	if( SocketType != ALIVE_SOCKET )
		return;

	Command.Empty();
	Command.CommandType = CMD_BIND;
	SendCommand(Command);

	if( CheckBindedTimer->Enabled == false )
		CheckBindedTimer->Enabled = true;
}
//---------------------------------------------------------------------------
void BarunSocket::ConnectHost()
{
	if( BarunMESDlg->CimParam.OnlineMode == false )
		return;

	// 2023-01-10 임시제거
//	Socket->RemoteHost = BarunMESDlg->CimParam.HostIP;
//	Socket->RemotePort = BarunMESDlg->CimParam.Port;
//	Socket->BlockMode  = bmBlocking;
//
//	if( Socket->Connected == false )
//	{
//		try
//		{
//			Socket->Connect();
//		}
//		catch (Exception* e)
//		{
//			GetOvenDB()->SaveLog(e->Message, MESSAGES, MyChamber->ChamberID);
//			e->Message = "";
//		}
//	}
}
//---------------------------------------------------------------------------
void BarunSocket::DisconnectHost()
{
	// 2023-01-10 임시제거
//	try
//	{
//		Socket->Disconnect();
//	}
//	catch (Exception* e)
//	{
//		GetOvenDB()->SaveLog(e->Message, MESSAGES, MyChamber->ChamberID);
//		e->Message = "";
//	}
}
//---------------------------------------------------------------------------
BARUN_RESULT BarunSocket::SendCommand(BARUN_COMMAND command)
{
	RxData.Empty();

	Command = command;
	SendedCommand = Command;
	ReceivedResult = RCVRESULT_WAIT;

	if( Command.CommandType == CMD_LOTEND ||
		Command.CommandType == CMD_LOTSCAN_CANCEL )
		ReceivedRecipe = "";

	MakeupTxData(Command.CommandType);
	SendToHost();
	return WaitAck();
}
//---------------------------------------------------------------------------
void BarunSocket::SendToHost()
{
	switch( Command.CommandType )
	{
	case CMD_BIND:
	case CMD_ALIVE:
		if( Connected )
		{
			String str, myInfo;
			AnsiString length, sendData;
			std::shared_ptr<TStringStream> tmpStream(new TStringStream(str));

			IsTransfering = true;

			length.sprintf("%08d", TxData.Length);
			sendData = length + TxData.Message;
			tmpStream->Write((void*)sendData.c_str(), sendData.Length());
			tmpStream->Seek(0, soFromBeginning);

			Socket->Active = true;
			// 2023-01-10 임시제거
//			Socket->SendStream(tmpStream.get());

			if( Command.CommandType != CMD_ALIVE )
			{
				if( Command.Resend )
					str ="[OVEN->HOST][RESEND] " + TxData.Message;
				else
					str ="[OVEN->HOST] " + TxData.Message;
				myInfo.sprintf(L"[Chamber %c %s]", MyChamber->ChamberID + 'A', SocketTypeString[SocketType].c_str());
				GetOvenDB()->SaveLog(myInfo + str, MESSAGES, MyChamber->ChamberID);
			}
		}
		break;

	case CMD_ALARM:
	case CMD_LOTSCAN:
	case CMD_LOTSCAN_DEL:
	case CMD_LOTSCAN_CANCEL:
	case CMD_LOTSTART:
	case CMD_LOTEND:
		if( Connected )
		{
			String str, myInfo;
			AnsiString length, sendData;
			std::shared_ptr<TStringStream> tmpStream(new TStringStream(str));

			IsTransfering = true;

			length.sprintf("%08d", TxData.Length);
			sendData = length + TxData.Message;
			tmpStream->Write((void*)sendData.c_str(), sendData.Length());
			tmpStream->Seek(0, soFromBeginning);

			Socket->Active = true;
			// 2023-01-10 임시제거
//			Socket->SendStream(tmpStream.get());

			if( Command.Resend )
				str ="[OVEN->HOST][RESEND] " + TxData.Message;
			else
				str ="[OVEN->HOST] " + TxData.Message;
			myInfo.sprintf(L"[Chamber %c %s]", MyChamber->ChamberID + 'A', SocketTypeString[SocketType].c_str());
			GetOvenDB()->SaveLog(myInfo + str, MESSAGES, MyChamber->ChamberID);
		}
		break;
	}
}
//---------------------------------------------------------------------------
const AnsiString LOC  = "BARUN1";
const AnsiString TYPE = "EQUIPMENT";
AnsiString BarunSocket::MakeupTxData(int command, bool test/*=false*/)
{
	if( command < 0 )
		return "";

	AnsiString typeField, bodyField;

	if( command == CMD_BIND ||
		command == CMD_ALIVE )
	{

		// Make Type field
		typeField = ID_LOC + "=" + LOC + "&";
		typeField += ID_TYPE + "=" + TYPE + "&";
		typeField += ID_ID + "=" + MachineID;

		// Make Body field
		bodyField = "&" + ID_IP + "=" + BarunMESDlg->CimParam.HostIP;
		bodyField += "&" + ID_COMMAND + "=" + BarunMESCommand[Command.CommandType];
//		bodyField += "&" + ID_ERROR + "=" + AliveCommand.AlarmCode;
	}
	else
	{
		// Make Type field
		typeField = ID_LOC + "=" + LOC + "&";
		typeField += ID_TYPE + "=" + TYPE + "&";
		typeField += ID_ID + "=" + MachineID;

		// Make Body field
		switch( Command.CommandType )
		{
		case CMD_ALARM:
			bodyField = "&" + ID_IP + "=" + BarunMESDlg->CimParam.HostIP;
			bodyField += "&" + ID_COMMAND + "=" + BarunMESCommand[Command.CommandType];
			if( Command.UserID.IsEmpty() == false )
				bodyField += "&" + ID_USERID + "=" + Command.UserID;
			bodyField += "&" + ID_ERROR + "=" + Command.AlarmCode;
			break;

		case CMD_LOTSCAN:
		case CMD_LOTSCAN_DEL:
			bodyField = "&" + ID_IP + "=" + BarunMESDlg->CimParam.HostIP;
			bodyField += "&" + ID_COMMAND + "=" + BarunMESCommand[Command.CommandType];
			bodyField += "&" + ID_LOT + "=" + Command.LotID;
			if( Command.UserID.IsEmpty() == false )
				bodyField += "&" + ID_USERID + "=" + Command.UserID;
			break;

		case CMD_LOTSCAN_CANCEL:
			bodyField = "&" + ID_IP + "=" + BarunMESDlg->CimParam.HostIP;
			bodyField += "&" + ID_COMMAND + "=" + BarunMESCommand[Command.CommandType];
			if( Command.UserID.IsEmpty() == false )
				bodyField += "&" + ID_USERID + "=" + Command.UserID;
			break;

		case CMD_LOTSTART:
		case CMD_LOTEND:
			bodyField = "&" + ID_IP + "=" + BarunMESDlg->CimParam.HostIP;
			bodyField += "&" + ID_COMMAND + "=" + BarunMESCommand[Command.CommandType];
			if( Command.UserID.IsEmpty() == false )
				bodyField += "&" + ID_USERID + "=" + Command.UserID;
			break;
		}
	}

	AnsiString msg = typeField + bodyField;

	if( test == false )
	{
		TxData.Message = msg;
		TxData.Length = msg.Length();
	}

	return msg;
}
//---------------------------------------------------------------------------
void BarunSocket::DecodeRxMsg()
{
	try
	{
		TStringList *tmpList = new TStringList;
		AnsiString str = RxData.Message;

		TReplaceFlags Flags = TReplaceFlags() << rfReplaceAll;
		str = StringReplace(str, "&", ",", Flags);
		tmpList->CommaText = str;
		int count = tmpList->Count;

		if( SendedCommand.CommandType == CMD_LOTSCAN )
			int i=0;

		for(int i=0; i<count; i++)
		{
			AnsiString str = tmpList->Strings[i];
			AnsiString key, value;

			if( str.IsEmpty() )
				continue;

			int pos = str.Pos("=");
			if( pos < 1 )
				continue;

			key = str.SubString(1, pos-1);
			if( key.IsEmpty() )
				continue;

			key = key.UpperCase();
			value = str.SubString(pos+1, str.Length()-pos);
			if( value.IsEmpty() )
				value = " ";
			RxData.DecodedData[key] = value;
		}
		delete tmpList;
	}
	catch (Exception* e)
	{
		GetOvenDB()->SaveLog(e->Message, MESSAGES, MyChamber->ChamberID);
		e->Message = "";
	}
}
//---------------------------------------------------------------------------
void BarunSocket::DoActionWithRx()
{
	if( IsReceivedResend() )
	{
		Command.Resend = true;
		ResendTimer->Enabled = true;
		return;
	}

	AnsiString cmd = RxData.DecodedData[RECV_ID_COMMAND];

	if( BarunMESCommand[SendedCommand.CommandType] == cmd )
	{
		switch( SendedCommand.CommandType )
		{
		case CMD_ALIVE:
			if( IsReceivedOK() )
			{
				INC(AliveCounter);
				ReceivedResult = RCVRESULT_OK;
			}
			else
				ReceivedResult = RCVRESULT_NG;
			break;

		case CMD_BIND:
			if( IsReceivedOK() )
			{
				Binded = true;
				AliveTimer->Enabled = true;
				ReceivedResult = RCVRESULT_OK;
			}
			else
			{
				Binded = false;
				AliveCounter = 0;
				AliveTimer->Enabled = false;
				BindTimer->Enabled = true;
				ReceivedResult = RCVRESULT_NG;
			}
			break;

		case CMD_LOTSCAN:
			if( IsReceivedOK() )
			{
				TReplaceFlags Flags = TReplaceFlags() << rfReplaceAll;

				AnsiString recipeData = RxData.DecodedData[RECV_ID_INFO];

				ReceivedRecipeName = RxData.DecodedData[RECV_ID_RECIPECD];
				ReceivedRecipeName = StringReplace(ReceivedRecipeName, "@", " ", Flags);

				if( ReceivedRecipe.IsEmpty() )
					ReceivedRecipe = recipeData;
				else
				{
					if( ReceivedRecipe != recipeData )
					{
						ReceivedResult = RCVRESULT_WRONG_RECIPE;
						break;
                    }
				}

				ReceivedResult = RCVRESULT_OK;

				// 레시피를 파일로 저장
				recipeData = StringReplace(recipeData, "/", "\r\n", Flags);
				recipeData = StringReplace(recipeData, "#", "=", Flags);

				String strFile;
				strFile.sprintf(L"%s%s%c\\remote.ptn",
								GetRootFolder().c_str(),
								L"PATTERN_CM_",
								'A' + MyChamber->ChamberID);

				if( FileExists(strFile) )
					DeleteFile(strFile);

				AnsiString str = strFile;
				FILE *pFile;
				pFile = fopen(str.c_str(), "a+t");
				if( pFile == nullptr )
					return;
				std::fwrite(recipeData.c_str(), recipeData.Length(), 1, pFile);
				fclose(pFile);
			}
			else
			{
				ReceivedResult = RCVRESULT_NG;
			}
			break;

		case CMD_LOTSCAN_CANCEL:
			if( IsReceivedOK() )
			{
				ReceivedResult = RCVRESULT_OK;
				ReceivedRecipe = "";

				String strFile;
				strFile.sprintf(L"%s%s%c\\remote.ptn",
								GetRootFolder().c_str(),
								L"PATTERN_CM_",
								'A' + MyChamber->ChamberID);

				if( FileExists(strFile) )
					DeleteFile(strFile);
			}
			else
				ReceivedResult = RCVRESULT_NG;
			break;

		default:
			if( IsReceivedOK() )
				ReceivedResult = RCVRESULT_OK;
			else
				ReceivedResult = RCVRESULT_NG;
			break;
		}
	}
}
//---------------------------------------------------------------------------
bool BarunSocket::IsReceivedOK()
{
	AnsiString res = RxData.DecodedData[RECV_ID_RESULT];
	return res == "OK";
}
//---------------------------------------------------------------------------
bool BarunSocket::IsReceivedResend()
{
	AnsiString str = RxData.DecodedData[RECV_ID_ERRORCODE];

	if( str.IsEmpty() )
		return false;

	return str.ToInt() == ERRCODE_RETRY_DATA;
}
//---------------------------------------------------------------------------
BARUN_RESULT BarunSocket::WaitAck()
{
	BARUN_RESULT res;
	TDateTime start = Now();

	while( 1 )
	{
		if( ReceivedResult == RCVRESULT_OK )
		{
			res.Result = true;
			break;
		}
		else
		if( ReceivedResult == RCVRESULT_NG )
		{
			AnsiString str = RxData.DecodedData[RECV_ID_ERRORCODE];

			res.Result = false;

			if( IsValidInt(str) )
			{
				int error = str.ToInt();

				res.ErrorCode = error;
				res.Error = RxData.DecodedData[RECV_ID_ERRORTEXT];

				TReplaceFlags Flags = TReplaceFlags() << rfReplaceAll;
				res.Error = StringReplace(res.Error, "@", " ", Flags);
				res.Error = StringReplace(res.Error, "$", ",", Flags);

/*				switch( error )
				{
				case ERRCODE_RETRY_DATA:
					res.Error = ERRSTR_RETRY_DATA;
					break;
				case ERRCODE_DUP_CONNECT:
					res.Error = ERRSTR_DUP_CONNECT;
					break;
				case ERRCODE_NO_LOTID:
					res.Error = ERRSTR_NO_LOTID;
					break;
				case ERRCODE_NO_RECIPE:
					res.Error = ERRSTR_NO_RECIPE;
					break;
				case ERRCODE_NO_WORKID:
					res.Error = ERRSTR_NO_WORKID;
					break;
				case ERRCODE_NO_OPERATIONID:
					res.Error = ERRSTR_NO_OPERATIONID;
					break;
				case ERRCODE_NO_USERID:
					res.Error = ERRSTR_NO_USERID;
					break;
				case ERRCODE_NO_LOTS:
					res.Error = ERRSTR_NO_LOTS;
					break;
				case ERRCODE_RUNNING_LOT:
					res.Error = ERRSTR_RUNNING_LOT;
					break;
				case ERRCODE_DUP_LOT:
					res.Error = ERRSTR_DUP_LOT;
					break;
				case ERRCODE_DUP_COMMAND:
					res.Error = ERRSTR_DUP_COMMAND;
					break;
				case ERRCODE_MES_DB_ERROR:
					res.Error = ERRSTR_MES_DB_ERROR;
					break;
				} */
			}
			else
			{
				res.ErrorCode = ERRCODE_MES_ERROR;
				res.Error = str;
			}
			break;
		}
		else
		if( ReceivedResult == RCVRESULT_WRONG_RECIPE )
		{
			res.Result = false;
			res.ErrorCode = ERRCODE_WRONG_RECIPE;
			res.Error = ERRSTR_WRONG_RECIPE;
			break;
		}

		if( SecondsBetween(start, Now()) > 10 )
		{
			res.Result = false;
			res.ErrorCode = ERRCODE_NO_RESPONSE;
			res.Error = ERRSTR_NO_RESPONSE;
			break;
		}

		Application->ProcessMessages();
		Sleep(100);
	}

	res.Received = RxData.Message;
	res.ReceivedRecipeName = ReceivedRecipeName;

	return res;
}
//---------------------------------------------------------------------------
