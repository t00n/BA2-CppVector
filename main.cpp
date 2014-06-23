#include <iostream>
#include <cstdlib>
#include "Vector.hpp"
using namespace std;



int main()
{
	Vector<int, false> vectorInt;
	vectorInt[0] = 5;
	cout << vectorInt.len() << endl;
	cout << vectorInt;
	Vector<char, false> vectorChar;
	vectorChar[0] = 'c';
	cin >> vectorChar;
	cout << vectorChar.len() << endl;
	cout << vectorChar;
	return EXIT_SUCCESS;
}