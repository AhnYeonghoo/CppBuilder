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
// 바른전자 MES Command 지정
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

// 	변수 지정자
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

// 에러코드
const int ERRCODE_NO_LOTID				= 1000;	// 해당 LOT ID 없음
const int ERRCODE_NO_RECIPE				= 1001;	// 해당 RECIPE 없음
const int ERRCODE_NO_WORKID				= 1002;	// 해당 작업지시서 없음
const int ERRCODE_NO_OPERATIONID		= 1003;	// 해당 공정 없음
const int ERRCODE_NO_USERID				= 1004;	// 해당 사용자 없음
const int ERRCODE_NO_LOTS				= 1005; // SCAN된 LOT이 없음
const int ERRCODE_RUNNING_LOT			= 1006; // 현재 진행 중
const int ERRCODE_DUP_LOT				= 1007; // 중복 LOT
const int ERRCODE_DUP_COMMAND			= 1008; // 중복 명령

const int ERRCODE_MES_DB_ERROR			= 3000; // MES 데이터베이스 오류
const int ERRCODE_RETRY_DATA			= 5000;	// 재전송 요구
const int ERRCODE_DUP_CONNECT			= 5001;	// 중복 접속에 의한 CLOSE
const int ERRCODE_WRONG_RECIPE			= -1000; // 이전 LOT로 전송 받은 레시피와 다름
const int ERRCODE_NO_RESPONSE			= -1001; // 응답 없음
const int ERRCODE_NOT_CONNECTED			= -1002; // MES 연결 상태가 아님
const int ERRCODE_MES_ERROR				= -1003; // MES 에러

const String ERRSTR_NO_LOTID			= L"해당 LOT이 존재하지 않습니다.";
const String ERRSTR_NO_RECIPE			= L"해당 RECIPE가 존재하지 않습니다.";
const String ERRSTR_NO_WORKID			= L"해당 작업지시서가 존재하지 않습니다.";
const String ERRSTR_NO_OPERATIONID		= L"해당 LOT은 OVEN[FCC01N] 공정의 LOT이 아닙니다.";
const String ERRSTR_NO_USERID			= L"해당 사용자가 존재하지 않습니다.";
const String ERRSTR_NO_LOTS				= L"SCAN된 LOT이 존재하지 않습니다.";
const String ERRSTR_RUNNING_LOT			= L"현재 진행 중입니다.";
const String ERRSTR_DUP_LOT				= L"중복된 LOT입니다.";
const String ERRSTR_DUP_COMMAND			= L"중복된 명령입니다.";
const String ERRSTR_MES_DB_ERROR		= L"MES 데이터베이스 오류";
const String ERRSTR_RETRY_DATA			= L"재전송 요구";
const String ERRSTR_DUP_CONNECT			= L"중복 접속에 의한 CLOSE";
const String ERRSTR_WRONG_RECIPE		= L"이전 LOT로 전송 받은 레시피와 다름";
const String ERRSTR_NO_RESPONSE			= L"응답 없음";
const String ERRSTR_NOT_CONNECTED		= L"MES 연결 상태가 아님";

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
