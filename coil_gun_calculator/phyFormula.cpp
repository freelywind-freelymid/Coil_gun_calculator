#include "phyFormula.h"

double get_magnetic_field_strength(int numberTurn, double current_A, double length_m)
{
    return (double)(numberTurn*current_A/length_m);
}

double get_magnetic_flux_density(int numberTurn, double current_A, double length_m)
{
    double H = get_magnetic_field_strength(numberTurn, current_A, length_m);

    return (double)(u_air * H);
}

double get_magnetic_flux_density(int numberTurn, double current_A, double length_m, double u)
{
    double H = get_magnetic_field_strength(numberTurn, current_A, length_m);

    return (double)(u*H);
}

double get_magnetic_flux(double magnetic_flux_density, double area_m2)
{
    return (double)(magnetic_flux_density*area_m2);
}

double get_inductance(int numberTurn, double magnetic_flux, double current_A)
{
    return (double)(numberTurn*magnetic_flux/current_A);
}

double get_inductance(int numberTurn, double area_m2, double length_m, double u)
{
    return (double)(pow(numberTurn, 2) * area_m2 * u / length_m);
}

double get_total_energy(double voltage_or_v, double c_or_mass)
{
    return (double)(0.5*c_or_mass*pow(voltage_or_v,2));
}

double get_cap_loss_energy(double current_A, capacitor cap, double time_s) {
    return (double)(current_A * current_A * cap.getResistance() * time_s);
}

double get_enameled_wire_loss_energy(double current_A, enameledWire wire, double time_s)
{
    return (double)(current_A*current_A*wire.getResistance()*time_s);
}

double get_resistance(double length_m, double area_m2, double p)
{
    if (area_m2 == 0) {
        return (double)-1;
    }

    return (double)(p*length_m/area_m2);
}

double get_current(double voltage_V, double resistance_ohm)
{
    if (resistance_ohm == 0) {
        return (double)-1;
    }

    return (double)(voltage_V/resistance_ohm);
}

capacitor charge_release_cap_voltage(capacitor cap, enameledWire wire, double time, bool isCharge)
{
    double old_volt = cap.getCurr_volt();
    double new_volt;

    try {
        double RC_Time = get_RC_constant_time(cap, wire);

        if (RC_Time == 0) {
            new_volt = 0;
            cap.setCurr_volt(new_volt);

            return cap;
        }

        if (isCharge) {           
            new_volt = old_volt + (cap.getMaxVoltage() - old_volt) * (1 - exp(-time / RC_Time));
        }
        else {
            new_volt = old_volt * exp(-time / RC_Time);
        } 

        cap.setCurr_volt(new_volt);
    }
    catch(std::exception) {
        cap.setCurr_volt(old_volt);
    }

    return cap;
}

double get_RC_constant_time(capacitor cap, enameledWire wire)
{
    return (double)(cap.getCapacity()*(cap.getResistance() + wire.getResistance()));
}

