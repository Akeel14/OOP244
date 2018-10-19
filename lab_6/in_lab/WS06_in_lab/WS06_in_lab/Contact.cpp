#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <string>
#include "Contact.h"

namespace sict
{
	bool Contact::checkValidPhone(const long long phoneNumber)
	{
		std::string phoneNumberString = std::to_string(phoneNumber);
		bool isPhoneInvalid = phoneNumber <= 0 || phoneNumberString.length() < 11 || phoneNumberString.length() > 12 || phoneNumberString[phoneNumberString.length() - 7] == '0' || phoneNumberString[phoneNumberString.length() - 10] == '0';
		
		// ! because the function checks if the phone is valid
		return !isPhoneInvalid;	
	}
	bool Contact::isStringValid(const char* string)
	{
		bool stringEmptyNull = string != nullptr && string[0] != '\0';
		return stringEmptyNull;
	}
	bool Contact::isEmpty() const
	{
		// Check if either Name, m_phoneNumbers pointers, and m_noOfPhoneNumbers is empty or null
		bool checkNamePhoneNumberPhones = m_name[0] == '\0' && m_phoneNumbers == nullptr && m_noOfPhoneNumbers == 0;
		return checkNamePhoneNumberPhones;
	}
	void Contact::storeName(const char* name)
	{
		if (isStringValid(name))
		{
			std::string s_name(name, strlen(name));
			std::strncpy(m_name, s_name.c_str(), strlen(name));
			m_name[strlen(name) - 1] = '\0';
		}
		else
			m_name[0] = '\0';
	}
	void Contact::storePhoneNumbers(const long long* phoneNumbers, const int noOfPhoneNumbers)
	{
		if (phoneNumbers != nullptr && noOfPhoneNumbers > 0)
		{
			// Allocate memory and increment counter
			m_phoneNumbers = new long long[noOfPhoneNumbers];
			m_noOfPhoneNumbers = 0;

			// Store the phone numbers
			for (int i = 0; i < noOfPhoneNumbers; ++i)
			{
				if (checkValidPhone(phoneNumbers[i]))
				{
					m_noOfPhoneNumbers++;
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
	{
		storeName(name);
		storePhoneNumbers(phoneNumbers, noOfPhoneNumbers);
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