#include <systemc-ams>

#define USE_LSF_GENERATOR_EQ

#ifdef USE_LSF_GENERATOR_EQ
#define USE_DELAY

class GeneratorEqSys :
	public sc_core::sc_module {
public:
	sca_tdf::sca_in<double> Wg; // generator angular speed
	sca_lsf::sca_out ddtFdr, ddtFqr; // magnetic flux derivatives
	sca_tdf::sca_out<double> Idr, Iqr; // stator direct and quadrature axis currents
	sca_tdf::sca_in<double> idtFdr, idtFqr; // magnetic flux linkage for stator direct and quadrature axis
	sca_tdf::sca_out<double> P, I; // generated power and current

	explicit GeneratorEqSys(sc_core::sc_module_name _name);

private:
	sca_lsf::sca_signal S;
	sca_lsf::sca_signal Ids;
	sca_lsf::sca_signal Iqs;
	sca_lsf::sca_signal Idr_i;
	sca_lsf::sca_signal Iqr_i;
	sca_lsf::sca_signal ddtFdr_i;
	sca_lsf::sca_signal ddtFqr_i;
	sca_lsf::sca_signal Fiqs;
	sca_lsf::sca_signal Fids;
	sca_lsf::sca_signal power;

	// Static sources.
	sca_lsf::sca_source source_1;
	sca_lsf::sca_signal source_1_y;
	sca_lsf::sca_source source_1000;
	sca_lsf::sca_signal source_1000_y;

	// Delays
#ifdef USE_DELAY
	sca_lsf::sca_delay Fiqs_delay;
	sca_lsf::sca_signal Fiqs_delay_out;
	sca_lsf::sca_delay Fids_delay;
	sca_lsf::sca_signal Fids_delay_out;

	sca_lsf::sca_delay ddtFdr_delay;
	sca_lsf::sca_delay ddtFqr_delay;
#endif

	// == S =  1 - Wg.read(); =================================================
	sca_lsf::sca_tdf::sca_source Wg_lsf_source;
	sca_lsf::sca_signal Wg_lsf_source_y;
	sca_lsf::sca_sub sub0;

	// == Ids =  (Fiqs - 1000) / RES_STATOR; ====================================
	sca_lsf::sca_sub sub1;
	sca_lsf::sca_signal sub1_out;
	sca_lsf::sca_gain gain0;

	// == Iqs = (Fids + 1000) * (-1 / RES_STATOR); ====================================
	sca_lsf::sca_add add0;
	sca_lsf::sca_signal add0_out;
	sca_lsf::sca_gain gain1;

	// == Idr_i = (idtFdr.read() - MUTUAL_REACTANCE*Ids)/REA_ROTOR; =========================
	sca_lsf::sca_tdf::sca_source idtFdr_lsf_source;
	sca_lsf::sca_signal idtFdr_lsf_source_y;
	sca_lsf::sca_sub sub2;
	sca_lsf::sca_signal sub2_out;
	sca_lsf::sca_gain gain2;

	// == Iqr_i = (idtFqr.read() - MUTUAL_REACTANCE*Iqs)/REA_ROTOR; =========================
	sca_lsf::sca_tdf::sca_source idtFqr_lsf_source;
	sca_lsf::sca_signal idtFqr_lsf_source_y;
	sca_lsf::sca_sub sub3;
	sca_lsf::sca_signal sub3_out;
	sca_lsf::sca_gain gain3;

	// == ddtFdr_i = -RES_ROTOR*Idr_i + (S * idtFqr.read()); ======================
	sca_lsf::sca_tdf::sca_gain gain4;
	sca_lsf::sca_signal gain4_out;
	sca_lsf::sca_add add1;

	// == ddtFqr_i = -RES_ROTOR*Iqr_i - (S * idtFdr.read()); ======================
	sca_lsf::sca_tdf::sca_gain gain5;
	sca_lsf::sca_signal gain5_out;
	sca_lsf::sca_sub sub4;

	// == Fiqs = REA_STATOR*Iqs + MUTUAL_REACTANCE*Iqr_i; ===================================
	sca_lsf::sca_add add2;

	// == Fids = REA_STATOR*Ids + MUTUAL_REACTANCE*Idr_i; ===================================
	sca_lsf::sca_add add3;

	// == power = REF_VOLT_DS * (Ids - Iqs) + REF_VOLT_QS * (Ids - Iqs); ======
	sca_lsf::sca_sub sub5;
	sca_lsf::sca_signal sub5_out;
	sca_lsf::sca_sub sub6;
	sca_lsf::sca_signal sub6_out;
	sca_lsf::sca_add add4;

	// == OUTPUTS =============================================================
	sca_lsf::sca_tdf::sca_sink Idr_sink;
	sca_lsf::sca_tdf::sca_sink Iqr_sink;
	sca_lsf::sca_tdf::sca_sink P_sink;
	sca_lsf::sca_tdf::sca_sink I_sink;
};

#else

class GeneratorEqSys :
	public sca_tdf::sca_module {
public:
	sca_tdf::sca_in<double> Wg; // generator angular speed
	sca_tdf::sca_out<double> ddtFdr, ddtFqr; // magnetic flux derivatives
	sca_tdf::sca_out<double> Idr, Iqr; // stator direct and quadrature axis currents
	sca_tdf::sca_in<double> idtFdr, idtFqr; // magnetic flux linkage for stator direct and quadrature axis
	sca_tdf::sca_out<double> P, I; // generated power and current

	explicit GeneratorEqSys(sc_core::sc_module_name _name);

	void set_attributes();

	void initialize();

	void processing();

	sc_core::sc_signal<double> sIds, sS, sIqs, sIdr_i, sIqr_i, sFiqs, sFids,
		sddtFdr_i, sddtFqr_i;

private:

	double Ids, S, Iqs, Idr_i, Iqr_i, Fiqs, Fids, ddtFdr_i, ddtFqr_i, power;
	double Ids_new, Iqs_new, Idr_i_new, Iqr_i_new, Fiqs_new, Fids_new, ddtFdr_i_new, ddtFqr_i_new;
	bool first;
};

#endif