#include "enameledWire.h"

enameledWire::enameledWire()
{
}

enameledWire::enameledWire(double diameter_mm, double length_m)
{
	this->diameter = diameter_mm;
	this->length = length_m;
}

enameledWire::enameledWire(double resistance_ohm)
{
	this->resistance = resistance_ohm;
}

void enameledWire::setDiameter(double diameter_mm)
{
	this->diameter = diameter_mm/1000;
}

double enameledWire::getDiameter()
{
	return this->diameter;
}

void enameledWire::setLength(double length_m)
{
	this->length = length_m;
}

double enameledWire::getLength()
{
	return this->length;
}

void enameledWire::setResistance(double resistance_ohm)
{
	this->resistance = resistance_ohm;
}

double enameledWire::getResistance()
{
	return this->resistance;
}
