#pragma once

#include <string>
#include "IParserResults.h"

struct SSZ_ParserResults : IParserResults
{
	SSZ_ParserResults() = default;

	SSZ_ParserResults(
		const std::string& name,
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
		float dk,
		float luz1,
		float luz2,
		float luz3,
		float luz4,
		float luz5,
		float stretch
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
		m_dk(dk),
		m_luz1(luz1),
		m_luz2(luz2),
		m_luz3(luz3),
		m_luz4(luz4),
		m_luz5(luz5),
		m_stretch(stretch)
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
		m_dk,
		m_luz1,
		m_luz2,
		m_luz3,
		m_luz4,
		m_luz5,
		m_stretch;

	void PrintResult() override
	{
	}
};
