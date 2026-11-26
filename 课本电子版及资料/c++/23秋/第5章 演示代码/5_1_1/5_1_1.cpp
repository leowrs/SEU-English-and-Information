#include <iostream>
using namespace std;
const int SIZE=3;
#define COUNT 4    //注意1（语法）：此处没有分号

double st[SIZE];   // 定义全局数组；
void display(double arr[]);  //将数组arr中的元素输出到屏幕上

void main()
{ 
	double student[SIZE];  //注意2：数组大小可以是：常变量SIZE
	int day[COUNT];       //数组大小可以是：符号常量COUNT
	
	int a[5-2]={1}; // 数组大小可以是常量表达式

	 /*
	int n;        //注意3（数组大小）：数组大小不能是变量
	cin>>n;
	int e[n];	
	// */

//注意4： 在未初始化时，全局数组元素初值为0，局部数组初值不定。
// /*
	cout<<"全局数组中元素的初值："<<endl;
	display(st);

	cout<<"局部数组中元素的初值："<<endl;
	display(student);
	//*/
}

void display(double arr[])
{
//数组是一种组合类型，不能作为整体进行访问和处理（字符数组除外）
	for(int i=0; i<SIZE; i++)  
		cout<<arr[i]<<"   ";
	cout<<endl<<endl;

}