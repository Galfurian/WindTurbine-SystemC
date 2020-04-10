#include "defines.hpp"
#include "wind_turbine/aerodynamic/aerodynamic.hpp"

Aerodynamic::Aerodynamic(sc_core::sc_module_name _name) :
	sca_tdf::sca_module(_name),
	Tw("Tw"),
	wind_speed("wind_speed"),
	Wm("Wm"),
	ro(),
	gamma(),
	lambda(),
	Cp(),
	torque(),
	first(),
	varWm()
{
	// Nothing to do.
}

void Aerodynamic::set_attributes()
{
	Tw.set_timestep(TIMESTEP);
	// wind_speed.set_timestep(0.01,sc_core::SC_SEC);
	// wind_speed.set_rate(0.001);
}

void Aerodynamic::initialize()
{
	ro = ro0;
	first = true;
	varWm = 2.10001;
}

void Aerodynamic::processing()
{
	if (first) {
		first = !first;
	} else {
		varWm = Wm.read();
	}

	lambda = varWm * ROT_RADIUS / wind_speed.read();
	gamma = lambda / (1 - 0.035 * lambda);
	Cp = 0.5 * (116 / gamma - 5) * exp(-21 / gamma);
	// Wind torque
	torque = M_PI / 2 * Cp * ro * pow(ROT_RADIUS, 2) * pow(wind_speed.read(), 3) / varWm;
	Tw.write(torque);
}
