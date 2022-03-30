#pragma once
#include <list>
#include <Windows.h>

#include "ITempSensorLink.h"

class TSL_ComPort : public ITempSensorLink
{
public:
	TSL_ComPort(const char* aComPortName);
	~TSL_ComPort();

	void GetData(double* aHumidity_pc, double* aTemp_C);
private:

	typedef struct
	{
		double mHumidity_pc;
		double mTemp_C;
	} Data;

	HANDLE mComPort;

	std::list<Data> mList;
};