#include "wind_turbine/turbine.hpp"

Turbine::Turbine(sc_core::sc_module_name _name) :
	sc_core::sc_module(_name),
	wind_speed("wind_speed"),
	power("power"),
	aerodynamic("aerodynamic"),
	mechanical("mechanical"),
	generator("generator"),
	Wg("Wg"),
	Tes("Tes"),
	Tw("Tw"),
	Is("Is"),
	Wm("Wm")
{
	aerodynamic.wind_speed(wind_speed);
	aerodynamic.Wm(Wm);
	aerodynamic.Tw(Tw);

	mechanical.Wm(Wm);
	mechanical.Wg(Wg);
	mechanical.Tw(Tw);
	mechanical.Te(Tes);

	generator.Te(Tes);
	generator.P(power);
	generator.I(Is);
	generator.Wg(Wg);
}