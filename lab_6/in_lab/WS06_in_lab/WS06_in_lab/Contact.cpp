#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <string>
#include "Contact.h"

namespace sict
{

	bool Contact::isValidPhoneNumber(const long long phoneNumber)
	{
		std::string phoneNumberString = std::to_string(phoneNumber);
		bool phoneInvalid = phoneNumber <= 0 || phoneNumberString.length() < 11 || phoneNumberString.length() > 12 || phoneNumberString[phoneNumberString.length() - 7] == '0' || phoneNumberString[phoneNumberString.length() - 10] == '0';
		return !phoneInvalid;
	}
	bool Contact::isStringValid(const char* string)
	{
		return (string != nullptr && string[0] != '\0');
	}
	bool Contact::isEmpty() const
	{
		return (m_name[0] == '\0' && m_phoneNumbers == nullptr && m_noOfPhoneNumbers == 0) ? true : false;
	}
	void Contact::storeStringCCS(const char* name)
	{
		if (isStringValid(name))
		{
			std::string s_name(name, strlen(name));
			std::strncpy(m_name, s_name.c_str(), sizeof(m_name));
			m_name[sizeof(m_name) - 1] = '\0';
		}
		else
			m_name[0] = '\0';
	}
	void Contact::storePhoneNumbersCLL(const long long* phoneNumbers, const int noOfPhoneNumbers)
	{
		if (phoneNumbers != nullptr && noOfPhoneNumbers > 0)
		{
			// Allocate memory and increment counter
			m_phoneNumbers = new long long[noOfPhoneNumbers];
			m_noOfPhoneNumbers = 0;

			// Store the phone numbers
			for (int i = 0; i < noOfPhoneNumbers; ++i)
			{
				if (isValidPhoneNumber(phoneNumbers[i]))
				{
					m_noOfPhoneNumbers += 1;
					m_phoneNumbers[m_noOfPhoneNumbers - 1] = phoneNumbers[i];
				}
			}
		}
		else
		{
			m_phoneNumbers = nullptr;
			m_noOfPhoneNumbers = 0;
		}
	}
	Contact::Contact()
		: m_noOfPhoneNumbers(0),
		  m_phoneNumbers(nullptr)
	{
		m_name[0] = '\0';
	}

	Contact::Contact(const char *name, const long long *phoneNumbers, const int noOfPhoneNumbers)
		// Gets the data when the object is created: name, phoneNumbers, number of phoneNumbers in the array
	{
		storeStringCCS(name);
		storePhoneNumbersCLL(phoneNumbers, noOfPhoneNumbers);
	}

	void Contact::display() const
	{
		std::string countryCode;
		std::string areaCode;
		std::string numberCode1;
		std::string numberCode2;
		std::string phoneNumberString;
		int phoneNumberStringLength;
		if (!isEmpty())
		{

			std::cout << m_name << std::endl;
			for (int phone = 0; phone < m_noOfPhoneNumbers; phone++)
			{
				phoneNumberString = std::to_string(m_phoneNumbers[phone]);
				phoneNumberStringLength = phoneNumberString.length();
				countryCode = phoneNumberString.substr(0, (phoneNumberStringLength - (areaCodeLength + numberLength)));
				areaCode = phoneNumberString.substr(phoneNumberStringLength - (areaCodeLength + numberLength), areaCodeLength);
				numberCode1 = phoneNumberString.substr(phoneNumberStringLength - numberLength, numberCode1Length);
				numberCode2 = phoneNumberString.substr(phoneNumberStringLength - numberCode2Length, numberCode2Length);

				std::cout << "(+" + countryCode + ")" + " " + areaCode + " " + numberCode1 + "-" + numberCode2 << std::endl;
			}
		}
		else
			std::cout << "Empty contact!" << std::endl;
	}

	Contact::~Contact()
	{
		delete[] m_phoneNumbers;
		m_phoneNumbers = nullptr;
	}
}