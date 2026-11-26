#include <iostream>
using namespace std;
const int SIZE=3;

void main()
{
	int a[4]={1,2,3},i;
	int * p;

	cout<<"数组元素名\t 内存地址\t     元素值"<<endl;
	for(i=0;i<SIZE;i++)
		cout<<"a["<<i<<"] \t \t"<< a+i<<"\t \t"<<a[i]<<endl;

//   /*   
	// 情况3：*(p++)与*(++p)作用不同
	cout<<endl<<endl<<"Case 3:都是p=a时"<<endl;
	p=a;
	cout<<"*(p++)="<<*(p++)<<endl;
    
	p=a;
    cout<<"*(++p)="<<*(++p)<<endl;
//*/

    /*   //情况4：(*p)++的值
	cout<<endl<<"Case 4:p=a时，"<<endl;
	p=a;
	cout<<"*p="<<*p<<endl;
	(*p)++;
	cout<<"运行完(*p)++，*p="<<*p<<endl;
	//*/

	cout<<endl<<endl;
}