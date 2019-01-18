#include "XlsxCell.h"



XlsxCell::XlsxCell(const std::string& content, char column, int row) :
	m_content(content),
	m_column(column),
	m_row(row)
{
}


XlsxCell::~XlsxCell()
{
}
