#include <iostream>
#include <cstdlib>
#include <cassert>
#include "Vector.hpp"
#include "DataVector.hpp"
using namespace std;

void testValueVector()
{
	DataVector<int> valueVector(10);
	valueVector[0] = 5;
	assert(valueVector[0] == 5);
	DataVector<int*> pointerVector(10);
	int * sept = new int(7);
	pointerVector[0] = sept;
	assert(*(pointerVector[0]) == 7);
	delete sept;
}

int main()
{
	testValueVector();
	Vector<int, true> vectorInt(10);
	vectorInt[0] = 5;
	cout << vectorInt.len() << endl;
	cout << vectorInt;
	Vector<int, false> vectorChar(vectorInt);
	cout << vectorChar;
	return EXIT_SUCCESS;
}