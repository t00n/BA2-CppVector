#include <iostream>
#include <cstdlib>
#include <cassert>
#include "Vector.hpp"
#include <vector>
using namespace std;

void constructors()
{
	// int, false
	Vector<int, false> intFalse1(10);
	intFalse1[0] = 1;
	intFalse1[5] = 6;
	assert(intFalse1.len() == 10);
	assert(intFalse1[0] == 1);
	assert(intFalse1[5] == 6);
	// int, false -> int, true
	Vector<int, true> intTrue1(intFalse1);
	assert(intTrue1.len() == 10);
	assert(intTrue1[0] == 1);
	assert(intTrue1[5] == 6);
	intTrue1[0] = 5;
	// int, true -> int, false
	Vector<int, false> intFalse2(intTrue1);
	assert(intFalse2.len() == 10);
	assert(intFalse2[0] == 5);
	assert(intFalse2[5] == 6);
	// int*, false
	Vector<int*, false> intStar1(10);
	intStar1[0] = new int(1);
	intStar1[1] = new int(2);
	assert(*(intStar1[0]) == 1);
	assert(*(intStar1[1]) == 2);
	// int, true -> int*, false
	Vector<int*, false> intStar2(intTrue1);
	assert(*(intStar2[0]) == 5);
	assert(*(intStar2[5]) == 6);
	assert(intStar2[0] != &(intFalse2[0]));
	assert(intStar2[5] != &(intFalse2[5]));
	// int*, false -> int, false
	Vector<int, false> intFalse3(intStar2);
	assert(intFalse3[0] == 5);
	assert(intFalse3[5] == 6);
	// int, false -> int*, false
	Vector<int*, false> intStar3(intFalse3);
	assert(*(intStar3[0]) == 5);
	assert(*(intStar3[5]) == 6);
	// int*, false -> int, true
	Vector<int, true> intTrue2(intStar3);
	assert(intTrue2[0] == 5);
	assert(intTrue2[5] == 6);
	assert(&(intTrue2[0]) != intStar3[0]);
	assert(&(intTrue2[5]) != intStar3[5]);
	// int*, false -> int*, false
	Vector<int*, false> intStar4(intStar3);
	assert(*(intStar4[0]) == 5);
	assert(*(intStar4[5]) == 6);
	assert(intStar4[0] != intStar3[0]);
	assert(intStar4[5] != intStar3[5]);
	// int, true -> int, true
	Vector<int, true> intTrue3(intTrue2);
	assert(intTrue3[0] == 5);
	assert(intTrue3[5] == 6);
	assert(&(intTrue3[0]) != &(intTrue2[0]));
	assert(&(intTrue3[5]) != &(intTrue2[5]));
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
	vectorIntStar[0] = new char('Z');
	vectorIntStar[5] = new char('A');
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
	vectorStatic1[1] = 11;
	assert(vectorStatic1[0] == 5);
	assert(vectorStatic1[5] == 6);
	assert(vectorStatic1[1] == 11);
}

int main()
{
	constructors(); // Ok
	operators();
	conversions(); // Ok
	vStatic(); // Ok
	return EXIT_SUCCESS;
}