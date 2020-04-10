#include "wind_inverter.hpp"

WindInverter::WindInverter(sc_core::sc_module_name _name) :
	sca_tdf::sca_module(_name),
	I("I"),
	Pwind("Pwind")
{

}
// set_rate for multi time domain

void WindInverter::set_attributes()
{
	I.set_timestep(SIM_STEP, sc_core::SC_SEC);
//  Pwind.set_timestep(SIM_STEP, sc_core::SC_SEC);
	Pwind.set_timestep(TIMESTEP);
	Pwind.set_rate(1000);

}

void WindInverter::initialize()
{

}

void WindInverter::processing()
{

	I.write((Pwind.read() * 0.95) / VBUS);

}
