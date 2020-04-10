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

//void windturbine::set_attributes(){
//power.set_timestep(1,sc_core::SC_SEC);
//power.set_rate(1000);
//wind.set_rate(0.001);
//}
