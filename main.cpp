#include <iostream>
#include <stdio.h>
#include <fstream>
#include "num.h"
#include "functions.h"
#include <ctime>
#include <chrono>
#include <iomanip>

using namespace std;

void runTimelongMul(const num& num1, const num& num2, num& res)
{
	auto start = chrono::high_resolution_clock::now();

	ios_base::sync_with_stdio(false);
	longMul(num1, num2, res);
	auto end = chrono::high_resolution_clock::now();
	double time_taken =
		chrono::duration_cast<chrono::nanoseconds>(end - start).count();
	time_taken *= 1e-9;
	ofstream myfile("Measure.txt"); 
	myfile << "Time taken by function <longMul> is : " << fixed
		<< time_taken << setprecision(9);
	myfile << " sec" << endl;
	myfile.close();
}

void runTimekaratsuba(num& num1, num& num2, int n, num& res)
{
	auto start = chrono::high_resolution_clock::now();

	ios_base::sync_with_stdio(false);
	karatsuba(num1, num2, n, res);
	auto end = chrono::high_resolution_clock::now();
	double time_taken =
		chrono::duration_cast<chrono::nanoseconds>(end - start).count();
	time_taken *= 1e-9;
	ofstream myfile("C:\TEMP\Measure.txt", ios::app);
	myfile << "Time taken by function <karatsuba> is : " << fixed
		<< time_taken << setprecision(9);
	myfile << " sec" << endl;
	myfile.close();
}

num& runTimeIterKaratsuba(num& num1, num& num2, int n, num& res)
{
	auto start = chrono::high_resolution_clock::now();

	ios_base::sync_with_stdio(false);
	num& temp = IterKaratsuba(num1, num2, n, res);
	auto end = chrono::high_resolution_clock::now();

	double time_taken =
		chrono::duration_cast<chrono::nanoseconds>(end - start).count();
	time_taken *= 1e-9;
	ofstream myfile("C:\TEMP\Measure.txt", ios::app); 
	myfile << "Time taken by function <IterKaratsuba> is : " << fixed
		<< time_taken << setprecision(9);
	myfile << " sec" << endl;
	myfile.close();

	return temp;
}

bool checkInput(int n)
{
	bool res = false;
	if (n == -1)
	{
		cout << "wrong output" << endl;
	}
	else if (n == 0)
	{
		cout << "The length of the numbers is 0.." << endl;
	}
	else
		res = true;
		
	return res;
}

int main()
{
	int* num1, * num2, * res;

	int n = cinN();

	if (checkInput(n))
	{
		num1 = cinArr(n);
		num2 = cinArr(n);

		if (num1 == nullptr || num2 == nullptr)
		{
			cout << "wrong output" << endl;
		}
		else
		{
			num number1(n, num1);
			num number2(n, num2);
			num number1cpy(n, num1);
			num number2cpy(n, num2);

			num res1;
			runTimelongMul(number1, number2, res1);
			cout << "Long multiplication: x * y = ";
			res1.printNumber();

			num res2;
			runTimekaratsuba(number1, number2, n, res2);
			cout << "Karatsuba (recursive): x * y = ";
			res2.printNumber();

			num res3Temp;
			num& res3 = runTimeIterKaratsuba(number1cpy, number2cpy, n, res3Temp);
			cout << "Karatsuba (iterative): x * y = ";
			res3.printNumber();
			
		}
	}
}