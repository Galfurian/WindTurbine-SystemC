#include <systemc-ams>
#include "tstep.hpp"

SCA_TDF_MODULE(house2)
{
    sca_tdf::sca_out<double> out; // Real Power = Apparent power * power factor
//	unsigned int i;

    std::ifstream house2powerfile;


    SCA_CTOR(house2) :
        out("out"),
        rp(0.0)
    {}

    void set_attributes();

    void initialize();

    void processing();


private:
    double rp; // real power
//	double ap; // apparent power
//	double pf; // power factor
};