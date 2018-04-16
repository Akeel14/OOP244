// File: Product.h
// Author: Lean Junio
// Description: Header for Product module

#ifndef AMA_PRODUCT_H
#define AMA_PRODUCT_H

#include <iostream>
#include "iProduct.h"
#include "ErrorState.h"

namespace AMA
{
	const int MAX_CHAR_SKU = 7;					
	const int MAX_CHAR_UNIT = 10;				
	const int MAX_CHAR_NAME = 75;				
	const double TAX_RATE = 0.13;				

	const int max_sku_length = MAX_CHAR_SKU;
	const int max_name_length = MAX_CHAR_NAME;
	const int max_unit_length = MAX_CHAR_UNIT;

	class Product : public iProduct
	{
		char m_type;
		char m_sku[MAX_CHAR_SKU];
		char m_unit[MAX_CHAR_UNIT];
		char* m_name;
		int m_qty;
		int m_needed;
		double m_price;
		bool m_taxable;

	protected:
		ErrorState er;
		void name(const char* name);
		const char* name() const;
		const char* sku() const;
		const char* unit() const;
		bool taxed() const;
		double price() const;
		double cost() const;
		void message(const char* errorMessage);
		bool isClear() const;

	public:
		Product(char type = 'N');
		Product(const char* sku, const char* name, const char* unit, int quantity = 0, bool taxable = true, double price = 0.0, int needed = 0);
		Product(const Product& other);
		Product& operator=(const Product& other);
		~Product();
		std::fstream& store(std::fstream& file, bool newLine = true) const;
		std::fstream& load(std::fstream& file);
		std::ostream& write(std::ostream& os, bool linear) const;
		std::istream& read(std::istream& is);
		bool operator==(const char* rhs) const;
		double total_cost() const;
		void quantity(int quantity);
		void price(double price);
		void needed(int needed);
		bool isEmpty() const;
		char type() const;
		int qtyNeeded() const;
		int quantity() const;
		bool operator>(const char* rhs) const;
		bool operator>(const iProduct& rhs) const;
		int operator+=(int units);
	};

	std::ostream& operator<<(std::ostream& os, const iProduct& other);
	std::istream& operator>>(std::istream& is, iProduct& other);
	double operator+=(double& total, const iProduct& other);
	iProduct* CreateProduct();
}

#endif // !AMA_PRODUCT_H


