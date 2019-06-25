#include "battery.hpp"

battery::battery(sc_core::sc_module_name _name) :
    sc_core::sc_module(_name),
    I("I"),
    V("V"),
    state_of_charge("state_of_charge"),
    Voc("Voc"),
    Rs("Rs"),
    deltaf("deltaf"),
    deltac("deltac"),
    tmpsoc("tmpsoc"),
    voc("voc"),
    batt("batt"),
    freq("freq")
{
    voc.in(I);
    voc.in2(deltac);
    voc.in3(deltaf);
    voc.out(Voc);
    voc.out2(Rs);
    voc.out3(state_of_charge);
    voc.out4(tmpsoc);

    batt.in(Rs);
    batt.in2(I);
    batt.in3(Voc);
    batt.out(V);

    freq.in(I);
    freq.in2(tmpsoc);
    freq.out(deltac);
    freq.out2(deltaf);
}