#include <systemc-ams>
#include "generator_Te.hpp"
#include "generator_lsf.hpp"
#include "generator_eq.hpp"

class Generator :
	public sc_core::sc_module {
public:
	sca_tdf::sca_out<double> Te; // generator torque
	sca_tdf::sca_out<double> P; // output power
	sca_tdf::sca_out<double> I; // output current
	sca_tdf::sca_in<double> Wg; // generator angular speed

	GeneratorTE teModule;
	GeneratorLSF lsfModule;
	GeneratorEqSys eqModule;

	sca_tdf::sca_signal<double> Idr, idtFdr, idtFqr, Iqr, ddtFdr, ddtFqr;

	explicit Generator(sc_core::sc_module_name _name);
};
