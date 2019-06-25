#include <systemc-ams>
#include "environment.hpp"
#include "turbine.hpp"

// Wind turbine model top model = turbine model + environment model

SC_MODULE(windturbine)
{

    sca_tdf::sca_out<double> power; //Output power

    //sca_tdf::sca_signal<double> Wg, Wm, wind, Te, theta, ddtFdr, ddtFqr, Idr, Iqr, idtFdr, idtFqr;

    sca_tdf::sca_signal<double> wind;
    //sc_signal<double> Wm2, Wm3;


    // Instantiation of turbine and environment
    turbine * turb;
    environment * env;


    SC_CTOR(windturbine) :
        power("power")
    {

        turb = new turbine("turb");
        env = new environment("env");


        turb->wind(wind);
        turb->power(power);

        env->wind(wind);

    }

    void set_attributes();

};
