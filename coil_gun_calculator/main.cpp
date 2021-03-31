#include <iostream>

#include "phyFormula.h"
#include "enameledWire.h"
#include "capacitor.h"

using namespace std;

double* get_loss_energy_array(enameledWire wire, capacitor cap, int resolution, double maxTime_s, double minTime_s) {

	//0 total loss; 1 wire; 2 cap; 3 total_ouput_energy
	double* energyLoss = new double[4];
	
	try {	
		double wire_resistance = get_resistance(wire.getLength(), Pi * pow(wire.getDiameter() / 2, 2), p_copper);
		if (wire_resistance == -1) {
			return new double[4]{ -1,-1,-1,-1 };
		}
		else {
			wire.setResistance(wire_resistance);
		}

		double delta = (maxTime_s - minTime_s) / resolution;

		double long current;
		double total_resistance = cap.getCapacity() + wire.getResistance();

		double wire_loss = 0.0;
		double cap_loss = 0.0;

		double total_output_energy = 0.0;
		double temp, delta_cap_voltage;

		for (double i = minTime_s; i < maxTime_s; i += delta) {
			current = get_current(cap.getCurr_volt(), total_resistance);

			wire_loss += get_enameled_wire_loss_energy(current, wire, delta);
			cap_loss += get_cap_loss_energy(current, cap, delta);

			temp = cap.getCurr_volt();
			charge_release_cap_voltage(cap,wire,delta,false);
			delta_cap_voltage = abs(temp - cap.getCurr_volt());

			total_output_energy += 0.5 * cap.getCapacity() * delta_cap_voltage * delta_cap_voltage;
		}

		energyLoss[0] = (double)(wire_loss + cap_loss);
		energyLoss[1] = (double)wire_loss;
		energyLoss[2] = (double)cap_loss;
		energyLoss[3] = (double)total_output_energy;
	}
	catch (exception) {
		return new double[4]{ -1,-1,-1,-1 };
	}

	return energyLoss;
}

int main() {

	enameledWire wire = enameledWire();
	capacitor cap = capacitor();

	bool flag = false;
	double doubleTemp = 0.0;

	cout << "\nWelcome to coil gun calculator!\n\n";
	cout << "Please input parameters of capacitor.\n";
	cout << "Max voltage (unit: V), capacity (unit:uF) and resistance (unit: m ohm) (if have)\n";
	cout << "If have not, enter -1. Default 50V, 1000uF and 100m ohm.\n";
	
	do {
		try {
			cin >> doubleTemp;
			if (doubleTemp != -1) {
				cap.setMaxVoltage(doubleTemp);
			}
			else {
				cap.setMaxVoltage(50.0);
			}

			cin >> doubleTemp;
			if (doubleTemp != -1) {
				cap.setCapacity(doubleTemp/1000000);
			}
			else {
				cap.setCapacity(1000/1000000);
			}

			cin >> doubleTemp;
			if (doubleTemp != -1) {
				cap.setResistance(doubleTemp / 1000);
			}
			else {
				cap.setResistance(100/1000);
			}

			flag = true;
		}
		catch (exception) {
			cout << "It is not a vaild number. Please enter again.";
			flag = false;
		}

		if (cap.getMaxVoltage() < 0 || cap.getCapacity() < 0 || cap.getResistance() < 0) {
			cout << "It is not a vaild number. Please enter again.";
			flag = false;
		}

	} while (!flag);
	flag = false; //reset

	cout << "\n\n";

	cout << "Please input parameters of wire.\n";
	cout << "Diameter (unit: mm) and length (unit: m) (if have)\n";
	cout << "If have not, enter -1. Default 0.8mm, 20m.\n";

	do {
		try {
			cin >> doubleTemp;
			if (doubleTemp != -1) {
				wire.setDiameter(doubleTemp);
			}
			else {
				wire.setDiameter(0.8);
			}

			cin >> doubleTemp;
			if (doubleTemp != -1) {
				wire.setLength(doubleTemp);
			}
			else {
				wire.setLength(20);
			}

			flag = true;
		}
		catch (exception) {
			cout << "It is not a vaild number. Please enter again.";
			flag = false;
		}

		if (wire.getDiameter() < 0 || wire.getLength() < 0) {
			cout << "It is not a vaild number. Please enter again.";
			flag = false;
		}

	} while (!flag);
	flag = false; //reset

	double* energy = get_loss_energy_array(wire,cap,100,6*cap.getCapacity()*(cap.getResistance()+wire.getResistance()),0);

	cout << "Totle energy loss: " << energy[0] << "J\n";
	cout << "The energy loss on wire: " << energy[1] << "J\n";
	cout << "The energy loss on capacitor: " << energy[2] << "J\n";
	cout << "Total output energy : " << energy[3] << "J\n\n";

	return 0;
}