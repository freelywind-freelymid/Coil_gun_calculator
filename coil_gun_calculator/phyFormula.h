#include <math.h>
#include <iostream>

#include "capacitor.h"
#include "enameledWire.h"

const double Pi = 3.14159265358979323846;

const double u_air = 4 * Pi * pow(10, -7);

const double p_copper = 1.68 * pow(10, -8);
const double p_aluminium = 2.65 * pow(10, -8);

double get_magnetic_field_strength(int numberTurn, double current_A, double length_m);

double get_magnetic_flux_density(int numberTurn, double current_A, double length_m);
double get_magnetic_flux_density(int numberTurn, double current_A, double length_m, double u);

double get_magnetic_flux(double magnetic_flux_density, double area_m2);

double get_inductance(int numberTurn, double magnetic_flux, double current_A);
double get_inductance(int numberTurn, double area_m2, double length_m, double u);

double get_total_energy(double voltage_or_v, double c_or_mass);
double get_cap_loss_energy(double current_A, capacitor cap, double time_s);
double get_enameled_wire_loss_energy(double current_A, enameledWire wire, double time_s);

double get_resistance(double length_m, double area_m2, double p);

double get_current(double voltage_V, double resistance_ohm);
void charge_release_cap_voltage(capacitor cap, enameledWire wire, double time_s, bool isCharge);
double get_RC_constant_time(capacitor cap, enameledWire wire);

