#include <systemc-ams>
#include "defines.hpp"

class WindInverter :
	public sca_tdf::sca_module {
public:
	sca_tdf::sca_out<double> I; // current connect to bus
	//sca_tdf::sca_in<double> Pwind, V; //power generated from wind, Bus voltage
	sca_tdf::sca_in<double> Pwind; //Power generated from wind

	explicit WindInverter(sc_core::sc_module_name _name);

	void set_attributes();

	void initialize();

	void processing();
};
