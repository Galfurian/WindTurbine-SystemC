#include <systemc-ams>
#include "defines.hpp"

class PvConverter :
	public sca_tdf::sca_module {
public:
	//sca_tdf::sca_in<double> in, in2; // PowerPV, Vbus
	sca_tdf::sca_in<double> in; // PowerPV, Omitting Vbus since it is a constant value, define it in tstep.h
	sca_tdf::sca_out<double> out;//I current out of converter
//	sca_tdf::sca_out<double> eta;//efficiency is constant

	explicit PvConverter(sc_core::sc_module_name _name);

	void set_attributes();

	void initialize();

	// Processes to calculate efficiency and current flow through PV panel
	void processing();
};
