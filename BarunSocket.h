//---------------------------------------------------------------------------

#ifndef BarunSocketH
#define BarunSocketH
//---------------------------------------------------------------------------
#include <System.Win.ScktComp.hpp>
#include <System.SyncObjs.hpp>
#include <map>
#include <memory>
#include "Web.Win.Sockets.hpp"

#include "Defines.h"

enum SOCKETTYPE { ALIVE_SOCKET = 0, COMMAND_SOCKET, ALARM_SOCKET, SOCKETTYPE_COUNT };
// �ٸ����� MES Command ����
enum {  CMD_BIND = 0, CMD_ALIVE, CMD_ALARM, CMD_LOTSCAN, CMD_LOTSCAN_DEL, CMD_LOTSCAN_CANCEL, CMD_LOTSTART, CMD_LOTEND, CMD_COUNT };
typedef enum { RCVRESULT_WAIT = 0, RCVRESULT_OK, RCVRESULT_NG, RCVRESULT_WRONG_RECIPE } RCVRESULT;

const AnsiString CMDSTR_BIND			= "Bind";
const AnsiString CMDSTR_ALIVE			= "Alive";
const AnsiString CMDSTR_ALARM			= "Error";
const AnsiString CMDSTR_LOTSCAN			= "LOT_SCAN";
const AnsiString CMDSTR_LOTSCAN_DEL		= "LOT_SCAN_DEL";
const AnsiString CMDSTR_LOTSCAN_CANCEL	= "LOT_SCAN_CANCEL";
const AnsiString CMDSTR_LOTSTART		= "LOT_START";
const AnsiString CMDSTR_LOTEND			= "LOT_END";

// 	���� ������
const AnsiString ID_IP					= "IP";
const AnsiString ID_COMMAND				= "CMD";
const AnsiString ID_LOT					= "Lot";
const AnsiString ID_INFO				= "Info";
const AnsiString ID_USERID				= "USER_ID";
const AnsiString ID_RESULT				= "Result";
const AnsiString ID_LOC					= "Loc";
const AnsiString ID_TYPE				= "Type";
const AnsiString ID_ID					= "ID";
const AnsiString ID_ERROR				= "ERROR";
const AnsiString ID_RECIPECD			= "RECIPE_CD";

const AnsiString RECV_ID_IP				= "IP";
const AnsiString RECV_ID_COMMAND		= "CMD";
const AnsiString RECV_ID_LOT			= "LOT";
const AnsiString RECV_ID_INFO			= "INFO";
const AnsiString RECV_ID_USERID			= "USER_ID";
const AnsiString RECV_ID_RESULT			= "RESULT";
const AnsiString RECV_ID_LOC			= "LOC";
const AnsiString RECV_ID_TYPE			= "TYPE";
const AnsiString RECV_ID_ID				= "ID";
const AnsiString RECV_ID_ERRORCODE		= "ERRORCODE";
const AnsiString RECV_ID_ERRORTEXT		= "ERRORTEXT";
const AnsiString RECV_ID_RECIPECD		= "RECIPE_CD";

// �����ڵ�
const int ERRCODE_NO_LOTID				= 1000;	// �ش� LOT ID ����
const int ERRCODE_NO_RECIPE				= 1001;	// �ش� RECIPE ����
const int ERRCODE_NO_WORKID				= 1002;	// �ش� �۾����ü� ����
const int ERRCODE_NO_OPERATIONID		= 1003;	// �ش� ���� ����
const int ERRCODE_NO_USERID				= 1004;	// �ش� ����� ����
const int ERRCODE_NO_LOTS				= 1005; // SCAN�� LOT�� ����
const int ERRCODE_RUNNING_LOT			= 1006; // ���� ���� ��
const int ERRCODE_DUP_LOT				= 1007; // �ߺ� LOT
const int ERRCODE_DUP_COMMAND			= 1008; // �ߺ� ���

const int ERRCODE_MES_DB_ERROR			= 3000; // MES �����ͺ��̽� ����
const int ERRCODE_RETRY_DATA			= 5000;	// ������ �䱸
const int ERRCODE_DUP_CONNECT			= 5001;	// �ߺ� ���ӿ� ���� CLOSE
const int ERRCODE_WRONG_RECIPE			= -1000; // ���� LOT�� ���� ���� �����ǿ� �ٸ�
const int ERRCODE_NO_RESPONSE			= -1001; // ���� ����
const int ERRCODE_NOT_CONNECTED			= -1002; // MES ���� ���°� �ƴ�
const int ERRCODE_MES_ERROR				= -1003; // MES ����

const String ERRSTR_NO_LOTID			= L"�ش� LOT�� �������� �ʽ��ϴ�.";
const String ERRSTR_NO_RECIPE			= L"�ش� RECIPE�� �������� �ʽ��ϴ�.";
const String ERRSTR_NO_WORKID			= L"�ش� �۾����ü��� �������� �ʽ��ϴ�.";
const String ERRSTR_NO_OPERATIONID		= L"�ش� LOT�� OVEN[FCC01N] ������ LOT�� �ƴմϴ�.";
const String ERRSTR_NO_USERID			= L"�ش� ����ڰ� �������� �ʽ��ϴ�.";
const String ERRSTR_NO_LOTS				= L"SCAN�� LOT�� �������� �ʽ��ϴ�.";
const String ERRSTR_RUNNING_LOT			= L"���� ���� ���Դϴ�.";
const String ERRSTR_DUP_LOT				= L"�ߺ��� LOT�Դϴ�.";
const String ERRSTR_DUP_COMMAND			= L"�ߺ��� ����Դϴ�.";
const String ERRSTR_MES_DB_ERROR		= L"MES �����ͺ��̽� ����";
const String ERRSTR_RETRY_DATA			= L"������ �䱸";
const String ERRSTR_DUP_CONNECT			= L"�ߺ� ���ӿ� ���� CLOSE";
const String ERRSTR_WRONG_RECIPE		= L"���� LOT�� ���� ���� �����ǿ� �ٸ�";
const String ERRSTR_NO_RESPONSE			= L"���� ����";
const String ERRSTR_NOT_CONNECTED		= L"MES ���� ���°� �ƴ�";

