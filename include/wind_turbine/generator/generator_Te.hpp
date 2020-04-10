#include <systemc-ams>

class GeneratorTE :
	public sca_tdf::sca_module {
public:
	sca_tdf::sca_in<double> Idr, Iqr; // stator direct and quadrature axis currents
	sca_tdf::sca_in<double> idtFdr, idtFqr; // magnetic flux linkage for stator direct and quadrature axis
	sca_tdf::sca_out<double> Te; // generator torque

	explicit GeneratorTE(sc_core::sc_module_name _name);

	void set_attributes();

	void initialize();

	void processing();
};
