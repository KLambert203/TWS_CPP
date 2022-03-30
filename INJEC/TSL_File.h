#pragma once
#include <list>
#include <Windows.h>
#include <fstream>

#include "ITempSensorLink.h"

class TSL_File : public ITempSensorLink
{
public:
	
	TSL_File(const char* aFileName);

	~TSL_File();

	virtual void GetData(double* aHumidity_pc, double* aTemp_C);

private:

	std::ifstream mFile;
};