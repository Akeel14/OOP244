// File: Date.cpp
// Author: Lean Junio
// Desc: Implementation file for Date Module

#include <iostream>
#include "Date.h"
using namespace std;

namespace AMA
{
	// Set all members to safe empty states
	Date::Date()
	{
		m_year = 0;
		m_month = 0;
		m_day = 0;
		m_comparator = 0;
		m_errorState = NO_ERROR;
	}

	// Valides and stores parameter values
	Date::Date(int year, int month, int day)
	{	
		// If all the parameters are valid
		if (checkParams(year, month, day))
		{
			m_year = year;
			m_month = month;
			m_day = day;
			m_errorState = NO_ERROR;
			m_comparator = year * 372 + month * 13 + day;
		}
		else
			*this = Date();
	}

	// Returns m_errorState
	int Date::errCode(void) const
	{
		return m_errorState;
	}

	// Returns true if m_errorState = NO_ERROR
	bool Date::bad(void) const
	{
		if (m_errorState == NO_ERROR)
			return true;
		else
			return m_errorState;
	}

	// Check if the compared dates are identical
	bool Date::operator==(const Date & rhs) const
	{
		bool day = m_day == rhs.m_day;
		bool month = m_month == rhs.m_month;
		bool year = m_year == rhs.m_year;

		if (day && month && year)
			return true;
		else
			return false;
	}

	// Check if the compared dates are NOT identical
	bool Date::operator!=(const Date & rhs) const
	{
		// if the *this and rhs are not identical, return true else return false
		return !(*this == rhs);
	}

	// check if the left date is lower than the date on the right
	bool Date::operator<(const Date & rhs) const
	{
		bool lessYear = m_year < rhs.m_year;
		bool lessMonth = m_month < rhs.m_month;
		bool lessDay = m_day < rhs.m_day;
		
		// check first if year is lower, then month, then day
		if (lessYear)
			return true;
		else if (lessMonth)
			return true;
		else if (lessDay)
			return true;
		else
			return false;
	}

	// Check if the left date is greater than the date on the right
	bool Date::operator>(const Date & rhs) const
	{
		bool equal = *this == rhs;
		bool leftLessRight = *this < rhs;

		if (equal || leftLessRight)
			return false;
		else
			return true;
	}

	// Check if the left <= rhs
	bool Date::operator<=(const Date & rhs) const
	{
		bool equal = *this == rhs;
		bool leftLessRight = *this < rhs;

		if (equal || leftLessRight)
			return true;
		else
			return false;
	}

	// Check if left >= right
	bool Date::operator>=(const Date & rhs) const
	{
		bool equal = *this == rhs;
		bool leftGreaterRight = *this > rhs;
		
		if (equal || leftGreaterRight)
			return true;
		else
			return false;
	}

	// Reads from the console in YYYY/MM/DD
	std::istream & Date::read(std::istream & istr)
	{
		char symbolToIgnore;

		errCode(NO_ERROR);
		istr >> m_year >> symbolToIgnore >> m_month >> symbolToIgnore >> m_day;

		if (cin.fail() || istr.fail())
		{
			*this = Date();
			errCode(CIN_FAILED);
		}

		else if (!checkParams(m_year, m_month, m_day))
		{
			istr.clear();
			return istr;
		}

		istr.clear();
		return istr;
	}

	// Writes the date to an ostr object
	std::ostream & Date::write(std::ostream & ostr) const
	{
		ostr << m_year << "/";
		(m_month < 10) ? ostr << 0 << m_month << "/" : ostr << m_month << "/";
		(m_day < 10) ? ostr << 0 << m_day << "/" : ostr << m_day;

		return ostr;
	}

	// Checks if month = 1 to 13
	int Date::mdays(int mon, int year) const
	{
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13;
		month--;
		return days[month] + int((month == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}

	// Set error state to one of the constants
	void Date::errCode(int errorCode)
	{
		if (checkErrorCode(errorCode))
			m_errorState = errorCode;
		else
			cout << "Entered errorCode (range: 0 - 4): " << errorCode << endl;
	}

	// Return true if parameters are valid
	bool Date::checkParams(int year, int month, int day)
	{
		// Check if the parameters all have values
		bool missingParameter = !year || !month || !day;		

		bool year_range = year >= min_year && year <= max_year;
		bool month_range = month >= 1 && month <= 12;
		bool day_range = day >= 1 && day <= 31;

		// If all the parameters have values, check if they have the correct ranges
		if (!missingParameter)
		{
			// Iff al the parameters are within their ranges
			if (year_range && month_range && day_range)
				return true;
			else
			{
				if (!year_range)
				{
					*this = Date();
					errCode(YEAR_ERROR);
				}

				else if (!month_range)
				{
					*this = Date();
					errCode(MON_ERROR);
				}

				else if (!day_range || m_day > mdays(m_month, m_year))
				{
					*this = Date();
					errCode(DAY_ERROR);
				}

				return false;
			}
		}
		else
			return false;
	}

	// Check if errorCode is valid
	bool Date::checkErrorCode(int errorCode)
	{
		if (errorCode >= 0 && errorCode <= 4)
			return true;
		else
			return false;
	}

	// Print out the date in the console
	std::ostream & operator<<(std::ostream & ostr, const Date &other)
	{
		return other.write(ostr);
	}

	// read the date from the console
	std::istream & operator>>(std::istream & istr, Date &other)
	{
		return other.read(istr);
 	}
}
