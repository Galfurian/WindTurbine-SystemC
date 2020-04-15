#include "defines.hpp"
#include "wind_turbine/generator/generator_eq.hpp"

#ifdef USE_LSF_GENERATOR_EQ

GeneratorEqSys::GeneratorEqSys(sc_core::sc_module_name _name) :
	sc_core::sc_module(_name),
	Wg("Wg"),
	ddtFdr("ddtFdr"),
	ddtFqr("ddtFqr"),
	Idr("Idr"),
	Iqr("Iqr"),
	idtFdr("idtFdr"),
	idtFqr("idtFqr"),
	P("P"),
	I("I"),

	S("S"),
	Ids("Ids"),
	Iqs("Iqs"),
	Idr_i("Idr_i"),
	Iqr_i("Iqr_i"),
	ddtFdr_i("ddtFdr_i"),
	ddtFqr_i("ddtFqr_i"),
	Fiqs("Fiqs"),
	Fids("Fids"),
	power("power"),

	source_1("source_1", 1),
	source_1_y("source_1_y"),
	source_1000("source_1000", 1000),
	source_1000_y("source_1000_y"),

#ifdef USE_DELAY
	Fiqs_delay("Fiqs_delay", sca_core::sca_time(TIMESTEP)),
	Fiqs_delay_out("Fiqs_delay_out"),
	Fids_delay("Fids_delay", sca_core::sca_time(TIMESTEP)),
	Fids_delay_out("Fids_delay_out"),

	ddtFdr_delay("ddtFdr_delay", sca_core::sca_time(TIMESTEP)),
	ddtFdr_delay_out("ddtFdr_delay_out"),
	ddtFqr_delay("ddtFqr_delay", sca_core::sca_time(TIMESTEP)),
	ddtFqr_delay_out("ddtFqr_delay_out"),
