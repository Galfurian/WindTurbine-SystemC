#include <systemc-ams>
#include "tstep.hpp"

class battery_voc :
    public sca_tdf::sca_module
{
public:
    /// SOC
    sca_tdf::sca_in<double> in;
    /// V_lost_C
    sca_tdf::sca_in<double> in2;
    /// V_lost_F
    sca_tdf::sca_in<double> in3;
    /// Voc
    sca_tdf::sca_out<double> out;
    /// Resistor
    sca_tdf::sca_out<double> out2;
    /// SOC
    sca_tdf::sca_out<double> out3;
    /// SOC
    sca_tdf::sca_out<double> out4;

    explicit battery_voc(sc_core::sc_module_name _name);

    void set_attributes() override;

    void initialize() override;

    void processing() override;

private:
    double tmpsoc;

};
