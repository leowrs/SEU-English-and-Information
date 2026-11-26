#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <ctime>

using namespace std;
const int a = -100, b =100;

void main()
{ 
	srand((unsigned)time( NULL ));
	int x,i;
	for(i=0; i<10;i++)
	{
		x = a+rand()%(b-a);
		cout<<setw(5)<<x;
	}
	cout<<endl;
	char ch;
	for(i=0;i<10;i++)
	{
		if(rand()%2==0)
		{
			ch = 'A'+ rand()%26;
			cout<<ch;
		}
		else
		{
			ch = 'a'+ rand()%26;
			cout<<ch;
		}
	}
	cout<<endl;

	for(i=0;i<10;i++)
	{
		int t = rand()%52;
		if( t<26) 
			ch = 'A' + t ;
		else
			ch = 'a' + t - 26;
			cout<<ch;
	}
	cout<<endl;
}