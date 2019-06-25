#include "imperial_defs.hpp"
#include "aerodynamic.hpp"

aerodynamic::aerodynamic(sc_core::sc_module_name _name) :
    sca_tdf::sca_module(_name),
    Tw("Tw"),
    wind("wind"),
    Wm("Wm"),
    ro(),
    gamma(),
    lambda(),
    Cp(),
    torque(),
    first(),
    varWm()
{
    // Nothing to do.
}

void aerodynamic::set_attributes()
{
    Tw.set_timestep(TIMESTEP);
    // wind.set_timestep(0.01,sc_core::SC_SEC);
    // wind.set_rate(0.001);
}

void aerodynamic::initialize()
{
    ro = ro0;
    first = true;
    varWm = 2.10001;
}

void aerodynamic::processing()
{
    if (first)
        first = !first;
    else
        varWm = Wm.read();

    lambda = varWm * radius / wind.read();
    gamma = lambda / (1 - 0.035 * lambda);
    Cp = 0.5 * (116 / gamma - 5) * exp(-21 / gamma);
    // Wind torque
    torque = PI / 2 * Cp * ro * pow(radius, 2) * pow(wind.read(), 3) / varWm;
    Tw.write(torque);
}
