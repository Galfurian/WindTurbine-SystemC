#include "imperial_defs.hpp"
#include "mechanical_delay.hpp"

void mechanical_delay::set_attributes()
{
    Wg_delayed.set_timestep(TIMESTEP);
}

void mechanical_delay::initialize()
{
}

void mechanical_delay::processing()
{
    Wg_delayed.write(Wg.read());
}
