#include <iostream>
using namespace std;
#include <ctime>
// �����ʹ� �ּҰ��� �����ϴ� �ڷ����̴�.
// �̸��� �������� ������ ������ ����� �޸𸮸� ����Ű��(Pointing) ����

int mainpointer()
{
	int x = 10;
	int* x_ptr;
	x_ptr = &x;

	cout << "x��: " << x << endl;
	cout << "x�� �ּҰ�: " << &x << endl;
	cout << "x_ptr�� ��: " << x_ptr << endl;
	cout << "x_ptr�� ����Ű�� ��: " << *x_ptr << endl;

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