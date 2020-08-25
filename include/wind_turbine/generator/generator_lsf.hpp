#include <systemc-ams>
#include "defines.hpp"

class GeneratorLSF :
	public sc_core::sc_module {
public:
//	sca_tdf::sca_in<double> ddtFdr, ddtFqr; // magnetic flux derivatives
	sca_lsf::sca_in ddtFdr, ddtFqr; // magnetic flux derivatives
	sca_tdf::sca_out<double> idtFdr, idtFqr; // magnetic flux values

//	sca_lsf::sca_signal lsfFdr, lsfFqr;
	sca_lsf::sca_signal	intFdr, intFqr;

	sca_lsf::sca_tdf::sca_source* inFdr, * inFqr; // convert to LSF domain
	sca_lsf::sca_integ* fdrInteg, * fqrInteg;
	sca_lsf::sca_tdf::sca_sink* outFdr, * outFqr;

	explicit GeneratorLSF(sc_core::sc_module_name _name);
};



