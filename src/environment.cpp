#include "environment.h"

void environment::set_attributes(){
 wind.set_timestep(0.001,sc_core::SC_SEC);

 // wind.set_timestep(60,sc_core::SC_SEC);

}

void environment::initialize(){
  int j;

  windspeed.open("./one_day_wind.txt");
  if(!windspeed) {
  cout << "Cannot open file."<<endl;
  exit(-1);
  }

}

void environment::processing(){


	if(counter%1000 == 0 ){
  	  windspeed >> speed;
  	  wind.write(1.03*speed);
	  counter++;
	}else{
  	  wind.write(1.03*speed);
	  counter++; 
	}




}
