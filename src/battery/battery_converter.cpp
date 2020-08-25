#include "battery_converter.hpp"

BatteryConverter::BatteryConverter(sc_core::sc_module_name _name) :
    sca_tdf::sca_module(_name),
    in("in"),
    in2("in2"),
    out("out")
{
    // Nothing to do.
}

void BatteryConverter::set_attributes()
{
    out.set_timestep(SIM_STEP, sc_core::SC_SEC);
    out.set_delay(1);
}

void BatteryConverter::initialize()
{

}

void BatteryConverter::processing()
{
    double tmp_vin = in.read();
    double tmp_iout = in2.read();
//	double tmp_vout = in3.read();

    //Variable efficiency dc/dc model
    //double efficiency = (0.24 * pow(tmp_vin, 2) - 0.0000663 * pow(tmp_vout, 2) - 0.00545 * pow(tmp_iout, 2) + 0.000713 * tmp_vin + 0.0116 * tmp_vout + 0.00689 * tmp_iout - 0.036967) / 4.5;
//	eta.write(efficiency);

    //Constant efficiency dc/dc
    double efficiency = 0.95;

    out.write(tmp_iout * VBUS / (efficiency * tmp_vin));
}