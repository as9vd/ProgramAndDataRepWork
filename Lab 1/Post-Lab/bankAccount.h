// bankAccount.h
// August 31st, 2021
// Asadbek Shamsiev, as9vd@virginia.edu

#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

// using namespace std;

class bankAccount {
	public:
		bankAccount();
		bankAccount(double amount);
		~bankAccount();
		double withdraw(double amount);
		double deposit(double amount);

		double getBalance() const;
	private:
		double balance;
};

#endif