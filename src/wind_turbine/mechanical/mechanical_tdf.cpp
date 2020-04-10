#include "defines.hpp"
#include "wind_turbine/mechanical/mechanical_tdf.hpp"

MechanicalTDF::MechanicalTDF(sc_core::sc_module_name _name) :
	sca_tdf::sca_module(_name),
	Wm("Wm"),
	Tw("Tw"),
	Wg("Wg"),
	Te("Te"),
	theta("theta"),
	ddtWm("ddtWm"),
	ddtWg("ddtWg"),
	Tms("Tms")
{

}

void MechanicalTDF::set_attributes()
{
	ddtWm.set_timestep(TIMESTEP);
	ddtWg.set_timestep(TIMESTEP);
	ddtWm.set_delay(1);
	ddtWg.set_delay(1);
}

void MechanicalTDF::initialize()
{
	Tm = 0.0;
	varWm = 2.10001;
	first = true;
	ddtWm.initialize(0.4949);
	ddtWg.initialize(-338.4232);
}

void MechanicalTDF::processing()
{
	// derive variation of angular speeds given mechanical torque,
	// generator torque and wind torque

	if (first) {
		first = !first;
	} else {
		varWm = Wm.read();
	}

	Tm = (STIFFNESS / GEAR_RATION) * theta.read() +
		 (DAMPING / GEAR_RATION) * (Wg.read() - varWm);
	Tms.write(Tm);
	ddtWm.write((-Tw.read() + Tm) / ROT_INERTIA);

	ddtWg.write((-Te.read() - (Tm / GEAR_RATION)) / GEN_INERTIA);
}
