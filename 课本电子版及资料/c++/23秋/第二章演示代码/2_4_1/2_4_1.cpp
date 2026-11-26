#include  <iostream>
using namespace std;
int main( )
{
      for (int i=0; i<4; i++)
      {
		  if (i==2)  break;                                 
		  cout<<"\t i= " <<i<<"\t " <<endl;
       }
       cout<<"提前结束循环"<<endl;

	  return 1;
}