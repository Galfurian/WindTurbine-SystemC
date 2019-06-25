#include <systemc-ams>
#include "tstep.hpp"

#define Voltage_reference 430

class cti_bus :
    public sca_tdf::sca_module
{
public:
    /// Ports connect to battery
    sca_tdf::sca_in<double> SOC;
    ///
    sca_tdf::sca_out<double> Ibatt_cnv;
    ///
//    sca_tdf::sca_out<double> Vbatt_cnv;
    /// Control signals for charge or discharge
//    sca_tdf::sca_out<int> Enable_charge;

    // Ports connect to PV panel
    sca_tdf::sca_in<double> Ipv_cnv;
//	sca_tdf::sca_out<double> Vpv_cnv;

    // Ports connect to wind turbine
    sca_tdf::sca_in<double> Iwind_inv;
//	sca_tdf::sca_out<double> Vwind_inv;

    // Ports connect to Grid load
    sca_tdf::sca_in<double> Phouse1;
    sca_tdf::sca_in<double> Phouse2;
    sca_tdf::sca_in<double> Phouse5;

    // Buy or Sell from/to utility grid
    sca_tdf::sca_out<double> Buy_from_grid;
    sca_tdf::sca_out<double> Sell_to_grid;

    explicit cti_bus(sc_core::sc_module_name _name);

    void set_attributes() override;

    void initialize() override;

    void processing() override;

private:
//	 double vref_cti, Ibatt_tmp, total_power;
    double Ibatt_tmp, total_load, total_generation;

};

