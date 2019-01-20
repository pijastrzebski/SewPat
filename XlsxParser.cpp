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

		auto sheetNum = 0;
 		for (const auto& sheet : m_workbook)
		{
			auto name = sheet.title();
			m_sheetsContainer.emplace_back(std::move(name));

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
				m_sheetsContainer[sheetNum].AddRowsToContainer(m_rowsContainer[m_rowIterator]);
				m_cellIterator = 0;
				m_rowIterator++;
			}			
			m_rowsContainer.clear();
			m_rowIterator = 0;
			sheetNum++;
		}
		std::clog << "\n**Reading spread sheet complete!**\n" << '\n';

		success = Parse();
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
	std::clog << "\n**Start Parsing**\n" << '\n';

	auto success = false;

	for (const auto& sheet : m_sheetsContainer)
	{
		switch (m_patternsContainer[sheet.m_name])
		{
		case SUKIENKA_Z_ZASZEWKA:
		{
			std::clog << "Detected Read Pattern: SUKIENKA_Z_ZASZEWKA\n";

			// gather the results
			m_sszResults = std::make_unique<SSZ_ParserResults>(
				sheet.m_name,
				// Upper left table
				stof(sheet.m_rowsContainer[0].m_cellsContainer[2].m_content),
				stof(sheet.m_rowsContainer[1].m_cellsContainer[2].m_content),
				stof(sheet.m_rowsContainer[2].m_cellsContainer[2].m_content),
				stof(sheet.m_rowsContainer[3].m_cellsContainer[2].m_content),
				stof(sheet.m_rowsContainer[4].m_cellsContainer[2].m_content),
				stof(sheet.m_rowsContainer[5].m_cellsContainer[2].m_content),
				stof(sheet.m_rowsContainer[6].m_cellsContainer[2].m_content),
				stof(sheet.m_rowsContainer[7].m_cellsContainer[2].m_content),
				stof(sheet.m_rowsContainer[8].m_cellsContainer[2].m_content),
				stof(sheet.m_rowsContainer[9].m_cellsContainer[2].m_content),
				stof(sheet.m_rowsContainer[10].m_cellsContainer[2].m_content),
				stof(sheet.m_rowsContainer[11].m_cellsContainer[2].m_content),
				stof(sheet.m_rowsContainer[12].m_cellsContainer[2].m_content),
				stof(sheet.m_rowsContainer[13].m_cellsContainer[2].m_content),
				// Top middle table
				stof(sheet.m_rowsContainer[0].m_cellsContainer[9].m_content),
				stof(sheet.m_rowsContainer[1].m_cellsContainer[9].m_content),
				stof(sheet.m_rowsContainer[2].m_cellsContainer[9].m_content),
				stof(sheet.m_rowsContainer[3].m_cellsContainer[9].m_content),
				stof(sheet.m_rowsContainer[4].m_cellsContainer[9].m_content),
				stof(sheet.m_rowsContainer[5].m_cellsContainer[9].m_content),
				// Rozciagliwosc
				stof(sheet.m_rowsContainer[6].m_cellsContainer[8].m_content)
			);

			//auto results = m_calculator->Calculate(m_sszResults);
		}
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
	success = true;
	std::clog << "\n**Parsing Complete!**\n" << '\n';

	return success;
}