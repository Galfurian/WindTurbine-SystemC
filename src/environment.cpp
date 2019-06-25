#include "environment.hpp"
#include "defines.hpp"

void environment::set_attributes()
{
    wind.set_timestep(0.001, sc_core::SC_SEC);

    // wind.set_timestep(60,sc_core::SC_SEC);

}

void environment::initialize()
{
    std::string filename = DATASET_DIR "/one_day_wind.txt";
    windspeed.open(filename.c_str());
    if (!windspeed)
    {
        std::cerr << "Cannot open environment file (" << filename << ")!\n" <<
                  std::endl;
        exit(-1);
    }

}

void environment::processing()
{
    if (counter % 1000 == 0)
    {
        windspeed >> speed;
        wind.write(1.03 * speed);
        counter++;
    }
    else
    {
        wind.write(1.03 * speed);
        counter++;
    }
}
