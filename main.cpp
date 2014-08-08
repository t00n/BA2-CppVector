#include <iostream>
#include <cstdlib>
#include "Vector.hpp"
using namespace std;

int main()
{
	Vector<int, true> vectorInt(10);
	vectorInt[0] = 5;
	cout << vectorInt.len() << endl;
	cout << vectorInt;
	Vector<int, false> vectorChar(10);
	vectorChar = vectorInt;
	cout << vectorChar;
	return EXIT_SUCCESS;
}