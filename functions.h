#pragma once
#include "num.h"

const int MAX_SIZE = 500;

int cinN();
int* cinArr(int n);
bool checkInput(int n);
void longMul(const num& num1, const num& num2, num& res);
void karatsuba(num& num1, num& num2, int n, num& res);
num& IterKaratsuba(num& num1, num& num2, int n, num& res);