extern const AnsiString BarunMESCommand[CMD_COUNT];

typedef struct _BARUN_COMMAND
{
	bool Resend;
	int CommandType;
	int ChamberID;
	AnsiString LotID;
	AnsiString Info;
	AnsiString UserID;
	AnsiString AlarmCode;

	void __fastcall Empty()
	{
		Resend = false;
		CommandType = -1;
		LotID = "";
		Info = "";
		UserID = "";
		AlarmCode = "";
	}
} BARUN_COMMAND;

typedef struct __BARUN_RESULT
{
	bool Result;
	int ErrorCode;
	AnsiString Received;
	AnsiString ReceivedRecipeName;
	String Error;
} BARUN_RESULT;

typedef struct __MESSAGE_FORMAT
{
	__int64 Length;
	AnsiString Message;
	std::map<AnsiString, AnsiString> DecodedData;

	void __fastcall Empty()
	{
		Length = 0;
		Message = "";
		DecodedData.clear();
	}
	bool __fastcall IsValid()
	{
		if( Message.IsEmpty() )
			return false;
		if( Length < 0 )
			return false;
//		if( Length != Message.Length() )
//			return false;

		return true;
	}
} MESSAGE_FORMAT;
//---------------------------------------------------------------------------

class TSocketReadThread : public TThread
{
private:
	bool *FConnected;

//	TTcpClient *FClientSocket;
	TClientSocket *FClientSocket;
	std::shared_ptr<TCriticalSection> CSLock;

	void SetConnected(bool *bVal)		{ FConnected = bVal; }
//	void SetClient(TTcpClient *IdVal)	{ FClientSocket = IdVal; }
	void SetClient(TClientSocket *IdVal)	{ FClientSocket = IdVal; }

public:
	TSocketReadThread(bool CreateSuspended)
		:TThread(CreateSuspended)
	{
		CSLock = std::shared_ptr<TCriticalSection> (new TCriticalSection());
	}
	__fastcall ~TSocketReadThread()
	{
	}

	void __fastcall Execute();
	__property bool* Connected = { read = FConnected, write = SetConnected };
	__property TTcpClient* ClientSocket = { read = FClientSocket, write = SetClient };
};
// ---------------------------------------------------------------------------
typedef std::shared_ptr<TSocketReadThread> SocketReadPtr;
// ---------------------------------------------------------------------------
#define RECV_BUFFER_SIZE	8192
class NormalOvenChamber;
class BarunSocket
{
private:
	NormalOvenChamber *MyChamber;
	int SocketType;

//	TTcpClient *Socket;
    TClientSocket *Socket;
	TTimer *CheckConnectedTimer;
	TTimer *CheckBindedTimer;
	TTimer *RetryConnectTimer;
	TTimer *ResendTimer;
	TTimer *AliveTimer;
	TTimer *BindTimer;
	SocketReadPtr ReadThread;
	int ConnectTryCnt;
	int BindTryCnt;

	MESSAGE_FORMAT RxData, TxData;
	BARUN_COMMAND Command;
	BARUN_COMMAND SendedCommand;
	int ReceivedResult;
	bool IsTransfering;
	bool DoNotRetryConnect;

	bool FirstData;
	int FullDataLength;
	AnsiString ReceivedRecipe;
	AnsiString ReceivedRecipeName;

	char RecvBuffer[RECV_BUFFER_SIZE];
	int RecvLength;

	void __fastcall OnCheckConnectedTimer(TObject *Sender);
	void __fastcall OnCheckBindedTimer(TObject *Sender);
	void __fastcall OnRetryConnectTimer(TObject *Sender);
	void __fastcall OnResendTimer(TObject *Sender);
	void __fastcall OnAliveTimer(TObject *Sender);
	void __fastcall OnBindTimer(TObject *Sender);

	void __fastcall OnSocketConnect(TObject *Sender);
	void __fastcall OnSocketDisconnect(TObject *Sender);
	void __fastcall OnSocketReceive(TObject *Sender, char *Buf, int &DataLen);
	void __fastcall OnSocketSend(TObject* Sender, char *Buf, int &DataLen);
	void __fastcall OnSocketError(TObject *Sender, int SocketError);

	void SendToHost();
	void DecodeRxMsg();
	void DoActionWithRx();
	bool IsReceivedOK();
	bool IsReceivedResend();
	BARUN_RESULT WaitAck();

public:
	BarunSocket(NormalOvenChamber* chamber, int socketType);
	~BarunSocket();

	bool Connected;
	bool Binded;
	unsigned int AliveCounter;
	AnsiString MachineID;

	void ConnectHost();
	void DisconnectHost();
	AnsiString MakeupTxData(int command, bool test=false);
	BARUN_RESULT SendCommand(BARUN_COMMAND command);
};
// ---------------------------------------------------------------------------
typedef std::shared_ptr<BarunSocket> SocketManagerPtr;
// ---------------------------------------------------------------------------

#endif
