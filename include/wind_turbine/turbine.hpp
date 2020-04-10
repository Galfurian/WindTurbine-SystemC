#include <systemc-ams>
#include "wind_turbine/aerodynamic/aerodynamic.hpp"
#include "wind_turbine/mechanical/mechanical.hpp"
#include "wind_turbine/generator/generator.hpp"

class Turbine :
	public sc_core::sc_module {
public:
	sca_tdf::sca_in<double> wind_speed;
	sca_tdf::sca_out<double> power;

	Aerodynamic aerodynamic;
	Mechanical mechanical;
	Generator generator;

	sca_tdf::sca_signal<double> Wg;
	sca_tdf::sca_signal<double> Tes;
	sca_tdf::sca_signal<double> Tw;
	sca_tdf::sca_signal<double> Is;
	sc_core::sc_signal<double> Wm;

	explicit Turbine(sc_core::sc_module_name _name);
};
