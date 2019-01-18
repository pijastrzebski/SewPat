#pragma once

#include "XlsxRow.h"

#include <string>
#include <vector>

class XlsxSheet
{
public:
	XlsxSheet();
	~XlsxSheet();

	explicit XlsxSheet(std::string&& name) :
		m_name(std::move(name)) {}

	void AddRowsToContainer(const std::vector<XlsxRow>& row)
	{
		m_rowsContainer.emplace_back(row);
	}

	std::vector<std::vector<XlsxRow>> m_rowsContainer;
	std::string m_name;
};

