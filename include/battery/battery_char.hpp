#include <systemc-ams>

class BatteryChar :
	public sc_core::sc_module {
public:
	// Interface and internal components declaration
	// Resistor, I load current, Voc affected by SOC
	sca_tdf::sca_in<double> in;
	sca_tdf::sca_in<double> in2;
	sca_tdf::sca_in<double> in3;
	// Vbatt
	sca_tdf::sca_out<double> out;

	sca_eln::sca_tdf::sca_isource i_batt;
	sca_eln::sca_tdf::sca_vsink v_batt;
	sca_eln::sca_tdf_vsource voc;
	sca_eln::sca_node n1;
	sca_eln::sca_node n2;
	sca_eln::sca_node_ref gnd;
	sca_eln::sca_tdf::sca_r rs;

	explicit BatteryChar(sc_core::sc_module_name _name);
};
