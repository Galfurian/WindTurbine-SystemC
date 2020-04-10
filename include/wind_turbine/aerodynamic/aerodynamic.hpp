#include <systemc-ams>

class Aerodynamic :
	public sca_tdf::sca_module {
public:
	/// Torque
	sca_tdf::sca_out<double> Tw;
	/// Wind speed.
	sca_tdf::sca_in<double> wind_speed;
	/// Mechanical angular speed.
	sca_tdf::sc_in<double> Wm;

	explicit Aerodynamic(sc_core::sc_module_name _name);

	void set_attributes() override;

	void initialize() override;

	void processing() override;

private:
	/// Air density
	double ro;
	/// Speed ratio
	double gamma, lambda;
	/// Power coefficient
	double Cp;
	/// Wind torque - internal variable
	double torque;
	bool first;
	double varWm;
};
