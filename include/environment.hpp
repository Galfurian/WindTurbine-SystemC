#include <systemc-ams>
#include "tstep.hpp"

SCA_TDF_MODULE (environment)
{
    sca_tdf::sca_out<double> wind; // wind speed

    std::ifstream windspeed;

    SCA_CTOR(environment) :
        wind("wind"),
        counter(0),
        speed(0)
    {}

    void set_attributes();

    void initialize();

    void processing();

private:
    int counter;
    double speed;
};
