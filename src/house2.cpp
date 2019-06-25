#include "house2.hpp"
#include "defines.hpp"

void house2::set_attributes()
{
    out.set_timestep(SIM_STEP, sc_core::SC_SEC);

}

void house2::initialize()
{
    int j = 0;

    std::string filename = DATASET_DIR "/loads/UKLOAD/one_week_h2.txt";
    house2powerfile.open(filename.c_str());
    if (!house2powerfile)
    {
        std::cerr << "Cannot open loads file (" << filename << ")!\n";
        exit(-1);
    }
//	for(j=0;j<3;j++){
//		in>>rp[j]>>ap[j]>>pf[j];
//	}
//	in.close();

}

void house2::processing()
{

    house2powerfile >> rp;

//	cout<< rp<<"\t" << ap<<"\t" << pf<<endl;
//	cout<<rp<<"The real power value"<<endl;
//	cout<<"The apparent power is"<<ap<<endl;
//	cout<<"The power factor is"<<pf<<endl;


    out.write(6.3 * rp / 0.95);// Effciency


}






