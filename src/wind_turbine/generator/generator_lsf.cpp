#include "defines.hpp"
#include "wind_turbine/generator/generator_lsf.hpp"

GeneratorLSF::GeneratorLSF(sc_core::sc_module_name _name) :
	sc_core::sc_module(_name),
	ddtFdr("ddtFdr"),
	ddtFqr("ddtFqr"),
	idtFdr("idtFdr"),
	idtFqr("idtFqr")
{
//	inFdr = new sca_lsf::sca_tdf::sca_source("inFdr", 1);
//	inFdr->inp(ddtFdr);
//	inFdr->y(lsfFdr);
//	inFdr->set_timestep(TIMESTEP);

	fdrInteg = new sca_lsf::sca_integ("fdrInteg", 1, 2.799606);
	fdrInteg->x(ddtFdr);
	fdrInteg->y(intFdr);
//	fdrInteg->set_timestep(TIMESTEP);

	outFdr = new sca_lsf::sca_tdf::sca_sink("outFdr");
	outFdr->x(intFdr);
	outFdr->outp(idtFdr);
//	outFdr->set_timestep(TIMESTEP);

//	inFqr = new sca_lsf::sca_tdf::sca_source("inFqr", 1);
//	inFqr->inp(ddtFqr);
//	inFqr->y(lsfFqr);
//	inFqr->set_timestep(TIMESTEP);

	fqrInteg = new sca_lsf::sca_integ("fqrInteg", 1, 2.8004);
	fqrInteg->x(ddtFqr);
	fqrInteg->y(intFqr);
//	fqrInteg->set_timestep(TIMESTEP);

	outFqr = new sca_lsf::sca_tdf::sca_sink("outFqr");
	outFqr->x(intFqr);
	outFqr->outp(idtFqr);
//	outFqr->set_timestep(TIMESTEP);
}