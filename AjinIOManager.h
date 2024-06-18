//---------------------------------------------------------------------------

#ifndef AjinIOManagerH
#define AjinIOManagerH
//---------------------------------------------------------------------------
#include "IOControlManager.h"

class AjinIOManager : public IOControlManager
{
protected:
	std::vector<int> AjinIOModuleType;

public:
	AjinIOManager();
	~AjinIOManager();

	bool __fastcall GetIsOutput(unsigned int addr);
	bool __fastcall GetValue(unsigned int addr);
	void __fastcall SetOutputValue(unsigned int addr, bool value);
};

#endif
