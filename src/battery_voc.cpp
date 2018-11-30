#include "battery_voc.h"

void battery_voc::set_attributes(){
	out.set_timestep(SIM_STEP,sc_core::SC_SEC);
	out2.set_timestep(SIM_STEP,sc_core::SC_SEC);
	out3.set_timestep(SIM_STEP,sc_core::SC_SEC);
	out4.set_timestep(SIM_STEP,sc_core::SC_SEC);
}

void battery_voc::initialize(){

}


void battery_voc::processing(){
	double tmpcurrent = in.read();
	//cout<<"tmpsoc_initial "<<tmpsoc<<endl;
	
	tmpsoc = tmpsoc-((tmpcurrent*SIM_STEP)/(3600*150.0)); //Modify the capacity

	double deltacurrent = in2.read();
	double deltafrequency = in3.read();
	
	//cout<<"deltacurrent "<<deltacurrent<<endl;
	//cout<<"deltafrequency "<<deltafrequency<<endl;
	tmpsoc = tmpsoc - deltacurrent - deltafrequency;
	//cout<<"tmpsoc "<<tmpsoc<<endl;
	//cout<<tmpcurrent<<endl;


	// Battery mangagement unit: if the SOC of battery less than 10%, the battery stop to work
	if(tmpsoc<=0.1){
		cout<<"SOC is less than or equal to 10%: "<<tmpsoc<<" @"<<sc_time_stamp()<<endl;
		sc_stop();
	}
	
	//if(tmpcurrent<=0.0){
	//	cout<<"Load current is less than or equal to zero: "<<tmpsoc<<" @"<<sc_time_stamp()<<endl;
	//	sc_stop();
	//}

	
	//12V 150Ah battery
	out.write((24.56*pow(tmpsoc,5)-71.5*pow(tmpsoc,4)+78.45*pow(tmpsoc,3)-40.51*pow(tmpsoc,2)+10.23*tmpsoc+2.067)*40);
	out2.write(0.0042*exp(-0.07909*tmpsoc)-0.0035);
	out3.write(tmpsoc);
	out4.write(tmpsoc);

	

}










