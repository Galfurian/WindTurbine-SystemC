#include <systemc-ams>

#include "battery.hpp"
#include "cti_bus.hpp"
#include "pv_panel.hpp"
#include "wind_turbine.hpp"
#include "battery_converter.hpp"
#include "pv_converter.hpp"
#include "wind_inverter.hpp"
#include "house.hpp"

#include "defines.hpp"

int sc_main(int argc, char * argv[])
{
    sc_set_time_resolution(TIMESTEP);

    //Signals for battery parts
    //sca_tdf::sca_signal<double> Ibatt, Vbatt, SOC, Ibatt_cnv, Vbatt_cnv;
    sca_tdf::sca_signal<double> Ibatt, Vbatt, SOC, Ibatt_cnv;

    //Signals for PV parts
    //sca_tdf::sca_signal<double> Power_pv, Ipv_cnv, Vpv_cnv;
    sca_tdf::sca_signal<double> Power_pv, Ipv_cnv, sun_irradiance;

    //Signals for wind turbine
    //sca_tdf::sca_signal<double> Power_wind, Vwind_inv, Iwind_inv, wind_speed;
    sca_tdf::sca_signal<double> Power_wind, Iwind_inv, wind_speed;

    sca_tdf::sca_signal<double> Phouse1, Phouse2, Phouse5;

    sca_tdf::sca_signal<double> buy, sell;

    //Singals for management
    //

    battery batt("batt");
    pv_panel pv("pv");
    windturbine wt("wt");
    converter_b batt_con("batt_con");
    converter_pv pv_con("pv_con");
    inverter_wt wt_inv("wt_inv");
    house house1("house1", DATASET_DIR "/loads/UKLOAD/one_week_h1.txt");
    house house2("house2", DATASET_DIR "/loads/UKLOAD/one_week_h2.txt");
    house house5("house5", DATASET_DIR "/loads/UKLOAD/one_week_h5.txt");
    cti_bus cti_bus("cti_bus");

    //----------------------Binding-------------------------------------------------
    //Battery
    batt.I(Ibatt);
    batt.V(Vbatt);
    batt.state_of_charge(SOC);

    //Battery converter
    batt_con.in(Vbatt);
    batt_con.in2(Ibatt_cnv);
    //	batt_con.in3(Vbatt_cnv);
    batt_con.out(Ibatt);

    //PV panel
    pv.P(Power_pv);
    pv.sun_irradiance(sun_irradiance);

    //PV converter
    pv_con.in(Power_pv);
    //	pv_con.in2(Vpv_cnv);
    pv_con.out(Ipv_cnv);

    //Wind turbine
    wt.power(Power_wind);
    //	wt.windspeed(wind_speed);

    //Wind inverter
    wt_inv.Pwind(Power_wind);
    //	wt_inv.V(Vwind_inv);
    wt_inv.I(Iwind_inv);

    //Load side -> A village is filled with 1 2 5 houses' combination.
    house1.out(Phouse1);
    house2.out(Phouse2);
    house5.out(Phouse5);

    //BUS
    cti_bus.SOC(SOC);
    cti_bus.Ibatt_cnv(Ibatt_cnv);
    //	cti_bus.Vbatt_cnv(Vbatt_cnv);

    cti_bus.Ipv_cnv(Ipv_cnv);
    //	cti_bus.Vpv_cnv(Vpv_cnv);

    cti_bus.Iwind_inv(Iwind_inv);
    //	cti_bus.Vwind_inv(Vwind_inv);

    cti_bus.Phouse1(Phouse1);
    cti_bus.Phouse2(Phouse2);
    cti_bus.Phouse5(Phouse5);

    cti_bus.Buy_from_grid(buy);
    cti_bus.Sell_to_grid(sell);


    //	sca_util::sca_decimation(1000);
    //
    //To store the values during simualtion

    sca_util::sca_trace_file * atf = sca_util::sca_create_tabular_trace_file(
        "wind.dat");
    //
    atf->set_mode(sca_util::sca_decimation(250));

    //Selecting signals to track
    //
    //

    //	sca_util::sca_trace(atf,buy,"BUY");
    //	sca_util::sca_trace(atf,sell,"SELL");

    //	sca_util::sca_trace(atf,Ibatt,"Ibatt");
    //	sca_util::sca_trace(atf,SOC,"SOC");
    //	sca_util::sca_trace(atf,Vbatt,"Vbatt");
    //	sca_util::sca_trace(atf,Phouse1,"Phouse1");
    //	sca_util::sca_trace(atf,Phouse2,"Phouse2");
    //	sca_util::sca_trace(atf,Phouse5,"Phouse5");
    //
    sca_util::sca_trace(atf, wt.wind, "Wind");
    //	sca_util::sca_trace(atf,Iwind_inv,"Wind_current");
    //	sca_util::sca_trace(atf,Ipv_cnv,"Pv_current");
    sca_util::sca_trace(atf, Power_wind, "Power_wind");
    //	sca_util::sca_trace(atf,wt.turb->gener->lsfModule->idtFdr,"Frd");

    //sca_util::sca_trace(atf,sun_irradiance,"Sun_profile");
    //sca_util::sca_trace(atf,Power_pv,"Power_pv");

    //	sc_start();


    //	sc_start(LENGTH, sc_core::SC_SEC);

    sc_start(LENGTH, sc_core::SC_SEC);

    std::cout << "YUKAI Report: The WHOLE SIMULATION LENGTH " << "====== "
              << sc_core::sc_time_stamp() << std::endl;

    //	sca_util::sca_close_tabular_trace_file( atf );
    return 0;
}
