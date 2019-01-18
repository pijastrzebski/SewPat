#pragma once

#include "xlnt/xlnt.hpp"
#include "IParser.h"

#include <string>


class XlsxParser : public IParser
{
public:
	XlsxParser();
	~XlsxParser();

	void Read(const std::string& filePath) override;

private:
	xlnt::workbook m_workbook;
};

