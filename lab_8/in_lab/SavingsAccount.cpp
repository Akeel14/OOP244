#include <iostream>
#include "SavingsAccount.h"

namespace sict {
    SavingsAccount::SavingsAccount(double initBalance, double interestRate) : Account(initBalance) {
        (interestRate > 0) ? m_Interest = interestRate : m_Interest = 0.0;
    }

    void SavingsAccount::monthEnd() {
        double interest = (balance() * m_Interest);
        credit(interest);
    }

    void SavingsAccount::display(std::ostream& os) const {
        os << "Account Type: Savings" << std::endl;
		os.precision(2);
		os << "Balance: $" << balance() << std::endl;
		os << "Interest Rate (%): " << m_Interest << std::endl;
    }
    
}

