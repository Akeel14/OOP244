#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstring>
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
			m_phoneNumbers = new long long[noOfPhoneNumbers];
			m_noOfPhoneNumbers = 0;

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
		std::cout << "Contact::Contact()" << std::endl;
		m_name[0] = '\0';
	}

	// Gets the data when the object is created: name, phoneNumbers, number of phoneNumbers in the array
	Contact::Contact(const char* name, const long long* phoneNumbers, const int noOfPhoneNumbers)
	{
		std::cout << "Contact::Contact(const char* name, const long long* phoneNumbers, const int noOfPhoneNumbers)" << std::endl;
		if (isStringValid(name))
		{
			storeStringCCS(name);
			storePhoneNumbersCLL(phoneNumbers, noOfPhoneNumbers);
		}
		else
			*this = Contact();
	}

	void Contact::display() const{
		std::string countryCode;
		std::string areaCode;
		std::string numberCode1;
		std::string numberCode2;
		std::string phoneNumberString;
		int phoneNumberStringLength;
		if (!isEmpty()) {
		
			std::cout << m_name << std::endl;
			for (int phone = 0; phone < m_noOfPhoneNumbers; phone++) {
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

    Contact::Contact(const Contact& other)
    {
        *this = other;
    }

    Contact& Contact::operator=(const Contact& rhs)
    {
		std::cout << "Contact& Contact::operator=(const Contact& rhs)" << std::endl;
        if (this != &rhs) 
        {
            strncpy(m_name, rhs.m_name, strlen(rhs.m_name));
			m_name[strlen(rhs.m_name) - 1] = '\0';
            m_noOfPhoneNumbers = rhs.m_noOfPhoneNumbers;

            if (rhs.m_phoneNumbers != nullptr) 
			{
                m_phoneNumbers = new long long[m_noOfPhoneNumbers];

                for (int i = 0; i < m_noOfPhoneNumbers; i++)
					m_phoneNumbers[i] = rhs.m_phoneNumbers[i];
            }
            else 
                m_phoneNumbers = nullptr;
        }

        return *this;
    }

    Contact& Contact::operator+=(long long phoneNumber)
    {
        bool valid = isValidPhoneNumber(phoneNumber);

        if (valid)
        {
            m_noOfPhoneNumbers++;
            
            long long* t_PhoneNumbers = new long long[m_noOfPhoneNumbers];

            for (int i = 0; i < m_noOfPhoneNumbers - 1; ++i)
                t_PhoneNumbers[i] = m_phoneNumbers[i];

            t_PhoneNumbers[m_noOfPhoneNumbers - 1] = phoneNumber;
            delete[] m_phoneNumbers;
            m_phoneNumbers = t_PhoneNumbers;
        }

        return *this;
    }

}