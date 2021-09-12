#pragma once
#include<iostream>
using namespace std;

class num {
private:

	int* arr;
	int phySize;
	int logSize;

public:
	num() : arr(nullptr), phySize(0), logSize(0) {}

	num(int size, int* num);
	num(const num& another);
	~num();

	int* getArr() { return arr; }
	int getDigit(int index) const { return arr[index]; }
	int getLogSize() const { return logSize; }
	int getPhySize() const { return phySize; }

	void initNumToZero(int size);
	void halfNum(int from, int to); //divides the number in the middle

	void insertDigit(int digit, int index);
	void mulDigit(int digit);
	void sum2numbers(const num& other);
	void sum3numbers(const num& other1, const num& other2);
	void sub(const num& other);

	void add_zero(int amount_of_zero);
	void delete_lead_zero(int amount);
	void delete_lead_zero();
	void reSize(); //converts the number to even length
	void update_numbers(num& num2); //checks if the numbers have the same amount of lead zeros and delete those zeros

	void operator=(num& other);
	void printNumber();
};
