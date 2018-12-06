/*
 * main.cpp
 *
 *  Created on: Dec 29, 2016
 *      Author: vinhhtq
 */

#include <iostream>
using namespace std;


class Base1 {
public:
	Base1() { cout << "_base1" ;}
	~Base1() {}
	virtual const char* run1() = 0;
};

class Base2 {
public:
	Base2() { cout << "_base2" ;}
	~Base2() {}
	virtual const char* run2() = 0;
};

class AA:
		public Base1,
		public Base2
{
public:
	AA(){ cout << "_AA" ;}
	~AA() {}

	const char* run1() { return "run1"; };
	const char* run2() { return "run2"; };
};

void func(Base1* ptr1, Base2* ptr2){
	cout << endl << ptr1->run1();
	cout << endl << ptr2->run2();
}

int main(int argc, char** argv){

	AA a;

	func(&a, &a);

	return 0;
}

