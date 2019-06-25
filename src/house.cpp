#include "house.hpp"
#include "defines.hpp"

house::house(sc_core::sc_module_name _name,
             std::string const & power_filename) :
    sca_tdf::sca_module(_name),
    out("out"),
    _power_filename(power_filename),
    _power_file(power_filename),
    _rp(0)
{
    // Nothing to do.
}

void house::set_attributes()
{
    out.set_timestep(SIM_STEP, sc_core::SC_SEC);
}

void house::initialize()
{
    if ((!_power_file.is_open()) || (!_power_file.good()))
    {
        std::cerr << "Cannot open loads file (" << _power_filename << ")!\n";
        exit(-1);
    }
//	for(j=0;j<3;j++){
//		in>>rp[j]>>ap[j]>>pf[j];
//	}
//	in.close();
}

void house::processing()
{
    _power_file >> _rp;
//    std::cout << rp << "\t" << ap << "\t" << pf << "\n";
//    std::cout << "The real power value : " << _rp << "\n";
//    std::cout << "The apparent power is" << ap << "\n";
//    std::cout << "The power factor is" << pf << "\n";
    // Effciency
    out.write(6.7 * _rp / 0.95);
}






