#include <assert.h>

#include "TSL_ComPort.h"

#define SYNC static_cast<int8_t>(0xff)

TSL_ComPort::TSL_ComPort(const char* aComPortName)
{
    mComPort = CreateFile(aComPortName, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, NULL);

    if (INVALID_HANDLE_VALUE == mComPort)
    {
        throw std::exception("CreateFile( , , , , , , ) failed!");
    }

    DCB lDCB;

    memset(&lDCB, 0, sizeof(lDCB));

    lDCB.DCBlength = sizeof(lDCB);

    if (!GetCommState(mComPort, &lDCB))
    {
        throw std::exception("GetCommState( , ) failed!");
    }

    //Modifier la config du port COM

    lDCB.fBinary = true;
    lDCB.BaudRate = CBR_115200;
    lDCB.ByteSize = 8;
    lDCB.StopBits = ONESTOPBIT;
    lDCB.fParity = NOPARITY;

    if (!SetCommState(mComPort, &lDCB))
    {
        throw std::exception("SetCommState( , ) failed!");
    }
}

TSL_ComPort::~TSL_ComPort()
{
    assert(INVALID_HANDLE_VALUE != mComPort);

    BOOL lRet = CloseHandle(mComPort);
    assert(lRet);

    (void)lRet;
}

void TSL_ComPort::GetData(double* aHumidity_pc, double* aTemp_C)
{
    assert(NULL != aHumidity_pc);
    assert(NULL != aTemp_C);

    // La temperature peut etre negative, il faud donc utiliser un type
    // signe.

    int8_t lRaw[3];
    DWORD  lSize_byte;

    if (!ReadFile(mComPort, lRaw, sizeof(lRaw), &lSize_byte, NULL))
    {
        throw std::exception("ReadFile( , , , ,  ) failed");
    }

    assert(sizeof(lRaw) == lSize_byte);

    Data lData;

    if (SYNC == lRaw[0]) { *aHumidity_pc = lRaw[1]; *aTemp_C = lRaw[2]; }
    else if (SYNC == lRaw[1]) { *aHumidity_pc = lRaw[2]; *aTemp_C = lRaw[0]; }
    else if (SYNC == lRaw[2]) { *aHumidity_pc = lRaw[0]; *aTemp_C = lRaw[1]; }
    else
    {
        throw std::exception("Corrupted data");
    }
}