#pragma once
#include "num.h"
#include <iostream>

namespace stack
{
	#define START 0
	#define AFTER_FIRST 1
	#define AFTER_SECOND 2 
	#define AFTER_THIRD 3

	class ItemType
	{
	private:
		num* num1, *num2;
		num* res;
		int line;
		int n; //num1, num2 number of digits
	
	public:
		num* a, *b, *c, *d, *aADDb, *cADDd;
		num* plusSize, *ac, *bd;

		ItemType(num& n1, num& n2, int n, num& res);
		ItemType(const ItemType& item);
		~ItemType();

		num& getN1() const { return *num1; }
		num& getN2() const { return *num2; }
		num& getRes() const { return *res; }
		int getN() const { return n; }
		int getLine() const { return line; }

		void setN(int newN) { n = newN; }
		void setLine(int Line) { line = Line; }

		void makeABCD(); //creates the local arrays - a,b,c,d, a+b, c+d
		void deleteLeadZero();
		void makeMid(); //calculates the expression (a+b)(b+d)-ac-bd
		void operator=(const ItemType& other);
	};
}


