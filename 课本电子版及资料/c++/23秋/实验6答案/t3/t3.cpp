#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

int main()
{
	int a, b, c;  //a,b,c分别代表勾股数
	ofstream ofile;
	ofile.open("myfile.txt");
	ofile << "勾股数：" << endl;

	for (a = 1; a <= 50; a++)
		for (b = a + 1; b <= 50; b++)  //要求 a<b
			for (c = b + 1; c <= 50; c++)
				if (a * a + b * b == c * c)
				{
					ofile << a << '\t' << b << '\t' << c << endl;
				}
	ofile << endl;
	cout << endl;
	ofile.close();
	return 0;
}