// File: Date.h
// Author: Lean Junio
// Desc: Header file for Date Module

#ifndef AMA_DATE_H
#define AMA_DATE_H

#include <iostream>

namespace AMA 
{
	const int NO_ERROR = 0;
	const int CIN_FAILED = 1;
	const int YEAR_ERROR = 2;
	const int MON_ERROR = 3;
	const int DAY_ERROR = 4;

	const int min_year = 2000;
	const int max_year = 2030;

	class Date
	{
	public:
		Date();
		Date(int year, int month, int day);
		int errCode(void) const;
		bool bad(void) const;
		bool operator==(const Date& rhs) const;
		bool operator!=(const Date& rhs) const;
		bool operator<(const Date& rhs) const;
		bool operator>(const Date& rhs) const;
		bool operator<=(const Date& rhs) const;
		bool operator>=(const Date& rhs) const;
		std::istream& read(std::istream& istr);
		std::ostream& write(std::ostream& ostr) const;

	private:
		int m_year, m_month, m_day, m_comparator, m_errorState;

		int mdays(int month, int year) const;
		void errCode(int errorCode);
		bool checkParams(int year, int month, int day);
		bool checkErrorCode(int errorCode);
	};

	std::ostream& operator<<(std::ostream& ostr, const Date&);
	std::istream& operator>>(std::istream& istr, Date&);
}

#endif // !AMA_DATE_H


