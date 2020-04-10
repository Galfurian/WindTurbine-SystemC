#include "defines.hpp"
#include "wind_turbine/generator/generator_Te.hpp"

GeneratorTE::GeneratorTE(sc_core::sc_module_name _name) :
	sca_tdf::sca_module(_name),
	Idr("Idr"),
	Iqr("Iqr"),
	idtFdr("idtFdr"),
	idtFqr("idtFqr"),
	Te("Te")
{

}

void GeneratorTE::set_attributes()
{
	Te.set_timestep(TIMESTEP);
	Te.set_delay(1);
}

void GeneratorTE::initialize()
{
	Te.initialize(0.0);
}

void GeneratorTE::processing()
{

	Te.write(idtFqr.read() * Idr.read() - idtFdr.read() * Iqr.read());
}
