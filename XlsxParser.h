#pragma once

#include "xlnt/xlnt.hpp"
#include "IParser.h"
#include "XlsxSheet.h"
#include "XlsxRow.h"
#include "XlsxCell.h"
#include "SSZ_ParserResults.h"
//#include "PatternCalculator.h"

#include <string>
#include <vector>
#include <unordered_map>

enum EReaderPatterns
{
	REKAW_DZIANINOWY = 0,
	REKAW_TKANINOWY,
	LUZNA_BLUZKA,
	SUKIENKA_Z_ZASZEWKA
};

class XlsxParser : public IParser
{	
public:
	XlsxParser();

	void Init() override;
	bool Read(const std::string& filePath) override;
	bool Parse() override;
	IParserResults* GetResults() override { return m_sszResults.get(); };

protected:
	std::vector<XlsxSheet> m_sheetsContainer;
	std::vector<XlsxRow> m_rowsContainer;
	std::unordered_map<std::string, EReaderPatterns> m_patternsContainer;

private:
	xlnt::workbook m_workbook;
	std::unique_ptr<IParserResults> m_sszResults;
	//std::unique_ptr<PatternCalculator> m_calculator;

	int m_cellIterator;
	int m_rowIterator;
};

