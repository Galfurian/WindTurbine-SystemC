#include <systemc-ams>
#include "tstep.hpp"

class battery_fre :
    public sca_tdf::sca_module
{
public:
    /// I load current
    sca_tdf::sca_in<double> in;
    /// SOC
    sca_tdf::sca_in<double> in2;
    /// V_lost_C
    sca_tdf::sca_out<double> out;
    /// V_lost_F
    sca_tdf::sca_out<double> out2;

    explicit battery_fre(sc_core::sc_module_name _name);

    void set_attributes() override;

    void initialize() override;

    void processing() override;


};
