#include <systemc-ams>
#include "tstep.hpp"

SCA_TDF_MODULE(house1)
{

    sca_tdf::sca_out<double> out; // Real Power = Apparent power * power factor

    std::ifstream house1powerfile;


    double rp; // real power
//	double ap; // apparent power
//	double pf; // power factor

    SCA_CTOR(house1) :
        out("out"),
        rp(0)
    {}

    void set_attributes();

    void initialize();

    void processing();


};
