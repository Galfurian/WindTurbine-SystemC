#include "systemc-ams.h"
#include "tstep.h"

SCA_TDF_MODULE (environment)
{
  sca_tdf::sca_out<double> wind; // wind speed 

  SCA_CTOR(environment): wind("wind"), counter(0), number(0) {}

  void set_attributes();
  void initialize();
  void processing();
  
private: 
  int counter,number;
  double speed[LENGTH];
};
