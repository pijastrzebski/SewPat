#pragma once

#include <string>

struct SSZ_ParserResults
{
	SSZ_ParserResults() = default;

	SSZ_ParserResults(
		std::string name,
		float opx,
		float opp,
		float ot,
		float ob,
		float SySvX,
		float SySvXTp,
		float SyTy,
		float ZWo,
		float ZTv,
		float ZKo,
		float SvRv,
		float RvNv,
		float Or,
		float on,
		float PcR1
	) :
		m_name(name),
		m_opx(opx),
		m_opp(opp),
		m_ot(ot),
		m_ob(ob),
		m_SySvX(SySvX),
		m_SySvXTp(SySvXTp),
		m_SyTy(SyTy),
		m_ZWo(ZWo),
		m_ZTv(ZTv),
		m_ZKo(ZKo),
		m_SvRv(SvRv),
		m_RvNv(RvNv),
		m_Or(Or),
		m_on(on),
		m_PcR1(PcR1)
	{}

	std::string m_name;

	float m_opx,
		m_opp,
		m_ot,
		m_ob,
		m_SySvX,
		m_SySvXTp,
		m_SyTy,
		m_ZWo,
		m_ZTv,
		m_ZKo,
		m_SvRv,
		m_RvNv,
		m_Or,
		m_on,
		m_PcR1;
};
