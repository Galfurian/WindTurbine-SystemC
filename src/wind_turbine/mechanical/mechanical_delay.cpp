#include "defines.hpp"
#include "wind_turbine/mechanical/mechanical_delay.hpp"

MechanicalDelay::MechanicalDelay(sc_core::sc_module_name _name) :
	sca_tdf::sca_module(_name),
	Wg("Wm"),
	Wg_delayed("Wm_delayed")
{

}

void MechanicalDelay::set_attributes()
{
	Wg_delayed.set_timestep(TIMESTEP);
}

void MechanicalDelay::initialize()
{
}

void MechanicalDelay::processing()
{
	Wg_delayed.write(Wg.read());
}
