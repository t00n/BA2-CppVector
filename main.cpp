#include <iostream>
#include <cstdlib>
#include <cassert>
#include "Vector.hpp"
using namespace std;

void constructors()
{
	// int, false
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
	Vector<int, false> vectorInt3(vectorInt2);
	assert(vectorInt3.len() == 10);
	assert(vectorInt3[0] == 5);
	assert(vectorInt3[5] == 6);
	// int*, false
	Vector<int*, false> vectorInt5(10);
	*(vectorInt5[0]) = 1;
	*(vectorInt5[1]) = 2;
	assert(*(vectorInt5[0]) == 1);
	assert(*(vectorInt5[1]) == 2);
	// int, true -> int*, false
	Vector<int*, false> vectorInt6(vectorInt3);
	assert(*(vectorInt6[0]) == 5);
	assert(*(vectorInt6[5]) == 6);
	assert(vectorInt6[0] != &(vectorInt3[0]));
	assert(vectorInt6[5] != &(vectorInt3[5]));
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
	assert(&(vectorInt9[0]) != vectorInt8[0]);
	assert(&(vectorInt9[5]) != vectorInt8[5]);
	// int*, false -> int*, false
	Vector<int*, false> vectorInt10(vectorInt8);
	assert(*(vectorInt10[0]) == 5);
	assert(*(vectorInt10[5]) == 6);
	assert(vectorInt10[0] != vectorInt8[0]);
	assert(vectorInt10[5] != vectorInt8[5]);
	// int, true -> int, true
	Vector<int, true> vectorInt11(vectorInt9);
	assert(vectorInt11[0] == 5);
	assert(vectorInt11[5] == 6);
	assert(&(vectorInt11[0]) != &(vectorInt9[0]));
	assert(&(vectorInt11[5]) != &(vectorInt9[5]));
}

void operators()
{

}

void conversions()
{
	Vector<char, false> vectorInt(10);
	vectorInt[0] = 90;
	vectorInt[5] = 65;
	Vector<int, false> vectorChar(vectorInt);
	assert(vectorChar[0] == 90);
	assert(vectorChar[0] == 'Z');
	assert(vectorChar[5] == 'A');
	Vector<int, true> vectorCharTrue(vectorInt);
	assert(vectorCharTrue[0] == 'Z');
	assert(vectorCharTrue[5] == 'A');
	Vector<int*, false> vectorCharStar(vectorInt);
	assert(*(vectorCharStar[0]) == 'Z');
	assert(*(vectorCharStar[5]) == 'A');

	Vector<char*, false> vectorIntStar(10);
	*(vectorIntStar[0]) = 90;
	*(vectorIntStar[5]) = 65;
	Vector<int*, false> vectorCharStar2(vectorIntStar);
	assert(*(vectorCharStar2[0]) == 'Z');
	assert(*(vectorCharStar2[5]) == 'A');
	Vector<int, true> vectorCharTrue2(vectorIntStar);
	assert(vectorCharTrue[0] == 'Z');
	assert(vectorCharTrue[5] == 'A');
	Vector<int, false> vectorChar2(vectorIntStar);
	assert(vectorChar2[0] == 'Z');
	assert(vectorChar2[5] == 'A');

	Vector<char, true> vectorIntTrue(10);
	vectorIntTrue[0] = 90;
	vectorIntTrue[5] = 65;
	Vector<int*, false> vectorCharStar3(vectorIntTrue);
	assert(*(vectorCharStar2[0]) == 'Z');
	assert(*(vectorCharStar2[5]) == 'A');
	Vector<int, true> vectorCharTrue3(vectorIntTrue);
	assert(vectorCharTrue[0] == 'Z');
	assert(vectorCharTrue[5] == 'A');
	Vector<int, false> vectorChar3(vectorIntTrue);
	assert(vectorChar2[0] == 'Z');
	assert(vectorChar2[5] == 'A');
}

void vStatic()
{
	Vector<int, false> vector(10);
	vector[0] = 5;
	vector[5] = 6;
	VectorStatic<int, false, 10> vectorStatic1(vector);
	cout << vectorStatic1 << endl;
}

int main()
{
	constructors(); // Ok
	operators();
	conversions(); // Ok
	vStatic();
	return EXIT_SUCCESS;
}