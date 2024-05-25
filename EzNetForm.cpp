//---------------------------------------------------------------------------

#include <vcl.h>
#include <DateUtils.hpp>
#include <FileCtrl.hpp>
#include "System.Math.hpp"

#pragma hdrstop

//#include "GEMForm.h"
#include "JobForm.h"
#include "EzNetForm.h"
#include "TerminalMsgForm.h"
#include "HelperFunctions.h"
#include "NormalOvenChamber.h"
#include "NormalOvenSystemManager.h"
#include "Database.h"
#include "ChamberFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "EZNETLib_OCX"
#pragma resource "*.dfm"

EzNetDlgPtr EzNetDlg[MAX_CHAMBER_COUNT];

bool IsValidIPAddr(const String sIpVal)
{
	std::auto_ptr<TStringList> slIp (new TStringList());
    slIp->Delimiter = '.';
	slIp->DelimitedText = sIpVal;

	if( slIp->Count != 4 )
		return false;

	for(int i=0; i<slIp->Count; i++)
    {
        int nVal = slIp->Strings[i].ToInt();
		if( nVal > 255 || nVal < 0 )
			return false;
	}

	return true;
}

//---------------------------------------------------------------------------
__fastcall TFmEzNet::TFmEzNet(TComponent* Owner, NormalOvenChamber *chamber)
	: TForm(Owner)
{
	Chamber = chamber;
	IsEzNetConnected = false;
}
//---------------------------------------------------------------------------

__fastcall TFmEzNet::~TFmEzNet(void)
{

}
//---------------------------------------------------------------------------
void __fastcall TFmEzNet::Init()
{
	String str;

	String folder;
	folder.sprintf(L"%s%c\\EzNetEQ\\EzNet.log", GetLogFolder().c_str(), 'A' + Chamber->ChamberID);

	EzNet->PassiveMode = FALSE;
	EzNet->IP = "127.0.0.1";
	EzNet->Port = 6000 + Chamber->ChamberID;
	EzNet->SetLogFile(GetBstr(folder).c_bstr(), TRUE);
    EzNet->SetLogRetention(30);

	int nRet = EzNet->Start();
	if (nRet < 0)
	{
		SetMessageStr(GetErrorCode(nRet));
		ShowMessageDlg();
		return;
	}

	nRet = EzNet->GetRuntimeState();
	if (nRet == 0 && Chamber->ChamberID == CHAMBER_A)
	{
		SetMessageStr("There is no SoftKey.");
		ShowMessageDlg();
	}
}

