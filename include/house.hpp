#include <systemc-ams>
#include "defines.hpp"

class House :
	public sca_tdf::sca_module {
public:
	// Real Power = Apparent power * power factor
	sca_tdf::sca_out<double> out;

	explicit House(sc_core::sc_module_name _name, std::string const& power_filename);

	void set_attributes() override;

	void initialize() override;

	void processing() override;

private:
	/// Filename.
	std::string _power_filename;
	/// File with power usage.
	std::ifstream _power_file;
	/// Real power
	double _rp;
	/// Apparent power
//	double _ap;
	/// Power factor
//	double _pf;

};