#endif

	Wg_lsf_source("Wg_lsf_source", 1),
	Wg_lsf_source_y("Wg_lsf_source_y"),
	sub0("sub0"),

	sub1("sub1"),
	sub1_out("sub1_out"),
	gain0("gain0", 1 / RES_STATOR),

	add0("add0"),
	add0_out("add0_out"),
	gain1("gain1", (-1 / RES_STATOR)),

	idtFdr_lsf_source("idtFdr_lsf_source", 1),
	idtFdr_lsf_source_y("idtFdr_lsf_source_y"),
	sub2("sub2"),
	sub2_out("sub2_out"),
	gain2("gain2", 1 / REA_ROTOR),

	idtFqr_lsf_source("idtFqr_lsf_source", 1),
	idtFqr_lsf_source_y("idtFqr_lsf_source_y"),
	sub3("sub3"),
	sub3_out("sub3_out"),
	gain3("gain3", 1 / REA_ROTOR),

	gain4("gain4", 1),
	gain4_out("gain4_out"),
	add1("add1"),

	gain5("gain5", 1),
	gain5_out("gain5_out"),
	sub4("sub4"),

	add2("add2"),

	add3("add3"),

	sub5("sub5"),
	sub5_out("sub5_out"),
	sub6("sub6"),
	sub6_out("sub6_out"),
	add4("add4"),

	Idr_sink("Idr_sink"),
	Iqr_sink("Iqr_sink"),
	ddtFdr_sink("ddtFdr_sink"),
	ddtFqr_sink("ddtFqr_sink"),
	P_sink("P_sink", 0.17),
	I_sink("I_sink", 1 / BAT_VOLTAGE)
{
//     S =  1 - Wg.read();
//     Ids =  (Fiqs - 1000)/RES_STATOR;
//     Iqs = -(Fids + 1000)/RES_STATOR;
//     Idr_i = (idtFdr.read() - MUTUAL_REACTANCE*Ids)/REA_ROTOR;
//     Iqr_i = (idtFqr.read() - MUTUAL_REACTANCE*Iqs)/REA_ROTOR;
//     ddtFdr_i = -RES_ROTOR*Idr_i + S*idtFqr.read();
//     ddtFqr_i = -RES_ROTOR*Iqr_i - S*idtFdr.read();
//     Fiqs = REA_STATOR*Iqs + MUTUAL_REACTANCE*Iqr_i;
//     Fids = REA_STATOR*Ids + MUTUAL_REACTANCE*Idr_i;
//     power = REF_VOLT_DS * (Ids - Iqs) + REF_VOLT_QS * (Ids - Iqs);

	// == SOURCES =============================================================
	source_1.y(source_1_y);
	source_1000.y(source_1000_y);

	// == INPUT SOURCES =======================================================
	idtFdr_lsf_source.inp(idtFdr);
	idtFdr_lsf_source.y(idtFdr_lsf_source_y);
	idtFdr_lsf_source.set_timestep(TIMESTEP);

	idtFqr_lsf_source.inp(idtFqr);
	idtFqr_lsf_source.y(idtFqr_lsf_source_y);
	idtFqr_lsf_source.set_timestep(TIMESTEP);

	// == S =  1 - Wg.read(); =================================================
	// ==          Wg.read()
	Wg_lsf_source.inp(Wg);
	Wg_lsf_source.y(Wg_lsf_source_y);
	Wg_lsf_source.set_timestep(TIMESTEP);
	// == S =  1 - Wg.read();
	sub0.x1(source_1_y);
	sub0.x2(Wg_lsf_source_y);
	sub0.y(S);

	// == Ids =  (Fiqs - 1000) / RES_STATOR; ====================================
	// ==        (Fiqs - 1000)
#ifdef USE_DELAY
	sub1.x1(Fiqs_delay_out);
#else
	sub1.x1(Fiqs);
#endif
	sub1.x2(source_1000_y);
	sub1.y(sub1_out);
	// == Ids =  (Fiqs - 1000) / RES_STATOR;
	gain0.x(sub1_out);
	gain0.y(Ids);

	// == Iqs = (Fids + 1000) * (-1 / RES_STATOR); ====================================
	// ==       (Fids + 1000)
#ifdef USE_DELAY
	add0.x1(Fids_delay_out);
#else
	add0.x1(Fids);
#endif
	add0.x2(source_1000_y);
	add0.y(add0_out);
	// == Iqs = (Fids + 1000) * (-1 / RES_STATOR);
	gain1.x(add0_out);
	gain1.y(Iqs);

	// == Idr_i = (idtFdr.read() - MUTUAL_REACTANCE*Ids)/REA_ROTOR; =========================
	// == (idtFdr.read() - [MUTUAL_REACTANCE * Ids])
	sub2.x1(idtFdr_lsf_source_y);
	sub2.x2(Ids);
	sub2.k2.set(MUTUAL_REACTANCE);
	sub2.y(sub2_out);
	// == Idr_i = (idtFdr.read() - MUTUAL_REACTANCE*Ids)/REA_ROTOR;
	gain2.x(sub2_out);
	gain2.y(Idr_i);

	// == Iqr_i = (idtFqr.read() - MUTUAL_REACTANCE*Iqs)/REA_ROTOR; =========================
	// ==         (idtFqr.read() - MUTUAL_REACTANCE*Iqs)
	sub3.x1(idtFqr_lsf_source_y);
	sub3.x2(Iqs);
	sub3.k2.set(MUTUAL_REACTANCE);
	sub3.y(sub3_out);
	// == Iqr_i = (idtFqr.read() - MUTUAL_REACTANCE*Iqs)/REA_ROTOR;
	gain3.x(sub3_out);
	gain3.y(Iqr_i);

	// == ddtFdr_i = -RES_ROTOR*Idr_i + (S * idtFqr.read()); ======================
	// ==                               (S * idtFqr.read());
	gain4.x(S);
	gain4.inp(idtFqr);
	gain4.y(gain4_out);
	// == ddtFdr_i = [-RES_ROTOR*Idr_i] + [S * idtFqr.read()];
	add1.x1(Idr_i);
	add1.k1.set(-RES_ROTOR);
	add1.x2(gain4_out);
	add1.y(ddtFdr_i);

	// == ddtFqr_i = -RES_ROTOR*Iqr_i - (S * idtFdr.read()); ======================
	// ==                               (S * idtFdr.read());
	gain5.x(S);
	gain5.inp(idtFdr);
	gain5.y(gain5_out);
	// == ddtFqr_i = -RES_ROTOR*Iqr_i - (S * idtFdr.read());
	sub4.k1.set(-RES_ROTOR);
	sub4.x1(Iqr_i);
	sub4.x2(gain5_out);
	sub4.y(ddtFqr_i);

	// == Fiqs = REA_STATOR*Iqs + MUTUAL_REACTANCE*Iqr_i; ===================================
	// == Fiqs = REA_STATOR*Iqs + MUTUAL_REACTANCE*Iqr_i;
	add2.k1.set(REA_STATOR);
	add2.x1(Iqs);
	add2.k2.set(MUTUAL_REACTANCE);
	add2.x2(Iqr_i);
	add2.y(Fiqs);

#ifdef USE_DELAY
	Fiqs_delay.x(Fiqs);
	Fiqs_delay.y(Fiqs_delay_out);
	Fiqs_delay.set_timestep(TIMESTEP);
#endif

	// == Fids = REA_STATOR*Ids + MUTUAL_REACTANCE*Idr_i; ===================================
	// == Fids = REA_STATOR*Ids + MUTUAL_REACTANCE*Idr_i;
	add3.k1.set(REA_STATOR);
	add3.x1(Ids);
	add3.k2.set(MUTUAL_REACTANCE);
	add3.x2(Idr_i);
	add3.y(Fids);

#ifdef USE_DELAY
	Fids_delay.x(Fids);
	Fids_delay.y(Fids_delay_out);
	Fids_delay.set_timestep(TIMESTEP);
#endif

	// == power = REF_VOLT_DS * (Ids - Iqs) + REF_VOLT_QS * (Ids - Iqs); ======
	// == (Ids - Iqs)
	sub5.x1(Ids);
	sub5.x2(Iqs);
	sub5.y(sub5_out);

	// == (Ids - Iqs)
	sub6.x1(Ids);
	sub6.x2(Iqs);
	sub6.y(sub6_out);

	// == power = REF_VOLT_DS * (Ids - Iqs) + REF_VOLT_QS * (Ids - Iqs);
	add4.k1.set(REF_VOLT_DS);
	add4.x1(sub5_out);
	add4.k2.set(REF_VOLT_QS);
	add4.x2(sub6_out);
	add4.y(power);

	// == OUTPUTS =============================================================
#ifdef USE_DELAY
	ddtFdr_delay.x(ddtFdr_i);
	ddtFdr_delay.y(ddtFdr_delay_out);

	ddtFqr_delay.x(ddtFqr_i);
	ddtFqr_delay.y(ddtFqr_delay_out);
#endif

	Idr_sink.x(Idr_i);
	Idr_sink.outp(Idr);
	Idr_sink.set_timestep(TIMESTEP);

	Iqr_sink.x(Iqr_i);
	Iqr_sink.outp(Iqr);
	Iqr_sink.set_timestep(TIMESTEP);

#ifdef USE_DELAY
	ddtFdr_sink.x(ddtFdr_delay_out);
#else
	ddtFdr_sink.x(ddtFdr_i);
#endif
	ddtFdr_sink.outp(ddtFdr);
	ddtFdr_sink.set_timestep(TIMESTEP);

#ifdef USE_DELAY
	ddtFqr_sink.x(ddtFqr_delay_out);
#else
	ddtFqr_sink.x(ddtFqr_i);
#endif
	ddtFqr_sink.outp(ddtFqr);
	ddtFqr_sink.set_timestep(TIMESTEP);

	P_sink.x(power);
	P_sink.outp(P);
	P_sink.set_timestep(TIMESTEP);

	I_sink.x(power);
	I_sink.outp(I);
	I_sink.set_timestep(TIMESTEP);

//	ddtFdr.set_timestep(TIMESTEP);
//	ddtFqr.set_timestep(TIMESTEP);
//	Idr.set_timestep(TIMESTEP);
//	Iqr.set_timestep(TIMESTEP);
//	idtFdr.set_timestep(TIMESTEP);
//	idtFqr.set_timestep(TIMESTEP);
//	P.set_timestep(TIMESTEP);
//	I.set_timestep(TIMESTEP);
//	ddtFdr.set_delay(1);
//	ddtFqr.set_delay(1);
}

