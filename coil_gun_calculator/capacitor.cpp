#include "capacitor.h"

capacitor::capacitor()
{
}

capacitor::capacitor(double maxVoltage, double C_uF)
{
	this->maxVoltage = maxVoltage;
	this->C_F = C_uF/1000000;
}

capacitor::capacitor(double maxVoltage, double C_uF, double resistance_mohm)
{
	this->maxVoltage = maxVoltage;
	this->C_F = C_uF/1000000;
	this->resistance_ohm = resistance_mohm/1000;
}

void capacitor::setMaxVoltage(double voltage_V)
{
	this->maxVoltage = voltage_V;
}

double capacitor::getMaxVoltage()
{
	return (double)this->maxVoltage;
}

void capacitor::setCurr_volt(double voltage_V)
{
	this->curr_volt = voltage_V;
}

double capacitor::getCurr_volt()
{
	return (double) this->curr_volt;
}

void capacitor::setCapacity(double C_uF)
{
	this->C_F = C_uF/1000000;
}

double capacitor::getCapacity()
{
	return (double) this->C_F;
}

void capacitor::setResistance(double resistance_mohm)
{
	this->resistance_ohm = resistance_mohm/1000;
}

double capacitor::getResistance()
{
	return (double) this->resistance_ohm;
}
