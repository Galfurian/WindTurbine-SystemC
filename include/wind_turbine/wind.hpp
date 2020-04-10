#include <systemc-ams>
#include "defines.hpp"

class Wind :
	public sca_tdf::sca_module {
public:
	sca_tdf::sca_out<double> wind_speed; // wind speed

	explicit Wind(sc_core::sc_module_name _name);

	void set_attributes();

	void initialize();

	void processing();

private:
	std::ifstream windspeed_file;
	int counter;
	double speed;
};
