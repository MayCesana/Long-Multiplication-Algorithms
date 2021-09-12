#include "itemType.h"
#include "num.h"

namespace stack
{
	ItemType::ItemType(num& n1, num& n2, int n, num& res) : num1(&n1), num2(&n2), n(n), line(START), res(&res), 
	a(nullptr), b(nullptr), c(nullptr), d(nullptr), ac(nullptr), bd(nullptr), aADDb(nullptr),
	cADDd(nullptr), plusSize(nullptr) {}
	
	ItemType::ItemType(const ItemType& item) : num1(item.num1), num2(item.num2), n(item.n), line(item.line),
		res(item.res), a(nullptr), b(nullptr), c(nullptr), d(nullptr), ac(nullptr), bd(nullptr), aADDb(nullptr),
		cADDd(nullptr), plusSize(nullptr) {}

	void ItemType::makeABCD()
	{
		num* aPtr = new num(*num1);
		num* bPtr = new num(*num1);
		num* cPtr = new num(*num2);
		num* dPtr = new num(*num2);
		
		(*aPtr).halfNum(0, n / 2);
		(*bPtr).halfNum(n / 2, (*bPtr).getLogSize());
		(*cPtr).halfNum(0, n / 2);
		(*dPtr).halfNum(n / 2, (*dPtr).getLogSize());

		num* acPtr = new num();
		num* bdPtr = new num();
		num* aADDbPtr = new num();
		num* cADDdPtr = new num();
		num* plusSizePtr = new num();
		(*aADDbPtr).initNumToZero((*aPtr).getLogSize() + 1);
		(*cADDdPtr).initNumToZero((*cPtr).getLogSize() + 1);
		(*aADDbPtr).sum3numbers(*aPtr, *bPtr);
		(*cADDdPtr).sum3numbers(*cPtr, *dPtr);

		(*aADDbPtr).update_numbers(*cADDdPtr);

		a = aPtr;
		b = bPtr;
		c = cPtr;
		d = dPtr;
		cADDd = cADDdPtr;
		aADDb = aADDbPtr;
		ac = acPtr;
		bd = bdPtr;
		plusSize = plusSizePtr;
	}
	
	void ItemType::operator=(const ItemType& other)
	{
		num1=other.num1;
		num2 = other.num2; n = other.n;
		line = other.line;
		res = other.res;
		a = other.a; b = other.b; c = other.c; d = other.d; aADDb = other.aADDb; cADDd = other.cADDd;
		plusSize = other.plusSize; bd = other.bd; ac = other.ac;
	}

	void ItemType::deleteLeadZero()
	{
		(*ac).delete_lead_zero();
		(*bd).delete_lead_zero();
		(*plusSize).delete_lead_zero();
	} 

	void ItemType::makeMid()
	{
		num* mid = new num();
		mid->initNumToZero((*plusSize).getLogSize()*2);

		mid->sum2numbers(*plusSize);
		mid->sub(*ac);
		mid->sub(*bd);
		plusSize = mid;
		(*plusSize).add_zero(n / 2);
		(*plusSize).delete_lead_zero();
		(*ac).add_zero(n);
	}

	ItemType::~ItemType()
	{
		delete num1;
		delete num2;
		delete res; 
		delete aADDb; delete cADDd;
		delete a; delete b; delete c; delete d; delete ac; delete bd; delete plusSize;
	}
}
