#include "wind_turbine/generator/generator.hpp"

Generator::Generator(sc_core::sc_module_name _name) :
	sc_core::sc_module(_name),
	Te("Te"),
	P("P"),
	I("I"),
	Wg("Wg"),
	teModule("teModule"),
	lsfModule("lsfModule"),
	eqModule("eqModule")
{
	teModule.Idr(Idr);
	teModule.idtFdr(idtFdr);
	teModule.idtFqr(idtFqr);
	teModule.Iqr(Iqr);
	teModule.Te(Te);

	lsfModule.ddtFdr(ddtFdr);
	lsfModule.ddtFqr(ddtFqr);
	lsfModule.idtFdr(idtFdr);
	lsfModule.idtFqr(idtFqr);

	eqModule.ddtFdr(ddtFdr);
	eqModule.ddtFqr(ddtFqr);
	eqModule.idtFdr(idtFdr);
	eqModule.idtFqr(idtFqr);
	eqModule.Idr(Idr);
	eqModule.Iqr(Iqr);
	eqModule.Wg(Wg);
	eqModule.P(P);
	eqModule.I(I);
}