//---------------------------------------------------------------------------

#ifndef MelsecCCLinkManagerH
#define MelsecCCLinkManagerH
//---------------------------------------------------------------------------
#include "IOControlManager.h"

#define MAX_IO_COUNT		64
#define MAX_INPUT_COUNT     32
#define MAX_OUTPUT_COUNT    32

class MelsecCCLinkManager : public IOControlManager
{
protected:

public:
	MelsecCCLinkManager();
	~MelsecCCLinkManager();

    bool __fastcall GetIsOutput(unsigned int addr);
	bool __fastcall GetValue(unsigned int addr);
	void __fastcall SetOutputValue(unsigned int addr, bool value);
};
#endif
