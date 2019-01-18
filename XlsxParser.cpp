#include "XlsxParser.h"

#include <future>

XlsxParser::XlsxParser() :
	m_cellIterator(0),
	m_rowIterator(0)
{
	Init();
}


void XlsxParser::Init()
{
	m_patternsContainer.insert({
		{ "rękaw dzianionowy" , EReaderPatterns::REKAW_DZIANINOWY},
		{ "rękaw tkaniniowy" , EReaderPatterns::REKAW_TKANINOWY },
		{ "luźna bluzka" , EReaderPatterns::LUZNA_BLUZKA },
		{ "sukienka z zaszewką" , EReaderPatterns::SUKIENKA_Z_ZASZEWKA } }
	);
}

bool XlsxParser::Read(const std::string& filePath)
{
	auto success = false;
	
	try
	{
		m_workbook.load(filePath);
		std::clog << "\n**Reading spread sheet**\n" << '\n';

 		for (const auto& sheet : m_workbook)
		{
			auto name = sheet.title();

			// get data from the xlsx sheet
			const int ASCII_A = 65;
			for (auto row : sheet.rows(false))
			{
				m_rowsContainer.emplace_back();

				for (auto cell : row)
				{
					m_rowsContainer[m_rowIterator].AddCellToContainer({
						cell.to_string(),
						static_cast<char>(m_cellIterator + ASCII_A),
						m_rowIterator + 1 });

					std::clog << "Content: " << m_rowsContainer[m_rowIterator].m_cellsContainer[m_cellIterator].m_content
						<< " Row: " << m_rowsContainer[m_rowIterator].m_cellsContainer[m_cellIterator].m_row
						<< " Column: " << m_rowsContainer[m_rowIterator].m_cellsContainer[m_cellIterator].m_column
						<< '\n';

					m_cellIterator++;
				}
				m_cellIterator = 0;
				m_rowIterator++;
			}
			m_sheetsContainer.emplace_back(std::move(name)).AddRowsToContainer(m_rowsContainer);
			
			m_rowsContainer.clear();
			m_rowIterator = 0;
		}
		std::clog << "\n**Reading spread sheet complete!**\n" << '\n';

		Parse();
		success = true;
	}
	catch (const std::exception& ex)
	{
		std::clog << "ReadXlsx Error: " << ex.what() << '\n';
	}
	catch (...)
	{
		std::clog << "ReadXlsx Unknown Error" << '\n';
	}
	return success;
}

bool XlsxParser::Parse()
{
	std::clog << "\n**Parsing spread sheet**\n" << '\n';

	auto success = false;

	for (const auto& sheet : m_sheetsContainer)
	{
		switch (m_patternsContainer[sheet.m_name])
		{
		case SUKIENKA_Z_ZASZEWKA:
			std::clog << "Detected Read Pattern: SUKIENKA_Z_ZASZEWKA\n";

			//Continue here!

			success = true;
			break;
		case REKAW_DZIANINOWY:
			std::clog << "Detected Read Pattern: REKAW_DZIANINOWY\n";
			//TODO: impl
			break;
		case REKAW_TKANINOWY:
			std::clog << "Detected Read Pattern: REKAW_TKANINOWY\n";
			//TODO: impl
			break;
		case LUZNA_BLUZKA:
			std::clog << "Detected Read Pattern: LUZNA_BLUZKA\n";
			//TODO: impl
			break;
		default:
			break;
		}
	}
	std::clog << "\n**Parsing spread sheet complete!**\n" << '\n';

	return success;
}