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
			if (linear) exp.write(os);
			else
			{
				os << "\nExpiry date: ";
				exp.write(os);
			}
		}
		return os;
	}
}