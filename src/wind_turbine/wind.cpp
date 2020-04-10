#include "wind_turbine/wind.hpp"
#include "defines.hpp"

Wind::Wind(sc_core::sc_module_name _name) :
	sca_tdf::sca_module(_name),
	wind_speed("wind_speed"),
	counter(0),
	speed(0)
{

}

void Wind::set_attributes()
{
	wind_speed.set_timestep(TIMESTEP);
	// wind.set_timestep(60,sc_core::SC_SEC);
}

void Wind::initialize()
{
	std::string filename = DATASET_DIR "/one_day_wind.txt";
	windspeed_file.open(filename.c_str());
	if (!windspeed_file) {
		std::cerr << "Cannot open wind file (" << filename << ")!\n" <<
				  std::endl;
		exit(-1);
	}
}

void Wind::processing()
{
	if (counter % 1000 == 0) {
		windspeed_file >> speed;
	}
	wind_speed.write(1.03 * speed);
	++counter;
}
