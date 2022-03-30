#include <assert.h>

#include "TSL_File.h"

#define SYNC static_cast<int8_t>(0xff)

TSL_File::TSL_File(const char* aFileName): mFile(aFileName)
{
}

TSL_File::~TSL_File()
{
}

void TSL_File::GetData(double* aHumidity_pc, double* aTemp_C)
{
	assert(NULL != aHumidity_pc);
	assert(NULL != aTemp_C);

	if (mFile.eof())
	{
		mFile.seekg(0);
	}

	mFile >> *aHumidity_pc;
	mFile >> *aTemp_C;

	Sleep(50);
}