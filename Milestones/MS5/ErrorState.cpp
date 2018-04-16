// File: ErrorState.cpp
// Author: Lean Junio
// Description: Implementation for ErrorState module

#include <iostream>
#include <cstring>
#include "ErrorState.h"
using namespace std;
using namespace AMA;

namespace AMA
{
	ErrorState::ErrorState(const char * errorMessage)
	{
		if (errorMessage != nullptr)
		{
			int length = strlen(errorMessage);
			m_message = new char[length];
			for (int i = 0; i < length; i++)
			{
				m_message[i] = errorMessage[i];
			}
			m_message[length] = '\0';
		}
		else
			m_message = nullptr;
	}
	ErrorState::~ErrorState()
	{
		delete[] m_message;
		m_message = nullptr;
	}
	void ErrorState::clear()
	{
		delete[] m_message;
		m_message = nullptr;
	}
	bool ErrorState::isClear() const
	{
		return (m_message == nullptr) ? true : false;
	}
	void ErrorState::message(const char * str)
	{
		int length = strlen(str);

		delete[] m_message;
		m_message = nullptr;

		m_message = new char[length + 1];
		for (int i = 0; i < length; i++)
		{
			m_message[i] = str[i];
		}
		m_message[length] = '\0';
	}
	const char * ErrorState::message() const
	{
		return m_message;
	}
	std::ostream & operator<<(std::ostream& os, const ErrorState & er)
	{
		if (!er.isClear())
		{
			os << er.message();
		}
		return os;
	}
}

