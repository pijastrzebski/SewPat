#pragma once

#include <string>

class XlsxCell
{
public:
	XlsxCell(const std::string& content, char column, int row);
	~XlsxCell();

	std::string m_content;
	char m_column;
	int m_row;
};

