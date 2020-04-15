#include "wind_turbine/wind_turbine.hpp"

WindTurbine::WindTurbine(sc_core::sc_module_name _name) :
	sc_core::sc_module(_name),
	power("power"),
	wind_speed("wind_speed"),
	turbine("turbine"),
	wind("wind")
{
	turbine.wind_speed(wind_speed);
	turbine.power(power);
	wind.wind_speed(wind_speed);
}
