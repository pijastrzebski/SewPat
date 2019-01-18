#pragma once

#include "XlsxCell.h"

#include <vector>

class XlsxRow
{
public:
	XlsxRow();
	XlsxRow(const XlsxRow& copy) = default;
	~XlsxRow();

	void AddCellToContainer(XlsxCell&& cell)
	{
		m_cellsContainer.emplace_back(std::move(cell));
	}
	std::vector<XlsxCell> m_cellsContainer;
};

