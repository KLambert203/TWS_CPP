
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2022 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TWS - CPP
// File      INJEC/INJEC.cpp

// ===== C ==================================================================
#include <assert.h>
#include <signal.h>

// ===== C++ ================================================================
#include <iostream>

// ====== INJECT ============================================================
#include "TempSensor.h"
#include "TSL_ComPort.h"
#include "TSL_File.h"

// Static variable
// //////////////////////////////////////////////////////////////////////////

static bool sStop = false;

// Static function declarations
// //////////////////////////////////////////////////////////////////////////

// COMMENTAIRE PEDAGOGIQUE
// La declaration de OnSigInt doit contenir le _cdecl parce que le code de la
// librairie standard C qui l'appele utilise cet convention d'appel qui
// fonctionne aussi avec des modules ecrit en C.
static void _cdecl OnSigInt(int aSignal);

// Entry point
// //////////////////////////////////////////////////////////////////////////

int main(int aCount, const char ** aVector)
{
    assert(1 <= aCount);
    assert(NULL != aVector);

    if (2 > aCount)
    {
        std::cerr << "USER ERROR  You must pass the COM port name as first argument\n";
        return 1;
    }

    assert(NULL != aVector[1]);

    _crt_signal_t lSig = signal(SIGINT, OnSigInt);
    assert(SIG_DFL == lSig);

    std::cout << "INSTRUCTION  Press Ctrl-C to stop\n";

    TSL_ComPort* lComPort = NULL;
    TSL_File* lFile = NULL;

    try
    {
        ITempSensorLink* lLink;

        if (0 == _strnicmp(aVector[1], "COM", 3))
        {
            lComPort = new TSL_ComPort(aVector[1]);
            lLink = lComPort;
        }
        else
        {
            lFile = new TSL_File(aVector[1]);
            lLink = lFile;
        }

        TempSensor lTS;
        lTS.SetLink(lLink);

        while (!sStop)
        {
            double lHumidity_pc;
            double lTemp_C;

            lTS.GetData(&lHumidity_pc, &lTemp_C);

            printf("Humidity: %.1f %%, Temperature: %.1f C\r", lHumidity_pc, lTemp_C);
        }

        std::cout << "\nStopped\n";
    }
    catch (std::exception eE)
    {
        std::cerr << "EXCEPTION  " << eE.what() << "\n";
        return 2;
    }

    return 0;
}

// Static function
// //////////////////////////////////////////////////////////////////////////

void OnSigInt(int aSignal)
{
    assert(SIGINT == aSignal);

    std::cout << "\nCtrl-C\n";

    sStop = true;
}
