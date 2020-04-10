#include <systemc-ams>
#include "defines.hpp"

class PvPanel :
	public sca_tdf::sca_module {
public:

	sca_tdf::sca_out<double> P;
	sca_tdf::sca_out<double> sun_irradiance;

	// double Gtop[SIMULATED_TIME], Gwest[SIMULATED_TIME];// Define in tstep.h
	double Gtop, Gwest;// Define in tstep.h

	unsigned int t;

	std::ifstream top; // To store the irradiance profile

	explicit PvPanel(sc_core::sc_module_name _name);

	void set_attributes();

	void initialize();

	void processing();
};
