#include <systemc-ams>

#include "battery_char.hpp"
#include "battery_voc.hpp"
#include "battery_fre.hpp"

class Battery :
	public sc_core::sc_module {
public:
	// Interface and internal components declaration.

	/// Ib current.
	sca_tdf::sca_in<double> I;
	/// Vb battery voltage
	sca_tdf::sca_out<double> V;
	/// State of Charge (SoC)
	sca_tdf::sca_out<double> state_of_charge;

	// Connecting signals.
	sca_tdf::sca_signal<double> Voc;
	sca_tdf::sca_signal<double> Rs;
	sca_tdf::sca_signal<double> deltaf;
	sca_tdf::sca_signal<double> deltac;
	sca_tdf::sca_signal<double> tmpsoc;

	// Instantiation of battery componenets
	BatteryVoc voc;
	BatteryChar batt;
	BatteryFrequency freq;

	explicit Battery(sc_core::sc_module_name _name);
};








