#include <iostream>
using namespace std;
#include <ctime>
// 포인터는 주소값을 저장하는 자료형이다.
// 이름이 포인터인 이유는 변수가 저장된 메모리를 가리키기(Pointing) 때문

int mainpointer()
{
	int x = 10;
	int* x_ptr;
	x_ptr = &x;

	cout << "x값: " << x << endl;
	cout << "x의 주소값: " << &x << endl;
	cout << "x_ptr의 값: " << x_ptr << endl;
	cout << "x_ptr이 가리키는 값: " << *x_ptr << endl;

	int arr[3] = { 1,2,3 };
	int* x_ptr2;
	x_ptr2 = &arr[0];
	x_ptr2++;

	cout << *x_ptr2 << endl;

	int xx = 10;
	int* x_ptr3 = &xx;
	int** x_ptr_ptr3 = &x_ptr3;

	cout << xx << endl;
	cout << *x_ptr3 << endl;
	cout << **x_ptr_ptr3 << endl;

	return 0;

	
}