//---------------------------------------------------------------------------

#ifndef DatabaseH
#define DatabaseH

#include <memory>
#include <Data.Win.ADDDB.hpp>
#include <System.Classes.hpp>
#include <System.syncObjs.hpp>
#include "Defines.h"
#include "Singleton.h"

enum
{
	ALL_ALL_ALL = 0, ALL_ALL_TIME,
	ALL_ALM_ALL,     ALL_ALM_TIME,
	ALL_MSG,ALL,     ALL_MSG_TIME,
	A_ALL_ALL,       A_ALL_TIME,
	A_ALM_ALL,       A_ALM_TIME,
	A_MSG_ALL,       A_MSG_TIME,
	B_ALL_ALL,       B_ALL_TIME,
	B_ALM_ALL,       B_ALM_TIME,
	B_MSG_ALL,       B_MSG_TIME
};

enum LOGTYPE
{
	ALARM = 0,
	MESSAGES,
	PRODUCT
};

typedef struct _OVEN_RECIPE
{
	int ChamberNo;
	String Recipe;
	int PtnNo;
	int CureTemp;
	int CureTime;

	void OVEN_RECIPE()
	{
		ChamberNo = 0;
		PtnNo = 0;
		CureTemp = 0;
		CureTime = 0;
		Recipe = "";
	}
} OVEN_RECIPE;

typedef struct _DB_USER
{
	int Grade;
	AnsiString ID;
	AnsiString Pw;
	AnsiString Name;

	void USER_INFO()
	{
		Grade = 0;
		ID = "";
		Pw = "";
		Name = "";
	}
} DB_USER;

typedef struct _DB_ERROR
{
	String Name;
	String Cause;
	String Action;
} DB_ERROR;

typedef struct OVEN_WORK
{
	TDateTime StartTime;
	TDateTime EndTime;
	String Recipe;
	int PtnNo;
	int CureTemp;
	int CureTime;
	int Remote;
	String UserID;
	int ChamberNo;
	String Filename;
} OVEN_WORK;

typedef std::shared_ptr<TADOQuery> QueryPtr;

class Database : public Singleton<Database>
{
protected:
	TCriticalSection *CriticalSection;

	TADOConnection *ErrDB;
	TADOConnection *MainDB;

	bool __fastcall IsDbConnected(TADOConnection *db);
	bool __fastcall DoExecSQL(TADOConnection *db, String queryStr);
	QueryPtr __fastcall DoOpen(TADOConnection *db, String queryStr);

public:
	Database();
	~Database();

	bool NewLogAdded;

	bool __fastcall ConnectErrDB();
	bool __fastcall IsFieldExisted(String table, String field);
};
//---------------------------------------------------------------------------
#endif
