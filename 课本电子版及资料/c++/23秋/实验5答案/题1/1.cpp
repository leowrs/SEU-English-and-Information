#include <iostream>
#include <iomanip>
using namespace std;
void main()
{
	int i=1, n=0;
	while(i<=2000)
	{
		if(i%3==2 && i%5==3 && i%7==2)
		{
			cout<<setw(8)<<i; 
			n++;
			if(n%5==0)
			cout<<endl;
		}
		i++;
	}
	cout<<endl;

}