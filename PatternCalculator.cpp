#include "PatternCalculator.h"

CalculatedResults PatternCalculator::Calculate(const SSZ_ParserResults& pr)
{
	CalculatedResults cr;

	cr.m_SyP  = pr.m_opp * pr.m_stretch / 9 + 10.8f + pr.m_dk;
	cr.m_SyL  = cr.m_SyP / 2;
	cr.m_SyT  = pr.m_ZWo / 4 - 1;
	cr.m_TB   = pr.m_ZWo / 10 + 4;
	cr.m_TK   = pr.m_ZTv - pr.m_ZKo;
	cr.m_a    = pr.m_opx * pr.m_stretch - 8 * pr.m_opp * pr.m_stretch / 7;
	cr.m_PyPc = pr.m_opp * pr.m_stretch / 7 + 5.5f + pr.m_luz1;
	cr.m_PcPl = pr.m_opp * pr.m_stretch / 7 - 1.5f + pr.m_luz2;
	cr.m_PlPx = 2 * pr.m_opp * pr.m_stretch / 7 - 4 + cr.m_a / 2 + pr.m_luz3;
	cr.m_PyPx = 4 * pr.m_opp * pr.m_stretch / 7 + cr.m_a / 2 + pr.m_luz1 + pr.m_luz2 + pr.m_luz3;
	cr.m_PcPv = 2 * cr.m_PcPl / 3;
	cr.m_PxPp = pr.m_opp * pr.m_stretch / 9 + 0.8f + cr.m_a / 8;
	cr.m_SyS2 = pr.m_opp * pr.m_stretch / 18 + 2.1f;
	cr.m_S3R2 = pr.m_SvRv + pr.m_luz1;
	cr.m_PcR1 = cr.m_SyP - cr.m_S1_R1;
	cr.m_PlR3 = cr.m_PcR1 - 2 - cr.m_a / 10;
	cr.m_R3R4 = pr.m_opp * pr.m_stretch / 18 - cr.m_a / 20;
	cr.m_R4S7 = cr.m_S3R2 - 1;
	cr.m_TxTa = cr.m_a / 4;
	cr.m_TaS4 = cr.m_SyT + pr.m_opp * pr.m_stretch / 18 + 3 * cr.m_a / 7;
	cr.m_S4S6 = cr.m_SyS2;
	cr.m_S4Sx = cr.m_S4S6 + 1.5f;
	cr.m_S5x = 2 * pr.m_opp * pr.m_stretch / 7 + cr.m_a / 4 + 4;
	cr.m_b = pr.m_ob * pr.m_stretch / 4 + pr.m_luz4 / 2;
	cr.m_wb = (pr.m_ob * pr.m_stretch - pr.m_ot * pr.m_stretch) / 5 - 1.5f; //
	cr.m_t = cr.m_b - cr.m_wb;
	cr.m_z = 2 * cr.m_t - pr.m_ot * pr.m_stretch / 2 - pr.m_luz5;
	cr.m_zp = 2 * cr.m_z / 5;
	cr.m_zt = 3 * cr.m_z / 5;

	return cr;
}
