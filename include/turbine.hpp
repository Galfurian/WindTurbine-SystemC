#include <systemc-ams>
#include "aerodynamic.hpp"
#include "generator.hpp"
#include "mechanical.hpp"

SC_MODULE (turbine)
{
    sca_tdf::sca_in<double> wind;
    sca_tdf::sca_out<double> power;

    aerodynamic * aero;
    mechanical * mech;
    generator * gener;

    sca_tdf::sca_signal<double> Wg, Tes, Tw;
    //sc_signal<double> Wm, Ps, Is;
    sca_tdf::sca_signal<double> Is;
    sc_core::sc_signal<double> Wm;

    SC_CTOR (turbine) :
        Tw("Tw"),
        wind("wind"),
        power("power")
    {

        aero = new aerodynamic("aero");
        mech = new mechanical("mech");
        gener = new generator("gener");

        aero->wind(wind);
        aero->Wm(Wm);
        aero->Tw(Tw);

        mech->Wm(Wm);
        mech->Wg(Wg);
        mech->Tw(Tw);
        mech->Te(Tes);

        gener->Te(Tes);
        gener->P(power);
        gener->I(Is);
        gener->Wg(Wg);
    }
};