void __fastcall TFmEzNet::FormCreate(TObject *Sender)
{
	Init();

	long svid[4];
	String sVal[4];

	ZeroMemory(svid, 4);

	svid[0] = SVID_EZNET_PREV_PROCSTATE;
	sVal[0] = "0";
	svid[1] = SVID_EZNET_PROC_STATE;
	sVal[1] = "0";
	svid[2] = SVID_EZNET_PREV_PROCSTATE;
	sVal[2] = "0";
	svid[3] = SVID_EZNET_PROC_STATE;
	sVal[3] = "0";

	SetSVID(svid, sVal, 4);
}
//---------------------------------------------------------------------------
WideString TFmEzNet::GetBstr(const String sVal) const
{
	return static_cast<WideString>(sVal);
}
//---------------------------------------------------------------------------
void __fastcall TFmEzNet::StartGEM()
{
	if (IsConnected() == false)
	{
		return;
	}

	long msgId = EzNet->CreateMsg(64, 19, FALSE);
	EzNet->SendMsg(msgId);
}
//---------------------------------------------------------------------------
void __fastcall TFmEzNet::StopGEM()
{
	if (IsConnected() == false)
	{
		return;
	}

	long msgId = EzNet->CreateMsg(64, 21, FALSE);
	EzNet->SendMsg(msgId);
}
//---------------------------------------------------------------------------
void __fastcall TFmEzNet::SetSVID(long svid[], String sVal[], int count)
{
	if (IsConnected() == false)
	{
		return;
	}

	int svidCount;

	long msgId = EzNet->CreateMsg(64, 1, FALSE);

	EzNet->OpenListItem(msgId);
		for(int i = 0; i < count; i++)
		{
			EzNet->OpenListItem(msgId);
				EzNet->AddU2Item(msgId, &svid[i], 1);
				EzNet->AddAsciiItem(msgId, GetBstr(sVal[i]).c_bstr(), sVal[i].Length());
			EzNet->CloseListItem(msgId);
		}
	EzNet->CloseListItem(msgId);
	EzNet->SendMsg(msgId);
}
//---------------------------------------------------------------------------
void __fastcall TFmEzNet::SetProcessState(int state)
{
	if (IsConnected() == false)
	{
		return;
	}

	long msgId = EzNet->CreateMsg(64, 3, FALSE);
	short temp = state;
	EzNet->AddU1Item(msgId, &temp, 1);
	EzNet->SendMsg(msgId);
}
//---------------------------------------------------------------------------
void __fastcall TFmEzNet::SetAlarm(int errCode)
{
	if (IsConnected() == false)
	{
		return;
	}

	long msgId = EzNet->CreateMsg(64, 5, FALSE);
	long temp = errCode;
	short alcd = 2;
	EzNet->OpenListItem(msgId);
		EzNet->AddU2Item(msgId, &temp, 1);
		EzNet->AddU1Item(msgId, &alcd, 1);
	EzNet->CloseListItem(msgId);
	EzNet->SendMsg(msgId);
}
//---------------------------------------------------------------------------
void __fastcall TFmEzNet::ClearAlarm(int errCode)
{
	if (IsConnected() == false)
	{
		return;
	}

	long msgId = EzNet->CreateMsg(64, 7, FALSE);
	long temp = errCode;
	EzNet->AddU2Item(msgId, &temp, 1);
	EzNet->SendMsg(msgId);
}
//---------------------------------------------------------------------------
void __fastcall TFmEzNet::ClearAlarmAll()
{
	if (Chamber == nullptr)
	{
		return;
	}

	for (int i=0; i<MAX_ALARM_COUNT; i++)
	{
		if (Chamber->AlarmStatus[i])
		{
			ClearAlarm(i);
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TFmEzNet::SendEventReport(long CEID)
{
	if (IsConnected() == false)
	{
		return;
	}

	long msgId = EzNet->CreateMsg(64, 9, FALSE);
	long temp = CEID;
	EzNet->AddU2Item(msgId, &temp, 1);
	EzNet->SendMsg(msgId);
}
//---------------------------------------------------------------------------
void __fastcall TFmEzNet::GoOnlineLocal()
{
	if (IsConnected() == false)
	{
		return;
	}

	long msgId = EzNet->CreateMsg(64, 11, FALSE);
	EzNet->SendMsg(msgId);
}
//---------------------------------------------------------------------------
void __fastcall TFmEzNet::GoOnlineRemote()
{
	if (IsConnected() == false)
	{
		return;
	}

	long msgId = EzNet->CreateMsg(64, 13, FALSE);
	EzNet->SendMsg(msgId);
}
//---------------------------------------------------------------------------
void __fastcall TFmEzNet::GoOffline()
{
	if (IsConnected() == false)
	{
		return;
	}

	long msgId = EzNet->CreateMsg(64, 15, FALSE);
	EzNet->SendMsg(msgId);
}
//---------------------------------------------------------------------------
void __fastcall TFmEzNet::RequestGemStatus()
{
	if (IsConnected() == false)
	{
		return;
	}

	long msgId = EzNet->CreateMsg(64, 17, FALSE);
	EzNet->SendMsg(msgId);
}
//---------------------------------------------------------------------------
void __fastcall TFmEzNet::SetJsckIDList(const int mesMode, TStringList *devList)
{
	if (IsConnected() == false)
	{
		return;
	}

	String strValue, strProcess;
	long svid;
	double vid;
	short temp;
	TStringList *ProcessList = new TStringList;
	long msgId;
	msgId = EzNet->CreateMsg(64, 22, FALSE);

	EzNet->OpenListItem(msgId);

//	if (mesMode == MES_LOT_MODE)
//	{
//		temp = mesMode;
//		EzNet->AddU1Item(msgId, &temp, 1);
//		EzNet->AddListItem(msgId, devList->Count);
//		for (int i = 0; i < devList->Count; i++)
//		{
//			EzNet->OpenListItem(msgId);
//			strValue = devList->Strings[i];
//			ProcessList->CommaText = strValue;
//			strProcess = ProcessList->Strings[0];
//			EzNet->AddAsciiItem(msgId, GetBstr(strProcess).c_bstr(), strProcess.Length());
//			strValue = ProcessList->Strings[1];
//			EzNet->AddAsciiItem(msgId, GetBstr(strValue).c_bstr(), strValue.Length());
//			EzNet->CloseListItem(msgId);
//		}
//		delete devList;
//
//		EzNet->CloseListItem(msgId);
//	}
//	else
//	{
	temp = mesMode;
	EzNet->AddU1Item(msgId, &temp, 1);

	EzNet->AddListItem(msgId, devList->Count);
	for(int i=0; i<devList->Count; i++)
	{
		EzNet->OpenListItem(msgId);
		strValue = devList->Strings[i];
		ProcessList->CommaText = strValue;
		strProcess = ProcessList->Strings[0];
		EzNet->AddAsciiItem(msgId, GetBstr(strProcess).c_bstr(), strProcess.Length());
		strValue = ProcessList->Strings[1];
		EzNet->AddAsciiItem(msgId, GetBstr(strValue).c_bstr(), strValue.Length());
		EzNet->CloseListItem(msgId);
	}

	EzNet->CloseListItem(msgId);

	EzNet->CloseListItem(msgId);
	EzNet->SendMsg(msgId);

    delete ProcessList;
}

/**********************************************
//Process Program Load Inquire(PPI)
호스트가 Recipe를 내려주기 전 미리 해당 Recipe명을 알려 줌
해당 Recipe가 존재 하는지 판단하여 응답 하여야 함
이미 존재 한다면 Ack 를 0보다 큰값으로 보냄
**********************************************/
void __fastcall TFmEzNet::OnS7F1W(long lMsgId)
{
	WideString sPPID = "";
	String recipeName;
	double length = 0;

	EzNet->GetListItemOpen(lMsgId);
		EzNet->GetAsciiItem(lMsgId, &sPPID);
		EzNet->GetU4Item(lMsgId, &length);
	EzNet->GetListItemClose(lMsgId);
	recipeName = sPPID;
	// strPPID이름을 가지고 존재하는지 허용할 수 있는 이름인지 확인 후
	// 아래의 응답을 보냅니다.
	// nAck
	// 0x00 = OK
	// 0x01 = Already Have
	// 0x02 = No Space
	// 0x03 = Invalid PORTID
	// 0x04 = Machine Running

	String str;
	str.sprintf(L"Host PPID inquire as %s.", recipeName.c_str());
	GetOvenDB()->SaveLog(str, MESSAGES);

	short nAck = 0x00;

	if( Chamber->IsRun )
		nAck = 4;
	else
	{
		/*******
		Recipe 가 이미 존재 하는지 판단하여 Ack Code를 분리 함
		1 : Already Exist
		********/
		if( IsGemRecipeExist(sPPID) )
		{
			nAck = 1;

			long svid[2];
			String sVal[2];

			ZeroMemory(svid, 2);

			svid[0] = SVID_PORTID;
			sVal[0] = IntToStr(Chamber->ChamberID);
			svid[1] = SVID_PPID;
			sVal[1] = sPPID;

			SetSVID(svid, sVal, 2);
			SendEventReport(CEID_PP_SELECTED);

			FmJob->ChamberFrame[Chamber->ChamberID]->SelectRecipe(sPPID);		// 2021-04-26 Add
		}
		else
			nAck = 0;
	}

	//S7F1에 대한 응답메세지인 S7F2생성.
	lMsgId = EzNet->CreateReplyMsg(lMsgId);
	EzNet->AddBinaryItem(lMsgId, &nAck , 1);

	EzNet->SendMsg(lMsgId);
}
//---------------------------------------------------------------------------

/**********************************************
//Process Program Send(PPS)
호스트가 Recipe를 내려줌 해당 Recipe는 RECIPE폴더
내부에 저장 됨 <사용안함>
**********************************************/
void __fastcall TFmEzNet::OnS7F3W(long lMsgId)
{
	int i;
	WideString sPPID = "";
	short nAck = 0x00;
	String str, recipeName, ptnFile;
	long nPtnNo = 1;

	// nAck
	// 0 = Accepted
	// 1 = Machine Running
	// 2 = Invalid PPBODY
	// 4 = Positive
	// 5 = Not Create File

	EzNet->GetListItemOpen(lMsgId);
		EzNet->GetAsciiItem(lMsgId, &sPPID);

	recipeName = sPPID;

	str.sprintf(L"Host Sended New Recipe as %s.", recipeName.c_str());
	GetOvenDB()->SaveLog(str, MESSAGES, -1);

	if( Chamber->IsRun )
		nAck = 3;
	else
	{
		ptnFile.sprintf(L"%s%c\\%s.ptn", GetRemotePatternFolder().c_str(),'A'+Chamber->ChamberID , recipeName.c_str());

		if( IsGemRecipeExist(recipeName) )
		{
			if( FileExists(ptnFile) )
			{
				DeleteFile(ptnFile);
				GetOvenDB()->DeleteRecipeWithPtnNoAndRcpName(Chamber->ChamberID, 0, recipeName);
			}
			str.sprintf(L"Host Sended Old Recipe %s is deleted.", recipeName.c_str());
			GetOvenDB()->SaveLog(str, MESSAGES);
		}

		//create file
		long ret = EzNet->GetFileBinaryItem(lMsgId, GetBstr(ptnFile).c_bstr());
		if( ret >= 0 )
		{
			PTN ptn;
			OVEN_RECIPE recipe;
			LoadTempPtn(Chamber->ChamberID, nPtnNo, ptn);

			recipe.ChamberNo = Chamber->ChamberID;
			recipe.Recipe = recipeName;
			recipe.PtnNo = nPtnNo;
			recipe.CureTemp = ptn.MaxTemp;
			recipe.CureTime = ptn.TotalTime;
//			recpie.
//			Recipe.TempPtn.Stc.SegCount
			GetOvenDB()->AddRecipe(recipe);

			str.sprintf(L"Host Sended New Recipe %s is saved.", recipeName.c_str());
			GetOvenDB()->SaveLog(str, MESSAGES);
		}
		else
			nAck = 5;//4;

		FmJob->ChamberFrame[Chamber->ChamberID]->UpdateRecipeComboBox();
	}

	EzNet->GetListItemClose(lMsgId);

	lMsgId = EzNet->CreateReplyMsg(lMsgId);
	EzNet->AddBinaryItem(lMsgId, &nAck , 1);
	EzNet->SendMsg(lMsgId);
}
//---------------------------------------------------------------------------

/**********************************************
//Process Program Request(PPR)
호스트가 Recipe를 요청함 장비는 해당 Recipe의
존재 여부를 판단하여 응답 하여야 함.
**********************************************/
void __fastcall TFmEzNet::OnS7F5W(long lMsgId)
{
	WideString sPPID = "";
	String sFilePath = "", recipeName;

	bool bRecipeExist = false;
	short nAck = 0x00;

	EzNet->GetAsciiItem(lMsgId, &sPPID);

	recipeName = sPPID;
	///////////////////////
	//해당 폴더 내부에 Recipe가 존재 하는지 여부를 판단하여
	//bRecipeExist 변수에 값을 셋팅
	///////////////////////
	if( IsGemRecipeExist(recipeName) )
	{
		bRecipeExist = true;
		sFilePath.sprintf(L"%s%c\\%s.ptn", GetRemotePatternFolder().c_str(),'A'+Chamber->ChamberID , recipeName.c_str());
	}
	else
	{
		if( GetOvenDB()->IsRecipeExist(Chamber->ChamberID, recipeName) )
		{
			bRecipeExist = true;
			OVEN_RECIPE recipe;
			GetOvenDB()->GetRecipe(Chamber->ChamberID, recipeName, recipe);

			sFilePath.sprintf(L"%sPATTERN_CM_%c\\%d.ptn", GetRootFolder().c_str(), 'A' + Chamber->ChamberID, recipe.PtnNo);
		}
		else
			bRecipeExist = false;
	}

	lMsgId = EzNet->CreateReplyMsg(lMsgId);

	EzNet->OpenListItem(lMsgId);

	if( bRecipeExist )
	{
		//요청한 Recipe가 존재하므로 S7F6을 통해 Recipe를 전송
		EzNet->AddAsciiItem(lMsgId, GetBstr(recipeName).c_bstr(), recipeName.Length());
		long ret = EzNet->AddFileBinaryItem(lMsgId, GetBstr(sFilePath).c_bstr());

		String str;
		str.sprintf(L"Sended the Recipe [%s].", recipeName.c_str());
		GetOvenDB()->SaveLog(str, MESSAGES);
	}
	else
	{
		String str;
		str.sprintf(L"Could not Send the Recipe [%s].", recipeName.c_str());
		GetOvenDB()->SaveLog(str, MESSAGES);

		// report that there is no file.
		// Zero-length list
	}
	EzNet->CloseListItem(lMsgId);
	EzNet->SendMsg(lMsgId);
}
//---------------------------------------------------------------------------

/**********************************
//Delete Process Program Send(DPS)
   Recipe삭제 요청
**********************************/
void __fastcall TFmEzNet::OnS7F17W(long lMsgId)
{
	short nCount, i;

	WideString sPPID="";
	String str, ptnFile, recipeName;

	short nAck = 0x00;//Acknowledge를 설정 하기 위한 변수
	long lReplyMsgID; //S7F17W에 대한 응답 메세지

	// nAck
	// 0: Accepted
	// 1: Length Error
	// 2: PPID not found

	std::shared_ptr<TStringList> sPPIDList (new TStringList());
    sPPIDList->Clear();

	//메시지를 열어서 아이템 확인
	EzNet->GetListItemOpen(lMsgId);

	nCount = EzNet->GetListItemOpen(lMsgId); //삭제할 갯수 := nCount

	if( nCount == 0 )	// 모두 지움.
	{
		ptnFile = GetRemotePatternFolder() + str.sprintf(L"%c\\", 'A'+Chamber->ChamberID);
		DeleteAllFile(ptnFile);

		TStringList *list = new TStringList();
		if( GetOvenDB()->GetRecipeList(Chamber->ChamberID, list) )
		{
			for(int i=0; i<list->Count; i++)
			{
				String recipeName = list->Strings[i];
				OVEN_RECIPE recipe;

				GetOvenDB()->GetRecipe(Chamber->ChamberID, recipeName, recipe);

				GetOvenDB()->DeleteRecipe(Chamber->ChamberID, recipeName);

				// 패턴 삭제 2021-11-09 패턴 삭제 해제 요청
//				ptnFile.sprintf(L"%sPATTERN_CM_%c\\%d.ptn", GetRootFolder().c_str(), 'A' + Chamber->ChamberID, recipe.PtnNo);
//				if( FileExists(ptnFile) )
//					DeleteFile(ptnFile);
			}
		}
		delete list;

		str = "All recipe is deleted by host.";
		GetOvenDB()->SaveLog(str, MESSAGES);
	}
	else
	if( nCount > 0)
	{
		for(i=0; i<nCount; i++)
		{
			EzNet->GetAsciiItem(lMsgId, &sPPID);
			recipeName = sPPID;

			if( GetOvenDB()->IsRecipeExist(0, recipeName) ||
				GetOvenDB()->IsRecipeExist(1, recipeName) )
			{
				if( IsGemRecipeExist(sPPID) )
				{
					ptnFile.sprintf(L"%s%c\\%s.ptn", GetRemotePatternFolder().c_str(), 'A'+Chamber->ChamberID , sPPID.c_bstr());
					if( FileExists(ptnFile) )
						DeleteFile(ptnFile);
				}

				for(int i = 0; i < GetManager()->ChamberCount; i++)
				{
					if( GetOvenDB()->IsRecipeExist(Chamber->ChamberID, sPPID) )
					{
						OVEN_RECIPE recipe;
						GetOvenDB()->GetRecipe(Chamber->ChamberID, sPPID, recipe);

						// 패턴 삭제
						ptnFile.sprintf(L"%sPATTERN_CM_%c\\%d.ptn", GetRootFolder().c_str(), 'A' + Chamber->ChamberID, recipe.PtnNo);
						if( FileExists(ptnFile) )
							DeleteFile(ptnFile);

						GetOvenDB()->DeleteRecipe(i, sPPID);
					}
				}

				str.sprintf(L"Host Sended Recipe %s is deleted.", sPPID.c_bstr());
				GetOvenDB()->SaveLog(str, MESSAGES);
			}
			else
			{
				nAck = 2;
				break;
			}
		}
	}
	else
		nAck = 1;	// Length error

	EzNet->GetListItemClose(lMsgId);

	//	삭제에 관한 응답을 보내는 부분
	lReplyMsgID = EzNet->CreateReplyMsg(lMsgId);  // S7F18 메세지 생성
	EzNet->AddBinaryItem(lReplyMsgID, &nAck, 1);	// ACK값 메세지에 첨부
	EzNet->SendMsg(lReplyMsgID);
}
//---------------------------------------------------------------------------

/********************************************
// Current EPPD Request (RER)
Host 레시피 리스트 조회/리스트 송부 요청
********************************************/
void __fastcall TFmEzNet::OnS7F19W(long lMsgId)
{
    // Modified 2021-06-28 모든 챔버 Recipe Request
	long lReplyMsgID;

	EzNet->GetListItemOpen(lMsgId);
	EzNet->GetListItemClose(lMsgId);

	String str;
	lReplyMsgID = EzNet->CreateReplyMsg(lMsgId);
	EzNet->OpenListItem(lReplyMsgID);

	// 각 챔버의 레시피 리스트 조회
	// 같은 이름은 제외한다.
	int idx;
	TStringList *sPPIDList = new TStringList;
	TStringList *recList = new TStringList;
	GetOvenDB()->GetRecipeList(Chamber->ChamberID, recList);

	for(int j=0; j<recList->Count; j++)
	{
		str = recList->Strings[j];
		if( sPPIDList->Find(str, idx) == false )
			sPPIDList->Add(str);
	}
	delete recList;

	// REMOTE_PATTERN 폴더 내의 레시피 조회
	WIN32_FIND_DATA filedata;
	str.sprintf(L"%c\\", Chamber->ChamberID);
	HANDLE filehandle = FindFirstFile((GetRemotePatternFolder() + str + "*.*").c_str(), &filedata);
	if( filehandle != INVALID_HANDLE_VALUE )
	{
		AnsiString file, filename, ext;
		do
		{
			file = filedata.cFileName;
			ext = ExtractFileExt(file);
			ext = LowerCase(ext);
			if( ext == ".ptn" )
			{
				int pos = file.Pos(ext);
				filename = file.SubString(1, pos-1);
				if( sPPIDList->Find(filename, idx) == false )
					sPPIDList->Add(filename);
			}
		} while(FindNextFile(filehandle, &filedata));
		FindClose(filehandle);
	}

	EzNet->AddListItem(lMsgId, sPPIDList->Count);
	for(int i=0; i<sPPIDList->Count; i++)
	{
		str = sPPIDList->Strings[i];
		EzNet->AddAsciiItem(lReplyMsgID, GetBstr(str).c_bstr(), str.Length());
	}
	delete sPPIDList;

	EzNet->CloseListItem(lReplyMsgID);
	EzNet->SendMsg(lReplyMsgID);

	str = "Send all the list of recipes.";
	GetOvenDB()->SaveLog(str, MESSAGES);
}
//---------------------------------------------------------------------------
void __fastcall TFmEzNet::OnS64F18(long lMsgId)
{
	short tmp;
	EzNet->GetListItemOpen(lMsgId);
		EzNet->GetU1Item(lMsgId, &tmp);
		GemState.Started = (tmp == 1) ? true : false;
		EzNet->GetU1Item(lMsgId, &tmp);
		GemState.Connected = (tmp == 1) ? true : false;
		EzNet->GetU1Item(lMsgId, &tmp);
		GemState.Established = (tmp == 1) ? true : false;
		EzNet->GetU1Item(lMsgId, &tmp);
		GemState.Enabled = (tmp == 1) ? true : false;
		EzNet->GetU1Item(lMsgId, &tmp);
		GemState.ControlState = tmp;
		EzNet->GetU1Item(lMsgId, &tmp);
		GemState.PrevControlState = tmp;
		EzNet->GetU1Item(lMsgId, &tmp);
		GemState.ProcessState = tmp;
		EzNet->GetU1Item(lMsgId, &tmp);
		GemState.PrevProcessState = tmp;
	EzNet->GetListItemClose(lMsgId);
}
//---------------------------------------------------------------------------
void __fastcall TFmEzNet::UpdateSvidParam()
{
	if (Chamber == nullptr)
	{
		return;
	}

	long svid[100];
	String sVal[100];

	ZeroMemory(svid, 100);

	int idx = 0;

	svid[idx] = SVID_PORTID;
	sVal[idx] = IntToStr(Chamber->ChamberID);
	idx++;

//	svid[idx] = SVID_TOTAL_SEG_COUNT;
//	sVal[idx].sprintf(L"%d", Chamber->Recipe.TempPtn.Stc.SegCount);
//	idx++;
//	svid[idx] = SVID_CURRENT_SEG_NO;
//	sVal[idx].sprintf(L"%d", Chamber->SegNo);
//	idx++;
//	svid[idx] = SVID_TOTAL_CURE_TIME;
//	sVal[idx] = IntToStr(Chamber->Recipe.TempPtn.TotalTime);
//	idx++;

	svid[idx] = SVID_EZNET_SET_TEMP_SP;
	sVal[idx].sprintf(L"%.1f", Chamber->Recipe.TempPtn.MaxTemp);
	idx++;
	svid[idx] = SVID_EZNET_SET_TIME;
	sVal[idx] = IntToStr(Chamber->GetCurrentSegTime());
	idx++;

	svid[idx] = SVID_EZNET_ACT_TEMP;
	sVal[idx].sprintf(L"%.1f", Chamber->PV);
	idx++;

	svid[idx] = SVID_EZNET_ACT_LOGGER1;
	sVal[idx].sprintf(L"%.1f", Chamber->LoggerData[0]);
	idx++;
	svid[idx] = SVID_EZNET_ACT_LOGGER2;
	sVal[idx].sprintf(L"%.1f", Chamber->LoggerData[1]);
	idx++;
	svid[idx] = SVID_EZNET_ACT_LOGGER3;
	sVal[idx].sprintf(L"%.1f", Chamber->LoggerData[2]);
	idx++;
	svid[idx] = SVID_EZNET_ACT_LOGGER4;
	sVal[idx].sprintf(L"%.1f", Chamber->LoggerData[3]);
	idx++;
	svid[idx] = SVID_EZNET_ACT_LOGGER5;
	sVal[idx].sprintf(L"%.1f", Chamber->LoggerData[4]);
	idx++;

	svid[idx] = SVID_EZNET_DOOR_STATUS;
	sVal[idx] = IntToStr(1);
//	if (Chamber->IsDoorWorking)
//	{
//		sVal[idx] = IntToStr(2);
//	}
//	else
	if (Chamber->IsDoorClosed() == true)
	{
		sVal[idx] = IntToStr(0);
	}
	else
	{
		sVal[idx] = IntToStr(1);
	}
	idx++;

	SetSVID(svid, sVal, idx);
}
//---------------------------------------------------------------------------
String __fastcall TFmEzNet::GetErrorCode(const short ret)
{
	String sRet = "";
	int lang = GetManager()->Language;

	switch (ret)
	{
	case LICENSE_PROBLEM:
		sRet = (lang== KOR)? ("라이센스(License)문제발생") : ("License Problem");
		break;
	case CONFIG_FILE_NOTFOUND:
		sRet = (lang == KOR)? ("환경설정 파일(Configuration File)이 존재하지 않음") : ("No Configuration File");
		break;
	case FILE_NOT_FOUND:
		sRet = (lang == KOR)? ("파일이 존재하지 않음") : ("There is no File");
		break;
	case FILE_IO_FAILURE:
		sRet = (lang == KOR)? ("파일 입출력(I/O) 실패") : ("File Input/Output Failure");
		break;
	case FILE_CREATION_ERROR:
		sRet = (lang == KOR)? ("파일 생성 실패") : ("Failure of file creation");
		break;
	case NO_ITEM:
		sRet = (lang == KOR)? ("아이템(Item)이 존재하지 않음") : ("There is no item");
		break;
	case TYPE_MISMATCH:
		sRet = (lang == KOR)? ("ITEM의 타입이 맞지 않음") : ("Type of Item is not matched");
		break;
	case SIZE_MISMATCH:
		sRet = (lang == KOR)? ("ITEM의 크기/개수가 맞지 않음") : ("Size and count of item is not matched");
		break;
	case ITEM_I1_OVERFLOW:
		sRet = (lang == KOR)? ("I1(1Byte Integer) Overflow 발생") : ("I1(1Byte Integer) Overflow happened");
		break;
	case ITEM_I2_OVERFLOW:
		sRet = (lang == KOR)? ("I2(2Byte Integer) Overflow 발생") : ("I2(2Byte Integer) Overflow happened");
		break;
	case ITEM_I4_OVERFLOW:
		sRet = (lang == KOR)? ("I4(4Byte Integer) Overflow 발생") : ("I4(4Byte Integer) Overflow happened");
		break;
	case ITEM_U1_OVERFLOW:
		sRet = (lang == KOR)? ("U1(1Byte Unsigned Integer) Overflow 발생") : ("U1(1Byte Unsigned Integer) Overflow happened");
		break;
	case ITEM_U2_OVERFLOW:
		sRet = (lang == KOR)? ("U2(2Byte Unsigned Integer) Overflow 발생") : ("U2(2Byte Unsigned Integer) Overflow happened");
		break;
	case ITEM_U4_OVERFLOW:
		sRet = (lang == KOR)? ("U4(4Byte Unsigned Integer) Overflow 발생") : ("U4(4Byte Unsigned Integer) Overflow happened");
		break;
	case INVALID_MSGID:
		sRet = (lang == KOR)? ("유효하지않은 Message ID") : ("Invalid Message ID");
		break;
	case INVALID_STREAM:
		sRet = (lang == KOR)? ("유효하지않은 Stream번호") : ("Invalid Stream Number");
		break;
	case INVALID_FUNCTION:
		sRet = (lang == KOR)? ("유효하지않은 Function 번호") : ("Invalid Function Number");
		break;
	case DUPLICATE_SYSTEMBYTE:
		sRet = (lang == KOR)? ("시스템바이트의 중복") : ("System Byte duplicate");
		break;
	case UNDEFINED_STRUCTURE:
		sRet = (lang == KOR)? ("정의되지 않 은Message Structure를 수신") : ("Received the not defined Message Structure");
		break;
	case NOT_CONNECTED:
		sRet = (lang == KOR)? ("아직 연결이 안된 상태임") : ("Not Connected yet");
		break;
	case LOW_LEVEL_ERROR:
		sRet = (lang == KOR)? ("Operating System 상의  Error") : ("Error of Operating System");
		break;
	case NOT_SUPPORTED:
		sRet = (lang == KOR)? ("지원되지 않는기능") : ("Not supported function");
		break;
	case ALREADY_CONNECTED:
		sRet = (lang == KOR)? ("이미 연결되어 있음") : ("Already connected");
		break;
	case ALREADY_STATRED:
		sRet = (lang == KOR)? ("이미 구동된 상태임") : ("Already drived");
		break;
	case THREAD_NULL:
		sRet = (lang == KOR)? ("각종 쓰레드(THREAD) 에러") : ("Various Thread error");
		break;
	case CREATE_EVENT_FAIL:
		sRet = (lang == KOR)? ("이벤트(EVENT)발생 에러") : ("Event happened error");
		break;
	case SERIAL_OPEN_FAIL:
		sRet = (lang == KOR)? ("시리얼 포트 구동 에러") : ("Serial Port activating error");
		break;
	case SERIAL_SETUP_FAIL:
		sRet = (lang == KOR)? ("시리얼 포트 초기화 에러") : ("Serial Port initializing error");
		break;
	case TIMER_CREATE_FAIL:
		sRet = (lang == KOR)? ("타이머 생성 실패") : ("Timer Creating error");
		break;
	case NOT_STARTED_YET:
		sRet = (lang == KOR)? ("프로그램이 구동되지 않았음") : ("Program not activated");
		break;
	case SOCKET_INUSE:
		sRet = (lang == KOR)? ("소켓(Socket)이 이미 사용중임") : ("Socket is used already");
		break;
	case SOCKET_STARTERROR:
		sRet = (lang == KOR)? ("소켓 구동 에러") : ("Socket Activating error");
		break;
	case SOCKET_INVALID:
		sRet = (lang == KOR)? ("소켓이 유효하지 않음") : ("Invalid Socket");
		break;
	case SOCKET_WINDOWERROR:
		sRet = (lang == KOR)? ("메시지 통신을 위한 Worker Window 에러") : ("Worker Window error for communitating message");
		break;
	case SOCKET_LOCALNAME:
		sRet = (lang == KOR)? ("Host Name을 알아오는 과정에서 에러발생") : ("Error happened during getting Host name");
		break;
	case SOCKET_CONNECTERROR:
		sRet = (lang == KOR)? ("소켓접속 에러") : ("Socket connecting error");
		break;
	case SOCKET_SETEVENT:
		sRet = (lang == KOR)? ("소켓 이벤트 설정 에러") : ("Socket Event Selecting error");
		break;
	case SOCKET_RESOLVE:
		sRet = (lang == KOR)? ("소켓함수 Resolve()수행 중 에러") : ("Resolve() executing error of Socket functions");
		break;
	default:
		break;
	}

	return sRet;
}
//---------------------------------------------------------------------------
void __fastcall TFmEzNet::SendJobEndEvent(String lotid, String cstid, String ppid)
{
	if (IsConnected() == false)
	{
		return;
	}

	long svid[4];
	String sVal[4];

	ZeroMemory(svid, 4);

	svid[0] = SVID_PORTID;
	sVal[0] = IntToStr(Chamber->ChamberID);
	svid[1] = SVID_LOTID;
	sVal[1] = lotid;
	svid[2] = SVID_EZNET_CSTID_LIST;
	sVal[2] = cstid;
	svid[3] = SVID_PPID;
	sVal[3] = ppid;

	SetSVID(svid, sVal, 4);
	SendEventReport(CEID_JOB_END);
}
//---------------------------------------------------------------------------
void __fastcall TFmEzNet::SendJobStartedEvent(String lotid, String cstid, String ppid)
{
	if (IsConnected() == false)
	{
		return;
	}

    long svid[4];
	String sVal[4];

	ZeroMemory(svid, 4);

	svid[0] = SVID_PORTID;
	sVal[0] = IntToStr(Chamber->ChamberID);
	svid[1] = SVID_LOTID;
	sVal[1] = lotid;
	svid[2] = SVID_EZNET_CSTID_LIST;
	sVal[2] = cstid;
	svid[3] = SVID_PPID;
	sVal[3] = ppid;

	SetSVID(svid, sVal, 4);
	SendEventReport(CEID_JOB_START);
}
//---------------------------------------------------------------------------
void __fastcall TFmEzNet::SendJobStartFailEvent(String lotid, String cstid, String ppid)
{
	if (IsConnected() == false)
	{
		return;
	}

    long svid[4];
	String sVal[4];

	ZeroMemory(svid, 4);

	svid[0] = SVID_PORTID;
	sVal[0] = IntToStr(Chamber->ChamberID);
	svid[1] = SVID_LOTID;
	sVal[1] = lotid;
	svid[2] = SVID_EZNET_CSTID_LIST;
	sVal[2] = cstid;
	svid[3] = SVID_PPID;
	sVal[3] = ppid;

	SetSVID(svid, sVal, 4);
	SendEventReport(CEID_JOB_START_FAIL);
}
//---------------------------------------------------------------------------
void __fastcall TFmEzNet::SendJobCancelEvent(String lotid, String cstid, String ppid)
{
	if (IsConnected() == false)
	{
		return;
	}

    long svid[4];
	String sVal[4];

	ZeroMemory(svid, 4);

	svid[0] = SVID_PORTID;
	sVal[0] = IntToStr(Chamber->ChamberID);
	svid[1] = SVID_LOTID;
	sVal[1] = lotid;
	svid[2] = SVID_EZNET_CSTID_LIST;
	sVal[2] = cstid;
	svid[3] = SVID_PPID;
	sVal[3] = ppid;

	SetSVID(svid, sVal, 4);
	SendEventReport(CEID_JOB_CANCEL);
}
//---------------------------------------------------------------------------
void __fastcall TFmEzNet::SendJobCancelFailEvent(String lotid, String cstid, String ppid)
{
	if (IsConnected() == false)
	{
		return;
	}

    long svid[4];
	String sVal[4];

	ZeroMemory(svid, 4);

	svid[0] = SVID_PORTID;
	sVal[0] = IntToStr(Chamber->ChamberID);
	svid[1] = SVID_LOTID;
	sVal[1] = lotid;
	svid[2] = SVID_EZNET_CSTID_LIST;
	sVal[2] = cstid;
	svid[3] = SVID_PPID;
	sVal[3] = ppid;

	SetSVID(svid, sVal, 4);
	SendEventReport(CEID_JOB_CANCEL_FAIL);
}
//---------------------------------------------------------------------------
void __fastcall TFmEzNet::SendBarcodeInfoEvent(String barcode)
{
	if (IsConnected() == false)
	{
		return;
	}

	long svid[2];
	String sVal[2];

	ZeroMemory(svid, 2);

	svid[0] = SVID_PORTID;
	sVal[0] = IntToStr(Chamber->ChamberID);
	svid[1] = SVID_LOTID;
	sVal[1] = barcode;

	SetSVID(svid, sVal, 2);
	SendEventReport(CEID_BCR_READ);
}
//---------------------------------------------------------------------------
void __fastcall TFmEzNet::SendPPSelectedEvent(String ppid)
{
	if (IsConnected() == false)
	{
		return;
	}

	long svid[2];
	String sVal[2];

	ZeroMemory(svid, 2);

	svid[0] = SVID_PORTID;
	sVal[0] = IntToStr(Chamber->ChamberID);
	svid[1] = SVID_PPID;
	sVal[1] = ppid;

	SetSVID(svid, sVal, 2);
	SendEventReport(CEID_PP_SELECTED);
}
//---------------------------------------------------------------------------
void __fastcall TFmEzNet::SendPPChangedEvent(String ppid, int changeStatus)
{
	if (IsConnected() == false)
	{
		return;
	}

	long svid[3];
	String sVal[3];

	ZeroMemory(svid, 3);

	svid[0] = SVID_PORTID;
	sVal[0] = IntToStr(Chamber->ChamberID);
	svid[1] = SVID_PPID_CHANGE_NAME;  //JSCK SVID 2211
	sVal[1] = ppid;
	svid[2] = SVID_PPID_CHANGE_STATUS; //JSCK SVID 2212
	sVal[2] = IntToStr(changeStatus);

	SetSVID(svid, sVal, 3);
	SendEventReport(CEID_PP_CHANGED); //JSCK CEID 1051
}
//---------------------------------------------------------------------------
void __fastcall TFmEzNet::SendDoorEvent()
{
	if (Chamber == nullptr)
	{
		return;
	}

	if (IsConnected() == false)
	{
		return;
	}

	int doorStatus = -1;
	int bodyDoorStatus = -1;

	if (Chamber->IsDoorClosed() == true)
	{
		doorStatus = 0;
	}
	else
	{
		doorStatus = 1;
	}

	long svid[2];
	String sVal[2];

	ZeroMemory(svid, 2);

	svid[0] = SVID_PORTID;
	sVal[0] = IntToStr(Chamber->ChamberID);
	svid[1] = SVID_EZNET_DOOR_STATUS;
	sVal[1] = IntToStr(doorStatus);

	SetSVID(svid, sVal, 2);
	SendEventReport(CEID_EZNET_DOOR_STATUS);  //JSCK CEID 1110
}
//--------------------------------------------------------------------------JSCK
void __fastcall TFmEzNet::SendJobStart(const int mesMode, const String recipeName, TStringList *devList)
{
	if (IsConnected() == false)
	{
		return;
	}

	long svid[3];
	String sVal[3];

	ZeroMemory(svid, 3);

	svid[0] = SVID_PORTID;
	sVal[0] = IntToStr(Chamber->ChamberID);
	svid[1] = SVID_EZNET_MES_MODE;
	sVal[1] = IntToStr(mesMode);
	svid[2] = SVID_PPID;
	sVal[2] = recipeName;

	SetSVID(svid, sVal, 3);
	SetJsckIDList(mesMode, devList);
	SendEventReport(CEID_EZNET_JOB_START); //JSCK CEID 1011
}
//---------------------------------------------------------------------------
void __fastcall TFmEzNet::SendJobStartFail(const int mesMode, const String recipeName, TStringList *devList)
{
	if (IsConnected() == false)
	{
		return;
	}

	long svid[3];
	String sVal[3];

	ZeroMemory(svid, 3);

	svid[0] = SVID_PORTID;
	sVal[0] = IntToStr(Chamber->ChamberID);
	svid[1] = SVID_EZNET_MES_MODE;
	sVal[1] = IntToStr(mesMode);
	svid[2] = SVID_PPID;
	sVal[2] = recipeName;

	SetSVID(svid, sVal, 3);
	SetJsckIDList(mesMode, devList);
	SendEventReport(CEID_EZNET_JOB_START_FAIL); //JSCK CEID 1016
}
//---------------------------------------------------------------------------
void __fastcall TFmEzNet::SendJobComplete(const int mesMode, const String recipeName, TStringList *devList, String startTime, String endTime)
{
	if (IsConnected() == false)
	{
		return;
	}

	long svid[5];
	String sVal[5];

	ZeroMemory(svid, 5);

	svid[0] = SVID_PORTID;
	sVal[0] = IntToStr(Chamber->ChamberID);
	svid[1] = SVID_EZNET_MES_MODE;
	sVal[1] = IntToStr(mesMode);
	svid[2] = SVID_PPID;
	sVal[2] = recipeName;
	svid[3] = SVID_EZNET_JOB_START_TIME;
	sVal[3] = startTime;
	svid[4] = SVID_EZNET_JOB_END_TIME;
	sVal[4] = endTime;

	SetSVID(svid, sVal, 5);
	SetJsckIDList(mesMode, devList);
	SendEventReport(CEID_EZNET_JOB_COMPLETE); //JSCK CEID 1014
}
//---------------------------------------------------------------------------
void __fastcall TFmEzNet::SendJobValidation(const int mesMode, const String recipeName, TStringList *devList)
{
	if (IsConnected() == false)
	{
		return;
	}

	long svid[3];
	String sVal[3];

	ZeroMemory(svid, 3);

	svid[0] = SVID_PORTID;
	sVal[0] = IntToStr(Chamber->ChamberID);
	svid[1] = SVID_EZNET_MES_MODE;
	sVal[1] = IntToStr(mesMode);
	svid[2] = SVID_PPID;
	sVal[2] = recipeName;

	SetSVID(svid, sVal, 3);
	SetJsckIDList(mesMode, devList);
	SendEventReport(CEID_EZNET_JOB_VALIDATION); //JSCK CEID 1012
}
//---------------------------------------------------------------------------
void __fastcall TFmEzNet::SendJobValidationFail(const int mesMode, const String recipeName, TStringList *devList)
{
	if (IsConnected() == false)
	{
		return;
	}

	long svid[3];
	String sVal[3];

	ZeroMemory(svid, 3);

	svid[0] = SVID_PORTID;
	sVal[0] = IntToStr(Chamber->ChamberID);
	svid[1] = SVID_EZNET_MES_MODE;
	sVal[1] = IntToStr(mesMode);
	svid[2] = SVID_PPID;
	sVal[2] = recipeName;

	SetSVID(svid, sVal, 3);
	SetJsckIDList(mesMode, devList);
	SendEventReport(CEID_EZNET_JOB_VALIDATION_FAIL); //JSCK CEID 1018
}
//---------------------------------------------------------------------------
void __fastcall TFmEzNet::SendJobCancel(const int mesMode, const String recipeName, TStringList *devList, String userid)
{
	if (IsConnected() == false)
	{
		return;
	}

	long svid[4];
	String sVal[4];

	ZeroMemory(svid, 4);

	svid[0] = SVID_PORTID;
	sVal[0] = IntToStr(Chamber->ChamberID);
	svid[1] = SVID_EZNET_MES_MODE;
	sVal[1] = IntToStr(mesMode);
	svid[2] = SVID_PPID;
	sVal[2] = recipeName;
	svid[3] = SVID_EZNET_USERID;
	sVal[3] = userid;

	SetSVID(svid, sVal, 4);
	SetJsckIDList(mesMode, devList);
	SendEventReport(CEID_EZNET_JOB_CANCEL); //JSCK CEID 1015
}
//---------------------------------------------------------------------------
void __fastcall TFmEzNet::SendJobCancelFail(const int mesMode, const String recipeName, TStringList *devList, String userid)
{
	if (IsConnected() == false)
	{
		return;
	}

	long svid[4];
	String sVal[4];

	ZeroMemory(svid, 4);

	svid[0] = SVID_PORTID;
	sVal[0] = IntToStr(Chamber->ChamberID);
	svid[1] = SVID_EZNET_MES_MODE;
	sVal[1] = IntToStr(mesMode);
	svid[2] = SVID_PPID;
	sVal[2] = recipeName;
	svid[3] = SVID_EZNET_USERID;
	sVal[3] = userid;

	SetSVID(svid, sVal, 4);
	SetJsckIDList(mesMode, devList);
	SendEventReport(CEID_EZNET_JOB_CANCEL_FAIL); //JSCK CEID 1017
}
//---------------------------------------------------------------------------
void __fastcall TFmEzNet::OnS2F41W(long lMsgId)
{
// S2F41
	short ack = 0;
	String mode, rcmd, name, value, lotid, ppid, cstid;
	AnsiString log;
	WideString temp;
	bool isValidSuccess = false;
	// Ack
	//0 = Acknowledge, command has been performed
	//1 = Command does not exists
	//2 = Cannot perform now
	//3 = At least one parameter is invalid
	//4 = Acknowledge, command will be performed with completion signalled later by an event
	//5 = Rejected, Already in the desired condition
	//6 = No such object exists

	int count = EzNet->GetListItemOpen(lMsgId);
	if (count != 2)
	{
		ack = 3;

		long replyMsgId = EzNet->CreateReplyMsg(lMsgId);
		EzNet->AddU1Item(replyMsgId, &ack, 1);
		EzNet->SendMsg(replyMsgId);
		return;
	}

	int maxChamberNo = GetManager()->ChamberCount - 1;
	EzNet->GetAsciiItem(lMsgId, &temp);
	rcmd = temp;

	int chamberNo;
	count = EzNet->GetListItemOpen(lMsgId);
	for (int i = 0; i < count; i++)
	{
		WideString tmp;
		EzNet->GetListItemOpen(lMsgId);
			EzNet->GetAsciiItem(lMsgId, &tmp);
			name = tmp;
			EzNet->GetAsciiItem(lMsgId, &tmp);
			value = tmp;
		EzNet->GetListItemClose(lMsgId);

		if (name == "LOTID")
		{
			lotid = value;
		}
		else
		if (name == "PPID")
		{
			ppid = value;
		}
		else
		if (name == "CSTID")
		{
			cstid = value;
		}
		else
		if (name == "PORTID")
		{
			chamberNo = value.ToIntDef(CHAMBER_A);
		}
		else
		if (name == "VALID")
		{
			int tmp = value.ToIntDef(0);
			isValidSuccess = (tmp == 1) ? true : false;
		}

//		String str;
//		str.sprintf(L"RCMD:%s Name:%s Value:%s MsgID:%d ParamCnt:%d", rcmd.c_str(), name.c_str(), value.c_str(), lMsgId, count);
//		GetOvenDB()->SaveLog(str, MESSAGES, Chamber->ChamberID);
	}
	EzNet->GetListItemClose(lMsgId);

	/**********************************
	해당 명령에 대하여 장비 상태를 확인 후 적용 가능 여부를 판단하여 명령을 수행
	**********************************/
	bool isCureStartFailed = false;
	if (rcmd == "PP-SELECT")
	{
		if (chamberNo != Chamber->ChamberID)
		{
			ack = 3;
		}
		else if (Chamber->Step != STEP_IDLE )
		{
			ack = 2;
		}
		else
		{
			if (ppid.IsEmpty() == false)
			{
				if (GetManager()->AutomationKind == SECS_GEM_SCK)
				{
					if (GetOvenDB()->IsRecipeExist(Chamber->ChamberID, ppid))
					{
						if (FmJob->ChamberFrame[Chamber->ChamberID]->SelectRecipe(ppid) == false)
						{
							ack = 3;
						}
						else
						{
							SetProcessState(STATE_READY);
						}
					}
					else
					{
					   ack = 3;
					}
				}
				else
				{
					if (IsGemRecipeExist(ppid))
					{
						if (FmJob->ChamberFrame[Chamber->ChamberID]->SelectRemoteRecipe(ppid) == false)
						{
							ack = 3;
						}
						else
						{
							SetProcessState(STATE_READY);
						}
					}
					else
					{
					   ack = 3;
					}
				}
			}
			else
			{
				ack = 3;
			}
		}
	}
	else
	if( rcmd == "JOB-VALID" )	// for JSCK GEM
	{
		if (Chamber->ValidationRequested)
		{
			if (chamberNo != Chamber->ChamberID || Chamber->Step != STEP_IDLE )
			{
				ack = 2;
			}
			else
			{
				if (isValidSuccess)
				{
					if( ppid.IsEmpty() == false )
					{
						if( GetOvenDB()->IsRecipeExist(chamberNo, ppid) )
						{
							if( FmJob->ChamberFrame[Chamber->ChamberID]->SelectRecipe(ppid) == false )
							{
								ack = 3;
							}
							else
							{
								SetProcessState(STATE_READY);
								ack = 0;
							}
						}
						else
						{
						   ack = 3;
						}
					}
					else
					{
						ack = 3;//3 = At least one parameter is invalid
					}
				}
			}

			Chamber->ValidationRequested = false;
			Chamber->ValidationSuccess = isValidSuccess;
		}
	}
	else
	if( rcmd == "MGZ-VALID" )	// for JSCK GEM
	{
		if (Chamber->ValidationRequested)
		{
			if (chamberNo != Chamber->ChamberID || Chamber->Step != STEP_IDLE )
			{
				ack = 2;
			}

			Chamber->ValidationRequested = false;
			Chamber->ValidationSuccess = isValidSuccess;
		}
	}
	else
	if (rcmd == "START")
	{
		if (FmJob->ChamberFrame[Chamber->ChamberID]->CureStart(true) == false)
		{
			ack = 2;
			isCureStartFailed = true;
			if (GetManager()->AutomationKind == SECS_GEM_SCK)
			{
				Chamber->ValidationRequested = false;
				Chamber->ValidationSuccess = false;
			}
		}
		else
		{
//			SetProcessState(STATE_EXECUTING);
		}
	}
	else
	if (rcmd == "STOP")
	{
		if( InRange(chamberNo, 0, maxChamberNo) == false )
			ack = 3;//-2;
		else
		if( GetChamber(chamberNo)->Step == STEP_DONE )
			ack = 5;//-3;
		else
		{
			if( FmJob->ChamberFrame[chamberNo]->CureStop(true) == false )
				ack = 2;//-1 = Cannot perform now
		}
	}
	else
	{
		ack = 1;   // Command does not exists
	}

	if (ack == 0)
	{
		if (rcmd == "PP-SELECT")
		{
			String str;
			str.sprintf(L"The recipe [%s] is selected.", ppid.c_str());
			GetOvenDB()->SaveLog(str, MESSAGES, chamberNo);
		}
	}
	else
	{
        String str;
		str.sprintf(L"The remote command [%s] is denied.", rcmd.c_str());
		GetOvenDB()->SaveLog(str, MESSAGES, chamberNo);
	}

	long replyMsgId = EzNet->CreateReplyMsg(lMsgId);
	EzNet->AddU1Item(replyMsgId, &ack, 1);
	EzNet->SendMsg(replyMsgId);

	if (isCureStartFailed)
	{
		ShowMessageDlg();
	}
}
//---------------------------------------------------------------------------

void __fastcall TFmEzNet::OnS10F3(long lMsgId)
{
	short tid;
	WideString tmp;
	EzNet->GetListItemOpen(lMsgId);
		EzNet->GetU1Item(lMsgId, &tid);
		EzNet->GetAsciiItem(lMsgId, &tmp);
	EzNet->GetListItemClose(lMsgId);

	String msg = tmp;

	String str;
	str.sprintf(L"GEM received TerminalMessageSingle(MsgID:%d Command:%s).", lMsgId, msg.c_str());
	GetOvenDB()->SaveLog(str, MESSAGES, Chamber->ChamberID);

	SetMessageStr(msg);
    ShowMessageDlg();
}
//---------------------------------------------------------------------------
void __fastcall TFmEzNet::EzNetMsgReceived(TObject *Sender, long lMsgId)
{
	short nStream, nFunction, nWbit;
	long lLength;
	long rMsgID;

	EzNet->GetMsgInfo(lMsgId, &nStream, &nFunction, &nWbit, &lLength);
	if (nStream == 2 && nFunction == 41)
	{
		OnS2F41W(lMsgId);
	}
	else
	if (nStream == 7 && nFunction == 1)
	{
		OnS7F1W(lMsgId);
	}
    else
	if (nStream == 7 && nFunction == 3)
	{
		OnS7F3W(lMsgId);
	}
    else
	if (nStream == 7 && nFunction == 5)
	{
		OnS7F5W(lMsgId);
	}
    else
	if (nStream == 7 && nFunction == 17)
	{
		OnS7F17W(lMsgId);
	}
	else
	if (nStream == 7 && nFunction == 19)
	{
		OnS7F19W(lMsgId);
	}
	else
	if (nStream == 10 && nFunction == 3)
	{
		OnS10F3(lMsgId);
	}
	else
	if (nStream == 64 && nFunction == 18)
	{
		OnS64F18(lMsgId);
	}
}
//---------------------------------------------------------------------------

void __fastcall TFmEzNet::EzNetOtherEvent(TObject *Sender, short nEventId, long lParm)

{
//
}
//---------------------------------------------------------------------------

void __fastcall TFmEzNet::RefreshTimer(TObject *Sender)
{
	RequestGemStatus();
}
//---------------------------------------------------------------------------

void __fastcall TFmEzNet::EzNetConnected(TObject *Sender, OLECHAR *strHost, short nPort)

{
	IsEzNetConnected = true;
    StartGEM();
}
//---------------------------------------------------------------------------

void __fastcall TFmEzNet::EzNetDisconnected(TObject *Sender, OLECHAR *strHost, short nPort)

{
	IsEzNetConnected = false;
}
//---------------------------------------------------------------------------
void __fastcall TFmEzNet::SendMgzValidation(const int chamberNo,
	const int mesMode, const String recipeName, const String mgzId)
{
    if (IsConnected() == false)
	{
		return;
	}

	long svid[4];
	String sVal[4];

	ZeroMemory(svid, 4);

	svid[0] = SVID_PORTID;
	sVal[0] = IntToStr(chamberNo);
	svid[1] = SVID_EZNET_MES_MODE;
	sVal[1] = IntToStr(mesMode);
	svid[2] = SVID_EZNET_CSTID;
	sVal[2] = mgzId;
	svid[3] = SVID_PPID;
	sVal[3] = recipeName;

	SetSVID(svid, sVal, 4);
	WaitForSingleObject((void*)Handle, 500);
	SendEventReport(CEID_EZNET_MGZ_VALIDATION);   //JSCK CEID 1019
}
//---------------------------------------------------------------------------
void __fastcall TFmEzNet::SendMgzValidationCancel(const int chamberNo,
	const int mesMode, const String recipeName, const String mgzId)
{
    if (IsConnected() == false)
	{
		return;
	}

	long svid[4];
	String sVal[4];

	ZeroMemory(svid, 4);

	svid[0] = SVID_PORTID;
	sVal[0] = IntToStr(chamberNo);
	svid[1] = SVID_EZNET_MES_MODE;
	sVal[1] = IntToStr(mesMode);
	svid[2] = SVID_EZNET_CSTID;
	sVal[2] = mgzId;
	svid[3] = SVID_PPID;
	sVal[3] = recipeName;

	SetSVID(svid, sVal, 4);
	WaitForSingleObject((void*)Handle, 500);
	SendEventReport(CEID_EZNET_MGZ_VALIDATION_CANCEL);    //JSCK CEID 1020
}
//---------------------------------------------------------------------------
void __fastcall TFmEzNet::SendMgzValidationFail(const int chamberNo,
	const int mesMode, const String recipeName, const String mgzId)
{
    if (IsConnected() == false)
	{
		return;
	}

	long svid[4];
	String sVal[4];

	ZeroMemory(svid, 4);

	svid[0] = SVID_PORTID;
	sVal[0] = IntToStr(chamberNo);
	svid[1] = SVID_EZNET_MES_MODE;
	sVal[1] = IntToStr(mesMode);
	svid[2] = SVID_EZNET_CSTID;
	sVal[2] = mgzId;
	svid[3] = SVID_PPID;
	sVal[3] = recipeName;

	SetSVID(svid, sVal, 4);
	WaitForSingleObject((void*)Handle, 500);
	SendEventReport(CEID_EZNET_MGZ_VALIDATION_FAIL);  //JSCK CEID 1021
}
//---------------------------------------------------------------------------
//void __fastcall TFmEzNet::SendPvDataList()
//{
//	if (Chamber == nullptr)
//	{
//		return;
//	}
//
//	String str;
//	long svid = SVID_EZNET_ACT_DATA_LIST;
//	double value;
//
//	EzGem->CloseMsg(svid);
//	EzGem->OpenListItem(svid);
//	for (int i = 0; i < Chamber->JsckPvDataList.size(); i++)
//	{
//		JSCK_GEM_PV_DATA data = Chamber->JsckPvDataList[i];
//
//		EzGem->OpenListItem(svid);
//		{
//			EzGem->OpenListItem(svid);
//			{
//				value = SVID_EZNET_ACT_TEMP;
//				EzGem->AddU4Item(svid, &value, 1);
//				str.sprintf(L"%.1f", data.PV);
//				EzGem->AddAsciiItem(svid, GetBstr(str).c_bstr(), str.Length());
//			}
//			EzGem->CloseListItem(svid);
//
//			for (int j = 0; j < 5; j++)
//			{
//				EzGem->OpenListItem(svid);
//				{
//					value = SVID_EZNET_ACT_LOGGER1 + j;
//					EzGem->AddU4Item(svid, &value, 1);
//					str.sprintf(L"%.1f", data.Logger[j]);
//					EzGem->AddAsciiItem(svid, GetBstr(str).c_bstr(), str.Length());
//				}
//				EzGem->CloseListItem(svid);
//			}
//		}
//		EzGem->CloseListItem(svid);
//	}
//	EzGem->CloseListItem(svid);
//
//	SendEventReport(CEID_EZNET_ACTUAL_DATA);
//}

//---------------------------------------------------------------------------

