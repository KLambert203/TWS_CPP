
// Author    KMS - Martin Dubois, P. Eng.
// Copyright (C) 2022 KMS
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   TWS - CPP
// File      INJEC/TempSensor.h

#pragma once

// ===== C++ ================================================================
#include <list>

// ===== Windows ============================================================
#include <Windows.h>
// ===== INJECT =============================================================

// COMMENTAIRE PEDAGOGIQUE
// La prochaine ligne est une "Forware declaration". Elle permet de declarer
// une classe en avance sans fournir sa declaration complete. Cela permet
// d'utiliser des pointeurs vers cette classe sans devoir inclure le fichier
// d'entete qui declare cette classe et les autre fichier entete que celui-ci
// inclu. Cette maniere de faire permet de rendre la compilation plus rapide
// et surtout de reduire le chance d'avoir des dependance cyclique dans les
// les fichierss entetes.
// Naturellement, le fichier source (.cpp) devra inclure le fichier entete
// qui contient la declaration de la classe pour pouvoir utiliser les
// methodes de la classe.
class ITempSensorLink;

class TempSensor
{

public:

    TempSensor(const char* aComPortName);

    ~TempSensor();

    void GetData(double* aHumidity_pc, double* aTemp_C);

private:

    typedef struct
    {
        double mHumidity_pc;
        double mTemp_C;
    }
    Data;

    HANDLE mComPort;

    std::list<Data> mList;

    Data mSum;

};
