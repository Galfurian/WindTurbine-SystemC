#include "defines.hpp"
#include "wind_turbine/mechanical/mechanical_lsf.hpp"

MechanicalLSF::MechanicalLSF(sc_core::sc_module_name _name) :
	sc_core::sc_module(_name),
	Wm("Wm"),
	Wmi("Wmi"),
	Wgi("Wgi"),
	theta("theta"),
	Wg("Wg"),
	ddtWm("ddtWm"),
	ddtWg("ddtWg"),
	inDdtWm("inDdtWm"),
	inDdtWg("inDdtWg"),
	idtWm("idtWm"),
	idtWg("idtWg"),
	sumW("sumW"),
	thetaSig("thetaSig"),
	tempWm2("tempWm2"),
	ddtWm_lsf("ddtWm_lsf", 1),
	ddtWg_lsf("ddtWg_lsf"),
	wmInteg("wmInteg", 1, 2.100001),
	wgInteg("wgInteg", 1, 2.2192116114),
	thetaInteg("thetaInteg", 1, 1.000268),
	outWm("outWm"),
	outWmi("outWmi"),
	outWgi("outWgi"),
	outTheta("outTheta"),
	outWg("outWg"),
	addW("addW")
{
	ddtWm_lsf.inp(ddtWm);
	ddtWm_lsf.y(inDdtWm);
	ddtWm_lsf.set_timestep(TIMESTEP);

	wmInteg.x(inDdtWm);
	wmInteg.y(idtWm);
	wmInteg.set_timestep(TIMESTEP);

	outWm.x(idtWm);
	outWm.outp(Wm);
	outWm.set_timestep(TIMESTEP);

	outWmi.x(idtWm);
	outWmi.outp(Wmi);
	outWmi.set_timestep(TIMESTEP);

	ddtWg_lsf.inp(ddtWg);
	ddtWg_lsf.y(inDdtWg);
	ddtWg_lsf.set_timestep(TIMESTEP);

	wgInteg.x(inDdtWg);
	wgInteg.y(idtWg);
	wgInteg.set_timestep(TIMESTEP);

	outWg.x(idtWg);
	outWg.outp(Wg);
	outWg.set_timestep(TIMESTEP);

	outWgi.x(idtWg);
	outWgi.outp(Wgi);
	outWgi.set_timestep(TIMESTEP);

	addW.x1(idtWg);
	addW.x2(idtWm);
	addW.y(sumW);
	addW.set_timestep(TIMESTEP);

	thetaInteg.x(sumW);
	thetaInteg.y(thetaSig);
	thetaInteg.set_timestep(TIMESTEP);

	outTheta.x(thetaSig);
	outTheta.outp(theta);
	outTheta.set_timestep(TIMESTEP);
}