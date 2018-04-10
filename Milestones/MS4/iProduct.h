#ifndef AMA_IPRODUCT_H
#define AMA_IPRODUCT_H
#include <iostream>
#include <fstream>
namespace AMA
{
    class iProduct
    {
    public:
        // newLine specifies if a newline should be inserted after each iProduct record
        // Insert the Product records into the file
        virtual std::fstream& store(std::fstream& file, bool newLine=true) const = 0;

        // Extract iProduct records from the file
        virtual std::fstream& load(std::fstream& file) = 0;

        // The bool argument will specify whether or not the records should be listed on a single line or on separate lines
        // insert the iProduct record for the current object into the ostream object
        virtual std::ostream& write(std::ostream& os, bool linear) const = 0;

        // extract the iProduct record for the current object from the istream object
        virtual std::istream& read(std::istream& is) = 0;

        // return true if the string received is identical to the stock keeping unit of an iProduct record
        virtual bool operator==(const char*) const = 0;

        // return the cost of a single unit of an iProduct with taxes included
        virtual double total_cost() const = 0;

        // Return the name of the iProduct
        virtual const char* name() const = 0;

        // This modifier will receive an integer holding the number of units of an iProduct that are currently available. This function will set the number of units available
        virtual void quantity(int) = 0;

        // Return number of units of an iProduct needed
        virtual int qtyNeeded() const = 0;

        // Return number of units of iProduct currently available
        virtual int quantity() const = 0;

        // Add units received to iProduct and return the total
        virtual int operator+=(int) = 0;

        // return true if the current object is greater than the referenced iProduct object
        virtual bool operator>(const iProduct&) const = 0;
    };

    // insert the iProduct record for the referenced object into the ostream object
    std::ostream& operator<<(std::ostream&, const iProduct&);

    // extract the iProduct record for the referenced object from the istream object
    std::istream& operator>>(std::istream&, iProduct&);

    // will add the total cost of the iProduct object to the double received and return the updated value of the double
    double operator+=(double&, const iProduct&);

    // Return the address of a Product object
    iProduct* CreateProduct();

    // return the address of a Perishable object
    iProduct* CreatePerishable();
}

#endif //AMA_IPRODUCT_H
