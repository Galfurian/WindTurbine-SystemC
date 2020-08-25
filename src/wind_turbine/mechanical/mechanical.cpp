#include "wind_turbine/mechanical/mechanical.hpp"

Mechanical::Mechanical(sc_core::sc_module_name _name) :
	sc_core::sc_module(_name),
	Wm("Wm"),
	Wg("Wg"),
	Tw("Tw"),
	Te("Te"),
	tdf("MechanicalTDF"),
	lsf("MechanicalLSF"),
	Wmi("Wmi"),
	Wei("Wei"),
	theta2("theta2"),
	ddtWm("ddtWm"),
	ddtWg("ddtWg")
{
	tdf.Tw(Tw);
	tdf.Te(Te);
	tdf.Wm(Wm);
	tdf.Wg(Wg);
	tdf.theta(theta2);
	tdf.ddtWm(ddtWm);
	tdf.ddtWg(ddtWg);

	lsf.Wmi(Wmi);
	lsf.Wgi(Wei);
	lsf.Wm(Wm);
	lsf.Wg(Wg);
	lsf.theta(theta2);
	lsf.ddtWm(ddtWm);
	lsf.ddtWg(ddtWg);
}