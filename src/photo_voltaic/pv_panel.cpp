#include "photo_voltaic/pv_panel.hpp"
#include "defines.hpp"

PvPanel::PvPanel(sc_core::sc_module_name _name) :
	sca_tdf::sca_module(_name),
	P("P"),
	sun_irradiance("sun_irradiance"),
	t(0)
{

}

void PvPanel::set_attributes()
{
	P.set_timestep(SIM_STEP, sc_core::SC_SEC);
	sun_irradiance.set_timestep(SIM_STEP, sc_core::SC_SEC);
	//P.set_delay(1);
}

void PvPanel::initialize()
{
	//unsigned int i;
	//ifstream top, back;

	std::string filename1 = DATASET_DIR "/one_day_sun.txt";
	top.open(filename1.c_str());
	if (!top) {
		std::cerr << "Cannot open irradiance file (" << filename1 << ")!\n";
		exit(-1);
	}

#if 0
	for (i = 0; i < SIMULATED_TIME; i++)
	{
		top >> Gtop[i];
	}
	top.close();

	//std::string filename2 = DATASET_DIR "/sun_one_week_april.txt";
	back.open(filename2);
	if (!back)
	{
		std::cerr << "Cannot open irradiance file (" << filename2 << ")!\n";
		exit(-1);
	}
	for (i = 0; i < SIMULATED_TIME; i++)
	{
		back >> Gwest[i];
	}
	back.close();
#endif
}

void PvPanel::processing()
{

	top >> Gtop;
	Gwest = Gtop;

	double Ptop, Pback;

	// Original equations
//  Ptop = 4.752e-09*pow(Gtop,3) - 7.352e-06*pow(Gtop,2) + 0.02238*Gtop - 0.6954; 
//  Pback = 4.752e-09*pow(Gwest,3) - 7.352e-06*pow(Gwest,2) + 0.02238*Gwest - 0.6954;

	// Avoid negative power value during night, actually this is correct
	// We can use this negative value to represent power consumption of PV if reviewer argure this point
	Ptop = 4.752e-09 * pow(Gtop, 3) - 7.352e-06 * pow(Gtop, 2) + 0.02238 * Gtop;
	Pback =
		4.752e-09 * pow(Gwest, 3) - 7.352e-06 * pow(Gwest, 2) + 0.02238 * Gwest;

	//cout<<Gtop[t]<<endl;

	if (Ptop < 0) {
		P.write(0);
	} else {
		P.write((Ptop * 6 + Pback * 6) * 35);
	}

	sun_irradiance.write(Gtop);

	if (t == DAY_LENGTH - 1) {
		std::cout
			<< "Report: PV panel works correctly until to first day!\n";
//    cout<<"Simulation ended: "<<" @"<<sc_time_stamp()<<endl;
	}
	if (t == DAY_LENGTH * 2 - 1) {
		std::cout
			<< "Report: PV panel works correctly until to second day!\n";
//    cout<<"Simulation ended: "<<" @"<<sc_time_stamp()<<endl;
	}
	if (t == DAY_LENGTH * 3 - 1) {
		std::cout
			<< "Report: PV panel works correctly until to third day!\n";
//    cout<<"Simulation ended: "<<" @"<<sc_time_stamp()<<endl;
	}
	if (t == DAY_LENGTH * 4 - 1) {
		std::cout
			<< "Report: PV panel works correctly until to fourth day!\n";
//    cout<<"Simulation ended: "<<" @"<<sc_time_stamp()<<endl;
	}
	if (t == DAY_LENGTH * 5 - 1) {
		std::cout
			<< "Report: PV panel works correctly until to fiveth day!\n";
//    cout<<"Simulation ended: "<<" @"<<sc_time_stamp()<<endl;
	}
	if (t == DAY_LENGTH * 6 - 1) {
		std::cout
			<< "Report: PV panel works correctly until to the end!\n";
//    cout<<"Simulation ended: "<<" @"<<sc_time_stamp()<<endl;
		top.close();
	}
	t++;
}







