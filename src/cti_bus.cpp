#include "cti_bus.hpp"

// All signals
// Omit bus votage, define it as VBUS
//     vref_cti(430.0),
//     Ibatt_tmp(0.0),
//     total_power(0.0),
//     SOC("SOC"),
//     Ibatt_cnv("Ibatt_cnv"),
//     Vbatt_cnv("Vbatt_cnv"),
//     Ipv_cnv("Ipv_cnv"),
//     Vpv_cnv("Vpv_cnv"),
//     Iwind_inv("Iwind_inv"),
//     Vwind_inv("Vwind_inv"),
//     Phouse1("Phouse1"),
//     Phouse2("Phouse2"),
//     Phouse5("Phouse5")
cti_bus::cti_bus(sc_core::sc_module_name _name) :
    sca_tdf::sca_module(_name),
    SOC("SOC"),
    Ibatt_cnv("Ibatt_cnv"),
    Ipv_cnv("Ipv_cnv"),
    Iwind_inv("Iwind_inv"),
    Phouse1("Phouse1"),
    Phouse2("Phouse2"),
    Phouse5("Phouse5"),
    Buy_from_grid("Buy_from_grid"),
    Sell_to_grid("Sell_to_grid"),
    Ibatt_tmp(0.0),
    total_load(0.0),
    total_generation(0.0)
{
    // Nothing to do.
}

void cti_bus::set_attributes()
{
    Ibatt_cnv.set_delay(1);
//	Vbatt_cnv.set_delay(1);
//	Vpv_cnv.set_delay(1);
//	Vwind_inv.set_delay(1);
}

void cti_bus::initialize()
{

}

void cti_bus::processing()
{

    double batt_soc = SOC.read();

    // The constant dc bus voltage connection
//    Vbatt_cnv.write(VBUS); //dcdc converter for battery
//    Vpv_cnv.write(vref_cti);   //dcdc converter for pv panel
//    Vwind_inv.write(vref_cti); //dcac converter for wind turbine

    // Compute the total power comsumption from load side
    total_load = (Phouse1.read() + Phouse2.read() + Phouse5.read());
//	std::cout << "Total load " << total_load << "\n";

    // Compute the total generation from PV and Wind turbine
    total_generation = (Ipv_cnv.read() + Iwind_inv.read()) * VBUS;
//	std::cout << "Total generation " << total_generation << "\n";

    // Determine charge or discharge battery, postive value means discharge
    Ibatt_tmp = (total_load - total_generation) / VBUS;

    if (Ibatt_tmp >= 0)
    {
        // Load is larger than generation

        // Do not forget merge!
        Sell_to_grid.write(0.0);
        if (batt_soc > 0.1)
        {
            // Battery has energy, can provilde power to load to compensate
            // generation is not enough.

            // Battery discharge current
            Ibatt_cnv.write(Ibatt_tmp);
            // Store the value of buy from grid
            Buy_from_grid.write(0.0);
        }
        else
        {
            // Battery is dead, cannot provide any more; the power need buy
            // from grid.

            // Battery no action;
            Ibatt_cnv.write(0.0);
            // Store the value of buy from grid
            Buy_from_grid.write(Ibatt_tmp * VBUS);
        }
    }
    else
    {
        // Load is less than generation

        Buy_from_grid.write(0.0);
        if (batt_soc < 0.9)
        {
            // The extra power can be absorbed in battery

            // Battery charge current, it is an negative value
            Ibatt_cnv.write(Ibatt_tmp);
            // Store the value for selling to grid
            Sell_to_grid.write(0.0);
        }
        else
        {
            // Battery is fully charged, cannot charge anymore, the extra
            // power can sell to grid.

            // Battery no action
            Ibatt_cnv.write(0.0);
            // Store the value for selling to grid
            Sell_to_grid.write(Ibatt_tmp * VBUS);
        }
    }
}