#else

#define THRESHOLD pow(10,-3)

GeneratorEqSys::GeneratorEqSys(sc_core::sc_module_name _name) :
	sca_tdf::sca_module(_name),
	Wg("Wg"),
	ddtFdr("ddtFdr"),
	ddtFqr("ddtFqr"),
	Idr("Idr"),
	Iqr("Iqr"),
	idtFdr("idtFdr"),
	idtFqr("idtFqr"),
	P("P"),
	I("I")
{

}

void GeneratorEqSys::set_attributes()
{
//	ddtFdr.set_timestep(TIMESTEP);
//	ddtFqr.set_timestep(TIMESTEP);
//	idtFdr.set_timestep(TIMESTEP);
//	idtFqr.set_timestep(TIMESTEP);
//	Idr.set_timestep(TIMESTEP);
//	Iqr.set_timestep(TIMESTEP);
//	P.set_timestep(TIMESTEP);
//	I.set_timestep(TIMESTEP);
//	P.set_delay(1);
//	I.set_delay(1);
	ddtFdr.set_delay(1);
	ddtFqr.set_delay(1);
}

void GeneratorEqSys::initialize()
{
	Fiqs = 0.0;
	Fids = 0.0;
	first = true;
}

void GeneratorEqSys::processing()
{
	if (first) {
		first = !first;
		S = -1.05;
		Ids = 25.7205177139132;
		Iqs = -23.5701284511721;
		Idr_i = -387.595129111054;
		Iqr_i = 385.660629524179;
		ddtFdr_i = 0.160761032888432;
		ddtFqr_i = -0.145285036193433;
		Fiqs = 1000.31121826429;
		Fids = -999.714801445741;
		power = REF_VOLT_DS * (Ids - Iqs) + REF_VOLT_QS * (Ids - Iqs);
	} else {
//     S =  1 - Wg.read();
//     Ids =  (Fiqs - 1000)/RES_STATOR;
//     Iqs = -(Fids + 1000)/RES_STATOR;
//     Idr_i = (idtFdr.read() - MUTUAL_REACTANCE*Ids)/REA_ROTOR;
//     Iqr_i = (idtFqr.read() - MUTUAL_REACTANCE*Iqs)/REA_ROTOR;
//     ddtFdr_i = -RES_ROTOR*Idr_i + S*idtFqr.read();
//     ddtFqr_i = -RES_ROTOR*Iqr_i - S*idtFdr.read();
//     Fiqs = REA_STATOR*Iqs + MUTUAL_REACTANCE*Iqr_i;
//     Fids = REA_STATOR*Ids + MUTUAL_REACTANCE*Idr_i;
//     power = REF_VOLT_DS * (Ids - Iqs) + REF_VOLT_QS * (Ids - Iqs);
		S = 1 - Wg.read();
		double idtFdr_read = idtFdr.read();
		double idtFqr_read = idtFqr.read();
		Fids_new = -999.70170657088342026
				   + (1.3950413642039010548E-6) * idtFdr_read
				   - (0.00467813606185818792) * idtFqr_read;
		Ids_new = 24.637651012341070291
				  + (0.3866228150296023188) * idtFdr_read
				  + (1.1529267472760617151E-4) * idtFqr_read;
		Iqs_new = -24.652349513766923794
				  - (1.1529267472760617151E-4) * idtFdr_read
				  + (0.38662281502960231877) * idtFqr_read;
		Fiqs_new = 1000.2981155772493269
				   + (0.0046781360618581879204) * idtFdr_read
				   + (1.395041364204009475E-6) * idtFqr_read;
		Idr_i_new = -386.50752235487471264
					- (0.38662231005553289004) * idtFdr_read
					- (0.0018086742941651606543) * idtFqr_read;
		Iqr_i_new = 386.73810770432992495
					+ (0.0018086742941651606543) * idtFdr_read
					- (0.38662231005553288998) * idtFqr_read;

		Idr_i = Idr_i_new;
		Fids = Fids_new;
		Iqr_i = Iqr_i_new;
		Fiqs = Fiqs_new;
		Iqs = Iqs_new;
		Ids = Ids_new;
		ddtFdr_i = -RES_ROTOR * Idr_i + S * idtFqr.read();
		ddtFqr_i = -RES_ROTOR * Iqr_i - S * idtFdr.read();
		power = REF_VOLT_DS * (Ids - Iqs) + REF_VOLT_QS * (Ids + Iqs);
	}

	sS.write(S);
	sIds.write(Ids);
	sIqs.write(Iqs);
	sIdr_i.write(Idr_i);
	sIqr_i.write(Iqr_i);
	sddtFdr_i.write(ddtFdr_i);
	sddtFqr_i.write(ddtFqr_i);
	sFiqs.write(Fiqs);
	sFids.write(Fids);

	Idr.write(Idr_i);
	Iqr.write(Iqr_i);
	ddtFdr.write(ddtFdr_i);
	ddtFqr.write(ddtFqr_i);
	//P.write(power*0.15);
	P.write(power * 0.17);
	I.write(power / BAT_VOLTAGE);
}

#endif