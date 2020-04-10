#include <systemc-ams>

class MechanicalDelay :
	public sca_tdf::sca_module {
public:
	sca_tdf::sca_in<double> Wg;
	sca_tdf::sca_out<double> Wg_delayed;

	explicit MechanicalDelay(sc_core::sc_module_name _name);

	void set_attributes();

	void initialize();

	void processing();

private:
};
