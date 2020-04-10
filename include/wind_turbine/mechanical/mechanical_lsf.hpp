#include <systemc-ams>
#include "defines.hpp"

class MechanicalLSF :
	public sc_core::sc_module {
public:
	sc_core::sc_out<double> Wm, Wmi, Wgi, theta; // mechanical angular speed
	sca_tdf::sca_out<double> Wg; // generator angular speed
	sc_core::sc_in<double> ddtWm, ddtWg; // first derivative of Wm, Wg
	sca_lsf::sca_signal inDdtWm, inDdtWg, idtWm, idtWg, sumW, thetaSig, tempWm2;

	sca_lsf::sca_de::sca_source ddtWm_lsf,  ddtWg_lsf; // convert to LSF domain
	sca_lsf::sca_integ wmInteg,  wgInteg,  thetaInteg;
	sca_lsf::sca_de::sca_sink outWm,  outWmi,  outWgi,  outTheta;
	sca_lsf::sca_tdf::sca_sink outWg;
	sca_lsf::sca_sub addW;

	explicit MechanicalLSF(sc_core::sc_module_name _name);

}; 
