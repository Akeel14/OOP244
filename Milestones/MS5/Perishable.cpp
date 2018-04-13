#include <iostream>
#include "Perishable.h"
#include "Product.h"
#include "Date.h"
using namespace std;
using namespace AMA;

namespace AMA
{
    Perishable::Perishable()
    {
        Product('P');
		mp_Err.clear();
    }

    fstream& Perishable::store(fstream& file, bool newLine) const
    {
		Product::store(file, false);
		(newLine) ? file << "," << exp << endl : file << ",";
        return file;
    }

	fstream& Perishable::load(fstream& file)
	{
		Product::load(file);
		exp.read(file);
		file.ignore();
		return file;
	}

	ostream& Perishable::write(ostream& os, bool linear) const
	{
		Product::write(os, linear);

		if (isClear() && !isEmpty())
		{
			if (linear) 
				exp.write(os);
			else
			{
				os << "\nExpiry date: ";
				exp.write(os);
			}
		}
		return os;
	}

	istream& Perishable::read(istream& is)
	{
		is.clear();
		Product::read(is);

		if (mp_Err.isClear()) {
			std::cout << "Expiry date (YYYY/MM/DD): ";
			exp.read(is);
		}

		if (exp.errCode() == CIN_FAILED) {
			mp_Err.clear();
			mp_Err.message("Invalid Date Entry");
		}
		if (exp.errCode() == YEAR_ERROR) {
			mp_Err.message("Invalid Year in Date Entry");
		}
		if (exp.errCode() == MON_ERROR) {
			mp_Err.clear();
			mp_Err.message("Invalid Month in Date Entry");
		}
		if (exp.errCode() == DAY_ERROR) {
			mp_Err.clear();
			mp_Err.message("Invalid Day in Date Entry");
		}
		if (exp.errCode()) {
			is.setstate(std::ios::failbit);
		}
		if (exp.errCode() != CIN_FAILED && exp.errCode() != YEAR_ERROR && exp.errCode() != MON_ERROR && exp.errCode() != DAY_ERROR) {
			mp_Err.clear();  //clear if there is no errorcodmp_Err
		}
		return is;
	}

	const Date& Perishable::expiry() const
	{
		return exp;
	}
}