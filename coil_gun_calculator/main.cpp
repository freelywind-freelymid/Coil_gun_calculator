#include <iostream>

#include "phyFormula.h"
#include "enameledWire.h"
#include "capacitor.h"

using namespace std;

double* get_loss_energy_array(enameledWire wire, capacitor cap, int resolution, double maxTime_s, double minTime_s) {

	//0 total loss; 1 wire; 2 cap; 3 total_ouput_energy
	double* energyLoss = new double[4];
	
	try {			
		double delta = (maxTime_s - minTime_s) / resolution;

		double long current;
		double total_resistance = cap.getCapacity() + wire.getResistance();

		double wire_loss = 0.0;
		double cap_loss = 0.0;

		double total_output_energy = 0.0;
		double temp,delta_cap_voltage;

		temp = cap.getCurr_volt();

		for (double i = minTime_s; i < maxTime_s; i += delta) {
			current = get_current(cap.getCurr_volt(), total_resistance);

			wire_loss += get_enameled_wire_loss_energy(current, wire, delta);
			cap_loss += get_cap_loss_energy(current, cap, delta);

			cap = charge_release_cap_voltage(cap,wire,i,false);
		}

		delta_cap_voltage = abs(cap.getCurr_volt() - temp);

		total_output_energy = 0.5 * cap.getCapacity() * delta_cap_voltage * delta_cap_voltage;

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
	int intTemp = 0;

	int numberOfwire = 1;
	double diameterFirstCircle = 30.0;
	int numberOfLevel = 1;
	int turnOfLevel = 50;
	bool isOneWireOneLevel = true;
	double connectionTime = 0.0;

	cout << "\n---------------------------------------------------------------------------------------------------------------\n";
	cout << "----------------------------------------Welcome to coil gun calculator!----------------------------------------\n";
	cout << "---------------------------------------------------------------------------------------------------------------\n\n";

	cout << "Please input parameters of capacitor.\n";
	cout << "Max voltage (unit: V), capacity (unit:uF), resistance (unit: m ohm) and current voltage (unit: V) (if have)\n";
	cout << "If have not, enter -1. Default 50V, 1000uF, 100m ohm and 40V.\n";
	
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
				cap.setCapacity(doubleTemp);
			}
			else {
				cap.setCapacity(1000);
			}

			cin >> doubleTemp;
			if (doubleTemp != -1) {
				cap.setResistance(doubleTemp);
			}
			else {
				cap.setResistance(100);
			}

			cin >> doubleTemp;
			if (doubleTemp != -1) {
				cap.setCurr_volt(doubleTemp);
			}
			else {
				cap.setCurr_volt(40);
			}

			flag = true;
		}
		catch (exception) {
			cout << "It is not a vaild number. Please enter again.\n";
			flag = false;
		}

		if (cap.getMaxVoltage() < 0 || cap.getCapacity() < 0 || cap.getResistance() < 0) {
			cout << "It is not a vaild number. Please enter again.\n";
			flag = false;
		}

	} while (!flag);
	flag = false; //reset

	cout << "\n";

	cout << "How many wire connect in parallel? (if know)\n";
	cout << "If don't know, enter -1. Default 1 wire only.\n";

	do {
		try {
			cin >> intTemp;
			if (intTemp != -1) {
				numberOfwire = 1;
			}
			else if(intTemp >= 0){
				numberOfwire = intTemp;
			}		

			flag = true;
		}
		catch (exception) {
			numberOfwire = 1;
			cout << "It is not a vaild number. Please enter again.\n";
			flag = false;
		}

	} while (!flag);
	flag = false; //reset

	cout << "\n";

	cout << "Is more than one wire on one level?\n";
	cout << "If 'Yes', please enter 1. If 'No', please enter 0.\n";

	do {
		try {
			cin >> intTemp;
			if (intTemp == 1 || intTemp == 0) {
				if (intTemp == 1) {
					isOneWireOneLevel = false;
				}
				else {
					isOneWireOneLevel = true;
				}
			}

			flag = true;
		}
		catch (exception) {
			cout << "It is not a vaild number. Please enter again.\n";
			flag = false;
		}

	} while (!flag);
	flag = false; //reset

	cout << "\n";

	cout << "Please input parameters of wire.\n";
	cout << "Diameter (unit: mm), diameter of first level (unit: mm), number of level and number of turn on each level. (if have)\n";
	cout << "If have not, enter -1. Default 0.8mm, 30mm, 1 and 50.\n";

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
				diameterFirstCircle = doubleTemp;
			}
			else {
				diameterFirstCircle = 30.0;
			}	

			cin >> intTemp;
			if (intTemp != -1) {
				numberOfLevel = intTemp;
			}
			else {
				numberOfLevel = 1;
			}

			cin >> intTemp;
			if (intTemp != -1) {
				turnOfLevel = intTemp;
			}
			else {
				turnOfLevel = 50;
			}

			if (wire.getDiameter() < 0 || diameterFirstCircle < 0 || numberOfLevel <= 0 || turnOfLevel < 0) {
				cout << "It is not a vaild number. Please enter again.\n";
				flag = false;
			}
			else {
				enameledWire* wireArray = new enameledWire[numberOfwire];

				for (int i = 0; i < numberOfwire; i++) {
					wireArray[i].setDiameter(wire.getDiameter() / 1000);

					double length = 0.0;
					if (isOneWireOneLevel) {
						length = 2 * Pi * (diameterFirstCircle / 2000 + i * wire.getDiameter()) * turnOfLevel;
						wireArray[i].setLength(length);
					}
					else {
						for (int i = 0; i < numberOfLevel; i++) {
							length += 2 * Pi * (diameterFirstCircle / 2000 + i * wire.getDiameter()) * turnOfLevel;
						}

						wireArray[i].setLength(length);
					}

					double wire_resistance = get_resistance(wire.getLength(), Pi * wire.getDiameter() * wire.getDiameter() / 4, p_copper);
					if (wire_resistance != -1) {
						wireArray[i].setResistance(wire_resistance * 1000);						
					}
				}	

				double total_resistance = 0.0;
				if (isOneWireOneLevel) {
					for (int i = 0; i < numberOfwire; i++) {
						total_resistance += (1 / wireArray[i].getResistance());
					}

					total_resistance = 1 / total_resistance;

					wire.setResistance(total_resistance);
				}
				else {
					 wire.setResistance(wireArray[0].getResistance()/numberOfwire);
				}
			}			

			flag = true;
		}
		catch (exception) {
			cout << "It is not a vaild number. Please enter again.\n";
			flag = false;
		}		

	} while (!flag);
	flag = false; //reset

	cout << "\n";

	cout << "Connection time (unit: ms)?\n";
	cout << "If you want to release 99.8% energy (6RC), please enter -1.\n";

	do {
		try {
			flag = true;

			cin >> doubleTemp;
			if (doubleTemp == -1) {
				connectionTime = get_RC_constant_time(cap, wire) * 6;
			}
			else if (doubleTemp >= 0) {
				connectionTime = doubleTemp;
			}
			else {
				flag = false;
			}
		}
		catch (exception) {
			cout << "It is not a vaild number. Please enter again.\n";
			flag = false;
		}

	} while (!flag);
	flag = false; //reset

	cout << "\n";

	double total_resistance = cap.getCapacity() + wire.getResistance();
	double peak_current = get_current(cap.getCurr_volt(),total_resistance);

	double* energy = get_loss_energy_array(wire,cap,10000,connectionTime,0.0);

	cout << "---------------------------------------------------------------------------------------------------------------\n";
	cout << "Result\n";
	cout << "---------------------------------------------------------------------------------------------------------------\n";
	cout << "Totle energy loss: " << energy[0] << " J \t\t\t\t The total resistance: " << total_resistance << " ohm \n";
	cout << "The energy loss on wire: " << energy[1] << " J	\t\t The resistance of wire: " << wire.getResistance() << " ohm \n";
	cout << "The energy loss on capacitor: " << energy[2] << " J \t\t The resistance of capacitor: " << cap.getResistance() <<" ohm \n\n";
	cout << "Total output energy: " << energy[3] << " J \t The RC time: " << get_RC_constant_time(cap,wire) << " s \t Total time: " << connectionTime << " s \n";
	cout << "Peak current: " << peak_current << " A \t Efficiency: " << (1 - energy[0] / energy[3]) * 100 << " %\n";

	cout << "\n";

	return 0;
}