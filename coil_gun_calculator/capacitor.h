#pragma once
class capacitor
{
private:
	double maxVoltage = 50.0;
	double curr_volt = 0.0;
	double C_F = 0.001;
	double resistance_ohm = 0.1;

public:
	capacitor();
	capacitor(double maxVoltage, double C_F);
	capacitor(double maxVoltage, double C_F, double resistance_mohm);

	void setMaxVoltage(double voltage_V);
	double getMaxVoltage();

	void setCurr_volt(double voltage_V);
	double getCurr_volt();

	void setCapacity(double C_uF);
	double getCapacity();

	void setResistance(double resistance_mohm);
	double getResistance();
};

