#pragma once
class ITempSensorLink
{
public:
	virtual void GetData(double* aHumidity_pc, double* aTemp_C) = 0;

};