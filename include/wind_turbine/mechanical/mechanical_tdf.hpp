#include <systemc-ams>

class MechanicalTDF :
	public sca_tdf::sca_module {
public:
	sca_tdf::sc_in<double> Wm; // mechanical angular speed, generator angular speed
	sca_tdf::sca_in<double> Tw, Wg; // wind torque
	sca_tdf::sca_in<double> Te; // generator torque
	sca_tdf::sc_in<double> theta; // angle between rotors
	sca_tdf::sc_out<double> ddtWm, ddtWg; // first derivatives of Wm, Wg
	sc_core::sc_signal<double> Tms;

	explicit MechanicalTDF(sc_core::sc_module_name _name);

	void set_attributes();

	void initialize();

	void processing();

private:

	double Tm; // mechanical torque
	double varWm;
	bool first;
};
