#include "battery/battery_char.hpp"

BatteryChar::BatteryChar(sc_core::sc_module_name _name) :
    sc_core::sc_module(_name),
    in("in"),
    in2("in2"),
    in3("in3"),
    out("out"),
    i_batt("i_batt"),
    v_batt("v_batt"),
    voc("voc"),
    n1("n1"),
    n2("n2"),
    gnd("gnd"),
    rs("rs")
{
    // Voc voltage instantiation
    voc.inp(in3);
    voc.p(n1);
    voc.n(gnd);

    // Internal resistance instantiation
    rs.p(n1);
    rs.n(n2);
    rs.scale = 1.0;
    rs.inp(in);

    // Load current instantiation
    i_batt.inp(in2);
    i_batt.p(n2);
    i_batt.n(gnd);

    // Output voltage of the battery
    v_batt.p(n2);
    v_batt.n(gnd);
    v_batt.outp(out);
}