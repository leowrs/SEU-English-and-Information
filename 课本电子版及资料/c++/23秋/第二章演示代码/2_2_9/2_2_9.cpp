#include <iostream>
using namespace std;

int main()
{
	char score;

	cout<<"ÊäÈë×Ö·û£º";
	cin>>score;

	switch(score)
	{
		case 'A':   
		case 'a':cout<<"excellent"<<endl; break;
		case 'B':
		case 'b':cout<<"good"<<endl; break;
		default:cout<<"Pay attention!"<<endl;
	}
	return 0;
}
 