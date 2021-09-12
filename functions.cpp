#include "functions.h"
#include "num.h"
#include "stack.h"

int* cinArr(int n)
{
	int i;
	char c;
	int* arr = new int[n];
	
	for (i = 0; i < n; i++)
	{
		c = getchar();
		if (c > '9' || c < '0')
		{
			return nullptr;
		}
		else
			arr[i] = static_cast<short int>(c) - 48;
	}
	c = getchar();
	if (c == ' ' || c == '\n')
		return arr;
	else
		return nullptr; //the number is longer then n
}

int cinN()
{
	bool lead_zero = true;
	char num[MAX_SIZE];
	cin.getline(num, MAX_SIZE);
	int res, i = 0;
	if (num[0] == ' ')
		i++;
	while (num[i] != '\0')
	{
		if (num[i] == '0' && lead_zero) //first show of zero
		{
			if (num[i + 1] != '\0')
			{
				return -1; //wrong input
			} //else - the number is zero
		} 
		else if (num[i] <= '9' && num[i] >= '0') 
		{
			lead_zero = false;
		}
		else
			return -1; //wrong input
		i++;
	}
	res = atoi(num);
	return res;
}
void longMul(const num& num1, const num& num2, num& res)
{
	res.initNumToZero(num1.getLogSize() + num2.getLogSize());
	for (int i = num2.getLogSize() - 1; i >= 0; --i)
	{
		num temp(num1);
		temp.mulDigit(num2.getDigit(i));
		temp.add_zero(num2.getLogSize() - 1 - i);
		res.sum2numbers(temp);
	}
}
void karatsuba(num& num1, num& num2, int n, num& res)
{
	if (n == 1)
	{
		res.initNumToZero(n * 2);
		res.sum2numbers(num1);
		res.mulDigit(num2.getDigit(0));
	}
	else
	{
		if (n % 2 == 1) //if the number is odd
		{
			num1.reSize();
			num2.reSize();
			n += 1;
		}
		res.initNumToZero(n * 2);

		num a(num1), b(num1), c(num2), d(num2);

		a.halfNum(0, n / 2);
		b.halfNum(n / 2, b.getLogSize());
		c.halfNum(0, n / 2);
		d.halfNum(n / 2, d.getLogSize());

		num ac, bd, aADDb, cADDd, preMid;
		aADDb.initNumToZero(a.getLogSize() + 1);
		cADDd.initNumToZero(c.getLogSize() + 1);
		aADDb.sum3numbers(a, b);
		cADDd.sum3numbers(c, d);

		//if the numbers have same amount of lead zeros - remove those zeros
		aADDb.update_numbers(cADDd);

		karatsuba(a, c, n / 2, ac);
		karatsuba(b, d, n / 2, bd);
		karatsuba(aADDb, cADDd, aADDb.getLogSize(), preMid);

		ac.delete_lead_zero();
		bd.delete_lead_zero();
		preMid.delete_lead_zero();

		num mid;
		mid.initNumToZero(preMid.getLogSize()*2);

		mid.sum2numbers(preMid);
		mid.sub(ac);
		mid.sub(bd);
		mid.add_zero(n / 2);
		mid.delete_lead_zero();
		ac.add_zero(n);

		res.sum2numbers(ac);
		res.sum2numbers(mid);
		res.sum2numbers(bd);
	}
}

using namespace stack;
num& IterKaratsuba(num& num1, num& num2, int n, num& res)
{
	Stack s;
	ItemType* curr = new ItemType(num1, num2, n, res);
	num* returnValue = &(curr->getRes());
	ItemType* next;
	s.push(*curr);
	while (!s.isEmpty())
	{
		curr = &(s.pop());
	
		if (curr->getLine() == START)
		{
			if (curr->getN() == 1) //stop condition
			{
				curr->getRes().initNumToZero(curr->getN() * 2);
				curr->getRes().sum2numbers(curr->getN1());
				curr->getRes().mulDigit(curr->getN2().getDigit(0));
				returnValue = &(curr->getRes());
			}
			else
			{
				if (curr->getN() % 2 == 1) //if the number is odd
				{
					curr->getN1().reSize();
					curr->getN2().reSize();
					curr->setN(curr->getN() + 1);
				}
				curr->getRes().initNumToZero(curr->getN() * 2);

				curr->setLine(AFTER_FIRST);
				curr->makeABCD();
				s.push(*curr);
				next = new ItemType(*(curr->a), *(curr->c), curr->getN()/2, *(curr->ac));
				s.push(*next);
			}
		}
		else if (curr->getLine() == AFTER_FIRST)
		{
			curr->setLine(AFTER_SECOND);
			curr->ac = returnValue;
			s.push(*curr);
			next = new ItemType(*(curr->b), *(curr->d), curr->getN() / 2, *(curr->bd));
			s.push(*next);
		}

		else if ((*curr).getLine() == AFTER_SECOND)
		{
			curr->setLine(AFTER_THIRD);
			curr->bd = returnValue;
			s.push(*curr);
			next = new ItemType(*(curr->aADDb), *(curr->cADDd), (*curr).aADDb->getLogSize(), *(curr->plusSize));
			s.push(*next);
		}

		else if (curr->getLine() == AFTER_THIRD)
		{
			curr->plusSize = returnValue;
			curr->deleteLeadZero();
			curr->makeMid();
			curr->getRes().sum2numbers((*curr->ac));
			curr->getRes().sum2numbers((*curr->plusSize));
			curr->getRes().sum2numbers((*curr->bd));
			returnValue = &(curr->getRes());
		}
	}
	return *returnValue;
}