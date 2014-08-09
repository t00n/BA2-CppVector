#include <iostream>
#include <cstdlib>
#include <cassert>
#include "Vector.hpp"
using namespace std;

void constructors()
{
	Vector<int, false> vectorInt1(10);
	vectorInt1[0] = 1;
	vectorInt1[5] = 6;
	assert(vectorInt1.len() == 10);
	assert(vectorInt1[0] == 1);
	assert(vectorInt1[5] == 6);
	// int, false -> int, true
	Vector<int, true> vectorInt2(vectorInt1);
	assert(vectorInt2.len() == 10);
	assert(vectorInt2[0] == 1);
	assert(vectorInt2[5] == 6);
	vectorInt2[0] = 5;
	// int, true -> int, false
	vectorInt1 = vectorInt2;
	assert(vectorInt1[0] == 5);
	Vector<int, false> vectorInt3(vectorInt2);
	assert(vectorInt3.len() == 10);
	assert(vectorInt3[0] == 5);
	assert(vectorInt3[5] == 6);
	// int, false -> int, true
	Vector<int, true> vectorInt4(10);
	vectorInt4 = vectorInt3;
	assert(vectorInt4[0] == 5);
	assert(vectorInt4[5] == 6);
	
	Vector<int*, false> vectorInt5(10);
	*(vectorInt5[0]) = 1;
	*(vectorInt5[1]) = 2;
	assert(*(vectorInt5[0]) == 1);
	assert(*(vectorInt5[1]) == 2);
	// int, true -> int*, false
	Vector<int*, false> vectorInt6(vectorInt4);
	assert(*(vectorInt6[0]) == 5);
	assert(*(vectorInt6[5]) == 6);
	// int*, false -> int, false
	Vector<int, false> vectorInt7(vectorInt6);
	assert(vectorInt7[0] == 5);
	assert(vectorInt7[5] == 6);
	// int, false -> int*, false
	Vector<int*, false> vectorInt8(vectorInt7);
	assert(*(vectorInt8[0]) == 5);
	assert(*(vectorInt8[5]) == 6);
	// int*, false -> int, true
	Vector<int, true> vectorInt9(vectorInt8);
	assert(vectorInt9[0] == 5);
	assert(vectorInt9[5] == 6);
}

void conversions()
{
	Vector<int, false> vectorInt(10);
	vectorInt[0] = 90;
	Vector<char, false> vectorChar(vectorInt);
	assert(vectorChar[0] == 90);
	cout << vectorChar << endl;
	// vectorChar = vectorInt;
}

int main()
{
	constructors();
	conversions();
	return EXIT_SUCCESS;
}