#include <iostream>
using namespace std;

void TableHead( )  
{
    cout<<"******************\n"<<endl;
    cout<<"* Welcome to C++! *\n"<<endl;
    cout<<"******************\n"<<endl;
}
int max (int a, int b)
{	return (a>=b?a:b);  }

void main()
{
	int x=3,y=5;
	TableHead( );
	cout<<"×î´óÖµ£º"<<max(x,y)<<endl;

}