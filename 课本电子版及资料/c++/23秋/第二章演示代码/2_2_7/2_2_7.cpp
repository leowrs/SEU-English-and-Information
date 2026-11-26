#include <iostream>
using namespace std;

int main()
{
	int a,b,c,max,t;

	cout<<"输入a，b，c："<<endl;
	cin>>a>>b>>c;

	max=  (t=a>=b?a:b ) >=c?t:c;
	cout<<"最大值为： "<<max<<endl<<endl;
	return 0;
}
