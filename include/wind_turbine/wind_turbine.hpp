#include <systemc-ams>
#include "wind_turbine/wind.hpp"
#include "wind_turbine/turbine.hpp"

// Wind wind_turbine model top model = wind_turbine model + wind model

class WindTurbine :
	public sc_core::sc_module {
public:
	sca_tdf::sca_out<double> power; //Output power
	//sca_tdf::sca_signal<double> Wg, Wm, wind, Te, theta, ddtFdr, ddtFqr, Idr, Iqr, idtFdr, idtFqr;
	sca_tdf::sca_signal<double> wind_speed;
	//sc_signal<double> Wm2, Wm3;

	// Instantiation of wind_turbine and wind
	Turbine turbine;
	Wind wind;

	explicit WindTurbine(sc_core::sc_module_name _name);
};
