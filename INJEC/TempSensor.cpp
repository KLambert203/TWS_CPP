
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2022 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TWS - CPP
// File      INJEC/TempSensor.cpp

// ===== C ==================================================================
#include <assert.h>

// ===== INJEC ==============================================================
#include "TempSensor.h"
#include "TSL_ComPort.h"
#include "TSL_File.h"

// Constants
// //////////////////////////////////////////////////////////////////////////

#define SYNC static_cast<int8_t>(0xff)

// Public
// //////////////////////////////////////////////////////////////////////////

TempSensor::TempSensor() : mLink(NULL)
{
    mSum.mHumidity_pc = 0.0;
    mSum.mTemp_C = 0.0;
}

TempSensor::~TempSensor()
{
}

// Cette fonction lit 3 octets du port COM. Le senseur transmet constament
// des donnees et il est impossible de savoir combien nous avons perdu
// d'octet avant de nous connecter. Il est facile de nous synchroniser car
// nous savons que le senseur envoit toujours une valeur de synchronisation
// (0xff) suivie du pourcentage d'humidite et de la temperature en Celcius.
// Les trois condition en fin de fonction dertermine la position de l'octet
// de synchronisation et par le fait meme la position des deux donnees. Si un
// ensemble de 3 octets ne contient pas d'octets de synchronisation, les
// donnees sont erronees.
void TempSensor::GetData(double* aHumidity_pc, double* aTemp_C)
{
    Data lData;
    mLink->GetData(&lData.mHumidity_pc, &lData.mTemp_C);

    mSum.mHumidity_pc += lData.mHumidity_pc;
    mSum.mTemp_C      += lData.mTemp_C;

    mList.push_front(lData);

    unsigned int lLen = mList.size();
    if (10 < lLen)
    {
        mSum.mHumidity_pc -= mList.back().mHumidity_pc;
        mSum.mTemp_C      -= mList.back().mTemp_C;

        mList.pop_back();
        lLen--;
    }

    *aHumidity_pc = mSum.mHumidity_pc / lLen;
    *aTemp_C      = mSum.mTemp_C      / lLen;
}

void TempSensor::SetLink(ITempSensorLink* iTempSensorLink)
{
    mLink = iTempSensorLink;
}
