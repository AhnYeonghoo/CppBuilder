//---------------------------------------------------------------------------

#ifndef TowerLampControlH
#define TowerLampControlH
#include <string>
#include <iostream>

//---------------------------------------------------------------------------
enum { TWR_RED = 0, TWR_YEL, TWR_GRN, TWR_BUZ, TWR_COUNT };
enum { TWR_AUTURUN = 0, TWR_STOP, TWR_LOTEND, TWR_ERR, TWR_MODE_COUNT };
enum { LAMP_OFF = 0, LAMP_ON, LAMP_BLINK };
enum { BUZZ_OFF = 0, BUZZ_ALARM };

class TowerLampControl
{
protected:
	int nTowerVal[TWR_COUNT][TWR_MODE_COUNT];

public:
	TowerLampControl();
	~TowerLampControl();

	int GetTwrVal(const auto nKind, const auto nMode) const;
	void SetTwrVal(const auto nKind, const auto nMode, const auto nVal);
	auto GetTwrValStr(const auto nKind) const;

	virtual bool operator==(const TowerLampControl& arg);
	virtual TowerLampControl& operator=(const TowerLampControl& arg);
	virtual void LoadValue(const auto sPath);
    virtual void SaveValue(const auto sPath);
};
#endif
