#include "enameledWire.h"

enameledWire::enameledWire()
{
}

enameledWire::enameledWire(double diameter_mm, double length_m)
{
	this->diameter = diameter_mm;
	this->length = length_m;
}

enameledWire::enameledWire(double resistance_mohm)
{
	this->resistance = resistance_mohm/1000;
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

void enameledWire::setResistance(double resistance_mohm)
{
	this->resistance = resistance_mohm/1000;
}

double enameledWire::getResistance()
{
	return this->resistance;
}
