#include <iostream>
using namespace std;

template<typename T>
T mymax(T p[2][3], int a, int b)
{
	T max1 = p[0][0];
	int i, j;
	for (i = 0; i < a; i++)
		for (j = 0; j < b; j++)
			if (max1 < p[i][j])
				max1 = p[i][j];
	return max1;
}
void main( )
{
	int im[2][3] = { 1,2,3,100,2,3 };
	double dm[2][3] = { 2,3,5,29.0,3 };
	cout << "二维矩阵im中的最大数是：" << mymax(im, 2, 3) << endl;
	cout << "二维矩阵dm中的最大数是：" << mymax(dm, 2, 3) << endl;
	system("pause");
}

 