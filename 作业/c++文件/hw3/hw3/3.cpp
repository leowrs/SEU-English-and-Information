// Original Author: GitHub @leowrs (https://github.com/leowrs)
#include<fstream>
#include<iomanip>
using namespace std;
int main()
{
	int a, b, c, k;
	ofstream ofile;
	ofile.open("myfile.txt");
	ofile << "¹´¹ÉÊý£º" << endl;
	for (a = 1; a <= 50; a++)
		for (b = a + 1; b <= 50; b++)
			for (c = b + 1; c <= 50; c++)
				if (c * c == a * a + b * b)
				{
					ofile << a << "\t" << b << "\t" << c << endl;
					break;
				}
	ofile.close();
	system("pause");
	return 0;
}