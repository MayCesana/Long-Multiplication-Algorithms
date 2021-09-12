#include "num.h"

num::num(int size, int* num) : arr(new int[size]), phySize(size), logSize(0) 
{
	for (int i = 0; i < size; ++i)
	{
		arr[i] = num[i];
	}
	logSize = size;
}
num::num(const num& another) : logSize(another.getLogSize()), phySize(another.getPhySize())
{
	arr = new int[phySize];
	for (int i = 0; i < logSize; i++)
	{
		arr[i] = another.getDigit(i);
	}
}
num::~num()
{
	delete[]arr;
}

void num::operator=(num& other)
{
	for (int i = 0; i < other.logSize; ++i)
	{
		arr[i] = other.arr[i];
	}
	delete[] other.arr;
	phySize = other.phySize;
	logSize = other.logSize;
}

void num::initNumToZero(int size)
{
	arr = new int[size];
	phySize = size;
	for (int i = 0; i < phySize; i++)
	{
		arr[i] = 0;
		logSize++;
	}
}
void num::insertDigit(int digit, int index)
{
	arr[index] = digit;
}
void num::mulDigit(int dig)
{
	int newSize = logSize + 1;
	int* tempArr = new int[newSize];
	tempArr[0] = 0;
	for (int i = 0; i < logSize; i++)
		tempArr[i+1] = arr[i];
	delete[] arr;
	logSize = phySize = newSize;
	arr = new int[newSize];
	int c = 0, s = 0, temp;
	int i;
	for (i = logSize - 1; i > 0; i--)
	{
		temp = tempArr[i] * dig + c;
		s = temp % 10;
		c = temp / 10;
		arr[i] = s;
	}
	arr[i] = c;
	delete[] tempArr;
}
void num::add_zero(int zeroNum)
{
	int newSize = logSize + zeroNum;
	int* temp = new int[logSize];

	for (int i = 0; i < logSize; ++i)
	{
		temp[i] = arr[i];
	}
	delete[] arr;
	arr = new int[newSize];
	for (int i = 0; i < logSize; ++i)
	{
		arr[i] = temp[i];
	}
	for (int i = logSize; i < newSize; ++i)
	{
		arr[i] = 0;
	}
	delete[] temp;
	logSize = phySize = newSize;
}
void num::delete_lead_zero(int amount)
{
	if (amount == logSize)
	{
		delete[]arr;
		arr = new int[1];
		logSize = phySize = 1;
		arr[0] = 0;
	}
	else
	{
		int* temp = new int[logSize];
		for (int i = 0; i < logSize; i++)
			temp[i] = arr[i];
		delete[]arr;
		arr = new int[logSize - amount];
		for (int i = 0; i < logSize - amount; i++)
			arr[i] = temp[i + amount];

		logSize = phySize = logSize - amount;
		delete[]temp;
	}

}
void num::delete_lead_zero()
{
	int countZero = 0;
	bool lead_zero = true;
	for (int i = 0; i < logSize && lead_zero; i++)
	{
		if (arr[i] == 0)
		{
			if (lead_zero)
				countZero++;
		}
		else
			lead_zero = false;
	}
	delete_lead_zero(countZero);
}
void num::sum2numbers(const num& other)
{
	int location = phySize - 1, res, c = 0;
	for (int i = other.getLogSize() - 1; i >= 0; i--)
	{
		res = (other.getDigit(i) + arr[location] + c) % 10;
		c = (other.getDigit(i) + arr[location] + c) / 10;
		insertDigit(res, location);
		location--;
	}
	if (location >= 0)
		arr[location] += c;

}
void num::sum3numbers(const num& other1, const num& other2)
{
	sum2numbers(other1);
	sum2numbers(other2);

}
void num::sub(const num& other)
{
	int dig1, dig2, k, j;
	int dif = logSize - other.getLogSize();
	for (int i = logSize - 1; i >= dif; i--)
	{
		dig1 = arr[i];
		dig2 = other.getDigit(i - dif);

		if (dig1 < dig2)
		{
			k = i - 1;
			while (arr[k] == 0)
				k--;
			arr[k] -= 1;
			for (j = k + 1; j < i; j++)
				if (arr[j] == 0)
					arr[j] = 9;
			dig1 += 10;
		}
		arr[i] = dig1 - dig2;
	}
}
void num::halfNum(int from, int to)
{
	int* new_arr = new int[phySize / 2];
	int k = 0;
	for (int i = from; i < to; i++)
	{
		new_arr[k] = arr[i];
		k++;
	}
	delete[]arr;
	arr = new_arr;
	phySize = logSize = phySize / 2;
}
void num::reSize()
{
	int new_size = logSize + 1;
	int* temp = new int[logSize];
	for (int i = 0; i < logSize; i++)
		temp[i] = arr[i];
	delete[]arr;
	arr = new int[new_size];
	arr[0] = 0;
	for (int i = 1; i < new_size; i++)
		arr[i] = temp[i - 1];
	logSize = phySize = new_size;
}
void num::update_numbers(num& num2)
{
	int zeroNum = 0;
	bool lead_zero = true;
	for (int i = 0; i < this->getLogSize() && lead_zero; i++)
	{
		if (getDigit(i) == 0 && num2.getDigit(i) == 0)
		{
			if (lead_zero)
				zeroNum++;
		}
		else
		{
			lead_zero = false;
		}
	}
	if (zeroNum)
	{
		this->delete_lead_zero(zeroNum);
		num2.delete_lead_zero(zeroNum);
	}

}
void num::printNumber()
{
	bool flag = false; //tell us if we can print zero
	for (int i = 0; i < logSize; ++i)
	{
		if (arr[i] != 0)
		{
			cout << arr[i];
			flag = true;
		}
		else if (arr[i] == 0 && i == logSize - 1)
		{
			cout << arr[i];
		}
		else if (arr[i] == 0 && flag == true)
		{
			cout << arr[i];
		}
	}
	cout << endl;
}
