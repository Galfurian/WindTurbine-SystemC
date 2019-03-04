#include "environment.h"

void environment::set_attributes(){
//  wind.set_timestep(0.001,sc_core::SC_SEC);

  wind.set_timestep(0.01,sc_core::SC_SEC);
}

void environment::initialize(){
  int j;

  ifstream in("./wind_one_week.txt");
  
  if(!in) {
  cout << "Cannot open file."<<endl;
  exit(-1);
  }

  for(j=0;j<LENGTH;j++){
  in >> speed[j];  
  }

  in.close();

}

void environment::processing(){


	if(counter%100 == 0 && number != 0 ){
  	  //wind.write(1.03*((speed[number]-2.389)*2.8/(12.366-2.389)+8.0));
  	  wind.write(1.03*speed[number]);
	  counter++;
	  number++;
	}else{
	  counter++;
  	 //wind.write(1.03*((speed[number]-2.389)*2.8/(12.366-2.389)+8.0));
  	  wind.write(1.03*speed[number]);
	  if (counter % 100 == 0)
		  number++; 
	}




}
