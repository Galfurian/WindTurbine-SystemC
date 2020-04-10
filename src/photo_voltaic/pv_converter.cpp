#include "photo_voltaic/pv_converter.hpp"

PvConverter::PvConverter(sc_core::sc_module_name _name) :
	sca_tdf::sca_module(_name)
{

}

void PvConverter::set_attributes()
{
	out.set_timestep(SIM_STEP, sc_core::SC_SEC);
	out.set_delay(1); // PV current is the output

}

void PvConverter::initialize()
{

}

void PvConverter::processing()
{
	double tmp_power = in.read();
	//double tmp_vbus = in2.read();

	double efficiency = 0.95;

	//out.write((efficiency * tmp_power)/tmp_vbus);
	out.write((efficiency * tmp_power) / VBUS);
}
