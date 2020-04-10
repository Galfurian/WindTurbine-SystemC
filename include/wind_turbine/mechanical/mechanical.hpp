#include <systemc-ams>
#include "mechanical_tdf.hpp"
#include "mechanical_lsf.hpp"

class Mechanical :
	public sc_core::sc_module {
public:
	sc_core::sc_out<double> Wm; // mechanical angular speed
	sca_tdf::sca_out<double> Wg; // generator angular speed
	sca_tdf::sca_in<double> Tw; // wind torque
	sca_tdf::sca_in<double> Te; // generator torque

	MechanicalTDF* tdf;
	MechanicalLSF* lsf;

	sc_core::sc_signal<double> Wmi, Wei, theta2, Wm_delay, theta_delay, Wmi_delay;
	sc_core::sc_signal<double> ddtWm, ddtWg;
	sca_tdf::sca_signal<double> Wg_delay;

	explicit Mechanical(sc_core::sc_module_name _name);
};
