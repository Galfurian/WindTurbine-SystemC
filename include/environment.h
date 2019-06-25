#include "systemc-ams.h"
#include "tstep.h"

SCA_TDF_MODULE (environment)
{
  sca_tdf::sca_out<double> wind; // wind speed 

  ifstream windspeed;

  SCA_CTOR(environment): wind("wind"), counter(0), speed(0) {}

  void set_attributes();
  void initialize();
  void processing();
  
private: 
  int counter;
  double speed;
};
