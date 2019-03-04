#include "systemc-ams.h"
#include "imperial_defs.h"

SC_MODULE (generator_lsf)
{
  sca_tdf::sca_in<double> ddtFdr, ddtFqr; // magnetic flux derivatives 
  sca_tdf::sca_out<double> idtFdr, idtFqr; // magnetic flux values 

  sca_lsf::sca_signal lsfFdr, lsfFqr, intFdr, intFqr; 

  sca_lsf::sca_tdf::sca_source * inFdr, * inFqr; // convert to LSF domain
  sca_lsf::sca_integ * fdrInteg, * fqrInteg; 
  sca_lsf::sca_tdf::sca_sink * outFdr, * outFqr; 
  
  SC_CTOR(generator_lsf): ddtFdr("ddtFdr"), ddtFqr("ddtFqr"), idtFdr("idtFdr"), idtFqr("idtFqr"){
    
    inFdr = new sca_lsf::sca_tdf::sca_source("inFdr", 0.001); 
    inFdr->inp(ddtFdr); 
    inFdr->y(lsfFdr); 
    inFdr->set_timestep(TIMESTEP);
     
    fdrInteg = new sca_lsf::sca_integ("fdrInteg", 0.001, 2.799606);  
    fdrInteg->x(lsfFdr); 
    fdrInteg->y(intFdr); 
    fdrInteg->set_timestep(TIMESTEP);
     
    outFdr = new sca_lsf::sca_tdf::sca_sink("outFdr"); 
    outFdr->x(intFdr);
    outFdr->outp(idtFdr); 
    outFdr->set_timestep(TIMESTEP);

    inFqr = new sca_lsf::sca_tdf::sca_source("inFqr", 0.001); 
    inFqr->inp(ddtFqr); 
    inFqr->y(lsfFqr); 
    inFqr->set_timestep(TIMESTEP);
     
    fqrInteg = new sca_lsf::sca_integ("fqrInteg", 0.001, 2.8004);  
    fqrInteg->x(lsfFqr); 
    fqrInteg->y(intFqr); 
    fqrInteg->set_timestep(TIMESTEP);
     
    outFqr = new sca_lsf::sca_tdf::sca_sink("outFqr"); 
    outFqr->x(intFqr);
    outFqr->outp(idtFqr); 
    outFqr->set_timestep(TIMESTEP);
  }
};



