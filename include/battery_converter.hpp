#include <systemc-ams>
#include "defines.hpp"

class BatteryConverter :
    public sca_tdf::sca_module
{
public:
    /// Vbatt
    sca_tdf::sca_in<double> in;
    /// Iload
    sca_tdf::sca_in<double> in2;
    /// Iin
    sca_tdf::sca_out<double> out;
    /// Efficiency
    //sca_tdf::sca_out<double> eta;

    explicit BatteryConverter(sc_core::sc_module_name _name);

    void set_attributes() override;

    void initialize() override;

    /// @brief processes to calculate efficiency and battery current load.
    void processing() override;
};
