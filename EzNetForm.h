//---------------------------------------------------------------------------

#ifndef EzNetFormH
#define EzNetFormH
//---------------------------------------------------------------------------
#include <time.h>
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "AdvPageControl.hpp"
#include <ComCtrls.hpp>
#include "AdvGrid.hpp"
#include "AdvObj.hpp"
#include "BaseGrid.hpp"
#include <Grids.hpp>
#include "AdvGlassButton.hpp"
#include <OleCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include "AdvEdit.hpp"
#include "AdvGroupBox.hpp"
#include "AdvOfficeButtons.hpp"
#include "AdvUtil.hpp"
#include "EZNETLib_OCX.h"

#include <memory>
#include "GEMDefines.h"
#include "Defines.h"
//---------------------------------------------------------------------------
typedef struct _GEMSTATE
{
	bool Started;
	bool Connected;
	bool Established;
	bool Enabled;
	int ControlState;
	int PrevControlState;
	int ProcessState;
	int PrevProcessState;

	_GEMSTATE()
	{
		Started = false;
		Connected = false;
		Established = false;
		Enabled = false;
		ControlState = 1;
		PrevControlState = 0;
		ProcessState = 0;
		PrevProcessState = 0;
	}
} GEMSTATE;

class NormalOvenChamber;
class TFmEzNet : public TForm
{
__published:	// IDE-managed Components
	TezNet *EzNet;
	TTimer *Refresh;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall EzNetMsgReceived(TObject *Sender, long lMsgId);
	void __fastcall EzNetOtherEvent(TObject *Sender, short nEventId, long lParm);
	void __fastcall RefreshTimer(TObject *Sender);
	void __fastcall EzNetConnected(TObject *Sender, OLECHAR *strHost, short nPort);
	void __fastcall EzNetDisconnected(TObject *Sender, OLECHAR *strHost, short nPort);



private:	// User declarations
	NormalOvenChamber *Chamber;
	bool IsEzNetConnected;

	WideString GetBstr(const String sVal) const;

	void __fastcall OnS2F41W(long lMsgId);   // Remote Command
	void __fastcall OnS10F3(long lMsgId);   // Terminal Message
	void __fastcall OnS7F1W(long lMsgId);
	void __fastcall OnS7F3W(long lMsgId);
	void __fastcall OnS7F5W(long lMsgId);
	void __fastcall OnS7F17W(long lMsgId);
	void __fastcall OnS7F19W(long lMsgId);
	void __fastcall OnS64F18(long lMsgId);

	void __fastcall Init();
	String __fastcall GetErrorCode(const short ret);

public:		// User declarations
	__fastcall TFmEzNet(TComponent* Owner, NormalOvenChamber *chamber);
	__fastcall ~TFmEzNet(void);

	GEMSTATE GemState;

	void __fastcall StartGEM();
	void __fastcall StopGEM();
	void __fastcall SetSVID(long svid[], String sVal[], int count);
	void __fastcall SetProcessState(int state);
	void __fastcall SetAlarm(int errCode);
	void __fastcall ClearAlarm(int errCode);
	void __fastcall ClearAlarmAll();
	void __fastcall SendEventReport(long CEID);

	void __fastcall UpdateSvidParam();
	void __fastcall UdpateGemState();
	void __fastcall SendBarcodeInfoEvent(String barcode);
	void __fastcall SendJobEndEvent(String lotid, String cstid, String ppid);
	void __fastcall SendJobStartedEvent(String lotid, String cstid, String ppid);
	void __fastcall SendJobStartFailEvent(String lotid, String cstid, String ppid);
	void __fastcall SendJobCancelEvent(String lotid, String cstid, String ppid);

	void __fastcall SendJobCancelFailEvent(String lotid, String cstid, String ppid);
	void __fastcall SendPPSelectedEvent(String ppid);
	void __fastcall SendPPChangedEvent(String ppid, int changeStatus);
	void __fastcall SendDoorEvent();
	// for JSCK EzNET
	void __fastcall SetJsckIDList(const int mesMode, TStringList *devList);
	void __fastcall SendJobStart(const int mesMode, const String recipeName, TStringList *devList);
	void __fastcall SendJobStartFail(const int mesMode, const String recipeName, TStringList *devList);
	void __fastcall SendJobComplete(const int mesMode, const String recipeName, TStringList *devList, String startTime, String endTime);
	void __fastcall SendJobValidation(const int mesMode, const String recipeName, TStringList *devList);
	void __fastcall SendJobValidationFail(const int mesMode, const String recipeName, TStringList *devList);
	void __fastcall SendJobCancel(const int mesMode, const String recipeName, TStringList *devList, String userid);
	void __fastcall SendJobCancelFail(const int mesMode, const String recipeName, TStringList *devList, String userid);
//	void __fastcall SendPvDataList();

	void __fastcall SendMgzValidation(const int chamberNo,
		const int mesMode, const String recipeName, const String mgzId);
	void __fastcall SendMgzValidationCancel(const int chamberNo,
		const int mesMode, const String recipeName, const String mgzId);
	void __fastcall SendMgzValidationFail(const int chamberNo,
		const int mesMode, const String recipeName, const String mgzId);
	//
    bool __fastcall IsConnected() { return IsEzNetConnected; }
	bool __fastcall IsGemConnected() { return GemState.Connected; }
	bool __fastcall IsOnlineRemote() { return GemState.ControlState == CONTROL_ONLINE_REMOTE; }
	bool __fastcall IsOnlineLocal() { return GemState.ControlState == CONTROL_ONLINE_LOCAL; }
	bool __fastcall IsOffline() { return GemState.ControlState == CONTROL_EQUIPMENT_OFFLINE; }

	void __fastcall GoOnlineRemote();
	void __fastcall GoOnlineLocal();
	void __fastcall GoOffline();
	void __fastcall RequestGemStatus();
};
//---------------------------------------------------------------------------
typedef std::shared_ptr<TFmEzNet> EzNetDlgPtr;
extern EzNetDlgPtr EzNetDlg[MAX_CHAMBER_COUNT];
//---------------------------------------------------------------------------
#endif
