#include  <iostream>
using namespace std;
void swap(int *p1,int *p2) 
{
	int  temp;      // 把temp改为 *temp;
//	cout<<temp<<endl;
    temp=*p1;      // 把temp改为 *temp;     
    *p1=*p2;
    *p2=temp;      // 把temp改为 *temp; 
}
//0xcccccccc : uninitialised stack memory
void  main( ) 
{    
	int *pointer_1,*pointer_2,a=10,b=68; 
    pointer_1=&a;        //使pointer_1指向a
    pointer_2=&b;       //使pointer_2指向b
    if(a<b) 
		swap(pointer_1,pointer_2); //swap(&a,&b)
	cout<<"max="<<a<<"\t min="<<b<<endl<<endl; 
}
