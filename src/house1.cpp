#include "house1.hpp"
#include "defines.hpp"

void house1::set_attributes()
{
    out.set_timestep(SIM_STEP, sc_core::SC_SEC);
}

void house1::initialize()
{
    int j = 0;

    std::string filename = DATASET_DIR "/loads/UKLOAD/one_week_h1.txt";
    house1powerfile.open(filename.c_str());
    if (!house1powerfile)
    {
        std::cerr << "Cannot open loads file (" << filename << ")!\n";
        exit(-1);
    }
//	for(j=0;j<3;j++){
//		in>>rp[j]>>ap[j]>>pf[j];
//	}
//	in.close();

}

void house1::processing()
{

    house1powerfile >> rp;

//	cout<< rp<<"\t" << ap<<"\t" << pf<<endl;
//	cout<<rp<<"The real power value"<<endl;
//	cout<<"The apparent power is"<<ap<<endl;
//	cout<<"The power factor is"<<pf<<endl;


    out.write(6.7 * rp / 0.95);// Effciency

}






