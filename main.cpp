#include <iostream>
#include <cstdlib>
#include <cassert>
#include <string>
#include "Vector.hpp"
#include "VectorString.hpp"
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
	assert(intStar1[5] == nullptr);
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
	// int*, false -> int*, true
	Vector<int*, true> intStar5(intStar4);
	assert(*(intStar5[0]) == 5);
	assert(*(intStar5[5]) == 6);
	assert(intStar5[0] != intStar4[0]);
	assert(intStar5[5] != intStar4[5]);
}

void operators()
{
	// int, false -> int, true
	Vector<int, false> intFalse1(10);
	intFalse1[0] = 5;
	intFalse1[5] = 6;
	Vector<int, true> intTrue1(10);
	intTrue1 = intFalse1;
	assert(intTrue1[0] == 5);
	assert(intTrue1[5] == 6);
	assert(&(intTrue1[1]) != nullptr);
	// int, true -> int, false
	intTrue1[1] = 1;
	intTrue1[2] = 2;
	intFalse1 = intTrue1;
	assert(intFalse1[1] == 1);
	assert(intFalse1[2] == 2);
	// int, false -> int*, false
	Vector<int*, false> intStar1(10);
	intStar1 = intFalse1;
	assert(*(intStar1[0]) == 5);
	assert(*(intStar1[1]) == 1);
	assert(*(intStar1[2]) == 2);
	assert(*(intStar1[5]) == 6);
	// int*, false -> int, false
	*(intStar1[1]) = 10;
	intFalse1 = intStar1;
	assert(intFalse1[1] == 10);
	// int, true -> int*,false
	Vector<int*, false> intStar2(10);
	intStar2 = intTrue1;
	assert(*(intStar2[0]) == 5);
	assert(*(intStar2[1]) == 1);
	assert(*(intStar2[2]) == 2);
	assert(*(intStar2[5]) == 6);
	assert(intStar2[0] != &(intTrue1[0]));
	assert(intStar2[1] != &(intTrue1[1]));
	assert(intStar2[2] != &(intTrue1[2]));
	assert(intStar2[5] != &(intTrue1[5]));
	// int*, false -> int, true
	Vector<int, true> intTrue2(10);
	intTrue2 = intStar2;
	assert(intTrue2[0] == 5);
	assert(intTrue2[1] == 1);
	assert(intTrue2[2] == 2);
	assert(intTrue2[5] == 6);
	assert(intStar2[0] != &(intTrue2[0]));
	assert(intStar2[1] != &(intTrue2[1]));
	assert(intStar2[2] != &(intTrue2[2]));
	assert(intStar2[5] != &(intTrue2[5]));
	// int, true -> int, true
	Vector<int, true> intTrue3(10);
	intTrue3 = intTrue2;
	assert(intTrue3[0] == 5);
	assert(intTrue3[1] == 1);
	assert(intTrue3[2] == 2);
	assert(intTrue3[5] == 6);
	assert(&(intTrue3[0]) != &(intTrue2[0]));
	assert(&(intTrue3[1]) != &(intTrue2[1]));
	assert(&(intTrue3[2]) != &(intTrue2[2]));
	assert(&(intTrue3[5]) != &(intTrue2[5]));
	// int*, false -> int*, false
	Vector<int*, false> intStar3(10);
	delete intStar2[3];
	intStar2[3] = nullptr;
	intStar3 = intStar2;
	assert(*(intStar3[0]) == 5);
	assert(*(intStar3[1]) == 1);
	assert(*(intStar3[2]) == 2);
	assert(*(intStar3[5]) == 6);
	assert(intStar2[0] != intStar3[0]);
	assert(intStar2[1] != intStar3[1]);
	assert(intStar2[2] != intStar3[2]);
	assert(intStar2[5] != intStar3[5]);
	assert(intStar3[3] == nullptr);
	// char, true -> int, true
	Vector<char, true> charTrue1(10);
	charTrue1[3] = 65;
	charTrue1[4] = 90;
	intTrue2 = charTrue1;
	assert(intTrue2[3] == 65);
	assert(intTrue2[4] == 90);
	assert(&(intTrue2[3]) != (int*)&(charTrue1[3]));
	assert(&(intTrue2[4]) != (int*)&(charTrue1[4]));
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

void sizeDifference()
{
	Vector<int, false> vector1(10);
	vector1[0] = 5;
	Vector<int, true> vector2(9);
	vector2 = vector1;
	assert(vector2[0] != 5);
	Vector<int*, true> vector3(9);
	vector2[1] = 6;
	vector3 = vector2 = vector1;
	assert(vector2[0] != 5);
	assert(*(vector3[0]) != 5);
	assert(vector2[1] == 6);
	assert(*(vector3[1]) == 6);
}

void strings()
{
	Vector<char, false> charFalse(7);
	charFalse[0] = 'W';
	charFalse[1] = 'o';
	charFalse[2] = 'r';
	charFalse[3] = 'k';
	charFalse[4] = 'i';
	charFalse[5] = 'n';
	charFalse[6] = 'g';
	cout << charFalse << endl;
	Vector<char*, false> charStar(10);
	charStar[0] = new char[5];
	charStar[0][0] = 'W';
	charStar[0][1] = 'o';
	charStar[0][2] = 'r';
	charStar[0][3] = 'k';
	charStar[0][4] = '\0';
	charStar[1] = new char[5];
	charStar[1][0] = 'i';
	charStar[1][1] = 'n';
	charStar[1][2] = 'g';
	charStar[1][3] = '!';
	charStar[1][4] = '\0';
	cout << charStar << endl;
	Vector<string, false> stringFalse(10);
	stringFalse[0] = "Wor";
	stringFalse[1] = "ki";
	stringFalse[2] = "ng!";
	cout << stringFalse << endl;
}

int main()
{
	constructors(); // Ok
	operators(); // Ok
	conversions(); // Ok
	vStatic(); // Ok
	sizeDifference(); // Ok
	strings(); // Ok
	return EXIT_SUCCESS;
}