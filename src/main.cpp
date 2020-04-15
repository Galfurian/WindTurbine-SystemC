#include <systemc-ams>
#include <chrono>

#include "battery/battery.hpp"
#include "photo_voltaic/pv_panel.hpp"
#include "wind_turbine/wind_turbine.hpp"
#include "battery_converter.hpp"
#include "photo_voltaic/pv_converter.hpp"
#include "city_power_grid.hpp"
#include "wind_inverter.hpp"
#include "house.hpp"

#include "defines.hpp"

int sc_main(int argc, char* argv[])
{
	sc_set_time_resolution(TIMESTEP);

	// == SIGNALS =============================================================
	// Signals for battery parts
	sca_tdf::sca_signal<double> Ibatt, Vbatt, SOC, Ibatt_cnv;
	// Signals for PV parts
	sca_tdf::sca_signal<double> Power_pv, Ipv_cnv, sun_irradiance;
	// Signals for wind wind_turbine
	sca_tdf::sca_signal<double> Power_wind, Iwind_inv, wind_speed;
	// Signals for houses.
	sca_tdf::sca_signal<double> Phouse1, Phouse2, Phouse5;
	// Signals for the city grid.
	sca_tdf::sca_signal<double> buy, sell;

	// == COMPONENTS ==========================================================
	// Battery.
	Battery battery("battery");
	// Battery converter.
	BatteryConverter battery_converter("battery_converter");
	// Photo-Voltaic pannel.
	PvPanel pv_panel("pv_panel");
	// Photo-Voltaic converter.
	PvConverter pv_converter("pv_converter");
	// Wind Turbine.
	WindTurbine wind_turbine("wind_turbine");
	// Wind Inverter.
	WindInverter wind_inverter("wind_inverter");
	// Houses
	House house1("house1", DATASET_DIR "/loads/UKLOAD/one_week_h1.txt");
	House house2("house2", DATASET_DIR "/loads/UKLOAD/one_week_h2.txt");
	House house5("house5", DATASET_DIR "/loads/UKLOAD/one_week_h5.txt");
	// City power grid.
	CityPowerGrid city_power_grid("city_power_grid");

	// == SIGNAL BINDING ======================================================
	// Battery
	battery.I(Ibatt);
	battery.V(Vbatt);
	battery.state_of_charge(SOC);

	// Battery converter
	battery_converter.in(Vbatt);
	battery_converter.in2(Ibatt_cnv);
	//battery_converter.in3(Vbatt_cnv);
	battery_converter.out(Ibatt);

	// Photo-Voltaic pannel.
	pv_panel.P(Power_pv);
	pv_panel.sun_irradiance(sun_irradiance);

	// Photo-Voltaic converter.
	pv_converter.in(Power_pv);
	//pv_converter.in2(Vpv_cnv);
	pv_converter.out(Ipv_cnv);

	// Wind Turbine.
	wind_turbine.power(Power_wind);
	//wind_turbine.windspeed(wind_speed);

	// Wind Inverter.
	wind_inverter.Pwind(Power_wind);
	//wind_inverter.V(Vwind_inv);
	wind_inverter.I(Iwind_inv);

	// Load side -> A village is filled with 1 2 5 houses' combination.
	house1.out(Phouse1);
	house2.out(Phouse2);
	house5.out(Phouse5);

	// City power grid.
	city_power_grid.SOC(SOC);
	city_power_grid.Ibatt_cnv(Ibatt_cnv);
	//	city_power_grid.Vbatt_cnv(Vbatt_cnv);
	city_power_grid.Ipv_cnv(Ipv_cnv);
	//	city_power_grid.Vpv_cnv(Vpv_cnv);
	city_power_grid.Iwind_inv(Iwind_inv);
	//	city_power_grid.Vwind_inv(Vwind_inv);
	city_power_grid.Phouse1(Phouse1);
	city_power_grid.Phouse2(Phouse2);
	city_power_grid.Phouse5(Phouse5);
	city_power_grid.Buy_from_grid(buy);
	city_power_grid.Sell_to_grid(sell);

	// == TRACING =============================================================
	sca_util::sca_trace_file* atf = sca_util::sca_create_tabular_trace_file("wind.dat");
	// Set decimantion.
	atf->set_mode(sca_util::sca_decimation(250));
	// Selecting signals to track.
//	sca_util::sca_trace(atf, buy, "BUY");
//	sca_util::sca_trace(atf, sell, "SELL");
	sca_util::sca_trace(atf, Ibatt, "Ibatt");
	sca_util::sca_trace(atf, SOC, "SOC");
	sca_util::sca_trace(atf, Vbatt, "Vbatt");
//	sca_util::sca_trace(atf, Phouse1, "Phouse1");
//	sca_util::sca_trace(atf, Phouse2, "Phouse2");
//	sca_util::sca_trace(atf, Phouse5, "Phouse5");
//	sca_util::sca_trace(atf, wind_turbine.wind_speed, "Wind Speed");
//	sca_util::sca_trace(atf, Iwind_inv, "Wind Current");
//	sca_util::sca_trace(atf, Ipv_cnv, "PV Current");
//	sca_util::sca_trace(atf, Power_wind, "Power_wind");
//	sca_util::sca_trace(atf, wind_turbine.turbine.generator.lsfModule.idtFdr, "Frd");
//	sca_util::sca_trace(atf, sun_irradiance, "Sun Irradiance");
//	sca_util::sca_trace(atf, Power_pv, "PV Power");

	// == SIMULATION ==========================================================
	auto start = std::chrono::steady_clock::now();
	sc_start(SIMULATED_TIME, sc_core::SC_SEC);
	auto end = std::chrono::steady_clock::now();

	std::cout
		<< "Report:\n"
		<< "Simulated Time  : "
		<< sc_core::sc_time_stamp()
		<< "\n"
		<< "Simulation Time : "
		<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000
		<< " s \n";

	// == CLOSE TRACES ========================================================
	sca_util::sca_close_tabular_trace_file(atf);

	return 0;
}
