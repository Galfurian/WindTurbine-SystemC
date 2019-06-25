#include "battery_voc.hpp"

battery_voc::battery_voc(sc_core::sc_module_name _name) :
    sca_tdf::sca_module(_name),
    in("in"),
    in2("in2"),
    in3("in3"),
    out("out"),
    out2("out2"),
    out3("out3"),
    out4("out4"),
    tmpsoc(0.9)
{
    // Nothing to do.
}

void battery_voc::set_attributes()
{
    out.set_timestep(SIM_STEP, sc_core::SC_SEC);
    out2.set_timestep(SIM_STEP, sc_core::SC_SEC);
    out3.set_timestep(SIM_STEP, sc_core::SC_SEC);
    out4.set_timestep(SIM_STEP, sc_core::SC_SEC);
}

void battery_voc::initialize()
{

}

void battery_voc::processing()
{
    double tmpcurrent = in.read();

    tmpsoc = tmpsoc - ((tmpcurrent * SIM_STEP) / (3600 *
                                                  204.0)); //Modify the capacity, 150Ah is the reference one

    double deltacurrent = in2.read();
    double deltafrequency = in3.read();

    tmpsoc = tmpsoc - deltacurrent - deltafrequency;

    // Battery mangagement unit:
    //  if the SOC of battery less than 10%, the battery stop to working
    if (tmpsoc <= 0.1)
    {
        std::cerr << "SOC is less than or equal to 10%: " << tmpsoc << " @"
                  << sc_core::sc_time_stamp() << "\n";
//        sc_stop();
    }

    //12V 150Ah battery
    out.write((24.56 * pow(tmpsoc, 5) - 71.5 * pow(tmpsoc, 4) +
               78.45 * pow(tmpsoc, 3) - 40.51 * pow(tmpsoc, 2) +
               10.23 * tmpsoc + 4.1) * 41);
    //out2.write(0.0042*exp(-0.07909*tmpsoc)-0.0035);
    out2.write(0.0005);
    out3.write(tmpsoc);
    out4.write(tmpsoc);


}










