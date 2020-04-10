#include "battery/battery_fre.hpp"

BatteryFrequency::BatteryFrequency(sc_core::sc_module_name _name) :
    sca_tdf::sca_module(_name),
    in("in"),
    in2("in2"),
    out("out"),
    out2("out2")
{
    // Nothing to do.
}

void BatteryFrequency::set_attributes()
{
    out.set_timestep(SIM_STEP, sc_core::SC_SEC);
    out2.set_timestep(SIM_STEP, sc_core::SC_SEC);
    out.set_delay(1);
    out2.set_delay(1);
}

void BatteryFrequency::initialize()
{

}


void BatteryFrequency::processing()
{

//    double tmpcurrent = in.read();
//    double tempsoc = in2.read();
//    double tmpfrequency;
//    double cap_act_current;
//    double delta_crate;

    // Rated Cpacity Effect
//    cap_act_current =
//        -44870 * pow(tmpcurrent, 0.132) + 438000; // Modify the correct capacity
//    delta_crate = (((tmpcurrent * SIM_STEP) / (cap_act_current * 1.0)) -
//                   ((tmpcurrent * SIM_STEP) / (3600 * 150)));

    //out.write(delta_crate);
    out.write(0.0);
    out2.write(0.0);
    //out2.write(delta_freq);


}
