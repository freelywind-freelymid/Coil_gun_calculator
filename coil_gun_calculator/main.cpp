#include <iostream>

#include "phyFormula.h"
#include "enameledWire.h"

using namespace std;

double get_enameled_wire_total_loss_energy(enameledWire wire,int resolution, double min, double max) {

	wire.setResistance(get_resistance(wire.getLength(),pow((wire.getDiameter()/2),2)*Pi,p_copper));

	double delta = (max - min)/resolution;

	for (double i = 0; i < max;i += delta) {
		
	}
}

int main() {

	enameledWire wire = enameledWire();

	cout << "Welcome to coil gun calculator!\n";


	return 0;
}