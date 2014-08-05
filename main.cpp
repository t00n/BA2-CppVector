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
	Vector<char, true> vectorChar(10);
	vectorChar[0] = 'c';
	cout << vectorChar.len() << endl;
	cout << vectorChar;
	return EXIT_SUCCESS;
}