#pragma once
class enameledWire
{
private:
	double diameter = 0.0;
	double length = 0.0;
	double resistance = 0.0;

public:
	enameledWire();
	enameledWire(double diameter_mm, double length_m);
	enameledWire(double resistance_ohm);

	void setDiameter(double diameter_mm);
	double getDiameter();

	void setLength(double length_m);
	double getLength();

	void setResistance(double resistance_ohm);
	double getResistance();
};

