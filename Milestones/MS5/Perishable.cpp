// File: Perishable.cpp
// Author: Lean Junio
// Description: Implementation file for Perishable module

#include <iostream>
#include "Perishable.h"
using namespace std;

namespace AMA
{
	Perishable::Perishable() : Product('P')
	{
		er.clear();
	}

	std::fstream & Perishable::store(std::fstream & file, bool newLine) const
	{
		Product::store(file, false);
		file << ',' << m_date << endl;
		return file;
	}
	std::fstream & Perishable::load(std::fstream & file)
	{
		Product::load(file);
		m_date.read(file);
		file.ignore();
		return file;
	}
	std::ostream & Perishable::write(std::ostream & os, bool linear) const
	{
		Product::write(os, linear);

		if (isClear() && !isEmpty())
		{
			if (linear)
				m_date.write(os);
			else
			{
				os << "\n Expiry date: ";
				m_date.write(os);
			}
		}
		return os;
	}
	std::istream & Perishable::read(std::istream & is)
	{
		is.clear();
		Product::read(is);

		if (er.isClear()) 
		{
			cout << " Expiry date (YYYY/MM/DD): ";
			m_date.read(is);
		}

		if (m_date.errCode() == CIN_FAILED)
		{
			er.clear();
			er.message("Invalid Date Entry");
		}

		if (m_date.errCode() == YEAR_ERROR)
		{
			er.message("Invalid Year in Date Entry");
		}

		if (m_date.errCode() == MON_ERROR)
		{
			er.clear();
			er.message("Invalid Month in Date Entry");
		}

		if (m_date.errCode() == DAY_ERROR)
		{
			er.clear();
			er.message("Invalid Day in Date Entry");
		}

		if (m_date.errCode())
		{
			is.setstate(std::ios::failbit);
		}

		if (m_date.errCode() != CIN_FAILED && m_date.errCode() != YEAR_ERROR && m_date.errCode() != MON_ERROR && m_date.errCode() != DAY_ERROR)
		{
			er.clear();
		}

		return is;
	}
	const Date & Perishable::expiry() const
	{
		return m_date;
	}
}

