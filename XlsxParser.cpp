#include "XlsxParser.h"

#include <future>

XlsxParser::XlsxParser()
{
}


XlsxParser::~XlsxParser()
{
}

void XlsxParser::Read(const std::string& filePath)
{
	try
	{
		m_workbook.load(filePath);
		std::clog << "Processing spread sheet" << '\n';

		auto workspace = m_workbook.active_sheet();
		for (auto row : workspace.rows(false))
		{
			for (auto cell : row)
			{
				std::clog << cell.to_string() << '\n';
			}
		}
		std::clog << "Processing spread sheet complete!" << '\n';
	}
	catch (const std::exception& ex)
	{
		std::clog << "ReadXlsx Error: " << ex.what() << '\n';
	}
	catch (...)
	{
		std::clog << "ReadXlsx Unknown Error" << '\n';
	}
}